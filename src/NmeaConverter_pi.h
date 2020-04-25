/******************************************************************************
 * updated: 12-04-2015  
 * Project:  OpenCPN
 * Purpose:  nmeaTranslate Plugin
 * Author:   Dirk Smits
 *
 ***************************************************************************
 *   Copyright (C) 2015 by Dirk Smits   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */


#ifndef NMEACONV_H
#define NMEACONV_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
      #include <wx/wx.h>
#endif

#include "version.h"

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    8

#include "ocpn_plugin.h"

#include "ec_defs.h"
#include "ec_engine.h"

#include <wx/arrstr.h> 
#include <wx/dynarray.h>
#include <wx/listctrl.h>
#include <wx/fileconf.h>
#include <wx/spinctrl.h>
//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------


class nmeaSendObj;
class nmeaSendObjectDlg;
class PreferenceDlg;
class localTimer;

typedef enum SentenceSendMode
{
    ALLVAL,
    TIMED
}_SentenceSendMode;

class NmeaConverter_pi : public opencpn_plugin_18
{
    WX_DECLARE_HASH_MAP(int, nmeaSendObj*, wxIntegerHash, wxIntegerEqual, MapOfnmeaSendObj);  
    
public:
    MapOfnmeaSendObj::iterator objit;
    NmeaConverter_pi(void *ppimgr);

//    The required PlugIn Methods
    int Init(void);
    bool DeInit(void);
    int GetAPIVersionMajor();
    int GetAPIVersionMinor();
    int GetPlugInVersionMajor();
    int GetPlugInVersionMinor();
    wxBitmap *GetPlugInBitmap();
    wxString GetCommonName();
    wxString GetShortDescription();
    wxString GetLongDescription();

//    The optional method overrides
    void SetNMEASentence(wxString &sentence);
    void SendNMEASentence(wxString sentence);
//    The override PlugIn Methods
    void ShowPreferencesDialog( wxWindow* parent );
    bool SaveConfig( void );
    bool LoadConfig( void );
    bool nmeaIsValid( wxString &sentence);
    int AddObjectToMap( nmeaSendObj* object, SentenceSendMode Mode = ALLVAL, int RepTime = 1, bool Degr = false );
    void ClearAllObjectsInMap();
    wxString ComputeChecksum( wxString sentence );
    wxString ReadNmeaInputToken(wxString SentencePlusNumber);
    nmeaSendObjectDlg* p_nmeaSendObjectDlg;
    PreferenceDlg* prefDlg;
    MapOfnmeaSendObj ObjectMap;
    bool b_CheckChecksum;
private:
    wxArrayString nmeaSentenceArray;
    wxArrayString nmeaIDArray;
    wxFileConfig* m_pconfig;     
};

class nmeaSendObj : wxObject
{
    // declare a hash map with string keys and string values for received sentences 
    WX_DECLARE_STRING_HASH_MAP( wxString, ReceivedSentences );

public:
    nmeaSendObj();
    nmeaSendObj(NmeaConverter_pi* pi, wxString FormatStr);
    ~nmeaSendObj();
    wxString GetFormatStr(){return FormatString;}
    void SetFormatString(wxString FormatStr);
    void SplitStringAlphaDigit(wxString theStr, wxString &alpha, long &digits);
    wxArrayString FindStartWithDollarSubSets(wxString FormatStr, wxString AllowdCharStr);
    void SetNMEASentence(wxString &sentence);
    void ComputeOutputSentence();
    int  ShowModal (wxWindow* parent);
    void SetSendMode(SentenceSendMode mode);
    SentenceSendMode GetSendMode(){ return SendMode;}
    void SetRepeatTime( int rtime);
    int GetRepeatTime(){ return RepeatTime;}
    NmeaConverter_pi* plugin;
    bool UseDegrees;
private:
    wxString FormatString;
    wxArrayString NeededVariables;
    wxArrayString NeededSentences;
    wxArrayString NeededSentencesMinusReceived;
    ReceivedSentences ReceivedSentencesMap;
    wxString VarAlphaDigit;
    wxString VarAlpha;
    wxString VarDigit;
    //wxTimer* m_timer;
    bool DlgActive;
    bool ValidFormatStr;
    
    SentenceSendMode SendMode;
    int RepeatTime;
    localTimer* p_timer;
};

class localTimer :public wxTimer
{
public:   
    localTimer();
    void Create( nmeaSendObj* theObject );
    ~localTimer();
    void Notify();
    void start(int seconds);
private:
    nmeaSendObj* theNmeaSendObj;
};
//*******************************************************************************************


////@begin includes

////@end includes

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_PREFERENCEDLG 10000
#define ID_CHECKBOX 10001
#define ID_LISTCTRL 10002
#define ID_PANEL 10003
#define ID_BUTTON_NEW 10004
#define ID_BUTTON_EDIT 10005
#define ID_BUTTON_DEL 10006
#define ID_BUTTON_OK 10007
#define SYMBOL_PREFERENCEDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_PREFERENCEDLG_TITLE _("PreferenceDlg")
#define SYMBOL_PREFERENCEDLG_IDNAME ID_PREFERENCEDLG
#define SYMBOL_PREFERENCEDLG_SIZE wxSize(400, 300)
#define SYMBOL_PREFERENCEDLG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * PreferenceDlg class declaration
 */

class PreferenceDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( PreferenceDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    PreferenceDlg();
    PreferenceDlg( NmeaConverter_pi* plugin, wxWindow* parent, wxWindowID id = SYMBOL_PREFERENCEDLG_IDNAME, const wxString& caption = SYMBOL_PREFERENCEDLG_TITLE, const wxPoint& pos = SYMBOL_PREFERENCEDLG_POSITION, const wxSize& size = SYMBOL_PREFERENCEDLG_SIZE, long style = SYMBOL_PREFERENCEDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PREFERENCEDLG_IDNAME, const wxString& caption = SYMBOL_PREFERENCEDLG_TITLE, const wxPoint& pos = SYMBOL_PREFERENCEDLG_POSITION, const wxSize& size = SYMBOL_PREFERENCEDLG_SIZE, long style = SYMBOL_PREFERENCEDLG_STYLE );

    /// Destructor
    ~PreferenceDlg();
    void Init();
    void CreateControls();
    void OnCheckboxClick( wxCommandEvent& event );
    void OnButtonNewClick( wxCommandEvent& event );
    void OnButtonEditClick( wxCommandEvent& event );
    void OnButtonDelClick( wxCommandEvent& event );
    void OnButtonOkClick( wxCommandEvent& event );
    void OnListViewSelected( wxListEvent& event );
    void UpdateListCtrFromMap();
    void UpdateGUI();

    wxBitmap GetBitmapResource( const wxString& name );
    wxIcon GetIconResource( const wxString& name );
    static bool ShowToolTips();
private:
    wxArrayString itemListBoxStrings;
    wxCheckBox* itemCheckBoxUseChecksum;
    wxListView* itemListView;
    wxListItem col0;
    wxListItem col1;
    wxButton* itemButtonEdit;
    wxButton* itemButtonDel;
    wxWindow* parentwindow;
    NmeaConverter_pi* pi;
};

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_NMEASENDOBJECT 10020
#define ID_RADIOBUTTON 10001
#define ID_RADIOBUTTON1 10002
#define ID_SPINCTRL 10003
#define ID_TEXTCTRL 10004
#define ID_BUTTON_OK1 10005
#define ID_BUTTON_CANCEL 10006
#define ID_CHECKBOXDEG 10008
#define SYMBOL_NMEASENDOBJECTDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_NMEASENDOBJECTDLG_TITLE _("nmeaSendObjectDlg")
#define SYMBOL_NMEASENDOBJECTDLG_IDNAME ID_NMEASENDOBJECT
#define SYMBOL_NMEASENDOBJECTDLG_SIZE wxSize(312, 200)
#define SYMBOL_NMEASENDOBJECTDLG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * nmeaSendObjectDlg class declaration
 */

class nmeaSendObjectDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( nmeaSendObjectDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    nmeaSendObjectDlg();
    nmeaSendObjectDlg( wxWindow* parent, wxWindowID id = SYMBOL_NMEASENDOBJECTDLG_IDNAME, const wxString& caption = SYMBOL_NMEASENDOBJECTDLG_TITLE, const wxPoint& pos = SYMBOL_NMEASENDOBJECTDLG_POSITION, const wxSize& size = SYMBOL_NMEASENDOBJECTDLG_SIZE, long style = SYMBOL_NMEASENDOBJECTDLG_STYLE );
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_NMEASENDOBJECTDLG_IDNAME, const wxString& caption = SYMBOL_NMEASENDOBJECTDLG_TITLE, const wxPoint& pos = SYMBOL_NMEASENDOBJECTDLG_POSITION, const wxSize& size = SYMBOL_NMEASENDOBJECTDLG_SIZE, long style = SYMBOL_NMEASENDOBJECTDLG_STYLE );
    ~nmeaSendObjectDlg();
    void Init();
    void CreateControls();
    void SetSendObjOfThisDlg( nmeaSendObj* object);
    void SetOutputStrTxt(wxString str);
    void OnRadiobuttonSelected( wxCommandEvent& event );
    void OnRadioButtonTimeSelected( wxCommandEvent& event );
    void OnSpinctrlUpdated( wxSpinEvent& event );
    void OnTextctrlTextUpdated( wxCommandEvent& event );
    void OnButtonOkClick( wxCommandEvent& event );
    void OnButtonCancelClick( wxCommandEvent& event );
    void OnUseDegreesClick ( wxCommandEvent& event );
    wxBitmap GetBitmapResource( const wxString& name );
    wxIcon GetIconResource( const wxString& name );
    static bool ShowToolTips();
    
    nmeaSendObj* SendObjOfThisDlg;
    wxSpinCtrl* itemSpinCtrl;
    wxRadioButton* itemRadioButtonVal;
    wxRadioButton* itemRadioButtonTime;
    wxStaticText* itemStaticTextSendString;
    wxTextCtrl* itemTextCtrlFormatStrCtr;
    wxButton* itemOKButton;
    wxButton* itemCancelButton;
    wxCheckBox* itemCheckBoxUseDegrees;
};


#endif //NMEACONV_H



