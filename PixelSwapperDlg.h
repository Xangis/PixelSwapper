#ifndef _PIXELSWAPPERDLG_H_
#define _PIXELSWAPPERDLG_H_

#include "wx/dnd.h"
#include "wx/html/helpctrl.h"
#include "wxSelectableBitmap.h"
#include "ResizeDlg.h"

#define ID_PIXELSWAPPER_DIALOG 10000
#define SYMBOL_PIXELSWAPPERDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxMAXIMIZE_BOX
#define SYMBOL_PIXELSWAPPERDLG_TITLE _("PixelSwapper")
#define SYMBOL_PIXELSWAPPERDLG_IDNAME ID_PIXELSWAPPER_DIALOG
#define SYMBOL_PIXELSWAPPERDLG_SIZE wxSize(400, 300)
#define SYMBOL_PIXELSWAPPERDLG_POSITION wxPoint( 1, 1 )
#define ID_TXT_THRESHOLD 10001
#define ID_TXT_OUTPUTFILE 10002
#define ID_BTN_MIRROR 10003
#define ID_BTN_CROP 10004
#define ID_TXT_INPUTFILE 10005
#define ID_BTN_BROWSEINPUT 10006
#define ID_BTN_LOAD 10008
#define ID_BTN_ROTATE 10009
#define ID_BTN_RESIZE 10010
#define ID_BTN_RESCALE 10011
#define ID_BTN_SAVE 10012
#define ID_BTN_REVERT 10013
#define ID_MAIN_PANEL 10014
#define ID_FILE_SAVE 10015
#define ID_FILE_LOAD 10016
#define ID_FILE_REVERT 10017
#define ID_TRANSFORM_ROTATE_RIGHT 10018
#define ID_TRANSFORM_ROTATE_LEFT 10019
#define ID_TRANSFORM_MIRROR_VERTICAL 10020
#define ID_TRANSFORM_MIRROR_HORIZONTAL 10021
#define ID_TRANSFORM_RESCALE_LARGER 10022
#define ID_TRANSFORM_RESCALE_SMALLER 10023
#define ID_TRANSFORM_RESIZE 10024
#define ID_TRANSFORM_CROP 10025
#define ID_HELP_ABOUT 10026
#define ID_HELP_HELP 10027
#define ID_STATUS_BAR 10028
#define ID_FILE_PASTE 10029
#define ID_FILE_PAGE_SETUP 10030
#define ID_FILE_PRINT 10031
#define ID_FILE_PRINT_PREVIEW 10032
#define ID_FILE_SAVE_AS 10033
#define ID_TRANSFORM_TOGRAYSCALE 10035
#define ID_FILE_EXIT 10036

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

class PixelSwapperDlg;

class PixelSwapperDropTarget: public wxFileDropTarget
{
public:
	PixelSwapperDropTarget( PixelSwapperDlg* dialog ) { _dialog = dialog; }
	virtual ~PixelSwapperDropTarget() {}
	virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);
private:
	PixelSwapperDlg* _dialog;
};

class PixelSwapperDlg: public wxFrame
{    
    DECLARE_DYNAMIC_CLASS( PixelSwapperDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    PixelSwapperDlg( );
    virtual ~PixelSwapperDlg();
    PixelSwapperDlg( wxWindow* parent, wxWindowID id = SYMBOL_PIXELSWAPPERDLG_IDNAME, const wxString& caption = SYMBOL_PIXELSWAPPERDLG_TITLE, const wxPoint& pos = SYMBOL_PIXELSWAPPERDLG_POSITION, const wxSize& size = SYMBOL_PIXELSWAPPERDLG_SIZE, long style = SYMBOL_PIXELSWAPPERDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PIXELSWAPPERDLG_IDNAME, const wxString& caption = SYMBOL_PIXELSWAPPERDLG_TITLE, const wxPoint& pos = SYMBOL_PIXELSWAPPERDLG_POSITION, const wxSize& size = SYMBOL_PIXELSWAPPERDLG_SIZE, long style = SYMBOL_PIXELSWAPPERDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

    void OnClose(wxCommandEvent& event );
    void OnCloseWindow( wxCloseEvent& event );
	bool OnDropFiles( const wxString& filename );

    void OnBtnMirrorClick( wxCommandEvent& event );
    //void OnBtnMirrorRightClick( wxCommandEvent& event ) { OnBtnMirrorRightClick( (wxEvent&)event ); }
    void OnBtnMirrorRightClick( wxCommandEvent &event );
    void OnBtnCropClick( wxCommandEvent& event );
    void OnBtnRotateClick( wxCommandEvent& event );
    //void OnBtnRotateRightClick( wxCommandEvent& event ) { OnBtnRotateRightClick( (wxEvent&)event ); }
    void OnBtnRotateRightClick( wxCommandEvent& event );
    void OnBtnRescaleClick( wxCommandEvent& event );
    //void OnBtnRescaleRightClick( wxCommandEvent& event ) { OnBtnRescaleRightClick( (wxEvent&)event ); }
    void OnBtnRescaleRightClick( wxCommandEvent& event );
    void OnBtnResizeClick( wxCommandEvent& event );
    void OnBtnBrowseinputClick( wxCommandEvent& event );
    void OnBtnLoadClick( wxCommandEvent& event );
    void OnBtnSaveClick( wxCommandEvent& event );
	void OnBtnSaveAsClick( wxCommandEvent& event );
	void OnBtnAboutClick( wxCommandEvent& event );
	void OnBtnHelpClick( wxCommandEvent& event );
	void OnBtnFilePaste( wxCommandEvent& event );
	void LoadFile(wxString filename);
    void OnTxtThresholdUpdated( wxCommandEvent& event );
	void ProcessResize(int x, int y);
    void OnPageSetup(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnPrintPreview(wxCommandEvent& event);
	void OnTransformToGrayscale(wxCommandEvent& event);
	void SetStatusSize( int width, int height );

	/// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );

    /// Should we show tooltips?
    static bool ShowToolTips();

private:
    void PlaceImageInWindow(void);
    wxButton* _btnMirror;
    wxButton* _btnRotate;
    wxButton* _btnCrop;
    wxButton* _btnResize;
    wxButton* _btnRescale;
	wxButton* _btnRevert;
    wxImage _currentImage;
    wxSelectableBitmap* _bmpImage;
    wxSizer* _mainSizer;
    wxButton* _btnLoad;
	PixelSwapperDropTarget* _dropTarget;
	ResizeDlg* _dlgResize;
    wxFrame* _mainFrame;
    wxPanel* _mainPanel;
    wxMenuBar* _mainMenu;
    wxMenu* _fileMenu;
    wxMenu* _transformMenu;
    wxMenu* _helpMenu;
    wxStatusBar* _statusBar;
    wxPrintData* _printData;
    wxPageSetupData* _pageSetupData;
	wxHtmlHelpController* _helpCtrl;
	double _scaleFactor;
	wxIcon _icon;
	wxIcon _originalIcon;
};


#endif
