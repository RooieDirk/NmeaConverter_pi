
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

#include "plotdemo.h"

    BEGIN_EVENT_TABLE(wxPlotFrame, wxFrame)
        EVT_BUTTON(wxID_ANY, wxPlotFrame::OnButtonClick)
        EVT_CHECKLISTBOX(ID_FUNCLIST, wxPlotFrame::OnFuncListCheck)
        EVT_CHECKBOX(wxID_ANY, wxPlotFrame::OnBoxCheck)
    END_EVENT_TABLE()

//------------------------------------------

wxPlotFrame::wxPlotFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, wxT("wxEcPlot demo"), wxDefaultPosition, wxSize(700,500), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer *TSizer = new wxBoxSizer(wxHORIZONTAL);
            editExpression = new wxTextCtrl(this, ID_EDIT, wxEmptyString);
            TSizer->Add(editExpression, 1, wxALL, 5);
            checkPolar = new wxCheckBox(this, wxID_ANY, wxT("Polar"));
            TSizer->Add(checkPolar, 0, wxALIGN_CENTER_VERTICAL, 5);
            buttonAdd = new wxButton(this, ID_ADD, wxT("Add"));
            TSizer->Add(buttonAdd, 0, wxALL, 5);
            buttonUseDemo = new wxButton(this, ID_USEDEMO, wxT("Use predefined"));
            TSizer->Add(buttonUseDemo, 0, wxALL, 5);
        VSizer->Add(TSizer, 0, wxEXPAND, 5);

        wxBoxSizer *MSizer = new wxBoxSizer(wxHORIZONTAL);

            wxBoxSizer *ASizer = new wxBoxSizer(wxVERTICAL);
                editAllDefFunc = new wxStaticText(this, wxID_ANY, wxT("Defined curves :"));
                ASizer->Add(editAllDefFunc, 0, wxLEFT, 5);
                listFunction = new wxCheckListBox(this, ID_FUNCLIST, wxDefaultPosition, wxSize(250,-1)); 
                ASizer->Add(listFunction, 1, wxALL|wxEXPAND, 5);

                wxBoxSizer *CSizer = new wxBoxSizer(wxHORIZONTAL);
                    buttonDelete = new wxButton(this, ID_DELETE, wxT("Delete"));
                    CSizer->Add(buttonDelete, 0, wxALL, 5);
                    buttonTangent = new wxButton(this, ID_TANGENT, wxT("Tangent"));
                    CSizer->Add(buttonTangent, 0, wxALL, 5);
                    buttonDX = new wxButton(this, ID_DX, wxT("Derivative"));
                CSizer->Add(buttonDX, 0, wxALL, 5);
                ASizer->Add(CSizer, 0, wxALIGN_CENTER, 5);

                wxFlexGridSizer* PSizer;
                    PSizer = new wxFlexGridSizer(3, 3, 0, 0);
                    PSizer->SetFlexibleDirection(wxBOTH);
                    PSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
                    labelX = new wxStaticText(this, wxID_ANY, wxT("X"));
                    labelX->Wrap(-1);
                    PSizer->Add(labelX, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT, 5);
                    editXMin = new wxTextCtrl(this, wxID_ANY, wxT("-10"));
                    PSizer->Add(editXMin, 0, wxRIGHT, 5);
                    editXMax = new wxTextCtrl(this, wxID_ANY, wxT("10"));
                    PSizer->Add(editXMax, 0, 0, 5);
                    labelY = new wxStaticText(this, wxID_ANY, wxT("Y"));
                    PSizer->Add(labelY, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT, 5);
                    editYMin = new wxTextCtrl(this, wxID_ANY, wxT("-10"));
                    editYMin->SetMaxLength(10); 
                    PSizer->Add(editYMin, 0, wxRIGHT, 5);
                    editYMax = new wxTextCtrl(this, wxID_ANY, wxT("10"));
                    PSizer->Add(editYMax, 0, 0, 5);
                    labelFormat = new wxStaticText(this, wxID_ANY, wxT("Format"));
                    PSizer->Add(labelFormat, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT, 5);
                    editFormat = new wxTextCtrl(this, wxID_ANY, wxT("%.1f"));
                    PSizer->Add(editFormat, 0, wxRIGHT, 5);
                    buttonAxisFont = new wxButton(this, ID_AXISFONT, wxT("Font"));
                    PSizer->Add(buttonAxisFont, 0, 0, 5);
                ASizer->Add(PSizer, 0, wxEXPAND, 5);

                wxGridSizer *GSizer = new wxGridSizer(2, 3, 0, 0);
                    buttonDefaultGrid = new wxButton(this, ID_DEFAULTGRID, wxT("Default grid"));
                    GSizer->Add(buttonDefaultGrid, 0, wxALL, 5);
                    buttonApplyGrid = new wxButton(this, ID_APPLY, wxT("Apply"));
                    GSizer->Add(buttonApplyGrid, 0, wxALL, 5);
                    buttonFitAxis = new wxButton(this, ID_FITAXIS, wxT("Fit axis"));
                    GSizer->Add(buttonFitAxis, 0, wxALL, 5);
                    buttonReset = new wxButton(this, ID_RESET, wxT("Reset"));
                    GSizer->Add(buttonReset, 0, wxALL, 5);
                    buttonOrtho = new wxButton(this, ID_ORTHO, wxT("Orthonorm."));
                    GSizer->Add(buttonOrtho, 0, wxALL, 5);
                    buttonUnzoom = new wxButton(this, ID_UNZOOM, wxT("Zoom -"));
                    GSizer->Add(buttonUnzoom, 0, wxALL, 5);
                ASizer->Add(GSizer, 0, wxEXPAND, 5);

                wxBoxSizer *KSizer = new wxBoxSizer(wxHORIZONTAL);
                    labelShow = new wxStaticText(this, wxID_ANY, wxT("Show"));
                    KSizer->Add(labelShow, 0, wxALL, 5);
                    checkShowGrid = new wxCheckBox(this, ID_SHOWGRID, wxT("Grid"));
                    KSizer->Add(checkShowGrid, 0, wxALL, 5);
                    checkShowAxis = new wxCheckBox(this, ID_SHOWAXIS, wxT("Axis"));
                    KSizer->Add(checkShowAxis, 0, wxALL, 5);
                    checkReticule = new wxCheckBox(this, ID_SHOWRETICULE, wxT("Reticule"));
                    KSizer->Add(checkReticule, 0, wxALL, 5);
                    checkPolarGrid = new wxCheckBox(this, ID_POLARGRID, wxT("Polar grid"));
                    KSizer->Add(checkPolarGrid, 0, wxALL, 5);
                ASizer->Add(KSizer, 0, wxALIGN_CENTER, 5);

            MSizer->Add(ASizer, 0, wxEXPAND, 5);

            Plot = new wxEcPlot(this);
            MSizer->Add(Plot, 1, wxEXPAND|wxALL, 5);
        VSizer->Add(MSizer, 1, wxEXPAND, 5);

        labelXY = new wxStaticText(this, wxID_ANY, wxT("( - , - )"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT|wxST_NO_AUTORESIZE);
	    VSizer->Add(labelXY, 0, wxALL|wxEXPAND, 5);
    this->SetSizer(VSizer);

    //-- Events
    Plot->Connect(wxEVT_MOTION, wxMouseEventHandler(wxPlotFrame::OnMouseEvent), NULL, this);

    //-- Display
    checkShowAxis->SetValue(true);
    checkShowGrid->SetValue(true);
    this->Layout();
    this->Center();
    #ifdef __WINDOWS__
        this->SetBackgroundColour(wxColour(204,204,204));
    #endif
    this->Show(true);
}

wxPlotFrame::~wxPlotFrame()
{
    Plot->Disconnect(wxEVT_MOTION, wxMouseEventHandler(wxPlotFrame::OnMouseEvent), NULL, this);
}

//------------------------------------------

void wxPlotFrame::DoRefreshCurveList()
{
    //Enabled curves are marked with the "Defined" attribute.
    //The attribute "Enabled" allows you to store a curve and deny its display.

    int i;
    wxEcCurve curCurve;
    listFunction->Clear();
    for (i=0 ; i<wxECD_CURVEMAX ; i++)
    {
        curCurve = *(Plot->GetCurve(i));
        if (curCurve.Defined) {
            if (curCurve.Type == wxECT_PARAMETRIC)
                listFunction->Append(wxString::Format(wxT("%d: %s, %s {%.1f..%.1f}"), i+1, curCurve.ExpressionX.c_str(), curCurve.ExpressionY.c_str(), curCurve.RangeMin, curCurve.RangeMax));
            else
                if (!curCurve.RangeEnabled)
                    listFunction->Append(wxString::Format(wxT("%d: %s"), i+1, curCurve.ExpressionX.c_str()));
                else
                    listFunction->Append(wxString::Format(wxT("%d: %s {%.1f..%.1f}"), i+1, curCurve.ExpressionX.c_str(), curCurve.RangeMin, curCurve.RangeMax));
            listFunction->Check(listFunction->GetCount()-1, curCurve.Enabled);
        }
    }
}

void wxPlotFrame::OnButtonClick(wxCommandEvent& event)
{
    long index;
    double Xpos;
    wxString buffer;
    wxEcCurve newcurve;
    wxEcAxis axis;
    wxFontData fontData;
    wxFontDialog *fontDlg;

    switch (event.GetId())
    {
        case ID_ADD:
            newcurve.Parse(editExpression->GetValue(), checkPolar->GetValue());
            if (Plot->AddCurve(newcurve) != wxNOT_FOUND)
            {
                Plot->Refresh();
                DoRefreshCurveList();
            } else
                wxMessageDialog(NULL, wxT("It seems there are too many curves loaded. So we can't add a new one."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
            break;

        case ID_USEDEMO:
            Plot->RemoveAllCurves();

            newcurve.Parse(wxT("sqr(x)/10 $ -7 4"));
            Plot->EnableCurve(Plot->AddCurve(newcurve), false);
            newcurve.Parse(wxT("3+4*cos(t)+4*cos(2*t) ; 4*sin(t)+3*sin(2*t) $ -pi pi"));
            Plot->EnableCurve(Plot->AddCurve(newcurve), false);
            newcurve.Parse(wxT("2*cos(x/2)"));
            Plot->EnableCurve(Plot->AddCurve(newcurve), false);
            newcurve.Parse(wxT("8*sin(4*t) $ -pi pi"), true);
            Plot->EnableCurve(Plot->AddCurve(newcurve), false);
            newcurve.Parse(wxT("t/2 $ 0 6*pi"), true);
            Plot->EnableCurve(Plot->AddCurve(newcurve), false);

            DoRefreshCurveList();
            wxMessageDialog(NULL, wxT("To enable the curves, see the listbox on your left.\nThere are small squares to tick.\n\nEnjoy !"), wxT("Information"), wxOK|wxICON_INFORMATION).ShowModal();
            //Plot->Refresh() is not necessary, because our new curves are disabled by default.
            break;

        case ID_DELETE:
            buffer = listFunction->GetStringSelection();
            if (buffer.Len() == 0)
            {
                wxMessageDialog(NULL, wxT("Please select a curve."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
                return;
            }
            if (buffer.BeforeFirst(wxT(':')).ToLong(&index))
            {
                Plot->DeleteCurve(index-1);
                Plot->Refresh();
                DoRefreshCurveList();
                listFunction->SetFocus();
            }
            break;

        case ID_TANGENT:
            buffer = listFunction->GetStringSelection();
            if (buffer.Len() == 0)
            {
                wxMessageDialog(NULL, wxT("Please select a curve."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
                return;
            }
            if (buffer.BeforeFirst(wxT(':')).ToLong(&index))
                if (wxGetTextFromUser(wxT("Select the X-coordinate :"), wxT("Draw a tangent"), wxT("0")).ToDouble(&Xpos))
                {
                    //wxTheApp->Yield();
                    if (!Plot->DrawTangent(index-1, Xpos))
                        wxMessageDialog(NULL, wxT("* You must select an enabled curve.\n* The only type of curve supported is wxECT_CARTESIAN.\n* You must respect the domain definition if the function is restricted."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
                    //To get the equation, call Plot->GetLastTangentEquation()

                    //Don't call Plot->Refresh() now because it won't redraw the tangent. Here, you have just drawn the tangent
                    //as a temporary layer which will be overwritten is you move a window over the client area !
                } else
                    wxMessageDialog(NULL, wxT("The coordinate is not correct."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
            break;

        case ID_DX:
            buffer = listFunction->GetStringSelection();
            if (buffer.Len() == 0)
            {
                wxMessageDialog(NULL, wxT("Please select a curve."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
                return;
            }
            //wxTheApp->Yield();
            if (buffer.BeforeFirst(wxT(':')).ToLong(&index))
            {
                if (!Plot->DrawDerivative(index-1))
                    wxMessageDialog(NULL, wxT("You can only derivate a wxECT_CARTESIAN curve, on the right domain definition.\nSo you can be incitated to restrict the domain to be able to derivate."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
                //Don't call Plot->Refresh() for the same reason
            }
            break;

        case ID_AXISFONT:
            fontData.SetInitialFont(Plot->GetAxis(true)->Font);
            fontDlg = new wxFontDialog(this, &fontData);
            if (fontDlg->ShowModal() == wxID_OK)
            {
                fontData = fontDlg->GetFontData();
                Plot->GetAxis(true)->Font = fontData.GetChosenFont();
                Plot->GetAxis(false)->Font = fontData.GetChosenFont();
                //fontData.GetColour() is not used
                Plot->Refresh();
            }
            wxDELETE(fontDlg);
            break;

        case ID_DEFAULTGRID:
            Plot->SetDefaultGrid();
            Plot->Refresh();
            break;

        case ID_APPLY:
            axis.Format = editFormat->GetValue();
            //-- X
            editXMin->GetValue().ToDouble(&(axis.MinValue));
            editXMax->GetValue().ToDouble(&(axis.MaxValue));
            axis.Validate();
            axis.StepValue = (axis.MaxValue - axis.MinValue)/10;
            Plot->SetAxis(axis, true);
            //-- Y
            editYMin->GetValue().ToDouble(&(axis.MinValue));
            editYMax->GetValue().ToDouble(&(axis.MaxValue));
            axis.Validate();
            axis.StepValue = (axis.MaxValue - axis.MinValue)/10;
            Plot->SetAxis(axis, false);
            //-- Show it
            Plot->Refresh();
            break;

        case ID_FITAXIS:
            Plot->FitYAxis();
            Plot->Refresh();
            break;

        case ID_RESET:
            // Colours are not affected
            Plot->Reset();
            DoRefreshCurveList();
            editExpression->SetFocus();
            break;

        case ID_ORTHO:
            Plot->Orthonormalize();
            Plot->Refresh();
            break;

        case ID_UNZOOM:
            Plot->Unzoom();
            Plot->Refresh();
            break;
    }
}

void wxPlotFrame::OnFuncListCheck(wxCommandEvent& event)
{
    long index;
    if (listFunction->GetString(event.GetInt()).BeforeFirst(wxT(':')).ToLong(&index))
    {
        index--;
        Plot->GetCurve(index)->Enabled = listFunction->IsChecked(event.GetInt());
        Plot->Refresh();
    }
}

void wxPlotFrame::OnBoxCheck(wxCommandEvent& event)
{
    wxEcEngine calculator;
    wxString buffer;
    double x, y;

    switch (event.GetId())
    {
        case ID_SHOWGRID:
            Plot->SetGridVisible(checkShowGrid->GetValue());
            Plot->Refresh();
            break;

        case ID_SHOWAXIS:
            Plot->GetAxis(true)->Visible = checkShowAxis->GetValue();
            Plot->GetAxis(false)->Visible = checkShowAxis->GetValue();
            Plot->Refresh();
            break;

        case ID_SHOWRETICULE:
            if (checkReticule->GetValue())
            {
                buffer = wxGetTextFromUser(wxT("The X-coordinate :"), wxT("Reticule"), wxEmptyString);
                calculator.SetFormula(buffer);
                x = calculator.Compute();
                if (calculator.GetLastError() == wxECE_NOERROR)
                {
                    calculator.SetConstant(wxT("x"), x);
                    buffer = wxGetTextFromUser(wxT("The Y-coordinate :"), wxT("Reticule"), wxEmptyString);
                    calculator.SetFormula(buffer);
                    y = calculator.Compute();
                    if (calculator.GetLastError() == wxECE_NOERROR)
                        Plot->SetReticule(x,y);
                }
            }
            Plot->SetReticuleVisible(checkReticule->GetValue());
            Plot->Refresh();
            break;

        case ID_POLARGRID:
            Plot->SetGridPolar(checkPolarGrid->GetValue());
            Plot->Refresh();
            break;
    }
}

void wxPlotFrame::OnMouseEvent(wxMouseEvent& event)
{
    double X = Plot->XToValue(event.GetX());
    double Y = Plot->YToValue(event.GetY());
    wxEcComplex point(X,Y);
    labelXY->SetLabel(wxString::Format(wxT("X=%.4f , Y=%.4f, R=%.4f, T=%.4f"), X, Y, point.Modulus(), point.Argument()));
    event.Skip();
}
