
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

#include "debugwin.h"

//------------------------------------------


wxDebugWindow::wxDebugWindow(wxWindow* Parent)
            : wxDialog(Parent, -1, wxT("Debug window"), wxDefaultPosition, wxSize(400, 350), wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxTAB_TRAVERSAL)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticBoxSizer *BoxGroup = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Output generated")), wxVERTICAL);
            labelFormula = new wxStaticText(this, wxID_ANY, wxT("Formula : ~"));
            BoxGroup->Add(labelFormula, 0, wxALL|wxEXPAND, 5);
            memoDebug = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_NOHIDESEL|wxTE_READONLY);
            BoxGroup->Add(memoDebug, 1, wxALL|wxEXPAND, 5);
        VSizer->Add(BoxGroup, 1, wxALL|wxEXPAND, 10);

        ButtonBar = new wxStdDialogButtonSizer();
            ButtonBarOK = new wxButton(this, wxID_OK);
            ButtonBar->AddButton(ButtonBarOK);
        ButtonBar->Realize();
    VSizer->Add(ButtonBar, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 10);

    this->SetSizer(VSizer);
    this->Layout();
    this->Center();
}

wxDebugWindow::~wxDebugWindow()
{
}
