
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

//------------------------------------------
//
//  Web link : http://en.wikipedia.org/wiki/List_of_fractals_by_Hausdorff_dimension
//
//------------------------------------------

#include "fractal.h"

    BEGIN_EVENT_TABLE(wxFractalFrame, wxFrame)
        EVT_MENU(wxID_ANY, wxFractalFrame::OnMenuClick)
        EVT_BUTTON(wxID_ANY, wxFractalFrame::OnButtonClick)
    END_EVENT_TABLE()

//------------------------------------------

wxFractalFrame::wxFractalFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, wxT("Mandelbrot's fractal"), wxDefaultPosition, wxSize(FRACTAL_WIDTH, FRACTAL_HEIGHT), (wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)&~wxMAXIMIZE_BOX&~wxRESIZE_BORDER)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    //-- Layout
    wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
            labelXmin = new wxStaticText(this, wxID_ANY, wxT("Xmin"));
            HSizer->Add(labelXmin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
            editXmin = new wxTextCtrl(this, wxID_ANY, wxT("-2"), wxDefaultPosition, wxSize(50,-1));
            HSizer->Add(editXmin, 0, wxALIGN_CENTER_VERTICAL, 5);
            labelXmax = new wxStaticText(this, wxID_ANY, wxT("Xmax"));
            HSizer->Add(labelXmax, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
            editXmax = new wxTextCtrl(this, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize(50,-1));
            HSizer->Add(editXmax, 0, wxALIGN_CENTER_VERTICAL, 5);
            labelYmix = new wxStaticText(this, wxID_ANY, wxT("Ymin"));
            HSizer->Add(labelYmix, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
            editYmin = new wxTextCtrl(this, wxID_ANY, wxT("-2"), wxDefaultPosition, wxSize(50,-1));
            HSizer->Add(editYmin, 0, wxALIGN_CENTER_VERTICAL, 5);
            labelYmax = new wxStaticText(this, wxID_ANY, wxT("Ymax"));
            HSizer->Add(labelYmax, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
            editYmax = new wxTextCtrl(this, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize(50,-1));
            HSizer->Add(editYmax, 0, wxALIGN_CENTER_VERTICAL, 5);
            labelDepth = new wxStaticText(this, wxID_ANY, wxT("Depth"));
            HSizer->Add(labelDepth, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
            editDepth = new wxTextCtrl(this, wxID_ANY, wxT("150"), wxDefaultPosition, wxSize(50,-1));
            HSizer->Add(editDepth, 0, wxALIGN_CENTER_VERTICAL, 5);
            buttonDraw = new wxButton(this, ID_DRAW, wxT("Draw"), wxDefaultPosition, wxSize(50,-1));
            HSizer->Add(buttonDraw, 0, wxALIGN_CENTER_VERTICAL, 5);
        VSizer->Add(HSizer, 0, wxEXPAND, 5);

        wxBoxSizer *CSizer = new wxBoxSizer(wxHORIZONTAL);
            labelRGB = new wxStaticText(this, wxID_ANY, wxT("RGB factors :"));
            CSizer->Add(labelRGB, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
            sliderR = new wxSlider(this, wxID_ANY, 255, 0, 255, wxDefaultPosition, wxSize(125,-1), wxSL_BOTH|wxSL_HORIZONTAL);
            CSizer->Add(sliderR, 0, wxALIGN_CENTER_VERTICAL, 5);
            sliderG = new wxSlider(this, wxID_ANY, 255, 0, 255, wxDefaultPosition, wxSize(125,-1), wxSL_BOTH|wxSL_HORIZONTAL);
            CSizer->Add(sliderG, 0, wxALIGN_CENTER_VERTICAL, 5);
            sliderB = new wxSlider(this, wxID_ANY, 255, 0, 255, wxDefaultPosition, wxSize(125,-1), wxSL_BOTH|wxSL_HORIZONTAL);
            CSizer->Add(sliderB, 0, wxALIGN_CENTER_VERTICAL, 5);
        VSizer->Add(CSizer, 0, wxEXPAND, 5);

        Notebook = new wxNotebook(this, wxID_ANY);
            PageView = new wxPanel(Notebook, wxID_ANY);
            Notebook->AddPage(PageView, wxT("View"), true, -1);
                wxBoxSizer *TVSizer = new wxBoxSizer(wxVERTICAL);
                    m_view = new wxStaticBitmap(PageView, ID_VIEW, wxBitmap(1,1), wxDefaultPosition, wxSize(FRACTAL_WIDTH, FRACTAL_HEIGHT));
                    TVSizer->Add(m_view, 1, wxEXPAND|wxALL, 5);
                PageView->SetSizer(TVSizer);

            PagePlot = new wxPanel(Notebook, wxID_ANY);
            Notebook->AddPage(PagePlot, wxT("Plot"), false, -1);
                wxBoxSizer *TPSizer = new wxBoxSizer(wxVERTICAL);
                    m_plot = new wxEcPlot(PagePlot, wxID_ANY, wxDefaultPosition, wxSize(FRACTAL_WIDTH, FRACTAL_HEIGHT));
                    TPSizer->Add(m_plot, 1, wxEXPAND|wxALL, 5);
                PagePlot->SetSizer(TPSizer);
        VSizer->Add(Notebook, 1, wxEXPAND|wxALL, 5);

        wxBoxSizer *BSizer = new wxBoxSizer(wxHORIZONTAL);
            buttonLeft = new wxButton(this, ID_BROWSE_LEFT, wxT("<<"), wxDefaultPosition, wxSize(50,-1));
            BSizer->Add(buttonLeft, 0, wxALL, 5);
            buttonRight = new wxButton(this, ID_BROWSE_RIGHT, wxT(">>"), wxDefaultPosition, wxSize(50,-1));
            BSizer->Add(buttonRight, 0, wxALL, 5);
            buttonTop = new wxButton(this, ID_BROWSE_TOP, wxT("^^"), wxDefaultPosition, wxSize(50,-1));
            BSizer->Add(buttonTop, 0, wxALL, 5);
            buttonDown = new wxButton(this, ID_BROWSE_BOTTOM, wxT("vv"), wxDefaultPosition, wxSize(50,-1));
            BSizer->Add(buttonDown, 0, wxALL, 5);
            buttonPlus = new wxButton(this, ID_BROWSE_PLUS, wxT("++"), wxDefaultPosition, wxSize(50,-1));
            BSizer->Add(buttonPlus, 0, wxALL, 5);
            buttonMinus = new wxButton(this, ID_BROWSE_MINUS, wxT("--"), wxDefaultPosition, wxSize(50,-1));
            BSizer->Add(buttonMinus, 0, wxALL, 5);
            buttonAnimation = new wxButton(this, ID_ANIMATION, wxT("Animation"));
            BSizer->Add(buttonAnimation, 0, wxALL, 5);
        VSizer->Add(BSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5);
    this->SetSizer(VSizer);

    //-- MenuBar
    MenuBar = new wxMenuBar();
        MenuFile = new wxMenu();
            MenuReset = new wxMenuItem(MenuFile, ID_MENU_RESET, wxString(wxT("&Reset")));
            MenuFile->Append(MenuReset);
            MenuSave = new wxMenuItem(MenuFile, ID_MENU_SAVE, wxString(wxT("&Save")));
            MenuFile->Append(MenuSave);
            MenuFile->AppendSeparator();
            MenuQuit = new wxMenuItem(MenuFile, wxID_EXIT, wxString(wxT("&Quit")));
            MenuFile->Append(MenuQuit);
        MenuBar->Append(MenuFile, wxT("&File"));
    this->SetMenuBar(MenuBar);

    //-- Initialization
    xmin = -2;
    xmax = 2;
    ymin = -2;
    ymax = 2;
    fdepth = 150;
    level = 1;

    //-- Events connected
    m_view->Connect(ID_VIEW, wxEVT_LEFT_DOWN, wxMouseEventHandler(wxFractalFrame::OnMouseDown), NULL, this);
    m_view->Connect(ID_VIEW, wxEVT_LEFT_UP, wxMouseEventHandler(wxFractalFrame::OnMouseUp), NULL, this);

    //-- Tools
    wxBitmap m_bitmap(FRACTAL_WIDTH, FRACTAL_HEIGHT);
    m_image = m_bitmap.ConvertToImage();

    m_plot->GetAxis(true)->MinValue = 0;
    m_plot->GetAxis(true)->MaxValue = FRACTAL_DEPTH;
    m_plot->GetAxis(true)->StepValue = 25;
    m_plot->GetAxis(true)->ShowValues = false;
    m_plot->GetAxis(false)->MinValue = 0;
    m_plot->GetAxis(false)->ShowValues = false;

    //-- Display
    this->Fit();
    this->Center();
    #ifdef __WINDOWS__
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    #endif

    DoGui();
    this->Show(true);
}

wxFractalFrame::~wxFractalFrame()
{
    m_view->Disconnect(ID_VIEW, wxEVT_LEFT_UP, wxMouseEventHandler(wxFractalFrame::OnMouseUp), NULL, this);
    m_view->Disconnect(ID_VIEW, wxEVT_LEFT_DOWN, wxMouseEventHandler(wxFractalFrame::OnMouseDown), NULL, this);
}

//------------------------------------------

void wxFractalFrame::DoComputeMandelbrot()
{
    int i, j, counter;
    unsigned char red, green, blue;
    wxEcComplex scannedPoint, zPoint;
    int thresholdR, thresholdG, thresholdB;

    //-- Initialization
    for (i=0 ; i<FRACTAL_WIDTH ; i++)
        for (j=0 ; j<FRACTAL_HEIGHT ; j++)
            m_fractal_mapping[i][j] = 0;
    for (i=0 ; i<=FRACTAL_DEPTH ; i++)
    {
        m_usage[i].x = i;
        m_usage[i].y = 0;
    }
    thresholdR = sliderR->GetValue();
    thresholdG = sliderG->GetValue();
    thresholdB = sliderB->GetValue();

    //-- Computation
    for (i=0 ; i<FRACTAL_WIDTH ; i++)
    {
        scannedPoint.Re = xmin + i*(xmax-xmin)/FRACTAL_WIDTH;
        for (j=0 ; j<FRACTAL_HEIGHT ; j++)
        {
            scannedPoint.Im = ymax - j*(ymax-ymin)/FRACTAL_HEIGHT;
            counter = 0;
            zPoint = wxEcComplex(0,0);
            while (true)
            {
                counter++;
                zPoint = (zPoint*zPoint) + scannedPoint;
                if ((counter>=fdepth) || (zPoint.Modulus()>4))
                    break;
            }
            m_usage[counter].y += 1;

            //-- Colors
            red   = (counter == fdepth ? 0 : (unsigned char)(thresholdR*counter/fdepth));
            green = (counter == fdepth ? 0 : (unsigned char)(thresholdG*counter/fdepth));
            blue  = (counter == fdepth ? 0 : (unsigned char)(thresholdB*counter/fdepth));
            m_image.SetRGB(i, j, red, green, blue);
        }
    }

    //-- Updates the GUI
    m_plot->Refresh();
    m_plot->FitYAxis();
    m_plot->Refresh();
    wxBitmap m_bitmap(m_image);
    m_view->SetBitmap(m_bitmap);
}

void wxFractalFrame::DoDraw(bool fromMemory)
{
    long lbuff;
    if (!fromMemory)
    {
        level = 1;
        editXmin->GetValue().ToDouble(&xmin);
        editXmax->GetValue().ToDouble(&xmax);
        editYmin->GetValue().ToDouble(&ymin);
        editYmax->GetValue().ToDouble(&ymax);
    }
    editDepth->GetValue().ToLong(&lbuff);
    fdepth = lbuff;
    if (fdepth > FRACTAL_DEPTH)
        fdepth = FRACTAL_DEPTH;
    if ((xmin<xmax) && (ymin<ymax))
    {
        m_curve.NumPoints = fdepth;
        m_curve.RangeMax = fdepth;
        m_plot->RemoveAllCurves();
        m_curve = wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxRED, 1, false, false, 0, fdepth, fdepth, &(m_usage[0]));
        m_plot->AddCurve(m_curve);
        DoComputeMandelbrot();
    }
    this->SetLabel(wxString::Format(wxT("Mandelbrot's fractal - Relative level : %d"), level));
}

void wxFractalFrame::DoGui()
{
    editXmin->SetValue(wxString::Format(wxT("%f"), xmin));
    editXmax->SetValue(wxString::Format(wxT("%f"), xmax));
    editYmin->SetValue(wxString::Format(wxT("%f"), ymin));
    editYmax->SetValue(wxString::Format(wxT("%f"), ymax));
    //DO NOT: editDepth->SetValue(wxString::Format(wxT("%d"), fdepth));
    DoDraw(true);
}

void wxFractalFrame::DoMinus()
{
    double step;
    level--;
    //-- X
    step = (xmax-xmin)/2;
    xmin -=step;
    xmax +=step;
    //-- Y
    step = (ymax-ymin)/2;
    ymin -=step;
    ymax +=step;
    DoGui();
}

//------------------------------------------

void wxFractalFrame::OnButtonClick(wxCommandEvent& event)
{
    int i, n;
    double step;
    wxString buffer;
    wxStandardPaths pathcatalog;

    switch (event.GetId())
    {
        case ID_DRAW:
            DoDraw(false);
            break;

        case ID_BROWSE_LEFT:
            step = (xmax-xmin)/2;
            xmin -= step;
            xmax -= step;
            DoGui();
            break;

        case ID_BROWSE_RIGHT:
            step = (xmax-xmin)/2;
            xmin += step;
            xmax += step;
            DoGui();
            break;

        case ID_BROWSE_TOP:
            step = (ymax-ymin)/2;
            ymin += step;
            ymax += step;
            DoGui();
            break;

        case ID_BROWSE_BOTTOM:
            step = (ymax-ymin)/2;
            ymin -= step;
            ymax -= step;
            DoGui();
            break;

        case ID_BROWSE_PLUS:
            level++;
            //-- X
            step = (xmax-xmin)/4;
            xmin +=step;
            xmax -=step;
            //-- Y
            step = (ymax-ymin)/4;
            ymin +=step;
            ymax -=step;
            DoGui();
            break;

        case ID_BROWSE_MINUS:
            DoMinus();
            break;

        case ID_ANIMATION:
            n = level;
            //-- Gets the directory where to save
            wxDirDialog dirDlg(this, wxT("Choose a destination"), wxEmptyString, wxDD_DEFAULT_STYLE|wxDD_DIR_MUST_EXIST);
            buffer = pathcatalog.GetExecutablePath();
            dirDlg.SetPath(wxPathOnly(buffer));
            if (dirDlg.ShowModal() == wxID_CANCEL)
                return;

            //-- Saves all the pictures
            buffer = this->GetLabel();
            for (i=1 ; i<=n ; i++)
            {
                this->SetLabel(wxString::Format(wxT("Progress : %d / %d"), i, n));
                DoMinus();
                m_image.SaveFile(wxString::Format(wxT("%s/anim_%d.bmp"), dirDlg.GetPath().c_str(), n-i+1));
            }
            this->SetLabel(buffer);
            break;
    }
}

void wxFractalFrame::OnMenuClick(wxCommandEvent& event)
{
    wxFileDialog *fileDlg;

    switch (event.GetId())
    {
        case ID_MENU_RESET:
            xmin = -2;
            xmax = 2;
            ymin = -2;
            ymax = 2;
            fdepth = 150;
            DoGui();
            break;

        case ID_MENU_SAVE:
            fileDlg = new wxFileDialog(this, wxT("Save as..."), wxEmptyString, wxEmptyString, wxT("All image types supported|*.bmp;*.png;*.jpg;*.jpeg;*.gif;*.pcx;*.pnm;*.tiff;*.tga;*.iff;*.xpm;*.ico;*.cur;*.ani"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
            if (fileDlg->ShowModal() == wxID_OK)
                m_image.SaveFile(fileDlg->GetPath());
            wxDELETE(fileDlg);
            break;
    }
}

void wxFractalFrame::OnMouseDown(wxMouseEvent& event)
{
    m_pointA = wxPoint(event.GetX(), event.GetY());
    event.Skip();
}

void wxFractalFrame::OnMouseUp(wxMouseEvent& event)
{
    wxRealPoint newXReal, newYReal;

    //-- Gets the ordered coordinates
    wxPoint newX, newY;
    newX.x = wxMin(m_pointA.x, event.GetX());
    newX.y = wxMax(m_pointA.x, event.GetX());
    newY.x = wxMax(m_pointA.y, event.GetY());
    newY.y = wxMin(m_pointA.y, event.GetY());

    //-- Computes real coordinates
    if ((newX.x<newX.y) && (newY.x>newY.y))
    {
        newXReal.x = xmin + newX.x*(xmax-xmin)/FRACTAL_WIDTH;
        newXReal.y = xmin + newX.y*(xmax-xmin)/FRACTAL_WIDTH;
        newYReal.x = ymin + (FRACTAL_HEIGHT-newY.x)*(ymax-ymin)/FRACTAL_HEIGHT;
        newYReal.y = ymin + (FRACTAL_HEIGHT-newY.y)*(ymax-ymin)/FRACTAL_HEIGHT;

        //-- Sets the new values
        xmin = newXReal.x;
        xmax = newXReal.y;
        ymin = newYReal.x;
        ymax = newYReal.y;

        DoGui();
    }
    else
        wxLogError(wxT("Invalide coordinates."));

    //-- Finalization
    event.Skip();
}
