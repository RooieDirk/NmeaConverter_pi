///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "tpControlDialogDef.h"

///////////////////////////////////////////////////////////////////////////

tpControlDialogDef::tpControlDialogDef( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_SizerControl = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 0, 0, 0 );
	fgSizer3->AddGrowableCol( 0 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_notebookControl = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelGeneral = new wxPanel( m_notebookControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer26;
	fgSizer26 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer26->SetFlexibleDirection( wxBOTH );
	fgSizer26->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_checkBoxSaveJSONOnStartup = new wxCheckBox( m_panelGeneral, wxID_ANY, _("Save JSON on startup"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	fgSizer26->Add( m_checkBoxSaveJSONOnStartup, 0, wxALL, 5 );

	m_checkBoxRecreateConfig = new wxCheckBox( m_panelGeneral, wxID_ANY, _("Delete config from conf\non shutdown"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	fgSizer26->Add( m_checkBoxRecreateConfig, 0, wxALL, 5 );


	m_panelGeneral->SetSizer( fgSizer26 );
	m_panelGeneral->Layout();
	fgSizer26->Fit( m_panelGeneral );
	m_notebookControl->AddPage( m_panelGeneral, _("General"), false );
	m_panelFileInput = new wxPanel( m_notebookControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_fgSizerJSON = new wxFlexGridSizer( 0, 2, 0, 0 );
	m_fgSizerJSON->AddGrowableCol( 1 );
	m_fgSizerJSON->SetFlexibleDirection( wxBOTH );
	m_fgSizerJSON->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextJSONFile = new wxStaticText( m_panelFileInput, wxID_ANY, _("Select JSON file to import"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextJSONFile->Wrap( -1 );
	m_fgSizerJSON->Add( m_staticTextJSONFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_filePickerInputJSON = new wxFilePickerCtrl( m_panelFileInput, wxID_ANY, wxEmptyString, _("Select a JSON file"), _("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	m_fgSizerJSON->Add( m_filePickerInputJSON, 0, wxALL|wxEXPAND, 5 );

	m_checkBoxSaveJSON = new wxCheckBox( m_panelFileInput, wxID_ANY, _("Save incoming JSON\nmessages"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_fgSizerJSON->Add( m_checkBoxSaveJSON, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_filePickerOutputJSON = new wxFilePickerCtrl( m_panelFileInput, wxID_ANY, wxEmptyString, _("Select a file"), _("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_SMALL|wxFLP_USE_TEXTCTRL );
	m_fgSizerJSON->Add( m_filePickerOutputJSON, 0, wxALL|wxEXPAND, 5 );

	m_checkBoxCloseAferWrite = new wxCheckBox( m_panelFileInput, wxID_ANY, _("Close save file after\neach write"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_checkBoxCloseAferWrite->SetValue(true);
	m_fgSizerJSON->Add( m_checkBoxCloseAferWrite, 0, wxALL, 5 );

	m_checkBoxAppendToFile = new wxCheckBox( m_panelFileInput, wxID_ANY, _("Append to file"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_checkBoxAppendToFile->SetValue(true);
	m_fgSizerJSON->Add( m_checkBoxAppendToFile, 0, wxALL, 5 );

	m_buttonImportJSON = new wxButton( m_panelFileInput, wxID_ANY, _("Import JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	m_fgSizerJSON->Add( m_buttonImportJSON, 0, wxALL, 5 );


	m_panelFileInput->SetSizer( m_fgSizerJSON );
	m_panelFileInput->Layout();
	m_fgSizerJSON->Fit( m_panelFileInput );
	m_notebookControl->AddPage( m_panelFileInput, _("File Input"), false );
	m_panelUserInput = new wxPanel( m_notebookControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_fgSizerUI = new wxFlexGridSizer( 0, 0, 0, 0 );
	m_fgSizerUI->AddGrowableCol( 0 );
	m_fgSizerUI->AddGrowableRow( 0 );
	m_fgSizerUI->SetFlexibleDirection( wxBOTH );
	m_fgSizerUI->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_notebookUI = new wxNotebook( m_panelUserInput, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelUICreateBoundary = new wxPanel( m_notebookUI, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->AddGrowableCol( 1 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticBoundaryName = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticBoundaryName->Wrap( -1 );
	fgSizer5->Add( m_staticBoundaryName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlBoundaryName = new wxTextCtrl( m_panelUICreateBoundary, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_textCtrlBoundaryName, 1, wxALIGN_RIGHT|wxALL, 5 );

	m_staticTextType = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextType->Wrap( -1 );
	fgSizer5->Add( m_staticTextType, 0, wxALL, 5 );

	wxString m_choiceBoundaryTypeChoices[] = { _("Exclusion"), _("Inclusion"), _("Neither") };
	int m_choiceBoundaryTypeNChoices = sizeof( m_choiceBoundaryTypeChoices ) / sizeof( wxString );
	m_choiceBoundaryType = new wxChoice( m_panelUICreateBoundary, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceBoundaryTypeNChoices, m_choiceBoundaryTypeChoices, 0 );
	m_choiceBoundaryType->SetSelection( 0 );
	fgSizer5->Add( m_choiceBoundaryType, 1, wxALIGN_RIGHT|wxALL, 5 );

	m_checkBoxBoundaryActive = new wxCheckBox( m_panelUICreateBoundary, wxID_ANY, _("Active"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_checkBoxBoundaryActive->SetValue(true);
	fgSizer5->Add( m_checkBoxBoundaryActive, 0, wxALL, 5 );

	m_checkBoxBoundaryVisible = new wxCheckBox( m_panelUICreateBoundary, wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxBoundaryVisible->SetValue(true);
	fgSizer5->Add( m_checkBoxBoundaryVisible, 1, wxALL, 5 );

	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextLineColour = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Line Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLineColour->Wrap( -1 );
	fgSizer6->Add( m_staticTextLineColour, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_colourPickerBoundaryLineColour = new wxColourPickerCtrl( m_panelUICreateBoundary, wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer6->Add( m_colourPickerBoundaryLineColour, 0, wxALL, 5 );


	fgSizer5->Add( fgSizer6, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextFillColour = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Fill Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFillColour->Wrap( -1 );
	fgSizer7->Add( m_staticTextFillColour, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_colourPickerBoundaryFillColour = new wxColourPickerCtrl( m_panelUICreateBoundary, wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer7->Add( m_colourPickerBoundaryFillColour, 1, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer5->Add( fgSizer7, 1, wxEXPAND, 5 );

	m_staticTextBoundaryPointsList = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Boundary Points"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBoundaryPointsList->Wrap( -1 );
	fgSizer5->Add( m_staticTextBoundaryPointsList, 0, wxALL, 5 );


	fgSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextCornetLat = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Corner Lat"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextCornetLat->Wrap( -1 );
	fgSizer24->Add( m_staticTextCornetLat, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlCornerLat = new wxTextCtrl( m_panelUICreateBoundary, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_textCtrlCornerLat, 0, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer5->Add( fgSizer24, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer25;
	fgSizer25 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer25->SetFlexibleDirection( wxBOTH );
	fgSizer25->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextCornerLon = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Corner Lon"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextCornerLon->Wrap( -1 );
	fgSizer25->Add( m_staticTextCornerLon, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlCornerLon = new wxTextCtrl( m_panelUICreateBoundary, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer25->Add( m_textCtrlCornerLon, 0, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer5->Add( fgSizer25, 1, wxEXPAND, 5 );

	m_staticTextNumPoints = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Number of Points"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextNumPoints->Wrap( -1 );
	fgSizer5->Add( m_staticTextNumPoints, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_choiceNumberOfPointsChoices[] = { _("3"), _("4"), _("5"), _("6"), _("2") };
	int m_choiceNumberOfPointsNChoices = sizeof( m_choiceNumberOfPointsChoices ) / sizeof( wxString );
	m_choiceNumberOfPoints = new wxChoice( m_panelUICreateBoundary, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceNumberOfPointsNChoices, m_choiceNumberOfPointsChoices, 0 );
	m_choiceNumberOfPoints->SetSelection( 0 );
	fgSizer5->Add( m_choiceNumberOfPoints, 0, wxALIGN_RIGHT|wxALL, 5 );

	m_checkBoxBoundaryBoundaryPointVisible = new wxCheckBox( m_panelUICreateBoundary, wxID_ANY, _("Boundary Point Visible"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_checkBoxBoundaryBoundaryPointVisible->SetValue(true);
	fgSizer5->Add( m_checkBoxBoundaryBoundaryPointVisible, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_checkBoxBoundaryPointRangeRingsVisible = new wxCheckBox( m_panelUICreateBoundary, wxID_ANY, _("Boundary Point\nRange Rings Visible"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	fgSizer5->Add( m_checkBoxBoundaryPointRangeRingsVisible, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer28;
	fgSizer28 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer28->SetFlexibleDirection( wxBOTH );
	fgSizer28->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText30 = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Number of Rings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer28->Add( m_staticText30, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_choiceBoundaryBoundaryPointRingNumberChoices[] = { _("0"), _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("8"), _("9"), _("10") };
	int m_choiceBoundaryBoundaryPointRingNumberNChoices = sizeof( m_choiceBoundaryBoundaryPointRingNumberChoices ) / sizeof( wxString );
	m_choiceBoundaryBoundaryPointRingNumber = new wxChoice( m_panelUICreateBoundary, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceBoundaryBoundaryPointRingNumberNChoices, m_choiceBoundaryBoundaryPointRingNumberChoices, 0 );
	m_choiceBoundaryBoundaryPointRingNumber->SetSelection( 0 );
	fgSizer28->Add( m_choiceBoundaryBoundaryPointRingNumber, 0, wxALL, 5 );


	fgSizer5->Add( fgSizer28, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer29;
	fgSizer29 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer29->SetFlexibleDirection( wxBOTH );
	fgSizer29->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText31 = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Rings Step"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer29->Add( m_staticText31, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlBoundaryBoundaryPointRingStep = new wxTextCtrl( m_panelUICreateBoundary, wxID_ANY, _("0.5"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	#ifdef __WXGTK__
	if ( !m_textCtrlBoundaryBoundaryPointRingStep->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrlBoundaryBoundaryPointRingStep->SetMaxLength( 4 );
	}
	#else
	m_textCtrlBoundaryBoundaryPointRingStep->SetMaxLength( 4 );
	#endif
	fgSizer29->Add( m_textCtrlBoundaryBoundaryPointRingStep, 0, wxALL, 5 );


	fgSizer5->Add( fgSizer29, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer30;
	fgSizer30 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer30->SetFlexibleDirection( wxBOTH );
	fgSizer30->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText32 = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Ring Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer30->Add( m_staticText32, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_choiceBoundaryBoundaryPointRingUnitsChoices[] = { _("Nautical Miles"), _("Kilometers") };
	int m_choiceBoundaryBoundaryPointRingUnitsNChoices = sizeof( m_choiceBoundaryBoundaryPointRingUnitsChoices ) / sizeof( wxString );
	m_choiceBoundaryBoundaryPointRingUnits = new wxChoice( m_panelUICreateBoundary, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceBoundaryBoundaryPointRingUnitsNChoices, m_choiceBoundaryBoundaryPointRingUnitsChoices, 0 );
	m_choiceBoundaryBoundaryPointRingUnits->SetSelection( 0 );
	fgSizer30->Add( m_choiceBoundaryBoundaryPointRingUnits, 0, wxALL, 5 );


	fgSizer5->Add( fgSizer30, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer31;
	fgSizer31 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer31->SetFlexibleDirection( wxBOTH );
	fgSizer31->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText33 = new wxStaticText( m_panelUICreateBoundary, wxID_ANY, _("Ring Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer31->Add( m_staticText33, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_colourPickerBoundaryBoundaryPointRingColour = new wxColourPickerCtrl( m_panelUICreateBoundary, wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer31->Add( m_colourPickerBoundaryBoundaryPointRingColour, 0, wxALL, 5 );


	fgSizer5->Add( fgSizer31, 1, wxEXPAND, 5 );

	m_buttonCreateBoundaryODAPI = new wxButton( m_panelUICreateBoundary, wxID_ANY, _("Create ODAPI"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_buttonCreateBoundaryODAPI, 0, wxALL, 5 );

	m_buttonCreateBoundaryJSON = new wxButton( m_panelUICreateBoundary, wxID_ANY, _("Create JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_buttonCreateBoundaryJSON, 0, wxALL, 5 );


	m_panelUICreateBoundary->SetSizer( fgSizer5 );
	m_panelUICreateBoundary->Layout();
	fgSizer5->Fit( m_panelUICreateBoundary );
	m_notebookUI->AddPage( m_panelUICreateBoundary, _("Create Boundary"), false );
	m_panelDeleteBoundary = new wxPanel( m_notebookUI, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer36;
	fgSizer36 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer36->AddGrowableCol( 1 );
	fgSizer36->SetFlexibleDirection( wxBOTH );
	fgSizer36->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextDeleteBoundaryGUID = new wxStaticText( m_panelDeleteBoundary, wxID_ANY, _("GUID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDeleteBoundaryGUID->Wrap( -1 );
	fgSizer36->Add( m_staticTextDeleteBoundaryGUID, 0, wxALL, 5 );

	m_textCtrDeleteBoundaryGUID = new wxTextCtrl( m_panelDeleteBoundary, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer36->Add( m_textCtrDeleteBoundaryGUID, 0, wxALIGN_RIGHT|wxALL, 5 );

	m_buttonDeleteBoundaryODAP = new wxButton( m_panelDeleteBoundary, wxID_ANY, _("Delete ODAPI"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer36->Add( m_buttonDeleteBoundaryODAP, 0, wxALL, 5 );

	m_buttonDeleteBoundaryJSON = new wxButton( m_panelDeleteBoundary, wxID_ANY, _("Delete JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer36->Add( m_buttonDeleteBoundaryJSON, 0, wxALL, 5 );


	m_panelDeleteBoundary->SetSizer( fgSizer36 );
	m_panelDeleteBoundary->Layout();
	fgSizer36->Fit( m_panelDeleteBoundary );
	m_notebookUI->AddPage( m_panelDeleteBoundary, _("Delete Boundary"), false );
	m_panelUICreateBoundaryPoint = new wxPanel( m_notebookUI, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer10->AddGrowableCol( 0 );
	fgSizer10->AddGrowableCol( 1 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextBPName = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBPName->Wrap( -1 );
	fgSizer10->Add( m_staticTextBPName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlBoundaryPointName = new wxTextCtrl( m_panelUICreateBoundaryPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_textCtrlBoundaryPointName, 1, wxALIGN_RIGHT|wxALL, 5 );

	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextBoundaryPointType = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBoundaryPointType->Wrap( -1 );
	fgSizer16->Add( m_staticTextBoundaryPointType, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_choiceBoundaryPointTypeChoices[] = { _("Exclusion"), _("Inclusion"), _("Neither") };
	int m_choiceBoundaryPointTypeNChoices = sizeof( m_choiceBoundaryPointTypeChoices ) / sizeof( wxString );
	m_choiceBoundaryPointType = new wxChoice( m_panelUICreateBoundaryPoint, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceBoundaryPointTypeNChoices, m_choiceBoundaryPointTypeChoices, 0 );
	m_choiceBoundaryPointType->SetSelection( 0 );
	fgSizer16->Add( m_choiceBoundaryPointType, 1, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer10->Add( fgSizer16, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextIconName = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Icon Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextIconName->Wrap( -1 );
	fgSizer18->Add( m_staticTextIconName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlBoundaryPointIconName = new wxTextCtrl( m_panelUICreateBoundaryPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_textCtrlBoundaryPointIconName, 0, wxALL, 5 );


	fgSizer10->Add( fgSizer18, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer9->AddGrowableCol( 1 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextLat = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Lat"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLat->Wrap( -1 );
	fgSizer9->Add( m_staticTextLat, 0, wxALL, 5 );

	m_textCtrlLatitude = new wxTextCtrl( m_panelUICreateBoundaryPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_textCtrlLatitude, 1, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer10->Add( fgSizer9, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextLon = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Lon"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLon->Wrap( -1 );
	fgSizer11->Add( m_staticTextLon, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlLongitude = new wxTextCtrl( m_panelUICreateBoundaryPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( m_textCtrlLongitude, 1, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer10->Add( fgSizer11, 1, wxEXPAND, 5 );

	m_checkBoxBoundaryPointVisible = new wxCheckBox( m_panelUICreateBoundaryPoint, wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_checkBoxBoundaryPointVisible->SetValue(true);
	fgSizer10->Add( m_checkBoxBoundaryPointVisible, 1, wxALL, 5 );

	m_checkBoxRingsVisible = new wxCheckBox( m_panelUICreateBoundaryPoint, wxID_ANY, _("Rings Visible"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_checkBoxRingsVisible->SetValue(true);
	fgSizer10->Add( m_checkBoxRingsVisible, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText10 = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Number of Rings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer13->Add( m_staticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_choiceBoundaryPointRingNumberChoices[] = { _("0"), _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("8"), _("9"), _("10") };
	int m_choiceBoundaryPointRingNumberNChoices = sizeof( m_choiceBoundaryPointRingNumberChoices ) / sizeof( wxString );
	m_choiceBoundaryPointRingNumber = new wxChoice( m_panelUICreateBoundaryPoint, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceBoundaryPointRingNumberNChoices, m_choiceBoundaryPointRingNumberChoices, 0 );
	m_choiceBoundaryPointRingNumber->SetSelection( 0 );
	fgSizer13->Add( m_choiceBoundaryPointRingNumber, 0, wxALL, 5 );


	fgSizer10->Add( fgSizer13, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer131;
	fgSizer131 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer131->SetFlexibleDirection( wxBOTH );
	fgSizer131->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText1RingStep = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Rings Step"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1RingStep->Wrap( -1 );
	fgSizer131->Add( m_staticText1RingStep, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlBoundaryPointRingStep = new wxTextCtrl( m_panelUICreateBoundaryPoint, wxID_ANY, _("0.5"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	#ifdef __WXGTK__
	if ( !m_textCtrlBoundaryPointRingStep->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrlBoundaryPointRingStep->SetMaxLength( 4 );
	}
	#else
	m_textCtrlBoundaryPointRingStep->SetMaxLength( 4 );
	#endif
	fgSizer131->Add( m_textCtrlBoundaryPointRingStep, 0, wxALL, 5 );


	fgSizer10->Add( fgSizer131, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextRinUnits = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Step Units"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRinUnits->Wrap( -1 );
	fgSizer14->Add( m_staticTextRinUnits, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_choiceBoundaryPointRingUnitsChoices[] = { _("Nautical Miles"), _("Kilometers") };
	int m_choiceBoundaryPointRingUnitsNChoices = sizeof( m_choiceBoundaryPointRingUnitsChoices ) / sizeof( wxString );
	m_choiceBoundaryPointRingUnits = new wxChoice( m_panelUICreateBoundaryPoint, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceBoundaryPointRingUnitsNChoices, m_choiceBoundaryPointRingUnitsChoices, 0 );
	m_choiceBoundaryPointRingUnits->SetSelection( 0 );
	fgSizer14->Add( m_choiceBoundaryPointRingUnits, 0, wxALL, 5 );


	fgSizer10->Add( fgSizer14, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextRingColour = new wxStaticText( m_panelUICreateBoundaryPoint, wxID_ANY, _("Ring Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRingColour->Wrap( -1 );
	fgSizer15->Add( m_staticTextRingColour, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_colourPickerBoundaryPointRingColour = new wxColourPickerCtrl( m_panelUICreateBoundaryPoint, wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer15->Add( m_colourPickerBoundaryPointRingColour, 0, wxALL, 5 );


	fgSizer10->Add( fgSizer15, 1, wxEXPAND, 5 );

	m_buttonCreateBoundaryPointODAPI = new wxButton( m_panelUICreateBoundaryPoint, wxID_ANY, _("Create ODAPI"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_buttonCreateBoundaryPointODAPI, 0, wxALL, 5 );

	m_buttonCreateBoundaryPointJSON = new wxButton( m_panelUICreateBoundaryPoint, wxID_ANY, _("Create JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_buttonCreateBoundaryPointJSON, 0, wxALL, 5 );


	fgSizer8->Add( fgSizer10, 1, wxEXPAND, 5 );


	m_panelUICreateBoundaryPoint->SetSizer( fgSizer8 );
	m_panelUICreateBoundaryPoint->Layout();
	fgSizer8->Fit( m_panelUICreateBoundaryPoint );
	m_notebookUI->AddPage( m_panelUICreateBoundaryPoint, _("Create Boundary Point"), false );
	m_panelDeleteBoundaryPoint = new wxPanel( m_notebookUI, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer35;
	fgSizer35 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer35->AddGrowableCol( 1 );
	fgSizer35->SetFlexibleDirection( wxBOTH );
	fgSizer35->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextDeleteBoundaryPointGUID = new wxStaticText( m_panelDeleteBoundaryPoint, wxID_ANY, _("GUID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDeleteBoundaryPointGUID->Wrap( -1 );
	fgSizer35->Add( m_staticTextDeleteBoundaryPointGUID, 0, wxALL, 5 );

	m_textCtrDeleteBoundaryPointGUID = new wxTextCtrl( m_panelDeleteBoundaryPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer35->Add( m_textCtrDeleteBoundaryPointGUID, 1, wxALIGN_RIGHT|wxALL, 5 );

	m_buttonDeleteBoundaryPointODAPI = new wxButton( m_panelDeleteBoundaryPoint, wxID_ANY, _("Delete ODAPI"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer35->Add( m_buttonDeleteBoundaryPointODAPI, 0, wxALL, 5 );

	m_buttonDeleteBoundaryPointJSON = new wxButton( m_panelDeleteBoundaryPoint, wxID_ANY, _("Delete JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer35->Add( m_buttonDeleteBoundaryPointJSON, 0, wxALL, 5 );


	m_panelDeleteBoundaryPoint->SetSizer( fgSizer35 );
	m_panelDeleteBoundaryPoint->Layout();
	fgSizer35->Fit( m_panelDeleteBoundaryPoint );
	m_notebookUI->AddPage( m_panelDeleteBoundaryPoint, _("Delete Boundary Point"), true );
	m_panelUICreateTextPoint = new wxPanel( m_notebookUI, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_fgSizerTextPoint = new wxFlexGridSizer( 0, 1, 0, 0 );
	m_fgSizerTextPoint->AddGrowableCol( 0 );
	m_fgSizerTextPoint->AddGrowableRow( 0 );
	m_fgSizerTextPoint->SetFlexibleDirection( wxBOTH );
	m_fgSizerTextPoint->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer19->AddGrowableCol( 0 );
	fgSizer19->AddGrowableCol( 1 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextTextPointName = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointName->Wrap( -1 );
	fgSizer19->Add( m_staticTextTextPointName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlTextPointName = new wxTextCtrl( m_panelUICreateTextPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( m_textCtrlTextPointName, 1, wxALIGN_RIGHT|wxALL, 5 );

	m_staticTextTextPointIconName = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Icon Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointIconName->Wrap( -1 );
	fgSizer19->Add( m_staticTextTextPointIconName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlTextPointIconName = new wxTextCtrl( m_panelUICreateTextPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( m_textCtrlTextPointIconName, 0, wxALIGN_RIGHT|wxALL, 5 );

	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer20->AddGrowableCol( 1 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextTextPointLat = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Lat"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointLat->Wrap( -1 );
	fgSizer20->Add( m_staticTextTextPointLat, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlTextPointLatitude = new wxTextCtrl( m_panelUICreateTextPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer20->Add( m_textCtrlTextPointLatitude, 0, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer19->Add( fgSizer20, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer21->AddGrowableCol( 1 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextTextPointLon = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Lon"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointLon->Wrap( -1 );
	fgSizer21->Add( m_staticTextTextPointLon, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlTextPointLongitude = new wxTextCtrl( m_panelUICreateTextPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_textCtrlTextPointLongitude, 0, wxALIGN_RIGHT|wxALL, 5 );


	fgSizer19->Add( fgSizer21, 1, wxEXPAND, 5 );

	m_checkBoxTextPointVisible = new wxCheckBox( m_panelUICreateTextPoint, wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_checkBoxTextPointVisible->SetValue(true);
	fgSizer19->Add( m_checkBoxTextPointVisible, 0, wxALL, 5 );


	m_fgSizerTextPoint->Add( fgSizer19, 1, wxEXPAND, 5 );

	m_staticTextTextPointText = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Text to Display with Point"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointText->Wrap( -1 );
	m_fgSizerTextPoint->Add( m_staticTextTextPointText, 0, wxALL, 5 );

	m_textCtrlTextPointTextToDisplay = new wxTextCtrl( m_panelUICreateTextPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	m_fgSizerTextPoint->Add( m_textCtrlTextPointTextToDisplay, 1, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer22->AddGrowableCol( 1 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextTextPointTextPosition = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Text position relative to point"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointTextPosition->Wrap( -1 );
	fgSizer22->Add( m_staticTextTextPointTextPosition, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_choiceTextPointTextPositionChoices[] = { _("Top"), _("Top Centre"), _("Bottom"), _("Bottom Centre"), _("Centre"), _("Right"), _("Left") };
	int m_choiceTextPointTextPositionNChoices = sizeof( m_choiceTextPointTextPositionChoices ) / sizeof( wxString );
	m_choiceTextPointTextPosition = new wxChoice( m_panelUICreateTextPoint, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTextPointTextPositionNChoices, m_choiceTextPointTextPositionChoices, 0 );
	m_choiceTextPointTextPosition->SetSelection( 0 );
	fgSizer22->Add( m_choiceTextPointTextPosition, 1, wxALIGN_RIGHT|wxALL, 5 );

	m_staticTextTextPointTextColour = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Text Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointTextColour->Wrap( -1 );
	fgSizer22->Add( m_staticTextTextPointTextColour, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_colourPickerTextPointTextColour = new wxColourPickerCtrl( m_panelUICreateTextPoint, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer22->Add( m_colourPickerTextPointTextColour, 1, wxALIGN_RIGHT|wxALL, 5 );

	m_staticTextTextPointBackgroundColour = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Background Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointBackgroundColour->Wrap( -1 );
	fgSizer22->Add( m_staticTextTextPointBackgroundColour, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_colourPickerTextPointTextBackgroundColour = new wxColourPickerCtrl( m_panelUICreateTextPoint, wxID_ANY, wxColour( 255, 255, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer22->Add( m_colourPickerTextPointTextBackgroundColour, 0, wxALIGN_RIGHT|wxALL, 5 );

	m_staticTextTextPointBackgroundTransparancy = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Background Transparancy"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointBackgroundTransparancy->Wrap( -1 );
	fgSizer22->Add( m_staticTextTextPointBackgroundTransparancy, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_sliderTextPointBackgroundTransparency = new wxSlider( m_panelUICreateTextPoint, wxID_ANY, 100, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	fgSizer22->Add( m_sliderTextPointBackgroundTransparency, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_fgSizerDisplayText = new wxFlexGridSizer( 0, 2, 0, 0 );
	m_fgSizerDisplayText->AddGrowableCol( 1 );
	m_fgSizerDisplayText->AddGrowableRow( 0 );
	m_fgSizerDisplayText->SetFlexibleDirection( wxBOTH );
	m_fgSizerDisplayText->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextTextPointFont = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Text Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointFont->Wrap( -1 );
	m_fgSizerDisplayText->Add( m_staticTextTextPointFont, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticTextTextPointTextFontExample = new wxStaticText( m_panelUICreateTextPoint, wxID_ANY, _("Example"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTextPointTextFontExample->Wrap( -1 );
	m_fgSizerDisplayText->Add( m_staticTextTextPointTextFontExample, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	fgSizer22->Add( m_fgSizerDisplayText, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	m_buttonTextPointFonts = new wxButton( m_panelUICreateTextPoint, wxID_ANY, _("Fonts"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer22->Add( m_buttonTextPointFonts, 0, wxALIGN_RIGHT|wxALL, 5 );

	wxString m_radioBoxTextPointTextDisplayChoices[] = { _("Always"), _("On Rollover Only"), _("Never") };
	int m_radioBoxTextPointTextDisplayNChoices = sizeof( m_radioBoxTextPointTextDisplayChoices ) / sizeof( wxString );
	m_radioBoxTextPointTextDisplay = new wxRadioBox( m_panelUICreateTextPoint, wxID_ANY, _("Show Display Text"), wxDefaultPosition, wxDefaultSize, m_radioBoxTextPointTextDisplayNChoices, m_radioBoxTextPointTextDisplayChoices, 1, wxRA_SPECIFY_ROWS );
	m_radioBoxTextPointTextDisplay->SetSelection( 0 );
	fgSizer22->Add( m_radioBoxTextPointTextDisplay, 0, wxALL, 5 );


	m_fgSizerTextPoint->Add( fgSizer22, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer27;
	fgSizer27 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer27->AddGrowableCol( 0 );
	fgSizer27->AddGrowableCol( 1 );
	fgSizer27->SetFlexibleDirection( wxBOTH );
	fgSizer27->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_buttonCreateTextPointODAPI = new wxButton( m_panelUICreateTextPoint, wxID_ANY, _("Create ODAPI"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer27->Add( m_buttonCreateTextPointODAPI, 0, wxALL, 5 );

	m_buttonCreateTextPointJSON = new wxButton( m_panelUICreateTextPoint, wxID_ANY, _("Create JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer27->Add( m_buttonCreateTextPointJSON, 0, wxALL, 5 );


	m_fgSizerTextPoint->Add( fgSizer27, 1, wxEXPAND, 5 );


	m_panelUICreateTextPoint->SetSizer( m_fgSizerTextPoint );
	m_panelUICreateTextPoint->Layout();
	m_fgSizerTextPoint->Fit( m_panelUICreateTextPoint );
	m_notebookUI->AddPage( m_panelUICreateTextPoint, _("Create Text Point"), false );
	m_panelDeleteTextPoint = new wxPanel( m_notebookUI, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer37;
	fgSizer37 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer37->AddGrowableCol( 1 );
	fgSizer37->SetFlexibleDirection( wxBOTH );
	fgSizer37->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextDeleteTextPointGUID = new wxStaticText( m_panelDeleteTextPoint, wxID_ANY, _("GUID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDeleteTextPointGUID->Wrap( -1 );
	fgSizer37->Add( m_staticTextDeleteTextPointGUID, 0, wxALL, 5 );

	m_textCtrlDeleteTextPointGUID = new wxTextCtrl( m_panelDeleteTextPoint, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer37->Add( m_textCtrlDeleteTextPointGUID, 0, wxALIGN_RIGHT|wxALL, 5 );

	m_buttonDeleteTextPointODAP = new wxButton( m_panelDeleteTextPoint, wxID_ANY, _("Delete ODAPI"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer37->Add( m_buttonDeleteTextPointODAP, 0, wxALL, 5 );

	m_buttonDeleteTextPointJSON = new wxButton( m_panelDeleteTextPoint, wxID_ANY, _("Delete JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer37->Add( m_buttonDeleteTextPointJSON, 0, wxALL, 5 );


	m_panelDeleteTextPoint->SetSizer( fgSizer37 );
	m_panelDeleteTextPoint->Layout();
	fgSizer37->Fit( m_panelDeleteTextPoint );
	m_notebookUI->AddPage( m_panelDeleteTextPoint, _("Delete Text Point"), false );
	m_panelPointIcon = new wxPanel( m_notebookUI, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizerPointIcon;
	fgSizerPointIcon = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizerPointIcon->AddGrowableCol( 0 );
	fgSizerPointIcon->SetFlexibleDirection( wxBOTH );
	fgSizerPointIcon->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizerAddDeletePointIcon;
	fgSizerAddDeletePointIcon = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizerAddDeletePointIcon->SetFlexibleDirection( wxBOTH );
	fgSizerAddDeletePointIcon->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxString m_radioBoxPointIconChoices[] = { _("add"), _("Delete") };
	int m_radioBoxPointIconNChoices = sizeof( m_radioBoxPointIconChoices ) / sizeof( wxString );
	m_radioBoxPointIcon = new wxRadioBox( m_panelPointIcon, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_radioBoxPointIconNChoices, m_radioBoxPointIconChoices, 1, wxRA_SPECIFY_ROWS );
	m_radioBoxPointIcon->SetSelection( 0 );
	fgSizerAddDeletePointIcon->Add( m_radioBoxPointIcon, 0, wxALL, 5 );


	fgSizerPointIcon->Add( fgSizerAddDeletePointIcon, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer34;
	fgSizer34 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer34->AddGrowableCol( 0 );
	fgSizer34->AddGrowableCol( 1 );
	fgSizer34->SetFlexibleDirection( wxBOTH );
	fgSizer34->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_buttonPointIconODAPI = new wxButton( m_panelPointIcon, wxID_ANY, _("ODAPI"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer34->Add( m_buttonPointIconODAPI, 0, wxALL, 5 );

	m_buttonPointIconJSON = new wxButton( m_panelPointIcon, wxID_ANY, _("JSON"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer34->Add( m_buttonPointIconJSON, 0, wxALL, 5 );


	fgSizerPointIcon->Add( fgSizer34, 1, wxEXPAND, 5 );


	m_panelPointIcon->SetSizer( fgSizerPointIcon );
	m_panelPointIcon->Layout();
	fgSizerPointIcon->Fit( m_panelPointIcon );
	m_notebookUI->AddPage( m_panelPointIcon, _("Point Icon"), false );

	m_fgSizerUI->Add( m_notebookUI, 1, wxEXPAND | wxALL, 5 );


	m_panelUserInput->SetSizer( m_fgSizerUI );
	m_panelUserInput->Layout();
	m_fgSizerUI->Fit( m_panelUserInput );
	m_notebookControl->AddPage( m_panelUserInput, _("User Input"), true );

	fgSizer3->Add( m_notebookControl, 0, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 0, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizerOKCancel;
	bSizerOKCancel = new wxBoxSizer( wxHORIZONTAL );

	m_buttonClose = new wxButton( this, wxID_ANY, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerOKCancel->Add( m_buttonClose, 0, wxALL, 5 );


	fgSizer4->Add( bSizerOKCancel, 1, wxEXPAND, 5 );


	fgSizer3->Add( fgSizer4, 1, wxEXPAND, 5 );


	m_SizerControl->Add( fgSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( m_SizerControl );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_checkBoxSaveJSONOnStartup->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxSaveJSONOnStartup ), NULL, this );
	m_checkBoxRecreateConfig->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxDeleteFromConfig ), NULL, this );
	m_filePickerInputJSON->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( tpControlDialogDef::OnFileChangeInputJSON ), NULL, this );
	m_checkBoxSaveJSON->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxSaveJSON ), NULL, this );
	m_filePickerOutputJSON->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( tpControlDialogDef::OnFileChangeOutputJSON ), NULL, this );
	m_checkBoxCloseAferWrite->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxCloseSaveFileAfterEachWrite ), NULL, this );
	m_checkBoxAppendToFile->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxAppendToFile ), NULL, this );
	m_buttonImportJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::tpControlOnClickImportJSON ), NULL, this );
	m_buttonCreateBoundaryODAPI->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryODAPI ), NULL, this );
	m_buttonCreateBoundaryJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryJSON ), NULL, this );
	m_buttonDeleteBoundaryODAP->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryODAPI ), NULL, this );
	m_buttonDeleteBoundaryJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryJSON ), NULL, this );
	m_buttonCreateBoundaryPointODAPI->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryPointODAPI ), NULL, this );
	m_buttonCreateBoundaryPointJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryPointJSON ), NULL, this );
	m_buttonDeleteBoundaryPointODAPI->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryPointODAPI ), NULL, this );
	m_buttonDeleteBoundaryPointJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryPointJSON ), NULL, this );
	m_buttonTextPointFonts->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickFonts ), NULL, this );
	m_buttonCreateTextPointODAPI->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateTextPointODAPI ), NULL, this );
	m_buttonCreateTextPointJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateTextPointJSON ), NULL, this );
	m_buttonDeleteTextPointODAP->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteTextPointODAPI ), NULL, this );
	m_buttonDeleteTextPointJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteTextPointJSON ), NULL, this );
	m_buttonPointIconODAPI->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickPointIconODAPI ), NULL, this );
	m_buttonPointIconJSON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickPointIconJSON ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::tpControlCloseClick ), NULL, this );
}

tpControlDialogDef::~tpControlDialogDef()
{
	// Disconnect Events
	m_checkBoxSaveJSONOnStartup->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxSaveJSONOnStartup ), NULL, this );
	m_checkBoxRecreateConfig->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxDeleteFromConfig ), NULL, this );
	m_filePickerInputJSON->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( tpControlDialogDef::OnFileChangeInputJSON ), NULL, this );
	m_checkBoxSaveJSON->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxSaveJSON ), NULL, this );
	m_filePickerOutputJSON->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( tpControlDialogDef::OnFileChangeOutputJSON ), NULL, this );
	m_checkBoxCloseAferWrite->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxCloseSaveFileAfterEachWrite ), NULL, this );
	m_checkBoxAppendToFile->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnCheckBoxAppendToFile ), NULL, this );
	m_buttonImportJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::tpControlOnClickImportJSON ), NULL, this );
	m_buttonCreateBoundaryODAPI->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryODAPI ), NULL, this );
	m_buttonCreateBoundaryJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryJSON ), NULL, this );
	m_buttonDeleteBoundaryODAP->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryODAPI ), NULL, this );
	m_buttonDeleteBoundaryJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryJSON ), NULL, this );
	m_buttonCreateBoundaryPointODAPI->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryPointODAPI ), NULL, this );
	m_buttonCreateBoundaryPointJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateBoundaryPointJSON ), NULL, this );
	m_buttonDeleteBoundaryPointODAPI->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryPointODAPI ), NULL, this );
	m_buttonDeleteBoundaryPointJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteBoundaryPointJSON ), NULL, this );
	m_buttonTextPointFonts->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickFonts ), NULL, this );
	m_buttonCreateTextPointODAPI->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateTextPointODAPI ), NULL, this );
	m_buttonCreateTextPointJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickCreateTextPointJSON ), NULL, this );
	m_buttonDeleteTextPointODAP->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteTextPointODAPI ), NULL, this );
	m_buttonDeleteTextPointJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickDeleteTextPointJSON ), NULL, this );
	m_buttonPointIconODAPI->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickPointIconODAPI ), NULL, this );
	m_buttonPointIconJSON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::OnButtonClickPointIconJSON ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tpControlDialogDef::tpControlCloseClick ), NULL, this );

}
