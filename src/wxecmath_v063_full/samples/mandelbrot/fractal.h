
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

#ifndef fractal_h
#define fractal_h

//------------------------------------------

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/notebook.h"
#include "wx/stdpaths.h"

#include "../../lib/ec_defs.h"
#include "../../lib/ec_plot.h"
#include "../../lib/ec_complex.h"

#define FRACTAL_WIDTH   (int) 500
#define FRACTAL_HEIGHT  (int) 400
#define FRACTAL_DEPTH   (int) 2048

//------------------------------------------

class wxFractalFrame : public wxFrame 
{
    DECLARE_EVENT_TABLE()
    private:
        enum
        {
            ID_BASE = 1000,
            ID_MENU_RESET,
            ID_MENU_SAVE,
            ID_DRAW,
            ID_VIEW,
            ID_BROWSE_LEFT,
            ID_BROWSE_RIGHT,
            ID_BROWSE_TOP,
            ID_BROWSE_BOTTOM,
            ID_BROWSE_PLUS,
            ID_BROWSE_MINUS,
            ID_ANIMATION
        };

        wxMenuBar *MenuBar;
        wxMenu *MenuFile;
        wxMenuItem *MenuReset, *MenuSave, *MenuQuit;
        wxStaticText *labelXmin;
        wxTextCtrl *editXmin;
        wxStaticText *labelXmax;
        wxTextCtrl *editXmax;
        wxStaticText *labelYmix;
        wxTextCtrl *editYmin;
        wxStaticText *labelYmax;
        wxTextCtrl *editYmax;
        wxStaticText *labelDepth;
        wxTextCtrl *editDepth;
        wxButton *buttonDraw;
        wxStaticText *labelRGB;
        wxSlider *sliderR;
        wxSlider *sliderG;
        wxSlider *sliderB;
        wxNotebook *Notebook;
        wxNotebookPage *PagePlot, *PageView;
        wxEcPlot *m_plot;
        wxEcCurve m_curve;
        wxStaticBitmap *m_view;
        wxButton *buttonLeft;
        wxButton *buttonRight;
        wxButton *buttonTop;
        wxButton *buttonDown;
        wxButton *buttonPlus;
        wxButton *buttonMinus;
        wxButton *buttonAnimation;

        wxEcCurve m_histogram;
        wxImage m_image;
        int m_fractal_mapping[FRACTAL_WIDTH][FRACTAL_HEIGHT];
        wxRealPoint m_usage[FRACTAL_DEPTH+1];
        int level;

        wxPoint m_pointA;

        void DoComputeMandelbrot();
        void DoDraw(bool fromMemory = false);
        void DoGui();
        void DoMinus();
    
    public:
        wxFractalFrame(wxWindow *parent);
        ~wxFractalFrame();

        double xmin, xmax, ymin, ymax;
        int fdepth;

        void OnButtonClick(wxCommandEvent& event);
        void OnMenuClick(wxCommandEvent& event);
        void OnMouseDown(wxMouseEvent& event);
        void OnMouseUp(wxMouseEvent& event);
};

#endif
