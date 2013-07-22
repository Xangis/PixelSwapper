#ifndef PIXELSWAPPERAPP_H_
#define PIXELSWAPPERAPP_H_

#include "wx/image.h"
#include "PixelSwapperDlg.h"

class PixelSwapperApp: public wxApp
{
    DECLARE_CLASS( PixelSwapperApp )
    DECLARE_EVENT_TABLE()

public:
    PixelSwapperApp();
    virtual bool OnInit();
    virtual int OnExit();
};

DECLARE_APP( PixelSwapperApp )

#endif
