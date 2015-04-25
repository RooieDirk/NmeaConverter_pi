
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

#include "matrix.h"

    BEGIN_EVENT_TABLE(wxMatrixFrame, wxFrame)
        EVT_MENU(wxID_ANY, wxMatrixFrame::OnMenuClick)
        EVT_BUTTON(wxID_ANY, wxMatrixFrame::OnButtonClick)
        EVT_COMMAND_SCROLL(ID_SCROLLBAR, wxMatrixFrame::OnScrollClick)
    END_EVENT_TABLE()

//------------------------------------------

wxMatrixFrame::wxMatrixFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, wxT("Matrix"), wxDefaultPosition, wxSize(500,500), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)
{
    wxBitmap defaultBmp;
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    //-- User interface
    wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);
        m_viewscroller = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxSUNKEN_BORDER|wxVSCROLL);
            /*wxBoxSizer **/SSizer = new wxBoxSizer(wxVERTICAL);
            m_view = new wxStaticBitmap(m_viewscroller, wxID_ANY, defaultBmp);
            m_view->Show(false);
            SSizer->Add(m_view, 0, wxALL, 0);
        VSizer->Add(m_viewscroller, 2, wxALL|wxEXPAND, 5);

        wxBoxSizer *BSizer = new wxBoxSizer(wxHORIZONTAL);
            wxBoxSizer *BLSizer = new wxBoxSizer(wxVERTICAL);
                m_fitbutton = new wxButton(this, ID_FITBUTTON, wxT("Fit"), wxDefaultPosition, wxSize(40,-1));
                BLSizer->Add(m_fitbutton, 0, wxALL, 5);
                m_fitbar = new wxScrollBar(this, ID_SCROLLBAR, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL);
                BLSizer->Add(m_fitbar, 1, wxALL|wxEXPAND, 5);
            BSizer->Add(BLSizer, 0, wxEXPAND, 5);
            m_plot = new wxEcPlot(this, wxID_ANY);
            BSizer->Add(m_plot, 1, wxALL|wxEXPAND, 5);
        VSizer->Add(BSizer, 1, wxEXPAND, 5);
    this->SetSizer(VSizer);

    //-- Menubar
    m_menubar = new wxMenuBar();
        m_menufile = new wxMenu();
            m_menuitemload = new wxMenuItem(m_menufile, wxID_OPEN, wxT("&Load image\tCtrl+O"));
            m_menufile->Append(m_menuitemload);
            m_menuitemsave = new wxMenuItem(m_menufile, wxID_SAVE, wxT("&Save image\tCtrl+S"));
            m_menufile->Append(m_menuitemsave);
            m_menuitemundo = new wxMenuItem(m_menufile, wxID_UNDO, wxT("&Undo (if possible)\tCtrl+Z"));
            m_menufile->Append(m_menuitemundo);
            m_menufile->AppendSeparator();
            m_menuitemquit = new wxMenuItem(m_menufile, wxID_EXIT, wxT("&Quit"));
            m_menufile->Append(m_menuitemquit);
        m_menubar->Append(m_menufile, wxT("&File"));

        m_menuimage = new wxMenu();
            m_menusubcolours = new wxMenu();
                m_menuitemkickred = new wxMenuItem(m_menusubcolours, ID_MENU_KICKRED, wxT("Kick red layer"));
                m_menusubcolours->Append(m_menuitemkickred);
                m_menuitemkickgreen = new wxMenuItem(m_menusubcolours, ID_MENU_KICKGREEN, wxT("Kick green layer"));
                m_menusubcolours->Append(m_menuitemkickgreen);
                m_menuitemkickblue = new wxMenuItem(m_menusubcolours, ID_MENU_KICKBLUE, wxT("Kick blue layer"));
                m_menusubcolours->Append(m_menuitemkickblue);
                m_menuitemgreyscale = new wxMenuItem(m_menusubcolours, ID_MENU_GREYSCALE, wxT("Grey scale"));
                m_menusubcolours->Append(m_menuitemgreyscale);
                m_menuitemusered = new wxMenuItem(m_menusubcolours, ID_MENU_USERED, wxT("Use red layer"));
                m_menusubcolours->Append(m_menuitemusered);
                m_menuitemusegreen = new wxMenuItem(m_menusubcolours, ID_MENU_USEGREEN, wxT("Use green layer"));
                m_menusubcolours->Append(m_menuitemusegreen);
                m_menuitemuseblue = new wxMenuItem(m_menusubcolours, ID_MENU_USEBLUE, wxT("Use blue layer"));
                m_menusubcolours->Append(m_menuitemuseblue);
                m_menuitemuseblack = new wxMenuItem(m_menusubcolours, ID_MENU_USEBLACK, wxT("Extract black color"));
                m_menusubcolours->Append(m_menuitemuseblack);
                m_menusubcolours->AppendSeparator();
                m_menuiteminverse = new wxMenuItem(m_menusubcolours, ID_MENU_INVERSE, wxT("Inverse"));
                m_menusubcolours->Append(m_menuiteminverse);
                m_menuitemluminosity = new wxMenuItem(m_menusubcolours, ID_MENU_LUMINOSITY, wxT("Luminosity"));
                m_menusubcolours->Append(m_menuitemluminosity);
                m_menuitemcontrast = new wxMenuItem(m_menusubcolours, ID_MENU_CONTRAST, wxT("Contrast stretching"));
                m_menusubcolours->Append(m_menuitemcontrast);
                m_menuitembinarization = new wxMenuItem(m_menusubcolours, ID_MENU_BINARIZATION, wxT("Binarization"));
                m_menusubcolours->Append(m_menuitembinarization);
                m_menuitemmedian = new wxMenuItem(m_menusubcolours, ID_MENU_MEDIAN, wxT("Median"));
                m_menusubcolours->Append(m_menuitemmedian);
            m_menuimage->Append(wxID_ANY, wxT("Colours and layers"), m_menusubcolours);

            m_menusubcolourspace = new wxMenu();
                m_menuitemrgb2ycbcr = new wxMenuItem(m_menusubcolours, ID_MENU_RGB2YCBCR, wxT("RGB --> YCbCr"));
                m_menusubcolourspace->Append(m_menuitemrgb2ycbcr);
                m_menuitemycbcr2rgb = new wxMenuItem(m_menusubcolours, ID_MENU_YCBCR2RGB, wxT("YCbCr --> RGB"));
                m_menusubcolourspace->Append(m_menuitemycbcr2rgb);
                m_menuitemrgb2yiq = new wxMenuItem(m_menusubcolours, ID_MENU_RGB2YIQ, wxT("RGB --> YIQ"));
                m_menusubcolourspace->Append(m_menuitemrgb2yiq);
                m_menuitemyiq2rgb = new wxMenuItem(m_menusubcolours, ID_MENU_YIQ2RGB, wxT("YIQ --> RGB"));
                m_menusubcolourspace->Append(m_menuitemyiq2rgb);
            m_menuimage->Append(wxID_ANY, wxT("Colour space"), m_menusubcolourspace);

            m_menusubmorphology = new wxMenu();
                m_menuitemdilate = new wxMenuItem(m_menusubmorphology, ID_MENU_DILATE, wxT("Dilation"));
                m_menusubmorphology->Append(m_menuitemdilate);
                m_menuitemerode = new wxMenuItem(m_menusubmorphology, ID_MENU_ERODE, wxT("Erosion"));
                m_menusubmorphology->Append(m_menuitemerode);
                m_menusubmorphology->AppendSeparator();
                m_menuitemopening = new wxMenuItem(m_menusubmorphology, ID_MENU_OPENING, wxT("Opening"));
                m_menusubmorphology->Append(m_menuitemopening);
                m_menuitemclosing = new wxMenuItem(m_menusubmorphology, ID_MENU_CLOSING, wxT("Closing"));
                m_menusubmorphology->Append(m_menuitemclosing);
            m_menuimage->Append(wxID_ANY, wxT("Morphology (black and white)"), m_menusubmorphology);

            m_menusubmatrix = new wxMenu();
                m_menuitemlowpass = new wxMenuItem(m_menusubmatrix, ID_MENU_LOWPASS, wxT("Averaging (low pass, smoothing)"));
                m_menusubmatrix->Append(m_menuitemlowpass);
                m_menuitemgaussianblur = new wxMenuItem(m_menusubmatrix, ID_MENU_GAUSSIANSMOOTHING, wxT("Gaussian smoothing"));
                m_menusubmatrix->Append(m_menuitemgaussianblur);
                m_menuitemhighpass = new wxMenuItem(m_menusubmatrix, ID_MENU_LAPLACIAN, wxT("Laplacian (high pass)"));
                m_menusubmatrix->Append(m_menuitemhighpass);
                m_menuitemprewitt = new wxMenuItem(m_menusubmatrix, ID_MENU_PREWITT, wxT("Prewitt"));
                m_menusubmatrix->Append(m_menuitemprewitt);
                m_menuitemsobel = new wxMenuItem(m_menusubmatrix, ID_MENU_SOBEL, wxT("Sobel"));
                m_menusubmatrix->Append(m_menuitemsobel);
                m_menusubmatrix->AppendSeparator();
                m_menuitemedgeenhancement = new wxMenuItem(m_menusubmatrix, ID_MENU_EDGES, wxT("Edge enhancement"));
                m_menusubmatrix->Append(m_menuitemedgeenhancement);
                m_menuitemdrawedges = new wxMenuItem(m_menusubmatrix, ID_MENU_DRAWEDGES, wxT("Draw edges"));
                m_menusubmatrix->Append(m_menuitemdrawedges);
                m_menuitemrise = new wxMenuItem(m_menusubmatrix, ID_MENU_RISE, wxT("Rise"));
                m_menusubmatrix->Append(m_menuitemrise);
                m_menusubmatrix->AppendSeparator();
                m_menuitemcustommatrix = new wxMenuItem(m_menusubmatrix, ID_MENU_CUSTOMMATRIX, wxT("Custom matrix..."));
                m_menusubmatrix->Append(m_menuitemcustommatrix);
            m_menuimage->Append(wxID_ANY, wxT("Matrix"), m_menusubmatrix);
        m_menubar->Append(m_menuimage, wxT("&Image"));

        m_menuhelp = new wxMenu();
            m_menuitemabout = new wxMenuItem(m_menuhelp, wxID_ABOUT, wxT("About"));
            m_menuhelp->Append(m_menuitemabout);
        m_menubar->Append(m_menuhelp, wxT("&?"));
    this->SetMenuBar(m_menubar);

    //-- Accelerators
    wxAcceleratorEntry ShortCuts[3];
    ShortCuts[0].Set(wxACCEL_CTRL, (int)'o', wxID_OPEN);
    ShortCuts[1].Set(wxACCEL_CTRL, (int)'s', wxID_SAVE);
    ShortCuts[2].Set(wxACCEL_CTRL, (int)'z', wxID_UNDO);
    this->SetAcceleratorTable(wxAcceleratorTable(3, ShortCuts));

    //-- Finalization
    m_viewscroller->EnableScrolling(true, true);
    //X
    m_plot->GetAxis(true)->MinValue = 0;
    m_plot->GetAxis(true)->MaxValue = 255;
    m_plot->GetAxis(true)->StepValue = 25;
    m_plot->GetAxis(true)->ShowValues = false;
    //Y
    m_plot->GetAxis(false)->MinValue = 0;
    m_plot->GetAxis(false)->ShowValues = false;
    //Curves                    X              Y              Type         Colour    W  Dots   Range  Min Max  Pts  Data
    m_plot->RemoveAllCurves();
    m_plot->AddCurve( wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxRED,   1, false, false, 0,  256, 256, m_vision.GetRedData()) );
    m_plot->AddCurve( wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxGREEN, 1, false, false, 0,  256, 256, m_vision.GetGreenData()) );
    m_plot->AddCurve( wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxBLUE,  1, false, false, 0,  256, 256, m_vision.GetBlueData()) );
    m_plot->AddCurve( wxEcCurve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxBLACK, 1, false, false, 0,  256, 256, m_vision.GetGreyData()) );
    m_plot->Refresh();

    //-- Events
    m_plot->Connect(wxEVT_MOTION, wxMouseEventHandler(wxMatrixFrame::OnMousePlotEvent), NULL, this);
    m_view->Connect(wxEVT_MOTION, wxMouseEventHandler(wxMatrixFrame::OnMouseViewEvent), NULL, this);

    //-- Display
    this->Layout();
    #ifdef __WINDOWS__
        this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    #endif
    this->Center();
    this->Show(true);
}

wxMatrixFrame::~wxMatrixFrame()
{
    m_view->Disconnect(wxEVT_MOTION, wxMouseEventHandler(wxMatrixFrame::OnMouseViewEvent), NULL, this);
    m_plot->Disconnect(wxEVT_MOTION, wxMouseEventHandler(wxMatrixFrame::OnMousePlotEvent), NULL, this);
}

//------------------------------------------

void wxMatrixFrame::DoGUI()
{
    long ymax;

    //-- Various updates
    m_viewscroller->SetScrollbars(SCROLL_RATE, SCROLL_RATE, m_vision.GetImage()->GetWidth()/SCROLL_RATE, m_vision.GetImage()->GetHeight()/SCROLL_RATE, 0, 0, false);
    SSizer->RecalcSizes();

    //-- Displays the plot
    m_vision.ComputeHistogram();
    m_plot->Refresh();
    ymax = m_plot->GetYMax();
    m_fitbar->SetScrollbar(ymax, ymax/20, ymax, ymax/20, true);
    m_plot->GetAxis(false)->MaxValue = ymax;
    m_plot->Refresh();

    //-- Shows the picture
    wxBitmap m_bitmap(*(m_vision.GetImage()));
    m_view->SetBitmap(m_bitmap);
    m_view->Show(true);
    m_view->Refresh();
}

//------------------------------------------

void wxMatrixFrame::OnMenuClick(wxCommandEvent& event)
{
    wxFileDialog *fileDlg = NULL;
    unsigned long threshold, lowlimit, highlimit;
    int i;
    long level;
    double sigma;
    wxEcMatrix tool(3,3), *pMat;
    wxEcEngine *calc = NULL;
    wxCustomMatrixDialog *cmDlg = NULL;

    switch (event.GetId())
    {
        case wxID_UNDO:
            m_vision.Undo();
            DoGUI();
            break;

        case wxID_OPEN:
            fileDlg = new wxFileDialog(this, wxT("Open a picture"), wxEmptyString, wxEmptyString, wxT("All image types supported|*.bmp;*.png;*.jpg;*.jpeg;*.gif;*.pcx;*.pnm;*.tiff;*.tga;*.iff;*.xpm;*.ico;*.cur;*.ani"), wxFD_OPEN);
            if (fileDlg->ShowModal() == wxID_OK)
            {
                m_vision.OpenImage(fileDlg->GetPath());
                DoGUI();
                //-- The histogram will be adjusted to the default picture
                m_plot->GetAxis(false)->Reset();
                m_plot->FitYAxis();
                m_plot->Refresh();
            }
            break;

        case wxID_SAVE:
            fileDlg = new wxFileDialog(this, wxT("Save as..."), wxEmptyString, wxEmptyString, wxT("All image types supported|*.bmp;*.png;*.jpg;*.jpeg;*.gif;*.pcx;*.pnm;*.tiff;*.tga;*.iff;*.xpm;*.ico;*.cur;*.ani"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
            if (fileDlg->ShowModal() == wxID_OK)
                m_vision.GetImage()->SaveFile(fileDlg->GetPath());
            break;

        case wxID_EXIT:
            this->Close();
            break;

        case ID_MENU_KICKRED:
            m_vision.KickColour(wxCL_RED);
            DoGUI();
            break;

        case ID_MENU_KICKGREEN:
            m_vision.KickColour(wxCL_GREEN);
            DoGUI();
            break;

        case ID_MENU_KICKBLUE:
            m_vision.KickColour(wxCL_BLUE);
            DoGUI();
            break;

        case ID_MENU_USEBLACK:
            m_vision.UseBlack();
            DoGUI();
            break;

        case ID_MENU_GREYSCALE:
            m_vision.GreyScale();
            DoGUI();
            break;

        case ID_MENU_USERED:
            switch (wxMessageDialog(NULL, wxT("Propagate to greyscale ?"), wxT("Question"), wxYES_NO).ShowModal())
            {
                case wxID_YES:
                    m_vision.Generalize(wxCL_RED);
                    break;
                case wxID_NO:
                    m_vision.KickColour(wxCL_GREEN|wxCL_BLUE);
                    break;
            }
            DoGUI();
            break;

        case ID_MENU_USEGREEN:
            switch (wxMessageDialog(NULL, wxT("Propagate to greyscale ?"), wxT("Question"), wxYES_NO).ShowModal())
            {
                case wxID_YES:
                    m_vision.Generalize(wxCL_GREEN);
                    break;
                case wxID_NO:
                    m_vision.KickColour(wxCL_RED|wxCL_BLUE);
                    break;
            }
            DoGUI();
            break;

        case ID_MENU_USEBLUE:
            switch (wxMessageDialog(NULL, wxT("Propagate to greyscale ?"), wxT("Question"), wxYES_NO).ShowModal())
            {
                case wxID_YES:
                    m_vision.Generalize(wxCL_BLUE);
                    break;
                case wxID_NO:
                    m_vision.KickColour(wxCL_RED|wxCL_GREEN);
                    break;
            }
            DoGUI();
            break;

        case ID_MENU_INVERSE:   
            m_vision.Inverse();
            DoGUI();
            break;

        case ID_MENU_ROTATECOLOURS:
            m_vision.RotateColours();
            DoGUI();
            break;

        case ID_MENU_LUMINOSITY:
            wxGetTextFromUser(wxT("Offset"), wxT("Signed integer required (-255..255) :"), wxT("0")).ToLong(&level);
            m_vision.Luminosity(level);
            DoGUI();
            break;

        case ID_MENU_CONTRAST:
            wxGetTextFromUser(wxT("Lower limit"), wxT("Unsigned integer required (0..255) :"), wxT("128")).ToULong(&lowlimit);
            wxGetTextFromUser(wxT("Upper limit"), wxT("Unsigned integer required (0..255) :"), wxT("128")).ToULong(&highlimit);
            if (lowlimit != highlimit)
            {
                m_vision.Equalization(lowlimit, highlimit);
                DoGUI();
            }
            break;

        case ID_MENU_BINARIZATION:
            wxGetTextFromUser(wxT("Threshold"), wxT("Unsigned integer required :"), wxT("128")).ToULong(&threshold);
            if (wxMessageDialog(this, wxT("Use direct direction ?"), wxT("Question"), wxYES|wxNO|wxICON_QUESTION).ShowModal() == wxID_YES)
                m_vision.Binarization(threshold, OP_DIRECT);
            else
                m_vision.Binarization(threshold, OP_INDIRECT);
            DoGUI();
            break;

        case ID_MENU_MEDIAN:
            m_vision.Median(2);
            DoGUI();
            break;

        case ID_MENU_RGB2YCBCR:
            m_vision.Rgb2YCbCr();
            DoGUI();
            break;

        case ID_MENU_YCBCR2RGB:
            m_vision.YCbCr2Rgb();
            DoGUI();
            break;

        case ID_MENU_RGB2YIQ:
            m_vision.Rgb2Yiq();
            DoGUI();
            break;

        case ID_MENU_YIQ2RGB:
            m_vision.Yiq2Rgb();
            DoGUI();
            break;

        case ID_MENU_DILATE:
        case ID_MENU_ERODE:
        case ID_MENU_OPENING:
        case ID_MENU_CLOSING:
            tool.Clear(1);

            if (wxMessageDialog(this, wxT("Is your picture entirely black and white ?"), wxT("Question"), wxYES|wxNO|wxICON_QUESTION).ShowModal() == wxID_YES)
            {
                if (wxMessageDialog(this, wxT("Is your object black and the background white ?"), wxT("Question"), wxYES|wxNO|wxICON_QUESTION).ShowModal() == wxID_NO)
                    m_vision.Inverse();
                switch(event.GetId())
                {
                    case ID_MENU_DILATE:
                        m_vision.Dilate(tool);
                        break;
                    case ID_MENU_ERODE:
                        m_vision.Erode(tool);
                        break;
                    case ID_MENU_OPENING:
                        m_vision.Erode(tool);
                        m_vision.Dilate(tool);
                        break;
                    case ID_MENU_CLOSING:
                        m_vision.Dilate(tool);
                        m_vision.Erode(tool);
                        break;
                }
                DoGUI();
            }
            else
                wxMessageDialog(this, wxT("You must first binarize your picture to make it black and white."), wxT("Something is wrong with the picture")).ShowModal();
            break;

        case ID_MENU_LOWPASS:
            wxGetTextFromUser(wxT("Radius"), wxT("Unsigned integer expected :"), wxT("1")).ToULong(&threshold);
            m_vision.LowPass(threshold);
            DoGUI();
            break;

        case ID_MENU_GAUSSIANSMOOTHING:
            wxGetTextFromUser(wxT("Radius"), wxT("Unsigned integer expected :"), wxT("2")).ToULong(&threshold);
            wxGetTextFromUser(wxT("Sigma"), wxT("Floating value required :"), wxT("1.4")).ToDouble(&sigma);
            m_vision.GaussianSmoothing(threshold, sigma);
            DoGUI();
            break;

        case ID_MENU_LAPLACIAN:
            if (wxMessageDialog(this, wxT("Do you want your image to be smoothed with a gaussian filter ?"), wxT("Question"), wxYES|wxNO|wxICON_QUESTION).ShowModal() == wxID_YES)
            {
                wxGetTextFromUser(wxT("Radius"), wxT("Unsigned integer expected :"), wxT("2")).ToULong(&threshold);
                wxGetTextFromUser(wxT("Sigma"), wxT("Floating value required :"), wxT("1.4")).ToDouble(&sigma);
                m_vision.Laplacian(true, threshold, sigma);
            }
            else
                m_vision.Laplacian(false);
            DoGUI();
            break;

        case ID_MENU_PREWITT:
            m_vision.Prewitt();
            DoGUI();
            break;

        case ID_MENU_SOBEL:
            m_vision.Sobel();
            DoGUI();
            break;

        case ID_MENU_EDGES:
            m_vision.Edges();
            DoGUI();
            break;

        case ID_MENU_DRAWEDGES:
            m_vision.DrawEdges();
            DoGUI();
            break;

        case ID_MENU_RISE:
            m_vision.Rise();
            DoGUI();
            break;

        case ID_MENU_CUSTOMMATRIX:
            cmDlg = new wxCustomMatrixDialog(this);
            if (cmDlg->ShowModal() == wxID_OK)
            {
                pMat = m_vision.GetFilter();
                pMat->SetDimensionality(5,5);

                calc = new wxEcEngine();
                for (i=0 ; i<25 ; i++)
                {
                    calc->SetFormula(cmDlg->m_edit[i]->GetValue());
                    calc->Compute();
                    pMat->GetData()[i] = (calc->GetLastError() == wxECE_NOERROR ? calc->GetLastResult() : 0);
                }
                wxDELETE(calc);
                m_vision.RunFilter();
            }
            cmDlg->Destroy();
            wxDELETE(cmDlg);
            DoGUI();
            break;

        case wxID_ABOUT:
            wxMessageDialog(this, wxT("Matrix - Demo\n(C) 2008-2010\n\nhttp://sourceforge.net/projects/wxecmath/"), wxT("About..."), wxOK|wxICON_INFORMATION).ShowModal();
            break;
    }
}

void wxMatrixFrame::OnButtonClick(wxCommandEvent& event)
{
    switch (event.GetId())
    {
        case ID_FITBUTTON:
            m_plot->Refresh();
            m_plot->FitYAxis();
            m_plot->Refresh();
            break;
    }
}

void wxMatrixFrame::OnScrollClick(wxScrollEvent& event)
{
    m_plot->GetAxis(false)->MaxValue = event.GetPosition();
    m_plot->Refresh();
}

void wxMatrixFrame::OnMousePlotEvent(wxMouseEvent& event)
{
    this->SetLabel(wxString::Format(wxT("Matrix - ( %.0f , %.0f )"), m_plot->XToValue(event.GetX()), m_plot->YToValue(event.GetY())));
    event.Skip();
}

void wxMatrixFrame::OnMouseViewEvent(wxMouseEvent& event)
{
    int x = event.GetX(), y = event.GetY();
    this->SetLabel(wxString::Format(wxT("Matrix - X=%d, Y=%d, R=%d, G=%d, B=%d"), x, y, m_vision.GetImage()->GetRed(x,y), m_vision.GetImage()->GetGreen(x,y), m_vision.GetImage()->GetBlue(x,y) ));
    event.Skip();
}
