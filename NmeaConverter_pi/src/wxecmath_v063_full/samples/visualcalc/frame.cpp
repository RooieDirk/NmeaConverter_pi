
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

#include "frame.h"

    BEGIN_EVENT_TABLE(wxCalcFrame, wxFrame)
        EVT_MENU(wxID_ANY, wxCalcFrame::OnMenuClick)

        EVT_CLOSE(wxCalcFrame::OnCloseEvent)

        EVT_COMBOBOX(ID_FUNCLIST, wxCalcFrame::OnFunctionSelected)
        EVT_COMBOBOX(ID_CONSTS, wxCalcFrame::OnConstantSelected)
        EVT_COMBOBOX(ID_TRIGO, wxCalcFrame::OnTrigoSelected)

        EVT_CHECKBOX(ID_ARCBOX, wxCalcFrame::OnCheckBoxClick)
        EVT_CHECKBOX(ID_HYPERBOLIC, wxCalcFrame::OnCheckBoxClick)

        //EVT_TEXT_ENTER(ID_FORMULA, wxCalcFrame::OnEqualClick)

        EVT_BUTTON(wxID_ANY, wxCalcFrame::OnButtonClick)
    END_EVENT_TABLE()


//-------------- CONSTRUCTOR ---------------

wxCalcFrame::wxCalcFrame(const bool DoShow, bool RequireCompact):wxFrame(NULL, -1, wxT("wxEcEngine demo"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)
{
    //---------- Fonts

    #ifdef __WINDOWS__
        wxSize ButtonSize = wxSize(35,35);
    #else
        wxSize ButtonSize = wxSize(40,40);
    #endif
    wxFont ButtonFont(*wxNORMAL_FONT);
        ButtonFont.SetWeight(wxFONTWEIGHT_BOLD);

    //---------- Combo boxes !

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    //wxBoxSizer *VSizer;
    VSizer = new wxBoxSizer(wxVERTICAL);

    //wxBoxSizer *ComboSizer;
    ComboSizer = new wxBoxSizer(wxHORIZONTAL);

    ComboFunctions = new wxComboBox(this, ID_FUNCLIST, wxT("Functions"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY);
        ComboFunctions->Append(wxT("- Functions -"));
        ComboFunctions->Append(wxT("abs"));
        ComboFunctions->Append(wxT("ceil"));
        ComboFunctions->Append(wxT("exp"));
        ComboFunctions->Append(wxT("hvi"));
        ComboFunctions->Append(wxT("int"));
        ComboFunctions->Append(wxT("inv"));
        ComboFunctions->Append(wxT("ln"));
        ComboFunctions->Append(wxT("log"));
        ComboFunctions->Append(wxT("sgn"));
        ComboFunctions->Append(wxT("sqr"));
        ComboFunctions->Append(wxT("sqrt"));
        ComboFunctions->Append(wxT("tri"));

        ComboFunctions->Append(wxEmptyString);
        ComboFunctions->Append(wxT("- Trigonometry -"));
        ComboFunctions->Append(wxT("acos"));
        ComboFunctions->Append(wxT("acsh"));
        ComboFunctions->Append(wxT("asin"));
        ComboFunctions->Append(wxT("asnh"));
        ComboFunctions->Append(wxT("atan"));
        ComboFunctions->Append(wxT("atnh"));
        ComboFunctions->Append(wxT("cos"));
        ComboFunctions->Append(wxT("cosh"));
        ComboFunctions->Append(wxT("sin"));
        ComboFunctions->Append(wxT("sinc"));
        ComboFunctions->Append(wxT("sinh"));
        ComboFunctions->Append(wxT("tan"));
        ComboFunctions->Append(wxT("tanh"));
        ComboFunctions->SetSelection(0);
        ComboFunctions->SetMinSize(wxSize(110,-1));

    ComboSizer->Add(ComboFunctions, 0, wxALL, 5);

    ComboConstants = new wxComboBox(this, ID_CONSTS, wxT("Constants"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY|wxCB_SORT);
    ComboConstants->SetMinSize(wxSize(160,-1));

    ComboSizer->Add(ComboConstants, 0, wxALL, 5);

    ComboTrigoMode = new wxComboBox(this, ID_TRIGO, wxT("Trigonometry"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY);
        ComboTrigoMode->Append(wxT("rad"));
        ComboTrigoMode->Append(wxT("deg"));
        ComboTrigoMode->Append(wxT("grad"));
        ComboTrigoMode->SetSelection(0);
    ComboTrigoMode->SetMinSize(wxSize(60,-1));

    ComboSizer->Add(ComboTrigoMode, 0, wxALL, 5);

    VSizer->Add(ComboSizer, 0, wxALIGN_CENTER|wxALL, 5);

    //---------- Formula editor !

    //wxBoxSizer* FormulaSizer;
    FormulaSizer = new wxBoxSizer(wxHORIZONTAL);

    ButtonClr = new wxButton(this, ID_CLR, wxT("Clr"), wxDefaultPosition, ButtonSize, 0);
    ButtonClr->SetForegroundColour(wxColour(255, 0, 0));

    FormulaSizer->Add(ButtonClr, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);

    //wxBoxSizer* FormulaSizerC1;
    FormulaSizerC1 = new wxBoxSizer(wxVERTICAL);

    CheckArc = new wxCheckBox(this, ID_ARCBOX, wxT("ArcTrigo"), wxDefaultPosition, wxDefaultSize, 0);

    FormulaSizerC1->Add(CheckArc, 0, wxALL, 5);

    CheckHyperbolic = new wxCheckBox(this, ID_HYPERBOLIC, wxT("Hyperbolic"), wxDefaultPosition, wxDefaultSize, 0);

    FormulaSizerC1->Add(CheckHyperbolic, 0, wxALL, 5);

    FormulaSizer->Add(FormulaSizerC1, 0, 0, 5);

    wxBoxSizer* FormulaSizerC2;
    FormulaSizerC2 = new wxBoxSizer(wxHORIZONTAL);

    EditFormula = new wxTextCtrl(this, ID_FORMULA, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH|wxTE_PROCESS_TAB);
    FormulaSizerC2->Add(EditFormula, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    FormulaSizer->Add(FormulaSizerC2, 1, wxEXPAND, 5);

    ButtonEqual = new wxButton(this, ID_EQUAL, wxT("="), wxDefaultPosition, ButtonSize, 0);
    ButtonEqual->SetForegroundColour(wxColour(255, 0, 0));
    
    FormulaSizer->Add(ButtonEqual, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);

    VSizer->Add(FormulaSizer, 0, wxEXPAND|wxLEFT|wxRIGHT, 5);

    //---------- Grid sizer !

    //wxGridSizer *GridSizer;
    GridSizer = new wxGridSizer(GRID_ROWS, GRID_COLS, 0, 0);

    ButtonCall = new wxButton(this, ID_CALL, wxT("Call"), wxDefaultPosition, ButtonSize, 0);
    ButtonCall->SetForegroundColour(wxColour(255, 0, 0));

    ButtonSin = new wxButton(this, ID_SIN, wxT("sin"), wxDefaultPosition, ButtonSize, 0);
    ButtonSin->SetForegroundColour(wxColour(128, 128, 64));

    ButtonExp = new wxButton(this, ID_EXP, wxT("exp"), wxDefaultPosition, ButtonSize, 0);
    ButtonExp->SetForegroundColour(wxColour(128, 128, 64));

    ButtonLn = new wxButton(this, ID_LN, wxT("ln"), wxDefaultPosition, ButtonSize, 0);
    ButtonLn->SetForegroundColour(wxColour(128, 128, 64));

    ButtonBracketOpen = new wxButton(this, ID_BRACKETOPEN, wxT("("), wxDefaultPosition, ButtonSize, 0);
    ButtonBracketOpen->SetForegroundColour(wxColour(192, 0, 192));

    Button7 = new wxButton(this, ID_7, wxT("7"), wxDefaultPosition, ButtonSize, 0);
    Button7->SetForegroundColour(wxColour(0, 0, 0));

    Button8 = new wxButton(this, ID_8, wxT("8"), wxDefaultPosition, ButtonSize, 0);
    Button8->SetForegroundColour(wxColour(0, 0, 0));

    Button9 = new wxButton(this, ID_9, wxT("9"), wxDefaultPosition, ButtonSize, 0);
    Button9->SetForegroundColour(wxColour(0, 0, 0));

    ButtonDiv = new wxButton(this, ID_DIV, wxT("/"), wxDefaultPosition, ButtonSize, 0);
    ButtonDiv->SetForegroundColour(wxColour(0, 0, 255));

    ButtonSet = new wxButton(this, ID_SET, wxT("Set"), wxDefaultPosition, ButtonSize, 0);
    ButtonSet->SetForegroundColour(wxColour(255, 0, 0));

    ButtonCos = new wxButton(this, ID_COS, wxT("cos"), wxDefaultPosition, ButtonSize, 0);
    ButtonCos->SetForegroundColour(wxColour(128, 128, 64));

    ButtonPow10 = new wxButton(this, ID_POW10, wxT("10^"), wxDefaultPosition, ButtonSize, 0);
    ButtonPow10->SetForegroundColour(wxColour(128, 128, 64));

    ButtonLog = new wxButton(this, ID_LOG, wxT("log"), wxDefaultPosition, ButtonSize, 0);
    ButtonLog->SetForegroundColour(wxColour(128, 128, 64));

    ButtonBracketClose = new wxButton(this, ID_BRACKETCLOSE, wxT(")"), wxDefaultPosition, ButtonSize, 0);
    ButtonBracketClose->SetForegroundColour(wxColour(192, 0, 192));

    Button4 = new wxButton(this, ID_4, wxT("4"), wxDefaultPosition, ButtonSize, 0);
    Button4->SetForegroundColour(wxColour(0, 0, 0));

    Button5 = new wxButton(this, ID_5, wxT("5"), wxDefaultPosition, ButtonSize, 0);
    Button5->SetForegroundColour(wxColour(0, 0, 0));

    Button6 = new wxButton(this, ID_6, wxT("6"), wxDefaultPosition, ButtonSize, 0);
    Button6->SetForegroundColour(wxColour(0, 0, 0));

    ButtonMult = new wxButton(this, ID_MULT, wxT("*"), wxDefaultPosition, ButtonSize, 0);
    ButtonMult->SetForegroundColour(wxColour(0, 0, 255));

    ButtonMP = new wxButton(this, ID_MP, wxT("M+"), wxDefaultPosition, ButtonSize, 0);
    ButtonMP->SetForegroundColour(wxColour(255, 0, 0));

    ButtonTan = new wxButton(this, ID_TAN, wxT("tan"), wxDefaultPosition, ButtonSize, 0);
    ButtonTan->SetForegroundColour(wxColour(128, 128, 64));

    ButtonPower = new wxButton(this, ID_POWER, wxT("^"), wxDefaultPosition, ButtonSize, 0);
    ButtonPower->SetForegroundColour(wxColour(128, 128, 64));

    ButtonSq2 = new wxButton(this, ID_SQ2, wxT("sq2"), wxDefaultPosition, ButtonSize, 0);
    ButtonSq2->SetForegroundColour(wxColour(128, 128, 64));

    ButtonSqrt = new wxButton(this, ID_SQRT, wxT("sqrt"), wxDefaultPosition, ButtonSize, 0);
    ButtonSqrt->SetForegroundColour(wxColour(128, 128, 64));

    Button1 = new wxButton(this, ID_1, wxT("1"), wxDefaultPosition, ButtonSize, 0);
    Button1->SetForegroundColour(wxColour(0, 0, 0));

    Button2 = new wxButton(this, ID_2, wxT("2"), wxDefaultPosition, ButtonSize, 0);
    Button2->SetForegroundColour(wxColour(0, 0, 0));

    Button3 = new wxButton(this, ID_3, wxT("3"), wxDefaultPosition, ButtonSize, 0);
    Button3->SetForegroundColour(wxColour(0, 0, 0));

    ButtonPlus = new wxButton(this, ID_PLUS, wxT("+"), wxDefaultPosition, ButtonSize, 0);
    ButtonPlus->SetForegroundColour(wxColour(0, 0, 255));

    ButtonDef = new wxButton(this, ID_DEF, wxT("Def"), wxDefaultPosition, ButtonSize, 0);
    ButtonDef->SetForegroundColour(wxColour(255, 0, 0));

    ButtonPi = new wxButton(this, ID_PI, wxT("pi"), wxDefaultPosition, ButtonSize, 0);
    ButtonPi->SetForegroundColour(wxColour(0, 192, 0));

    ButtonPercent = new wxButton(this, ID_PERCENT, wxT("%"), wxDefaultPosition, ButtonSize, 0);
    ButtonPercent->SetForegroundColour(wxColour(0, 192, 0));

    ButtonE = new wxButton(this, ID_E, wxT("e"), wxDefaultPosition, ButtonSize, 0);
    ButtonE->SetForegroundColour(wxColour(0, 192, 0));

    ButtonReverse = new wxButton(this, ID_REVERSE, wxT("1/x"), wxDefaultPosition, ButtonSize, 0);
    ButtonReverse->SetForegroundColour(wxColour(128, 128, 64));

    Button0 = new wxButton(this, ID_0, wxT("0"), wxDefaultPosition, ButtonSize, 0);
    Button0->SetForegroundColour(wxColour(0, 0, 0));

    ButtonComma = new wxButton(this, ID_COMMA, wxT(","), wxDefaultPosition, ButtonSize, 0);
    ButtonComma->SetForegroundColour(wxColour(128, 128, 128));

    ButtonPlusMinus = new wxButton(this, ID_PLUSMINUS, wxT("+/-"), wxDefaultPosition, ButtonSize, 0);
    ButtonPlusMinus->SetForegroundColour(wxColour(128, 128, 128));

    ButtonMinus = new wxButton(this, ID_MINUS, wxT("-"), wxDefaultPosition, ButtonSize, 0);
    ButtonMinus->SetForegroundColour(wxColour(0, 0, 255));

        wxButton* GridButtonArray[36] = {   ButtonCall, ButtonSin, ButtonExp, ButtonLn, ButtonBracketOpen, Button7,
                                            Button8, Button9, ButtonDiv, ButtonSet, ButtonCos, ButtonPow10, ButtonLog,
                                            ButtonBracketClose, Button4, Button5, Button6, ButtonMult, ButtonMP,
                                            ButtonTan, ButtonPower, ButtonSq2, ButtonSqrt, Button1, Button2, Button3,
                                            ButtonPlus, ButtonDef, ButtonPi, ButtonPercent, ButtonE, ButtonReverse,
                                            Button0, ButtonComma, ButtonPlusMinus, ButtonMinus
                                        };
        int i;
        for (i=0 ; i<36 ; i++)
        {
            GridSizer->Add(GridButtonArray[i], 0, wxALL, 5);
            GridButtonArray[i]->SetFont(ButtonFont);
        }
        ButtonClr->SetFont(ButtonFont);
        ButtonEqual->SetFont(ButtonFont);

    VSizer->Add(GridSizer, 1, wxALL|wxEXPAND, 5);

    this->SetSizer(VSizer);

    //---------- Menu bar !

    MenuBar = new wxMenuBar();

    MenuEdit = new wxMenu();
        MenuCopyResult = new wxMenuItem(MenuEdit, MENU_COPYRESULT, wxT("Copy &result"), wxT("Copy the latest computed result"));
        MenuEdit->Append(MenuCopyResult);
        MenuCopyFormula = new wxMenuItem(MenuEdit, MENU_COPYFORMULA, wxT("Copy &formula"),  wxT("Copy the latest evaluated formula"));
        MenuEdit->Append(MenuCopyFormula);
        MenuPaste = new wxMenuItem(MenuEdit, MENU_PASTE, wxT("&Paste"), wxT("Get data from the clipboard"));
        MenuEdit->Append(MenuPaste);
        MenuEdit->AppendSeparator();
        MenuDebug = new wxMenuItem(MenuEdit, MENU_DEBUG, wxT("&Debug"), wxT("Check the latest computation"));
        MenuEdit->Append(MenuDebug);
        MenuEdit->AppendSeparator();
        MenuQuit = new wxMenuItem(MenuEdit, MENU_QUIT, wxT("&Quit"));
        MenuEdit->Append(MenuQuit);
    MenuBar->Append(MenuEdit, wxT("&Edit"));

    MenuTools = new wxMenu();
        MenuSimplify = new wxMenuItem(MenuTools, MENU_SIMPLIFY, wxT("&Simplify"), wxT("Make the corrections needed"));
        MenuTools->Append(MenuSimplify);
        MenuValidate = new wxMenuItem(MenuTools, MENU_ISVALID, wxT("&Is valid ?"), wxT("Show you if it will be rejected"));
        MenuTools->Append(MenuValidate);
        MenuCloseBrackets = new wxMenuItem(MenuTools, MENU_CLOSEBRACKETS, wxT("&Close all brackets"), wxT("To make your formula acceptable"));
        MenuTools->Append(MenuCloseBrackets);
        MenuTools->AppendSeparator();
        MenuResetConst = new wxMenuItem(MenuTools, MENU_RESETCONST, wxT("&Reset all constants"), wxT("Go back to default constants"));
        MenuTools->Append(MenuResetConst);
        MenuTools->AppendSeparator();
        MenuCompact = new wxMenuItem(MenuTools, MENU_COMPACT, wxT("&Use a compact calculator"), wxT("A more friendly interface maybe"), wxITEM_CHECK);
        MenuTools->Append(MenuCompact);
    MenuBar->Append(MenuTools, wxT("&Tools"));

    MenuQuestionMark = new wxMenu();
        MenuAbout = new wxMenuItem(MenuQuestionMark, MENU_ABOUT, wxT("&About"));
        MenuQuestionMark->Append(MenuAbout);
    MenuBar->Append(MenuQuestionMark, wxT("&?"));

    this->SetMenuBar(MenuBar);

    //---------- StatusBar !

    StatusBar = this->CreateStatusBar(2, wxST_SIZEGRIP);

    //---------- Initialization

    Calc = new wxEcEngine();
    Calc->UseDebug(true);
    Memory = 0;

    //---------- Final !

    UpdateUI();
    EditFormula->SetFocus();
    this->SetIcon(wxIcon(icon_xpm));
    this->Layout();
    this->Fit();
    this->Center();
    #ifdef __WINDOWS__
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    #endif
    if (RequireCompact)
    {
        MenuCompact->Check(true);
        Compact(true);
    }
    if (DoShow)
        this->Show(true);
}

wxCalcFrame::~wxCalcFrame()
{
    //wxDELETE(Calc);
}

void wxCalcFrame::Compact(bool DoCompact)
{
    size_t Index;
    if (DoCompact)
    {
        VSizer->Hide(ComboSizer);
        FormulaSizer->Hide(FormulaSizerC1);
    } else {
        VSizer->Show(ComboSizer);
        FormulaSizer->Show(FormulaSizerC1);
    }
    for (Index=0 ; Index<GRID_ROWS*GRID_COLS ; Index++)
        GridSizer->GetItem(Index)->SetBorder((1-DoCompact)*5);

    this->Layout();
    this->Fit();
}

void wxCalcFrame::ShowMessage(wxString Message, int IconType)
{
    wxMessageDialog(this, Message, wxT("Information"), wxOK|IconType).ShowModal();
}

void wxCalcFrame::UpdateUI()
{
    Calc->ListAllConstants((wxControlWithItems*)ComboConstants);
    ComboTrigoMode->SetSelection(Calc->GetTrigonometricMode());
    ButtonCos->SetLabel(TranslateTrigoFunction(wxT("cos")));
    ButtonSin->SetLabel(TranslateTrigoFunction(wxT("sin")));
    ButtonTan->SetLabel(TranslateTrigoFunction(wxT("tan")));
}


//------------------ MENU ------------------

    static unsigned int CountChar(wxString *Input, wxChar What)
    {
        size_t i;
        unsigned int Result = 0;
        for (i=0 ; i<Input->Len() ; i++)
            if (Input->GetChar(i) == What)
                Result++;
        return Result;
    }

    bool wxCalcFrame::CopyToClipboard(wxString Content)
    {
        bool Result = false;
        if (Content.Len() > 0)
            if (wxTheClipboard->Open())
            {
                wxTheClipboard->SetData(new wxTextDataObject(Content));
                //Info: the pointer must not be wxDeleted because it is a locator for a later use
                wxTheClipboard->Close();
                Result = true;
            }
        if (Result)
            ShowMessage(wxString::Format(wxT("'%s' has been copied into the clipboard."), Content.c_str()));
        else
            ShowMessage(wxT("There is no data to copy."), wxICON_ERROR);
        return Result;
    }

void wxCalcFrame::OnMenuClick(wxCommandEvent& event)
{
    bool HasSomething;
    int BrDelta, i;
    wxString Buffer;
    wxTextDataObject Content;
    wxArrayString LogData;
    wxAboutDialogInfo About;
    wxDebugWindow *DebugDialog = NULL;

    switch (event.GetId())
    {
        case MENU_COPYRESULT:
            CopyToClipboard(wxString::Format(wxT("%f"), Calc->GetLastResult()));
            break;

        case MENU_COPYFORMULA:
            CopyToClipboard(Calc->GetFormula());
            break;

        case MENU_PASTE:
            HasSomething = false;
            Buffer.Empty();
            if (wxTheClipboard->Open())
            {
                if (wxTheClipboard->IsSupported(wxDF_TEXT))
                {
                    wxTheClipboard->GetData(Content);
                    Buffer = Content.GetText();
                    //-- We get the first line only :)
                    if (Buffer.Find(wxT("\r")) != wxNOT_FOUND)
                        Buffer = Buffer.BeforeFirst(wxT('\r'));
                    if (Buffer.Find(wxT("\n")) != wxNOT_FOUND)
                        Buffer = Buffer.BeforeFirst(wxT('\n'));
                    HasSomething = (Buffer.Len() > 0);
                }
                wxTheClipboard->Close();
            }
            if (HasSomething)
            {
                EditFormula->SetValue(Buffer);
                EditFormula->SetInsertionPointEnd();
            }
            else
                ShowMessage(wxT("The clipboard does not contain a valid content."), wxICON_ERROR);   
            break;

        case MENU_DEBUG:
            #ifdef wxECM_USEDEBUG
                DebugDialog = new wxDebugWindow(this);
                if (Calc->GetFormula().Len() > 0)
                    DebugDialog->labelFormula->SetLabel(wxString::Format(wxT("Formula : %s = %f"), Calc->GetFormula().c_str(), Calc->GetLastResult()));
                LogData = Calc->GetLog();
                DebugDialog->memoDebug->Clear();
                for (i=0 ; i<(int)LogData.GetCount() ; i++)
                    DebugDialog->memoDebug->AppendText(wxString::Format(wxT("%s\r\n"), LogData.Item(i).c_str()));
                DebugDialog->memoDebug->AppendText(wxString::Format(wxT("\r\n\r\nResult : %f\r\nState : %s\r\nTip : %s\r\n\r\n"), Calc->GetLastResult(), Calc->TranslateError(Calc->GetLastError()).c_str(), Calc->GetIndicator().c_str()));
                DebugDialog->ShowModal();
                DebugDialog->Destroy();
                wxDELETE(DebugDialog);
            #else
                wxMessageDialog(NULL, wxT("This feature is not available when \"wxECM_USEDEBUG\" is not defined in \"ec_defs.h\"."), wxT("Error"), wxOK|wxICON_ERROR).ShowModal();
            #endif
            break;

        case MENU_QUIT:
            this->Close();
            break;

        case MENU_SIMPLIFY:
            Buffer = GetCurrentFormula();
            Calc->Simplify(&Buffer);
            EditFormula->SetValue(Buffer);
            EditFormula->SetInsertionPointEnd();
            StatusBar->SetStatusText(wxT("Simplification done"), STATUS_INFO);
            break;

        case MENU_ISVALID:
            Buffer = GetCurrentFormula();
            if (Calc->IsValid(&Buffer))
                ShowMessage(wxT("Your formula will be accepted."));
            else
                ShowMessage(wxT("The formula you are currently typing does not appear to be valid."), wxICON_ERROR);
            break;

        case MENU_CLOSEBRACKETS:
            Buffer = GetCurrentFormula();

            //-- Action !
            BrDelta = CountChar(&Buffer, '(') - CountChar(&Buffer, ')');
            if (BrDelta > 0)
                for (i=0 ; i<BrDelta ; i++)
                    Buffer = Buffer.Append(wxT(")"));
            if (BrDelta < 0)
                for (i=0 ; i<-BrDelta ; i++)
                    Buffer = wxString::Format(wxT("(%s"), Buffer.c_str());
            EditFormula->SetValue(Buffer);
            EditFormula->SetInsertionPointEnd();
            if (BrDelta < 0)
                BrDelta = -BrDelta;
            StatusBar->SetStatusText(wxString::Format(wxT("%d brackets added"), BrDelta), STATUS_INFO);
            break;

        case MENU_RESETCONST:
            Calc->ResetConstants();
            UpdateUI();
            StatusBar->SetStatusText(wxT("Constants reinitialized"), STATUS_INFO);
            break;

        case MENU_COMPACT:
            Compact(MenuCompact->IsChecked());
            break;

        case MENU_ABOUT:
            About.SetName(wxECD_SOFTWARE);
            About.SetIcon(wxIcon(icon_xpm));
            About.SetVersion(wxString::Format(wxT("v%s"), wxECD_VERSION));
            About.SetCopyright(wxT("Copyright © 2008-2010, ecrucru"));
            About.SetDescription(wxT(" "));
            About.SetWebSite(wxECD_URL);
            #if wxUSE_UNICODE
                About.SetLicence(wxString::Format(wxT("Compiled with %s Unicode."), wxVERSION_STRING));
            #else
                About.SetLicence(wxString::Format(wxT("Compiled with %s."), wxVERSION_STRING));
            #endif
            wxAboutBox(About);
            break;

    }
}

void wxCalcFrame::OnCloseEvent(wxCloseEvent& event)
{
    this->Destroy();
}


//----------------- COMBOX -----------------

void wxCalcFrame::OnFunctionSelected(wxCommandEvent& event)
{
    wxString Selection = ComboFunctions->GetValue();
    if ((Selection.Len()>0) && (!Selection.StartsWith(wxT("-"))))
    {
        ApplyFunction(Selection);
        ComboFunctions->SetSelection(0);    //it will generate a new event, but it will be ignored by the conditions
    }
}

void wxCalcFrame::OnConstantSelected(wxCommandEvent& event)
{
    wxString Selection = ComboConstants->GetValue().BeforeFirst(wxT(' '));
    if (Selection != wxEmptyString)
    {
        ApplyString(Selection);
        ComboConstants->SetSelection(wxNOT_FOUND);
    }
}

void wxCalcFrame::OnTrigoSelected(wxCommandEvent& event)
{
    int Modus = ComboTrigoMode->GetSelection();
    if ((0<=Modus) && (Modus<=2))
        Calc->SetTrigonometricMode(Modus);
}

void wxCalcFrame::OnCheckBoxClick(wxCommandEvent& event)
{
    UpdateUI();
}


//----------------- EVENTS -----------------

    void wxCalcFrame::ApplyBracket(wxChar Car)
    {
        long From, To;
        EditFormula->GetSelection(&From, &To);
        if (From != To)
        {
            EditFormula->Replace(From, To, wxString::Format(wxT("(%s)"), EditFormula->GetStringSelection().c_str()));
            EditFormula->SetFocus();
        } else
            ApplyChar(Car);
    }

    void wxCalcFrame::ApplyChar(wxChar Car)
    {
        ApplyString(Car);
    }

    void wxCalcFrame::ApplyFunction(wxString SelFunc)
    {
        wxString Buffer;
        long From, To;

        EditFormula->GetSelection(&From, &To);
        if (From != To)
        {
            EditFormula->Replace(From, To, wxString::Format(wxT("%s(%s)"), SelFunc.c_str(), EditFormula->GetStringSelection().c_str()));
            EditFormula->SetFocus();
        } else {
            Buffer = GetCurrentFormula();
            if ((Buffer.Last() == wxT(')')) || (wxString(wxECD_NUMERIC).Find(Buffer.Last()) != wxNOT_FOUND))
                Buffer = Buffer.Append(wxT("*"));
            Buffer = Buffer.Append(SelFunc).Append(wxT("("));
            EditFormula->SetValue(Buffer);
            EditFormula->SetFocus();
            EditFormula->SetInsertionPointEnd();
        }
    }

    void wxCalcFrame::ApplyOperator(wxChar Car)
    {
        long From, To;

        EditFormula->GetSelection(&From, &To);
        if (From != To) {
            EditFormula->Replace(From, To, wxString::Format(wxT("(%s)%c"), EditFormula->GetStringSelection().c_str(), Car));
            EditFormula->SetFocus();
        } else
            ApplyChar(Car);
    }

    void wxCalcFrame::ApplyString(wxString Str)
    {
        wxString Buffer;
        long From, To;

        EditFormula->GetSelection(&From, &To);
        if (From != To)
        {
            EditFormula->Replace(From, To, Str);
            EditFormula->SetFocus();
        } else {
            Buffer = GetCurrentFormula().Append(Str);
            EditFormula->SetValue(Buffer);
            EditFormula->SetFocus();
            EditFormula->SetInsertionPointEnd();
        }
    }

    wxString wxCalcFrame::GetCurrentFormula()
    {
        wxString Buffer = EditFormula->GetValue();
        if (Buffer.Find(wxT('=')) != wxNOT_FOUND)
            Buffer = Buffer.BeforeFirst(wxT('=')).Trim(false).Trim(true);
        return Buffer;
    }

    bool wxCalcFrame::IsArcTrigo()
    {
        return (CheckArc->GetValue() == true);
    }

    bool wxCalcFrame::IsHyperbolic()
    {
        return (CheckHyperbolic->GetValue() == true);
    }

    wxString wxCalcFrame::TranslateTrigoFunction(wxString Function)
    {
        if (IsHyperbolic())
            return (!IsArcTrigo() ? Function+wxT("h") : wxString::Format(wxT("a%c%ch"), Function.GetChar(0), Function.GetChar(2)));
        else
            return (!IsArcTrigo() ? Function : wxT("a")+Function);
    }

void wxCalcFrame::OnButtonClick(wxCommandEvent& event)
{
    wxString Buffer, MemoryName, NewConstantName;
    double Value, ValueOld, ValueNew;
    long From, To;

    switch (event.GetId())
    {
        case ID_CLR:
            StatusBar->SetStatusText(wxEmptyString, STATUS_INFO);
            EditFormula->SetValue(wxEmptyString);
            EditFormula->SetFocus();
            //Memory = 0;
            //Calc->DeleteConstant(MEMORY_NAME);
            UpdateUI();
            break;

        case ID_EQUAL:
            Buffer = GetCurrentFormula();
            Calc->Reset(true, false);
            Calc->SetFormula(Buffer);
            if (Calc->GetLastError() == wxECE_NOERROR)
                EditFormula->SetValue(wxString::Format(wxT("%s = %f"), Calc->GetFormula().c_str(), Calc->Compute()));
            else
                EditFormula->SetValue(Buffer);
            EditFormula->SetFocus();
            EditFormula->SetInsertionPointEnd();
            UpdateUI();
            StatusBar->SetStatusText(Calc->TranslateError(Calc->GetLastError()), STATUS_INFO);
            break;

        case ID_CALL:
            ApplyString(MEMORY_NAME);
            break;

        case ID_SIN:
            ApplyFunction(TranslateTrigoFunction(wxT("sin")));
            break;

        case ID_EXP:
            ApplyFunction(wxT("exp"));
            break;

        case ID_LN:
            ApplyFunction(wxT("ln"));
            break;

        case ID_BRACKETOPEN:
            ApplyBracket(wxT('('));
            break;

        case ID_7:
            ApplyChar(wxT('7'));
            break;

        case ID_8:
            ApplyChar(wxT('8'));
            break;

        case ID_9:
            ApplyChar(wxT('9'));
            break;

        case ID_DIV:
            ApplyOperator(wxT('/'));
            break;

        case ID_SET:
            Value = Calc->GetLastResult();
            Calc->SetConstant(MEMORY_NAME, Value);        // will redefine it implicitely
            UpdateUI();
            StatusBar->SetStatusText(wxString::Format(wxT("%f stored as '%s'"), Value, MEMORY_NAME), STATUS_INFO);
            break;

        case ID_COS:
            ApplyFunction(TranslateTrigoFunction(wxT("cos")));
            break;

        case ID_POW10:
            ApplyFunction(wxT("10^"));
            break;

        case ID_LOG:
            ApplyFunction(wxT("log"));
            break;

        case ID_BRACKETCLOSE:
            ApplyBracket(wxT(')'));
            break;

        case ID_4:
            ApplyChar(wxT('4'));
            break;

        case ID_5:
            ApplyChar(wxT('5'));
            break;

        case ID_6:
            ApplyChar(wxT('6'));
            break;

        case ID_MULT:
            ApplyOperator(wxT('*'));
            break;

        case ID_MP:
            MemoryName = MEMORY_NAME;
            Calc->GetConstant(MemoryName, &ValueOld);
            ValueNew = Calc->GetLastResult();
            Calc->SetConstant(MEMORY_NAME, ValueOld + ValueNew);
            UpdateUI();
            StatusBar->SetStatusText(wxString::Format(wxT("%.3f + %.3f = %f"), ValueOld, ValueNew, ValueOld+ValueNew), STATUS_INFO);
            break;

        case ID_TAN:
            ApplyFunction(TranslateTrigoFunction(wxT("tan")));
            break;

        case ID_POWER:
            ApplyOperator(wxT('^'));
            break;

        case ID_SQ2:
            ApplyFunction(wxT("sqr"));
            break;

        case ID_SQRT:
            ApplyFunction(wxT("sqrt"));
            break;

        case ID_1:
            ApplyChar(wxT('1'));
            break;

        case ID_2:
            ApplyChar(wxT('2'));
            break;

        case ID_3:
            ApplyChar(wxT('3'));
            break;

        case ID_PLUS:
            ApplyOperator(wxT('+'));
            break;

        case ID_DEF:
            Value = Calc->GetLastResult();
            NewConstantName = wxGetTextFromUser(wxString::Format(wxT("Constant's name for '%f' :"), Value), wxT("(Re)define a constant"), wxEmptyString);
            if (NewConstantName != wxEmptyString)
            {
                Calc->SetConstant(NewConstantName, Value);
                UpdateUI();
                StatusBar->SetStatusText(wxString::Format(wxT("'%s' set as %f"), NewConstantName.c_str(), Value), STATUS_INFO);
            }
            break;

        case ID_PI:
            ApplyString(wxT("pi"));
            break;

        case ID_PERCENT:
            ApplyString(wxT("*percent"));
            break;

        case ID_E:
            ApplyChar(wxT('e'));
            break;

        case ID_REVERSE:
            ApplyFunction(wxT("inv"));
            break;

        case ID_0:
            ApplyChar(wxT('0'));
            break;

        case ID_COMMA:
            ApplyChar(wxT('.'));
            break;

        case ID_PLUSMINUS:
            EditFormula->GetSelection(&From, &To);
            if (From != To)
            {
                Buffer = EditFormula->GetStringSelection();
                if (Buffer.StartsWith(wxT("-")))
                    EditFormula->Replace(From, To, Buffer.Right(1));
                else
                    EditFormula->Replace(From, To, wxString::Format(wxT("-%s"), Buffer.c_str()));
            } else
                ApplyChar(wxT('-'));
            EditFormula->SetFocus();
            break;

        case ID_MINUS:
            ApplyOperator(wxT('-'));
            break;
    }
}
