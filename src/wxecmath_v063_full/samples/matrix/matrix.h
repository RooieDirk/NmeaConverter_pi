
/*  wxEcMath - version 0.6.3
 *  Copyright (C) 2008-2010, http://sourceforge.net/projects/wxecmath/
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef matrix_h
#define matrix_h

//------------------------------------------

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "../../lib/ec_defs.h"
#include "../../lib/ec_plot.h"
#include "../../lib/ec_matrix.h"
#include "vision.h"
#include "custommatrix.h"

//------------------------------------------

#define SCROLL_RATE 25

class wxMatrixFrame : public wxFrame 
{
    DECLARE_EVENT_TABLE()
    private:
        enum
        {
            ID_MENU_KICKRED = 1000,
            ID_MENU_KICKGREEN,
            ID_MENU_KICKBLUE,
            ID_MENU_GREYSCALE,
            ID_MENU_USERED,
            ID_MENU_USEGREEN,
            ID_MENU_USEBLUE,
            ID_MENU_USEBLACK,
            ID_MENU_INVERSE,
            ID_MENU_ROTATECOLOURS,
            ID_MENU_LUMINOSITY,
            ID_MENU_CONTRAST,
            ID_MENU_BINARIZATION,
            ID_MENU_MEDIAN,
            ID_MENU_RGB2YCBCR,
            ID_MENU_YCBCR2RGB,
            ID_MENU_RGB2YIQ,
            ID_MENU_YIQ2RGB,
            ID_MENU_DILATE,
            ID_MENU_ERODE,
            ID_MENU_OPENING,
            ID_MENU_CLOSING,
            ID_MENU_LOWPASS,
            ID_MENU_GAUSSIANSMOOTHING,
            ID_MENU_LAPLACIAN,
            ID_MENU_PREWITT,
            ID_MENU_SOBEL,
            ID_MENU_EDGES,
            ID_MENU_DRAWEDGES,
            ID_MENU_RISE,
            ID_MENU_CUSTOMMATRIX,
            ID_FITBUTTON,
            ID_SCROLLBAR
        };

        wxScrolledWindow *m_viewscroller;
        wxBoxSizer *SSizer;
        wxStaticBitmap *m_view;
        wxButton *m_fitbutton;
        wxScrollBar *m_fitbar;
        wxEcPlot *m_plot;

        wxMenuBar *m_menubar;
        wxMenu *m_menufile, *m_menuimage, *m_menuhelp;
        wxMenu *m_menusubcolours, *m_menusubmorphology, *m_menusubcolourspace, *m_menusubmatrix;
        wxMenuItem *m_menuitemundo, *m_menuitemload, *m_menuitemsave, *m_menuitemquit,
                   *m_menuitemkickred, *m_menuitemkickgreen, *m_menuitemkickblue, *m_menuitemgreyscale,
                   *m_menuitemusered, *m_menuitemusegreen, *m_menuitemuseblue, *m_menuitemuseblack,
                   *m_menuiteminverse, *m_menuitemrotatecolours, *m_menuitemluminosity, *m_menuitemcontrast,
                   *m_menuitembinarization, *m_menuitemmedian, *m_menuitemrgb2cmy, *m_menuitemcmy2rgb,
                   *m_menuitemrgb2ycbcr, *m_menuitemycbcr2rgb, *m_menuitemrgb2yiq, *m_menuitemyiq2rgb, *m_menuitemdilate,
                   *m_menuitemerode, *m_menuitemopening, *m_menuitemclosing, *m_menuitemlowpass, *m_menuitemhighpass,
                   *m_menuitemgaussianblur, *m_menuitemprewitt, *m_menuitemsobel, *m_menuitemedgeenhancement,
                   *m_menuitemdrawedges, *m_menuitemrise, *m_menuitemcustommatrix, *m_menuitemabout;

        wxVisionManager m_vision;
        void DoGUI();

    public:
        wxMatrixFrame(wxWindow *parent);
        ~wxMatrixFrame();

        void OnMenuClick(wxCommandEvent& event);
        void OnButtonClick(wxCommandEvent& event);
        void OnScrollClick(wxScrollEvent& event);
        void OnMousePlotEvent(wxMouseEvent& event);
        void OnMouseViewEvent(wxMouseEvent& event);
};

#endif
