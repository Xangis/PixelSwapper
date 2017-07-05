#include "wx/wx.h"

#include "wx/bitmap.h"
#include "wx/dialog.h"
#include "wx/image.h"
#include "wx/aboutdlg.h"
#include "wx/filesys.h"
#include "wx/fs_zip.h"
#include "wx/dataobj.h"
#include "wx/clipbrd.h"
#include "wx/metafile.h"
#include "wx/accel.h"
#include "wx/stdpaths.h"
#include "PixelSwapperDlg.h"
#include "PixelSwapperPrint.h"
#include <algorithm>

#if !wxUSE_PRINTING_ARCHITECTURE
#error "You must set wxUSE_PRINTING_ARCHITECTURE to 1 in setup.h, and recompile the library."
#endif

IMPLEMENT_DYNAMIC_CLASS( PixelSwapperDlg, wxFrame )

BEGIN_EVENT_TABLE( PixelSwapperDlg, wxFrame )
    EVT_CLOSE( PixelSwapperDlg::OnCloseWindow )
    EVT_BUTTON( ID_BTN_MIRROR, PixelSwapperDlg::OnBtnMirrorClick )
    EVT_BUTTON( ID_BTN_RESCALE, PixelSwapperDlg::OnBtnRescaleClick )
    EVT_BUTTON( ID_BTN_RESIZE, PixelSwapperDlg::OnBtnResizeClick )
    EVT_BUTTON( ID_BTN_CROP, PixelSwapperDlg::OnBtnCropClick )
    EVT_BUTTON( ID_BTN_ROTATE, PixelSwapperDlg::OnBtnRotateClick )
	EVT_BUTTON( ID_BTN_REVERT, PixelSwapperDlg::OnBtnLoadClick )
    EVT_TEXT( ID_TXT_THRESHOLD, PixelSwapperDlg::OnTxtThresholdUpdated )
	EVT_MENU( ID_FILE_SAVE, PixelSwapperDlg::OnBtnSaveClick )
	EVT_MENU( ID_FILE_SAVE_AS, PixelSwapperDlg::OnBtnSaveAsClick )
	EVT_MENU( ID_FILE_LOAD, PixelSwapperDlg::OnBtnBrowseinputClick )
	EVT_MENU( ID_FILE_REVERT, PixelSwapperDlg::OnBtnLoadClick )
	EVT_MENU( ID_TRANSFORM_ROTATE_RIGHT, PixelSwapperDlg::OnBtnRotateClick )
	EVT_MENU( ID_TRANSFORM_ROTATE_LEFT, PixelSwapperDlg::OnBtnRotateRightClick )
	EVT_MENU( ID_TRANSFORM_MIRROR_VERTICAL, PixelSwapperDlg::OnBtnMirrorRightClick )
	EVT_MENU( ID_TRANSFORM_MIRROR_HORIZONTAL, PixelSwapperDlg::OnBtnMirrorClick )
	EVT_MENU( ID_TRANSFORM_RESCALE_SMALLER, PixelSwapperDlg::OnBtnRescaleClick )
	EVT_MENU( ID_TRANSFORM_RESCALE_LARGER, PixelSwapperDlg::OnBtnRescaleRightClick )
	EVT_MENU( ID_TRANSFORM_CROP, PixelSwapperDlg::OnBtnCropClick )
	EVT_MENU( ID_TRANSFORM_RESIZE, PixelSwapperDlg::OnBtnResizeClick )
	EVT_MENU( ID_TRANSFORM_TOGRAYSCALE, PixelSwapperDlg::OnTransformToGrayscale )
	EVT_MENU( ID_HELP_ABOUT, PixelSwapperDlg::OnBtnAboutClick )
	EVT_MENU( ID_HELP_HELP, PixelSwapperDlg::OnBtnHelpClick )
	EVT_MENU( ID_FILE_PASTE, PixelSwapperDlg::OnBtnFilePaste )
    EVT_MENU( ID_FILE_PRINT, PixelSwapperDlg::OnPrint )
    EVT_MENU( ID_FILE_PRINT_PREVIEW, PixelSwapperDlg::OnPrintPreview )
    EVT_MENU( ID_FILE_PAGE_SETUP, PixelSwapperDlg::OnPageSetup )
    EVT_MENU( ID_FILE_EXIT, PixelSwapperDlg::OnClose )
END_EVENT_TABLE()

PixelSwapperDlg::PixelSwapperDlg( )
{
}

PixelSwapperDlg::~PixelSwapperDlg()
{
}

PixelSwapperDlg::PixelSwapperDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool PixelSwapperDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    _btnMirror = NULL;
    _btnCrop = NULL;
    _btnRotate = NULL;
    _btnRescale = NULL;
    _btnResize = NULL;
    _bmpImage = NULL;
	_btnRevert = NULL;
    _mainSizer = NULL;
	_dropTarget = NULL;
	_dlgResize = NULL;
    _mainFrame = NULL;
    _mainPanel = NULL;
    _mainMenu = NULL;
    _fileMenu = NULL;
    _transformMenu = NULL;
    _helpMenu = NULL;
    _statusBar = NULL;
	//_aboutDlg = NULL;
	_helpCtrl = NULL;
    _printData = NULL;
    _pageSetupData = NULL;
	_scaleFactor = 1.0;
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxFrame::Create( parent, id, caption, pos, size, style );
	wxFileSystem::AddHandler(new wxZipFSHandler);
	wxInitAllImageHandlers();
	CreateControls();
	if( _icon.LoadFile(_T("pixelswap.ico"), wxBITMAP_TYPE_ICO ))
	{
		SetIcon(_icon);
                wxTopLevelWindow::SetIcon(_icon);
	}
	_dropTarget = new PixelSwapperDropTarget(this);
	wxWindow::SetDropTarget( _dropTarget );
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    _printData = new wxPrintData;
    _printData->SetPaperId( wxPAPER_LETTER );
    _pageSetupData = new wxPageSetupDialogData(*_printData);
    _pageSetupData->SetDefaultMinMargins(true);
    //Centre();
	return true;
}

void PixelSwapperDlg::OnClose(wxCommandEvent&)
{
	Close();
}

void PixelSwapperDlg::CreateControls()
{
    _mainFrame = this;
	// Set up menus
    _mainMenu = new wxMenuBar;
    _fileMenu = new wxMenu;
    _fileMenu->Append( ID_FILE_LOAD, _("Open File\tCtrl+O"), _("Load file from disk") );
	_fileMenu->Append( ID_FILE_SAVE, _("Save\tCtrl+S"), _("Save file to disk") );
    _fileMenu->Append( ID_FILE_SAVE_AS, _("Save As\tCtrl+A"), _("Save file to disk") );
	_fileMenu->Append( ID_FILE_PASTE, _("Paste\tCtrl+V"), _("Paste image data from the clipboard") );
    _fileMenu->Append( ID_FILE_REVERT, _("Revert\tCtrl+Z"), _("Revert to original file") );
    _fileMenu->Append( ID_FILE_PAGE_SETUP, _("Page Setup\tAlt+S"), _("") );
    _fileMenu->Append( ID_FILE_PRINT, _("Print\tCtrl+P"), _("") );
    _fileMenu->Append( ID_FILE_PRINT_PREVIEW, _("Print Preview\tAlt+W"), _("") );
    _fileMenu->Append( ID_FILE_EXIT, _("Exit\tAlt+F4"), _("") );
    _mainMenu->Append(_fileMenu, _("File"));
    _transformMenu = new wxMenu;
	_transformMenu->Append( ID_TRANSFORM_CROP, _("Crop\tAlt+C"), _("") );
	_transformMenu->Append( ID_TRANSFORM_MIRROR_HORIZONTAL, _("Mirror Horizontal\tCtrl+M"), _("") );
	_transformMenu->Append( ID_TRANSFORM_MIRROR_VERTICAL, _("Mirror Vertical\tAlt+M"), _("") );
	_transformMenu->Append( ID_TRANSFORM_RESCALE_LARGER, _("Rescale Larger\tCtrl+R"), _("") );
	_transformMenu->Append( ID_TRANSFORM_RESCALE_SMALLER, _("Rescale Smaller\tAlt+R"), _("") );
    _transformMenu->Append( ID_TRANSFORM_RESIZE, _("Resize\tAlt+I"), _("") );
    _transformMenu->Append( ID_TRANSFORM_ROTATE_RIGHT, _("Rotate Right\tAlt+T"), _("") );
    _transformMenu->Append( ID_TRANSFORM_ROTATE_LEFT, _("Rotate Left\tCtrl+T"), _("") );
    _transformMenu->Append( ID_TRANSFORM_TOGRAYSCALE, _("To Grayscale\tCtrl+G"), _("") );
    _mainMenu->Append(_transformMenu, _("Transform"));
    _helpMenu = new wxMenu;
	_helpMenu->Append( ID_HELP_HELP, _("Help\tF1") );
    _helpMenu->Append( ID_HELP_ABOUT, _("About\tCtrl+I") );
    _mainMenu->Append( _helpMenu, _("&Help") );
    _mainFrame->SetMenuBar(_mainMenu);

    wxSizer* itemSizer1 = new wxBoxSizer(wxVERTICAL);
    _mainFrame->SetSizer(itemSizer1);

    _mainPanel = new wxPanel( this, ID_MAIN_PANEL );

    wxPanel* itemDialog1 = _mainPanel;

    _mainSizer = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(_mainSizer);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    _mainSizer->Add(itemBoxSizer3, 0, wxALIGN_LEFT|wxALL, 1);

    _btnCrop = new wxButton( itemDialog1, ID_BTN_CROP, _("Crop"), wxDefaultPosition, wxSize( 68, 26 ), 0 );
    itemBoxSizer3->Add(_btnCrop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

    _btnMirror = new wxButton( itemDialog1, ID_BTN_MIRROR, _("Mirror"), wxDefaultPosition, wxSize( 68, 26 ), 0 );
    itemBoxSizer3->Add(_btnMirror, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
	_btnMirror->Connect(ID_BTN_MIRROR, wxEVT_RIGHT_DOWN, wxCommandEventHandler(PixelSwapperDlg::OnBtnMirrorRightClick), NULL, this);

    _btnRescale = new wxButton( itemDialog1, ID_BTN_RESCALE, _("Rescale"), wxDefaultPosition, wxSize( 68, 26 ), 0 );
    itemBoxSizer3->Add(_btnRescale, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
	_btnRescale->Connect(ID_BTN_RESCALE, wxEVT_RIGHT_DOWN, wxCommandEventHandler(PixelSwapperDlg::OnBtnRescaleRightClick), NULL, this);

    _btnResize = new wxButton( itemDialog1, ID_BTN_RESIZE, _("Resize"), wxDefaultPosition, wxSize( 68, 26 ), 0 );
    itemBoxSizer3->Add(_btnResize, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

    _btnRevert = new wxButton( itemDialog1, ID_BTN_REVERT, _("Revert"), wxDefaultPosition, wxSize( 68, 26 ), 0 );
    itemBoxSizer3->Add(_btnRevert, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

    _btnRotate = new wxButton( itemDialog1, ID_BTN_ROTATE, _("Rotate"), wxDefaultPosition, wxSize( 68, 26 ), 0 );
    itemBoxSizer3->Add(_btnRotate, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
	_btnRotate->Connect(ID_BTN_ROTATE, wxEVT_RIGHT_DOWN, wxCommandEventHandler(PixelSwapperDlg::OnBtnRotateRightClick), NULL, this);

    wxBitmap _bmpImageBitmap(wxNullBitmap);
    _bmpImage = new wxSelectableBitmap( itemDialog1, wxID_STATIC, _bmpImageBitmap, wxDefaultPosition, wxSize( 120, 120 ), wxNO_BORDER );
	_mainSizer->Add(_bmpImage, 1, wxGROW|wxALIGN_LEFT|wxALL, 5);

    _statusBar = new wxStatusBar( _mainPanel, ID_STATUS_BAR );
    _statusBar->SetFieldsCount(4);
    _statusBar->SetStatusText( _("No File Loaded"), 0 );
    _statusBar->SetStatusText( _("Width: 0"), 1 );
    _statusBar->SetStatusText( _("Height: 0"), 2 );
	_statusBar->SetStatusText( _("100%"), 3 );
	int widths[4] = { -1, 90, 90, 62 };
	_statusBar->SetStatusWidths( 4, widths );
    // Filename, height, width.
	_mainSizer->Add(_statusBar, 0, wxGROW|wxALL, 0 );

	_helpCtrl = new wxHtmlHelpController(wxHF_CONTENTS);
#ifdef __WXMAC__
        wxString filename = wxStandardPaths::Get().GetResourcesDir() + _("//pixelswapper.htb");
#else
#ifdef WIN32
	wxString filename = wxStandardPaths::Get().GetDataDir() + _("\\pixelswapper.htb");
#else
        wxString filename = _("./pixelswapper.htb");
#endif
#endif
	if( !_helpCtrl->AddBook(filename))
	{
		wxMessageBox( _("Unable to load help file.  Please make sure that pixelswapper.htb is in the program directory.") );
	}

	// Finally, attach the panel to the main sizer.
	itemSizer1->Add(itemDialog1, 1, wxALL|wxGROW, 0);
}

bool PixelSwapperDlg::ShowToolTips()
{
    return true;
}

wxBitmap PixelSwapperDlg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon PixelSwapperDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
}

void PixelSwapperDlg::OnTxtThresholdUpdated( wxCommandEvent& event )
{
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnBrowseinputClick( wxCommandEvent& event )
{
	wxFileDialog fdialog( NULL, _T("Choose a file"), _T("."), _T(""), _T("All Supported File Types|*.bmp;*.gif;*.ico;*.iff;*.jpg;*.jpeg;*.pcx;*.png;*.pnm;*.tga;*.tif;*.tiff;*.xpm;*.BMP;*.GIF;*.ICO;*.IFF;*.JPG;*.JPEG;*.PCX;*.PNG;*.PNM;*.TGA;*.TIF;*.TIFF;*.XPM|BMP Files (*.bmp)|*.bmp;*.BMP|GIF Files (*.gif)|*.gif;*.GIF|Icon Files (*.ico)|*.ico;*.ICO|IFF Files (*.iff)|*.iff;*.Iff|JPEG Files (*.jpg,*.jpeg)|*.jpg;*.jpeg;*.JPG;*.JPEG|PCX Files (*.pcx)|*.pcx;*.PCX|PNG Files (*.png)|*.png;*.PNG|PNM Files (*.pnm)|*.pnm;*.PNM|TGA Files (*.tga)|*.tga;*.TGA|TIF Files (*.tif,*.tiff) |*.tif;*.tiff;*.TIF;*.TIFF|X Pixmap Files (*.xpm)|*.xpm;*.XPM||"), wxFD_OPEN|wxFD_CHANGE_DIR );
	wxString fileName;
	if( fdialog.ShowModal() != wxID_OK )
	{
		return;
	}
	fileName = fdialog.GetPath();
	_statusBar->SetStatusText( fileName, 0 );
	wxCommandEvent nullEvent;
	OnBtnLoadClick( nullEvent );
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnMirrorClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Mirror( false );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnMirrorRightClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Mirror( true );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnRescaleClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		int x = 2;
		_currentImage = _currentImage.Rescale( (_currentImage.GetWidth() / x), (_currentImage.GetHeight() / x) );
        PlaceImageInWindow();
	}
	event.Skip(false);
}

void PixelSwapperDlg::OnBtnRescaleRightClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		int x = 2;
		_currentImage = _currentImage.Rescale( (_currentImage.GetWidth() * x), (_currentImage.GetHeight() * x) );
        PlaceImageInWindow();
	}
	event.Skip(false);
}

void PixelSwapperDlg::OnBtnResizeClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		if( _dlgResize == NULL )
		{
			_dlgResize = new ResizeDlg(this);
		}
		_dlgResize->SetValues( _currentImage.GetWidth(), _currentImage.GetHeight() );
		_dlgResize->ShowModal();
	}
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnAboutClick( wxCommandEvent& event )
{
	// Show about box.
    wxAboutDialogInfo info;
    info.SetName(_("PixelSwapper"));
    info.SetVersion(_("1.22"));
    info.SetCopyright(_("(c) 2006-2017 Jason Champion"));
	info.AddDeveloper(_("Jason Champion"));
	info.SetIcon(_icon);
	info.SetLicense(_("PixelSwapper is free software and may be distributed freely under the terms of the MIT license."));
	info.SetWebSite(_("https://github.com/Xangis/PixelSwapper"));
	info.SetDescription(_("PixelSwapper uses the wxWidgets libraries."));

    wxAboutBox(info);
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnHelpClick( wxCommandEvent& event )
{
	_helpCtrl->DisplayContents();
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnFilePaste( wxCommandEvent& event )
{
	wxBitmapDataObject data;
	wxTheClipboard->Open();
	bool success = wxTheClipboard->GetData(data);
	wxTheClipboard->Close();
	if( success )
	{
		wxBitmap bitmap = data.GetBitmap();
		if( bitmap.Ok() )
		{
			_currentImage = bitmap.ConvertToImage();
            PlaceImageInWindow();
		}
	}
}

// Part two - processes information returned by resize dialog.
void PixelSwapperDlg::ProcessResize(int x, int y)
{
	if( x == 0 || y == 0 )
	{
		return;
	}
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Rescale( x, y );
        PlaceImageInWindow();
	}
}

void PixelSwapperDlg::OnBtnCropClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		wxRect rect;
		_bmpImage->GetSelection( rect );
		if( rect.IsEmpty() )
		{
			wxMessageBox( _("Please select the region to crop by clicking and dragging the mouse." ));
			return;
		}
		// Compensate for scale if necessary.
		if( _scaleFactor < 1.0 )
		{
			rect.SetTop( ((double)rect.GetTop() / _scaleFactor) );
			rect.SetLeft( ((double)rect.GetLeft() / _scaleFactor) );
			rect.SetWidth( ((double)rect.GetWidth() / _scaleFactor) );
			rect.SetHeight( ((double)rect.GetHeight() / _scaleFactor) );
		}
		_currentImage = _currentImage.GetSubImage( rect );
        PlaceImageInWindow();
	}
	event.Skip(false);
}

void PixelSwapperDlg::OnBtnRotateClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Rotate90( true );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void PixelSwapperDlg::OnTransformToGrayscale( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.ConvertToGreyscale();
		PlaceImageInWindow();
	}
	event.Skip(false);
}

void PixelSwapperDlg::OnBtnRotateRightClick( wxCommandEvent& event )
{
	if( _currentImage.Ok() )
	{
		_currentImage = _currentImage.Rotate90( false );
        PlaceImageInWindow();
	}
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnSaveAsClick( wxCommandEvent& event )
{
	wxString origfile = _statusBar->GetStatusText( 0 );
	wxFileDialog fdialog( NULL, _T("Choose a file"), _T("."), origfile, _T("BMP file (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|Icon Files (*.ico)|*.ico|JPEG Files (*.jpg)|*.jpg|PCX Files (*.pcx)|*.pcx|PNG Files (*.png)|*.png|PNM Files (*.pnm)|*.pnm|TGA Files (*.tga)|*.tga|TIFF Files (*.tif)|*.tif|X Pixmap Files (*.xpm)|*.xpm||"), wxFD_SAVE|wxFD_CHANGE_DIR );
	fdialog.SetFilterIndex(5);
	wxString fileName;
	if( fdialog.ShowModal() != wxID_OK )
	{
		return;
	}
	fileName = fdialog.GetPath();
	_statusBar->SetStatusText( fileName, 0 );

	int fileType;

	switch( fdialog.GetFilterIndex() )
	{
	case 0:
		fileType = wxBITMAP_TYPE_BMP;
		break;
	case 1:
		fileType = wxBITMAP_TYPE_GIF;
		break;
	case 2:
		fileType = wxBITMAP_TYPE_ICO;
		break;
	case 3:
		fileType = wxBITMAP_TYPE_JPEG;
		break;
	case 4:
		fileType = wxBITMAP_TYPE_PCX;
		break;
	case 5:
		fileType = wxBITMAP_TYPE_PNG;
		break;
	case 6:
		fileType = wxBITMAP_TYPE_PNM;
		break;
	case 7:
		fileType = wxBITMAP_TYPE_TGA;
		break;
	case 8:
		fileType = wxBITMAP_TYPE_TIF;
		break;
	case 9:
		fileType = wxBITMAP_TYPE_XPM;
		break;
	default:
		fileType = wxBITMAP_TYPE_BMP;
		break;
	}

	_currentImage.SaveFile( fileName, fileType );
    event.Skip(false);
}

void PixelSwapperDlg::OnBtnSaveClick( wxCommandEvent& event )
{
	_currentImage.SaveFile( _statusBar->GetStatusText( 0 ) );
	event.Skip(false);
}

void PixelSwapperDlg::LoadFile(wxString filename )
{
	_statusBar->SetStatusText( filename, 0 );
	wxCommandEvent nullEvent;
	OnBtnLoadClick( nullEvent );
}

void PixelSwapperDlg::OnBtnLoadClick( wxCommandEvent& event )
{
    wxString filename = _statusBar->GetStatusText( 0 );
    _currentImage.LoadFile( filename, wxBITMAP_TYPE_ANY );
    if( _currentImage.Ok() )
    {
        PlaceImageInWindow();
		_statusBar->SetStatusText( filename, 0 );
		wxString name = filename.AfterLast('\\');
		//filename.Last
		SetTitle(wxString::Format(_("PixelSwapper - %s"), name.c_str()));
    }
    event.Skip(false);
}

void PixelSwapperDlg::OnCloseWindow( wxCloseEvent& event )
{
	Destroy();
    event.Skip(false);
}

bool PixelSwapperDlg::OnDropFiles(const wxString& filename)
{
	_currentImage.LoadFile( filename, wxBITMAP_TYPE_ANY );
    if( _currentImage.Ok() )
    {
		_statusBar->SetStatusText( filename, 0 );
        PlaceImageInWindow();
    }
	return true;
}

bool PixelSwapperDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
	if( filenames.GetCount() < 1 || !_dialog )
	{
		return false;
	}

	return _dialog->OnDropFiles( filenames[0] );
}

void PixelSwapperDlg::SetStatusSize( int width, int height )
{
	_statusBar->SetStatusText( wxString::Format(_("Width: %d"), width ), 1 );
	_statusBar->SetStatusText( wxString::Format(_("Height: %d"), height ), 2 );
	_statusBar->SetStatusText( wxString::Format(_("%d%%"), (int)(_scaleFactor * 100 )), 3);
}

void PixelSwapperDlg::OnPrint(wxCommandEvent& WXUNUSED(event))
{
    wxPrintDialogData printDialogData(* _printData);

    wxPrinter printer(& printDialogData);
    PixelSwapperPrint printout(_("PixelSwapper Printout"));
    if( _currentImage.Ok() )
    {
        printout.SetBitmap(wxBitmap(_currentImage));
    }
    if (!printer.Print(this, &printout, true /*prompt*/))
    {
        if (wxPrinter::GetLastError() == wxPRINTER_ERROR)
        {
            wxMessageBox(_("There was a problem printing.\nPerhaps your current printer is not set correctly?"), _("Printing"), wxOK);
        }
    }
    else
    {
        (*_printData) = printer.GetPrintDialogData().GetPrintData();
    }
}

void PixelSwapperDlg::OnPrintPreview(wxCommandEvent& WXUNUSED(event))
{
    // Pass two printout objects: for preview, and possible printing.
    wxPrintDialogData printDialogData(* _printData);
    PixelSwapperPrint* printoutForPreview = new PixelSwapperPrint;
    PixelSwapperPrint* printoutForPrint = new PixelSwapperPrint;
    if( _currentImage.Ok() )
    {
        printoutForPreview->SetBitmap(wxBitmap(_currentImage));
        printoutForPrint->SetBitmap(wxBitmap(_currentImage));
    }
    wxPrintPreview *preview = new wxPrintPreview(printoutForPreview, printoutForPrint, & printDialogData);
    if (!preview->Ok())
    {
        delete preview;
        wxMessageBox(_("There was a problem previewing.\nPerhaps your current printer is not set correctly?"), _("Previewing"), wxOK);
        return;
    }

    wxPreviewFrame *frame = new wxPreviewFrame(preview, this, _("Print Preview"), wxPoint(100, 100), wxSize(600, 650));
    frame->Centre(wxBOTH);
    frame->Initialize();
    frame->Show();
}

void PixelSwapperDlg::OnPageSetup(wxCommandEvent& WXUNUSED(event))
{
    wxPageSetupDialog pageSetupDialog(this, _pageSetupData);

    pageSetupDialog.ShowModal();

    (*_printData) = pageSetupDialog.GetPageSetupData().GetPrintData();
    (*_pageSetupData) = pageSetupDialog.GetPageSetupData();
}

void PixelSwapperDlg::PlaceImageInWindow()
{
    if( _currentImage.Ok() )
    {
		// Allow an arbitrary 16 pixel border for width.
		int width = wxSystemSettings::GetMetric ( wxSYS_SCREEN_X ) - 18;
		// Allow an arbitrary 96 pixel border for height.
		int height = wxSystemSettings::GetMetric ( wxSYS_SCREEN_Y ) - 154;
		if( _currentImage.GetWidth() > width || _currentImage.GetHeight() > height )
		{
			double xratio = (double)width / (double)_currentImage.GetWidth();
			double yratio = (double)height / (double)_currentImage.GetHeight();
			double ratio = std::min( xratio, yratio );
			_bmpImage->SetBitmap( _currentImage.Scale( _currentImage.GetWidth() * ratio, _currentImage.GetHeight() * ratio ) );
			_scaleFactor = ratio;
		}
		else
		{
			_scaleFactor = 1.0;
			_bmpImage->SetBitmap( _currentImage );
		}
		_bmpImage->SetSize( -1, -1, (_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor ));
		_bmpImage->SetSizeHints((_currentImage.GetWidth() * _scaleFactor), (_currentImage.GetHeight() * _scaleFactor) );
		SetStatusSize( _currentImage.GetWidth(), _currentImage.GetHeight() );
		_icon.CopyFromBitmap(_currentImage);
		SetIcon(_icon);
		Fit();
		Refresh();
    }
}
