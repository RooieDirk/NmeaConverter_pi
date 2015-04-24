
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

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

//------------------------------------------

#include "../../lib/ec_defs.h"
#include "../../lib/ec_engine.h"

//------------------------------------------

class wxSpeedApp : public wxApp
{
	virtual bool OnInit();
};

IMPLEMENT_APP(wxSpeedApp)

bool wxSpeedApp::OnInit()
{
    wxApp::OnInit();

    //-- Initialization
    long i, start, end, numcomp=350000;
    double speed;
    wxEcEngine calculator;
    calculator.SetFormula(wxT("(1+sqrt(5))/2-2*cos(2*pi/5)"));    //= 1

    //-- Computes
    start = wxGetLocalTime();
    for (i=0 ; i<numcomp ; i++)
        calculator.Compute();
    end = wxGetLocalTime();

    //-- Displays the result
    if (end != start)
    {
        speed = numcomp / (end-start);
        wxMessageDialog(NULL, wxString::Format(wxT("%.0f per second"), speed), wxT("Speed"), wxOK).ShowModal();
    }
    return false;
}
