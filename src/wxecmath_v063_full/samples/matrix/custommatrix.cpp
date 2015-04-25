
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

#include "custommatrix.h"

//------------------------------------------

wxCustomMatrixDialog::wxCustomMatrixDialog(wxWindow* parent)
                    : wxDialog(parent, wxID_ANY, wxT("Custom matrix"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
    int i;

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
        wxGridSizer *GSizer = new wxGridSizer(5, 5, 2, 2);
            for (i=0 ; i<25 ; i++)
            {
                m_edit[i] = new wxTextCtrl(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(50,-1));
                GSizer->Add(m_edit[i], 0, wxALL, 0);
            }
        HSizer->Add(GSizer, 1, wxALL|wxEXPAND, 10);

        wxBoxSizer *BSizer = new wxBoxSizer(wxVERTICAL);
            BSizer->Add(0, 0, 1, wxEXPAND, 5);
            m_buttonCancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
            BSizer->Add(m_buttonCancel, 0, wxBOTTOM|wxRIGHT, 10);
            m_buttonOk = new wxButton(this, wxID_OK, wxT("&OK"));
            BSizer->Add(m_buttonOk, 0, wxBOTTOM|wxRIGHT, 10);
        HSizer->Add(BSizer, 0, wxEXPAND, 10);
    this->SetSizer(HSizer);

    this->Layout();
    this->Fit();
    this->Center();
    m_edit[12]->SetValue(wxT("1"));
    m_edit[12]->SetFocus();
}

wxCustomMatrixDialog::~wxCustomMatrixDialog()
{
}
