#include "wx/wx.h"

#include "PixelSwapperApp.h"

IMPLEMENT_APP( PixelSwapperApp )

IMPLEMENT_CLASS( PixelSwapperApp, wxApp )

BEGIN_EVENT_TABLE( PixelSwapperApp, wxApp )
END_EVENT_TABLE()

PixelSwapperApp::PixelSwapperApp()
{
}

bool PixelSwapperApp::OnInit()
{
#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
    PixelSwapperDlg* mainWindow = new PixelSwapperDlg(NULL, ID_PIXELSWAPPER_DIALOG, _("PixelSwapper"));
    mainWindow->Show(true);
	if( argc > 1 )
	{
		mainWindow->LoadFile( wxString(argv[1]) );
	}
    return true;
}

int PixelSwapperApp::OnExit()
{
    return wxApp::OnExit();
}

