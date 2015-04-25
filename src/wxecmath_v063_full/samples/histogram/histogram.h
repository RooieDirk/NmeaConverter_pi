
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

#ifndef histogram_h
#define histogram_h

//------------------------------------------

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "../../lib/ec_defs.h"
#include "../../lib/ec_engine.h"
#include "../../lib/ec_plot.h"

//------------------------------------------

class wxHistogramFrame : public wxFrame 
{
    DECLARE_EVENT_TABLE()
    private:
        enum
        {
            ID_RED = 1000,
            ID_GREEN,
            ID_BLUE,
            ID_GRAY,
            ID_FIT,
            ID_PLOT
        };

        wxMenuBar *MenuBar;
        wxMenu *MenuFile;
        wxMenuItem *MenuLoad, *MenuQuit;
        wxCheckBox *CheckRed, *CheckGreen, *CheckBlue, *CheckGray;
        wxButton *ButtonFit;
        wxEcPlot *Plot;
        wxStaticText *LabelMouse;

        wxRealPoint histoR[256], histoG[256], histoB[256], histoN[256];
        wxEcCurve curveR, curveG, curveB, curveN;
        int curveRID, curveGID, curveBID, curveNID;

        void DoRefresh();

    public:
        wxHistogramFrame(wxWindow* parent);
        ~wxHistogramFrame();

        void OnMenuLoadClick(wxCommandEvent& event);
        void OnMenuQuitClick(wxCommandEvent& event);
        void OnSelectionClick(wxCommandEvent& event) { DoRefresh(); }
        void OnFitClick(wxCommandEvent& event);
        void OnMouseEvent(wxMouseEvent& event);
};

#endif
