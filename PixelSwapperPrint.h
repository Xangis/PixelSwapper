#ifndef _PIXELSWAPPER_PRINT_H_
#define _PIXELSWAPPER_PRINT_H_

#include "wx/wx.h"
#include "wx/print.h"
#include "wx/printdlg.h"

class PixelSwapperPrint: public wxPrintout
{
 public:
  PixelSwapperPrint(const wxChar *title = _("PixelSwapper Printout")):wxPrintout(title) {}
  bool OnPrintPage(int page);
  bool HasPage(int page);
  bool OnBeginDocument(int startPage, int endPage);
  void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);
  void DrawPage(wxDC *dc);
  void SetBitmap( wxBitmap bitmap ) { _bitmap = bitmap; }
private:
  wxBitmap _bitmap;
};

#endif
