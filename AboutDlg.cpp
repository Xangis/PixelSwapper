#include "AboutDlg.h"

/*!
 * AboutDlg type definition
 */
IMPLEMENT_DYNAMIC_CLASS( AboutDlg, wxDialog )

/*!
 * AboutDlg event table definition
 */
BEGIN_EVENT_TABLE( AboutDlg, wxDialog )
END_EVENT_TABLE()

/*!
 * AboutDlg constructors
 */
AboutDlg::AboutDlg( )
{
}

AboutDlg::AboutDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * AboutDlg creator
 */
bool AboutDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

/*!
 * Control creation for AboutDlg
 */
void AboutDlg::CreateControls()
{
    AboutDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 7);

	wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("PixelSwapper Version 1.22\n(c) 2006-2020 Lambda Centauri\nDeveloped by Jason Champion\nhttps://lambdacentauri.com"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 10);
}

/*!
 * Should we show tooltips?
 */
bool AboutDlg::ShowToolTips()
{
    return true;
}
