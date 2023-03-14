///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/clrpicker.h>
#include <wx/slider.h>
#include <wx/radiobox.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

#include "wxWTranslateCatalog.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class tpControlDialogDef
///////////////////////////////////////////////////////////////////////////////
class tpControlDialogDef : public wxDialog
{
	private:

	protected:
		wxBoxSizer* m_SizerControl;
		wxNotebook* m_notebookControl;
		wxPanel* m_panelGeneral;
		wxCheckBox* m_checkBoxSaveJSONOnStartup;
		wxCheckBox* m_checkBoxRecreateConfig;
		wxPanel* m_panelFileInput;
		wxFlexGridSizer* m_fgSizerJSON;
		wxStaticText* m_staticTextJSONFile;
		wxFilePickerCtrl* m_filePickerInputJSON;
		wxCheckBox* m_checkBoxSaveJSON;
		wxFilePickerCtrl* m_filePickerOutputJSON;
		wxCheckBox* m_checkBoxCloseAferWrite;
		wxCheckBox* m_checkBoxAppendToFile;
		wxButton* m_buttonImportJSON;
		wxPanel* m_panelUserInput;
		wxFlexGridSizer* m_fgSizerUI;
		wxNotebook* m_notebookUI;
		wxPanel* m_panelUICreateBoundary;
		wxStaticText* m_staticBoundaryName;
		wxTextCtrl* m_textCtrlBoundaryName;
		wxStaticText* m_staticTextType;
		wxChoice* m_choiceBoundaryType;
		wxCheckBox* m_checkBoxBoundaryActive;
		wxCheckBox* m_checkBoxBoundaryVisible;
		wxStaticText* m_staticTextLineColour;
		wxColourPickerCtrl* m_colourPickerBoundaryLineColour;
		wxStaticText* m_staticTextFillColour;
		wxColourPickerCtrl* m_colourPickerBoundaryFillColour;
		wxStaticText* m_staticTextBoundaryPointsList;
		wxStaticText* m_staticTextCornetLat;
		wxTextCtrl* m_textCtrlCornerLat;
		wxStaticText* m_staticTextCornerLon;
		wxTextCtrl* m_textCtrlCornerLon;
		wxStaticText* m_staticTextNumPoints;
		wxChoice* m_choiceNumberOfPoints;
		wxCheckBox* m_checkBoxBoundaryBoundaryPointVisible;
		wxCheckBox* m_checkBoxBoundaryPointRangeRingsVisible;
		wxStaticText* m_staticText30;
		wxChoice* m_choiceBoundaryBoundaryPointRingNumber;
		wxStaticText* m_staticText31;
		wxTextCtrl* m_textCtrlBoundaryBoundaryPointRingStep;
		wxStaticText* m_staticText32;
		wxChoice* m_choiceBoundaryBoundaryPointRingUnits;
		wxStaticText* m_staticText33;
		wxColourPickerCtrl* m_colourPickerBoundaryBoundaryPointRingColour;
		wxButton* m_buttonCreateBoundaryODAPI;
		wxButton* m_buttonCreateBoundaryJSON;
		wxPanel* m_panelDeleteBoundary;
		wxStaticText* m_staticTextDeleteBoundaryGUID;
		wxTextCtrl* m_textCtrDeleteBoundaryGUID;
		wxButton* m_buttonDeleteBoundaryODAP;
		wxButton* m_buttonDeleteBoundaryJSON;
		wxPanel* m_panelUICreateBoundaryPoint;
		wxStaticText* m_staticTextBPName;
		wxTextCtrl* m_textCtrlBoundaryPointName;
		wxStaticText* m_staticTextBoundaryPointType;
		wxChoice* m_choiceBoundaryPointType;
		wxStaticText* m_staticTextIconName;
		wxTextCtrl* m_textCtrlBoundaryPointIconName;
		wxStaticText* m_staticTextLat;
		wxTextCtrl* m_textCtrlLatitude;
		wxStaticText* m_staticTextLon;
		wxTextCtrl* m_textCtrlLongitude;
		wxCheckBox* m_checkBoxBoundaryPointVisible;
		wxCheckBox* m_checkBoxRingsVisible;
		wxStaticText* m_staticText10;
		wxChoice* m_choiceBoundaryPointRingNumber;
		wxStaticText* m_staticText1RingStep;
		wxTextCtrl* m_textCtrlBoundaryPointRingStep;
		wxStaticText* m_staticTextRinUnits;
		wxChoice* m_choiceBoundaryPointRingUnits;
		wxStaticText* m_staticTextRingColour;
		wxColourPickerCtrl* m_colourPickerBoundaryPointRingColour;
		wxButton* m_buttonCreateBoundaryPointODAPI;
		wxButton* m_buttonCreateBoundaryPointJSON;
		wxPanel* m_panelDeleteBoundaryPoint;
		wxStaticText* m_staticTextDeleteBoundaryPointGUID;
		wxTextCtrl* m_textCtrDeleteBoundaryPointGUID;
		wxButton* m_buttonDeleteBoundaryPointODAPI;
		wxButton* m_buttonDeleteBoundaryPointJSON;
		wxPanel* m_panelUICreateTextPoint;
		wxFlexGridSizer* m_fgSizerTextPoint;
		wxStaticText* m_staticTextTextPointName;
		wxTextCtrl* m_textCtrlTextPointName;
		wxStaticText* m_staticTextTextPointIconName;
		wxTextCtrl* m_textCtrlTextPointIconName;
		wxStaticText* m_staticTextTextPointLat;
		wxTextCtrl* m_textCtrlTextPointLatitude;
		wxStaticText* m_staticTextTextPointLon;
		wxTextCtrl* m_textCtrlTextPointLongitude;
		wxCheckBox* m_checkBoxTextPointVisible;
		wxStaticText* m_staticTextTextPointText;
		wxTextCtrl* m_textCtrlTextPointTextToDisplay;
		wxStaticText* m_staticTextTextPointTextPosition;
		wxChoice* m_choiceTextPointTextPosition;
		wxStaticText* m_staticTextTextPointTextColour;
		wxColourPickerCtrl* m_colourPickerTextPointTextColour;
		wxStaticText* m_staticTextTextPointBackgroundColour;
		wxColourPickerCtrl* m_colourPickerTextPointTextBackgroundColour;
		wxStaticText* m_staticTextTextPointBackgroundTransparancy;
		wxSlider* m_sliderTextPointBackgroundTransparency;
		wxFlexGridSizer* m_fgSizerDisplayText;
		wxStaticText* m_staticTextTextPointFont;
		wxStaticText* m_staticTextTextPointTextFontExample;
		wxButton* m_buttonTextPointFonts;
		wxRadioBox* m_radioBoxTextPointTextDisplay;
		wxButton* m_buttonCreateTextPointODAPI;
		wxButton* m_buttonCreateTextPointJSON;
		wxPanel* m_panelDeleteTextPoint;
		wxStaticText* m_staticTextDeleteTextPointGUID;
		wxTextCtrl* m_textCtrlDeleteTextPointGUID;
		wxButton* m_buttonDeleteTextPointODAP;
		wxButton* m_buttonDeleteTextPointJSON;
		wxPanel* m_panelPointIcon;
		wxRadioBox* m_radioBoxPointIcon;
		wxButton* m_buttonPointIconODAPI;
		wxButton* m_buttonPointIconJSON;
		wxButton* m_buttonClose;

		// Virtual event handlers, overide them in your derived class
		virtual void OnCheckBoxSaveJSONOnStartup( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckBoxDeleteFromConfig( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileChangeInputJSON( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnCheckBoxSaveJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileChangeOutputJSON( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnCheckBoxCloseSaveFileAfterEachWrite( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckBoxAppendToFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void tpControlOnClickImportJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCreateBoundaryODAPI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCreateBoundaryJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDeleteBoundaryODAPI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDeleteBoundaryJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCreateBoundaryPointODAPI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCreateBoundaryPointJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDeleteBoundaryPointODAPI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDeleteBoundaryPointJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickFonts( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCreateTextPointODAPI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCreateTextPointJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDeleteTextPointODAPI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDeleteTextPointJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickPointIconODAPI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickPointIconJSON( wxCommandEvent& event ) { event.Skip(); }
		virtual void tpControlCloseClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		tpControlDialogDef( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Test Plugin Control Dialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 750,716 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
		~tpControlDialogDef();

};

