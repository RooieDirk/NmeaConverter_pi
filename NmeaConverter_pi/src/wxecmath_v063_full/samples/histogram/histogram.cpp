
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

#include "histogram.h"

    BEGIN_EVENT_TABLE(wxHistogramFrame, wxFrame)
        EVT_MENU(wxID_OPEN, wxHistogramFrame::OnMenuLoadClick)
        EVT_MENU(wxID_EXIT, wxHistogramFrame::OnMenuQuitClick)
        EVT_CHECKBOX(ID_RED, wxHistogramFrame::OnSelectionClick)
        EVT_CHECKBOX(ID_GREEN, wxHistogramFrame::OnSelectionClick)
        EVT_CHECKBOX(ID_BLUE, wxHistogramFrame::OnSelectionClick)
        EVT_CHECKBOX(ID_GRAY, wxHistogramFrame::OnSelectionClick)
        EVT_BUTTON(ID_FIT, wxHistogramFrame::OnFitClick)
    END_EVENT_TABLE()

//------------------------------------------

wxHistogramFrame::wxHistogramFrame(wxWindow* parent)
                : wxFrame(parent, wxID_ANY, wxT("Histogram"), wxDefaultPosition, wxSize(500,500), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)
{
    //-- Layout
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
            CheckRed = new wxCheckBox(this, ID_RED, wxT("&Red"));
            CheckRed->SetValue(true);
            HSizer->Add(CheckRed, 0, wxALL, 5);

            CheckGreen = new wxCheckBox(this, ID_GREEN, wxT("&Green"));
            CheckGreen->SetValue(true);
            HSizer->Add(CheckGreen, 0, wxALL, 5);

            CheckBlue = new wxCheckBox(this, ID_BLUE, wxT("&Blue"));
            CheckBlue->SetValue(true);
            HSizer->Add(CheckBlue, 0, wxALL, 5);

            CheckGray = new wxCheckBox(this, ID_GRAY, wxT("Gr&ay"));
            CheckGray->SetValue(true);
            HSizer->Add(CheckGray, 0, wxALL, 5);

            ButtonFit = new wxButton(this, ID_FIT, wxT("Fit"), wxDefaultPosition, wxSize(40,-1));
            HSizer->Add(ButtonFit, 0, 0, 5);
        VSizer->Add(HSizer, 0, wxEXPAND, 5);

        Plot = new wxEcPlot(this, ID_PLOT);
        VSizer->Add(Plot, 1, wxEXPAND|wxALL, 5);
	    LabelMouse = new wxStaticText(this, wxID_ANY, wxT("-"));
	    VSizer->Add(LabelMouse, 0, wxALL, 5);
    this->SetSizer(VSizer);

    //-- MenuBar
    MenuBar = new wxMenuBar(0);
        MenuFile = new wxMenu();
            MenuLoad = new wxMenuItem(MenuFile, wxID_OPEN, wxString(wxT("&Load")));
            MenuFile->Append(MenuLoad);
            MenuFile->AppendSeparator();
            MenuQuit = new wxMenuItem(MenuFile, wxID_EXIT, wxString(wxT("&Quit")));
            MenuFile->Append(MenuQuit);
        MenuBar->Append(MenuFile, wxT("&File"));
    this->SetMenuBar(MenuBar);

    //-- Styles
    Plot->RemoveAllCurves();                                                //needed for safety
    Plot->SetAxis(wxEcAxis(0,255,30,*wxRED,true,false), true);              //X
    Plot->SetAxis(wxEcAxis(0,100,10,*wxRED,true,false), false);             //Y
    Plot->SetBackgroundColour(*wxWHITE);
    Plot->SetGridColour(*wxLIGHT_GREY);

    //-- Display
    this->Layout();
    this->Center(wxBOTH);
    #ifdef __WINDOWS__
        this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    #endif
    this->Show(true);

    //-- Events
    Plot->Connect(wxEVT_MOTION, wxMouseEventHandler(wxHistogramFrame::OnMouseEvent), NULL, this);
}

wxHistogramFrame::~wxHistogramFrame()
{
    Plot->Disconnect(wxEVT_MOTION, wxMouseEventHandler(wxHistogramFrame::OnMouseEvent), NULL, this);
}

//------------------------------------------

void wxHistogramFrame::DoRefresh()
{
    if (Plot->CountCurve() != 4)
        return;

    Plot->GetCurve(curveRID)->Enabled = CheckRed->GetValue();
    Plot->GetCurve(curveGID)->Enabled = CheckGreen->GetValue();
    Plot->GetCurve(curveBID)->Enabled = CheckBlue->GetValue();
    Plot->GetCurve(curveNID)->Enabled = CheckGray->GetValue();
    Plot->Refresh();
}

void wxHistogramFrame::OnMenuLoadClick(wxCommandEvent& event)
{
    //-- Declarations
    wxImage image;
    int R, G, B, i, x, y, maxY;
    wxFileDialog *fileDialog;

    //-- Opens the file
    fileDialog = new wxFileDialog(this, wxT("Open a picture"), wxEmptyString, wxEmptyString, wxT("All image types supported|*.bmp;*.png;*.jpg;*.jpeg;*.gif;*.pcx;*.pnm;*.tiff;*.tga;*.iff;*.xpm;*.ico;*.cur;*.ani"), wxFD_OPEN);
    if (fileDialog->ShowModal() == wxID_OK)
    {
        image.LoadFile(fileDialog->GetPath());

        //-- Initialization
        maxY = 0;
        for (i=0 ; i<256 ; i++)
        {
            histoR[i].x = i;
            histoG[i].x = i;
            histoB[i].x = i;
            histoN[i].x = i;

            histoR[i].y = 0;
            histoG[i].y = 0;
            histoB[i].y = 0;
            histoN[i].y = 0;
        }

        //-- Computes histogram
        for (x=0 ; x<image.GetWidth() ; x++)
            for (y=0 ; y<image.GetHeight() ; y++)
            {
                R = image.GetRed(x,y);
                G = image.GetGreen(x,y);
                B = image.GetBlue(x,y);

                histoR[R].y++;
                histoG[G].y++;
                histoB[B].y++;
                histoN[(299*R + 587*G + 114*B)/1000].y++;
            }
    }
    wxDELETE(fileDialog);

    //-- Define the curves
    //                 X              Y              Type         Colour    W  Dots   Range  Min  Max  Pts  Data
    curveR = wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxRED,   1, false, false, 0,   256, 256, &(histoR[0]));
    curveG = wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxGREEN, 1, false, false, 0,   256, 256, &(histoG[0]));
    curveB = wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxBLUE,  1, false, false, 0,   256, 256, &(histoB[0]));
    curveN = wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxBLACK, 1, false, false, 0,   256, 256, &(histoN[0]));

    Plot->RemoveAllCurves();
    curveRID = Plot->AddCurve(curveR);
    curveGID = Plot->AddCurve(curveG);
    curveBID = Plot->AddCurve(curveB);
    curveNID = Plot->AddCurve(curveN);

    DoRefresh();
    Plot->FitYAxis();
    DoRefresh();
}

void wxHistogramFrame::OnFitClick(wxCommandEvent& event)
{
    Plot->GetAxis(false)->Reset();
    Plot->FitYAxis();
    Plot->Refresh();
}

void wxHistogramFrame::OnMenuQuitClick(wxCommandEvent& event)
{
    this->Close();
}

void wxHistogramFrame::OnMouseEvent(wxMouseEvent& event)
{
    LabelMouse->SetLabel(wxString::Format(wxT("( %.0f , %.0f )"), Plot->XToValue(event.GetX()), Plot->YToValue(event.GetY())));
    event.Skip();
}
