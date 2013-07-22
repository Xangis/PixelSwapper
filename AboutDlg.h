#ifndef _ABOUTDLG_H_
#define _ABOUTDLG_H_

#include "wx/wx.h"

////@begin control identifiers
#define ID_ABOUT 22000
#define SYMBOL_ABOUTDLG_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_ABOUTDLG_TITLE _("About PixelSwapper")
#define SYMBOL_ABOUTDLG_IDNAME ID_ABOUT
#define SYMBOL_ABOUTDLG_SIZE wxSize(400, 300)
#define SYMBOL_ABOUTDLG_POSITION wxDefaultPosition
////@end control identifiers

/**
     @brief     About dialog
	 Implements a wxWidgets about box
	 \author Jason Champion
*/
class AboutDlg: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( AboutDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AboutDlg( );
    AboutDlg( wxWindow* parent, wxWindowID id = SYMBOL_ABOUTDLG_IDNAME, const wxString& caption = SYMBOL_ABOUTDLG_TITLE, const wxPoint& pos = SYMBOL_ABOUTDLG_POSITION, const wxSize& size = SYMBOL_ABOUTDLG_SIZE, long style = SYMBOL_ABOUTDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ABOUTDLG_IDNAME, const wxString& caption = SYMBOL_ABOUTDLG_TITLE, const wxPoint& pos = SYMBOL_ABOUTDLG_POSITION, const wxSize& size = SYMBOL_ABOUTDLG_SIZE, long style = SYMBOL_ABOUTDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

    /// Should we show tooltips?
    static bool ShowToolTips();
};

#endif
    // _ABOUTDLG_H_
