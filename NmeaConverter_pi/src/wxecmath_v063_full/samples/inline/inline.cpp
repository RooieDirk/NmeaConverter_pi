
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

#include "../../lib/ec_defs.h"
#include "../../lib/ec_engine.h"

//------------------------------------------

class wxInlineFrame : public wxFrame 
{
    private:
        DECLARE_EVENT_TABLE()
        enum
        {
            ID_FRAME = 1000,
            ID_COMPUTE
        };
        wxTextCtrl *editFormula;
        wxButton *buttonCompute;
        wxStaticText *labelWarning;
    public:
        wxInlineFrame();
        ~wxInlineFrame();

        void OnComputeClick(wxCommandEvent& event);
};

    BEGIN_EVENT_TABLE(wxInlineFrame, wxFrame)
        EVT_BUTTON(ID_COMPUTE, wxInlineFrame::OnComputeClick)
    END_EVENT_TABLE()

wxInlineFrame::wxInlineFrame() : wxFrame(NULL, wxID_ANY, wxT("Simpliest demo"), wxDefaultPosition, wxSize(350,100), wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
            editFormula = new wxTextCtrl(this, wxID_ANY);
            editFormula->SetMinSize(wxSize(250, -1));
            HSizer->Add(editFormula, 1, wxALL, 5);
            buttonCompute = new wxButton(this, ID_COMPUTE, wxT("Compute"));
            HSizer->Add(buttonCompute, 0, wxALL, 5);
        VSizer->Add(HSizer, 1, wxEXPAND, 5);

    labelWarning = new wxStaticText(this, wxID_ANY, wxT("-"));
    VSizer->Add(labelWarning, 0, wxALL, 5);

    this->SetSizer(VSizer);
    this->Layout();
    this->Fit();
    this->Center();

    #ifdef __WINDOWS__
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    #endif
}

wxInlineFrame::~wxInlineFrame()
{
}

void wxInlineFrame::OnComputeClick(wxCommandEvent& event)
{
    wxEcEngine calculator;
    double result;

    calculator.SetFormula(editFormula->GetValue());
    result = calculator.Compute();
    if (calculator.GetLastError() == wxECE_NOERROR)
        editFormula->SetValue(wxString::Format(wxT("%f"), result));
    labelWarning->SetLabel(calculator.TranslateError(calculator.GetLastError()));
    editFormula->SetFocus();
}

//------------------------------------------

class wxInlineDemoApp: public wxApp
{
    private:
        wxInlineFrame *mainFrame;
    public:
        virtual bool OnInit();
};

    DECLARE_APP(wxInlineDemoApp)
    IMPLEMENT_APP(wxInlineDemoApp)

bool wxInlineDemoApp::OnInit()
{
    wxApp::OnInit();
    mainFrame = new wxInlineFrame();
    SetTopWindow(mainFrame);
    mainFrame->Show(true);
    return true;
}
