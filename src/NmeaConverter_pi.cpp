
/******************************************************************************
 * updated: 25-04-2015  
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



#include <wx/tokenzr.h>
#include <algorithm>    // std::max
#include "NmeaConverter_pi.h"
#include "icons.h"

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new NmeaConverter_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

NmeaConverter_pi::NmeaConverter_pi(void *ppimgr):opencpn_plugin_18(ppimgr)
{
          // Create the PlugIn icons
      initialize_images();
}

int NmeaConverter_pi::Init(void)
{
    prefDlg = NULL;
    p_nmeaSendObjectDlg=NULL;
    b_CheckChecksum = true;
    //    Get a pointer to the opencpn configuration object
    m_pconfig = GetOCPNConfigObject();
    //    And load the configuration items
    LoadConfig();
    return ( WANTS_NMEA_SENTENCES | WANTS_PREFERENCES );
}

bool NmeaConverter_pi::DeInit(void)
{
    for( objit = ObjectMap.begin(); objit != ObjectMap.end(); ++objit )
                objit->second->~nmeaSendObj();    
    return true;
}

int NmeaConverter_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int NmeaConverter_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int NmeaConverter_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int NmeaConverter_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxString NmeaConverter_pi::GetCommonName()
{
      return _("NmeaConverter_pi");
}

wxString NmeaConverter_pi::GetShortDescription()
{
      return _("Plugin for manipulating nmea sentences");
}

wxString NmeaConverter_pi::GetLongDescription()
{
      return _T("Plugin for manipulating nmea sentences.\n\
Cherry picking from existing sentences, calculate new data with\n\
spreadsheet like formulas or just plain send  new sentences.\n\
Not easy, although it is easy to make errors and crash OpenCPN");

}

wxBitmap *NmeaConverter_pi::GetPlugInBitmap()
{
      return _img_nmeaconverter_pi;
}

void NmeaConverter_pi::SetNMEASentence(wxString &sentence)
{
    wxString s = sentence; //local copy of sentence
    s.Trim(); // Removes white-space (space, tabs, form feed, newline and carriage return)
    if ( b_CheckChecksum )
    {      
        if ( nmeaIsValid( s ) )
        {
            //send to all objects
            for ( auto const &ent1 : ObjectMap)
                ent1.second->SetNMEASentence(s);
                //objit->second->SetNMEASentence(s);       
        }
    }
    else
    {
        for ( auto const &ent1 : ObjectMap)
                ent1.second->SetNMEASentence(s);
    }
    
}

void NmeaConverter_pi::SendNMEASentence(wxString sentence)
{
    sentence.Trim();
    wxString Checksum = ComputeChecksum(sentence);
    sentence = sentence.Append(wxT("*"));
    sentence = sentence.Append(Checksum);
    sentence = sentence.Append(wxT("\r\n"));
    PushNMEABuffer(sentence);
}

bool NmeaConverter_pi::nmeaIsValid( wxString &sentence)
{
    bool r = false;
    wxString s = sentence;
    wxString checksum; 
    if ( s.Mid( s.Length() -3,1 ) == _("*") )
    {
        checksum = s.Right(2);        
        s = s.Left( s.Length() -3 );
        if ( ComputeChecksum( s ) == checksum )
        {            
            r = true;
        }
    }
    else
        r = true; // if no checksum available then result is also true
    sentence = s;
    return r;
}

int NmeaConverter_pi::AddObjectToMap( nmeaSendObj* object, SentenceSendMode Mode, int RepTime, bool Degr)
{
    int index;
    if ( ObjectMap.empty() ) // map is wxEmptyString
        index = 0;
    else 
        index = ObjectMap.size();
    ObjectMap[index] = object;
    object->SetSendMode( Mode );
    object->SetRepeatTime( RepTime );
    object->UseDegrees = Degr;
    return index;
}
void NmeaConverter_pi::ClearAllObjectsInMap()
{
    if ( !ObjectMap.empty() ) 
    {
        unsigned int i = 0;
        while(i < ObjectMap.size() ) //clear the ojects
        {
            nmeaSendObj* CurrObj = ObjectMap[i];
            delete CurrObj;
            i++;
        }
        ObjectMap.clear(); //and clear the map
    }
}
wxString NmeaConverter_pi::ComputeChecksum( wxString sentence )
{
    unsigned char calculated_checksum = 0;
    for(wxString::const_iterator i = sentence.begin()+1; i != sentence.end() && *i != '*'; ++i)
        calculated_checksum ^= static_cast<unsigned char> (*i);

   return( wxString::Format(_("%02X"), calculated_checksum) );
}


void NmeaConverter_pi::ShowPreferencesDialog( wxWindow* parent )
{
    LoadConfig();
    if ( prefDlg == NULL )
    {        
        prefDlg = new PreferenceDlg(this, parent);
    }
    
    if ( prefDlg->ShowModal() == wxID_OK )
    {
        SaveConfig();        
    }
    //DialogWindows are deleted after closing?? So we do it here and set pointers to NULL
    try
    {
        prefDlg->Destroy();
        prefDlg = NULL;
 //       p_nmeaSendObjectDlg->Destroy();
    }
    catch(...)
    { wxPuts(_("Dlg already deleted:_)"));}
    
    prefDlg = NULL;
//    p_nmeaSendObjectDlg=NULL;    
}

bool NmeaConverter_pi::SaveConfig( void )
{
    wxFileConfig *pConf = (wxFileConfig *) m_pconfig;
    int count = (int) ObjectMap.size();
    int i = 1;
    if( pConf ) 
    {
        pConf->SetPath( _T("/PlugIns/NmeaConverter") );
        pConf->Write( _T("DoUseCheckSums"), b_CheckChecksum );
        pConf->Write( _T("ObjectCount" ), count );
        for( objit = ObjectMap.begin(); objit != ObjectMap.end(); ++objit )
        {
            nmeaSendObj* CurrObj = objit->second;
            pConf->SetPath( wxString::Format( _T("/PlugIns/NmeaConverter/Object%d"), i  ) );
            pConf->Write( _T("FormatString"),CurrObj->GetFormatStr() );
            pConf->Write( _T("SendMode"),int(CurrObj->GetSendMode() ) );
            pConf->Write( _T("RepeatTime"),int(CurrObj->GetRepeatTime() ) );
            pConf->Write( _T("CalcDegrees"),bool(CurrObj->UseDegrees ) );
            i++;
        }
        return true;
    } else
        return false;
}

bool NmeaConverter_pi::LoadConfig( void )
{
    wxFileConfig *pConf = (wxFileConfig *) m_pconfig;

    if( pConf ) {
        pConf->SetPath( _T("/PlugIns/NmeaConverter") );
        pConf->Read( _T("DoUseCheckSums"), &b_CheckChecksum, true );
        int o_cnt;
        pConf->Read( _T("ObjectCount"), &o_cnt, -1 );
        ClearAllObjectsInMap();
        for( int i = 1; i <= o_cnt; i++ )
        {
            pConf->SetPath( wxString::Format( _T("/PlugIns/NmeaConverter/Object%d"), i  ) );
            wxString FormatS;
            pConf->Read( _T("FormatString"), &FormatS, wxEmptyString );
            int SendModeInt;
            pConf->Read( _T("SendMode"), &SendModeInt, int(ALLVAL) );
            int RepTime;
            pConf->Read( _T("RepeatTime"), &RepTime, 1 );
            bool UseDeg;
            pConf->Read( _T("CalcDegrees"), &UseDeg, false );
              AddObjectToMap( new nmeaSendObj( this, FormatS), SentenceSendMode(SendModeInt), RepTime, UseDeg  );
            
        }
        return true;
    } else
        return false;
}

//************************************************************************************
nmeaSendObj::nmeaSendObj()
{    
}
nmeaSendObj::nmeaSendObj(NmeaConverter_pi* pi, wxString FormatStr)
{
    //set some variables
    plugin = pi;
    DlgActive = false;
    SendMode = ALLVAL;
    RepeatTime = 1;
    p_timer = NULL;
    ValidFormatStr = false;
    VarAlphaDigit = wxT("$ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789?");
    VarAlpha = wxT("$ABCDEFGHIJKLMNOPQRSTUVWXYZ?");
    VarDigit = wxT("0123456789");
    //parse Formatstring into arrays 
    SetFormatString( FormatStr );
}
nmeaSendObj::~nmeaSendObj()
{
    if (p_timer != NULL) 
    {
        localTimer* t = p_timer;
        delete t;
    }
       
}

void nmeaSendObj::SetFormatString(wxString FormatStr)
{
    if( FormatStr == wxEmptyString )
        FormatStr = wxT("$DummyFormat");
    FormatString=FormatStr;   
    //find needed Variables
    NeededVariables = FindStartWithDollarSubSets( FormatStr, VarAlphaDigit);
    //find needed Sentences
    NeededSentences.Clear();
    unsigned int i = 0; 

    while ( i < NeededVariables.Count() )
    {
        unsigned int j = 0;
        while (( ( VarAlpha.Find(NeededVariables[i].Mid(j,1)) >= 0 ) ) && 
                (j < NeededVariables[i].Length()-1))
          j++;

        if ( NeededSentences.Index( NeededVariables[i].Mid(0,j) ) == wxNOT_FOUND )
            NeededSentences.Add( NeededVariables[i].Mid(0,j) );
        i++;
    }
    NeededSentencesMinusReceived = NeededSentences;   
}

wxArrayString nmeaSendObj::FindStartWithDollarSubSets(wxString FormatStr, wxString AllowdCharStr)
{  //Find pieces of text starting with'$' wich are the variables used
    size_t startpos=2;
    
    wxArrayString ReturnArray;

    {
        while ( (FormatStr.find( wxT("$"), startpos ) != (size_t)wxNOT_FOUND) &&( startpos < FormatStr.Length() ))
        {
            startpos = FormatStr.find( wxT("$"), startpos );
            size_t i = startpos;
        
            while ( ( AllowdCharStr.find(FormatStr.Mid(i,1)) != (size_t)wxNOT_FOUND ) & 
                    ( i < FormatStr.Length() ) )
            {  
                i++;
            }
            
            wxString SubString= FormatStr.SubString( startpos, i-1 );
            // Check if Substring has a valid value. Should end with a digit
            long test = 0;
            wxString s;
            SplitStringAlphaDigit(SubString, s, test);
            if (( test > 0 ) && (SubString.Length() > 4))
                if ( ReturnArray.Index( SubString ) == wxNOT_FOUND )
                    {
                        ReturnArray.Add( SubString );
                    }
            startpos = i;
        } 
    }
    return ReturnArray;
}
void nmeaSendObj::SplitStringAlphaDigit(wxString theStr, wxString &alpha, long &digiti)
{
    wxString digit;
    for ( unsigned int i = 0; i < theStr.length(); i++ )
        if ( VarAlpha.Find(theStr.Mid(i,1)) != wxNOT_FOUND )
            alpha.Append( theStr.Mid(i,1) );
        else if ( VarDigit.Find(theStr.Mid(i,1)) != wxNOT_FOUND )
            digit.Append( theStr.Mid(i,1) );
    if(!digit.ToLong(&digiti)) { digiti=-1; }    
}

void nmeaSendObj::SetNMEASentence(wxString &sentence)
{
    unsigned int i = 0;
    while ( i < NeededSentences.GetCount() )
    {
        wxString s = sentence.Left( NeededSentences[i].Length() );
        if  ( s.Matches(NeededSentences[i]) ) //we have a wildcard match
        {
            ReceivedSentencesMap[NeededSentences[i]] = sentence; //save sentence
            int j = NeededSentencesMinusReceived.Index(NeededSentences[i]);
            if (  j != wxNOT_FOUND ){//!= wxNOT_FOUND )
                NeededSentencesMinusReceived.RemoveAt(j);
            }
        }
        i++;
    }
    if ( NeededSentencesMinusReceived.IsEmpty() & ( SendMode == ALLVAL) )
    {
        ComputeOutputSentence();
        NeededSentencesMinusReceived = NeededSentences;
    }
}

void nmeaSendObj::ComputeOutputSentence()
{
    wxString sendFormat = FormatString;
    //iterate through variables and update values
    //The variablesArray is set in SetFormatString()
    for( int i = 0; i < (int)NeededVariables.GetCount(); i++ )
    {
        //split variable inname and number
        wxString Varkey = NeededVariables[i];
        wxString SenteceKey;
        long FieldNo;
        SplitStringAlphaDigit( Varkey, SenteceKey, FieldNo);
        
        //put nmea sentence in array. each field in separate cell
        wxArrayString nmeatokenarray; //array with tokenized nmea sentence
        wxString s = ReceivedSentencesMap[SenteceKey];
        wxStringTokenizer tkznmea(s, wxT(","));
        while ( tkznmea.HasMoreTokens() )
            nmeatokenarray.Add( tkznmea.GetNextToken() );
        //replace variable name by value
        if ((long)nmeatokenarray.GetCount() >= FieldNo )
            sendFormat.Replace( Varkey , nmeatokenarray[FieldNo] );
        else
            sendFormat.Replace( Varkey , wxT("noData") );
    }
    //by now the variables in our formatstr are replaced by values.
    
    //split formatstring in fields, so we can calculate each field apart
    wxArrayString formattokenarray;
    wxStringTokenizer tkzformat(sendFormat, wxT(","));
        while ( tkzformat.HasMoreTokens() )
            formattokenarray.Add( tkzformat.GetNextToken() );
    for (int j=1 ; j < (int)formattokenarray.GetCount(); j++)
    {
        // find max number of decimals so we can set the output later to the right amount of needed decimals.
        size_t NoOfDecimals = 0;
        size_t NoOfDigits = 0;
        size_t IinString = 0;
        bool IsValidNumber= true;
        wxString s=formattokenarray[j];
        
        while (IinString < s.Length()){
            // Go to start of begin number
            while ( _("0123456789.").find( s[IinString] ) == (size_t)wxNOT_FOUND )
                if(IinString < s.Length()) IinString++; else break;
            
            wxString temp_s;
            while ( _("0123456789.").find( s[IinString] ) != (size_t)wxNOT_FOUND ){             
                if(IinString < s.Length()){
                    temp_s.Append(s[IinString]);
                    IinString++;                
                }
                    else break;
            }  // temp_s contains now one number
            if ( temp_s.find( _(".") ) != (size_t)wxNOT_FOUND ){ // floatingpoint number
                double value;
                if(!temp_s.ToDouble(&value)){ IsValidNumber = false; }
                NoOfDecimals = std::max(NoOfDecimals, temp_s.Length()-temp_s.find( _(".") ) - 1 );
                if ( (temp_s.Left(1) == _("0")) & (temp_s.find( _(".")) > 1) )
                    NoOfDigits = std::max( NoOfDigits,  temp_s.find( _(".") ) );
            } else{ //integer no
                long value;
                if(!temp_s.ToLong(&value)) { IsValidNumber = false; }
                if ( temp_s.Left(1) == _("0") )
                    NoOfDigits = std::max( NoOfDigits,  temp_s.Length() );
            }
        }    
        
        wxString result;
        wxEcEngine calc;
        if (UseDegrees) calc.SetTrigonometricMode(wxECA_DEGREE);
        if (calc.SetFormula( formattokenarray[j] ))
        {
            result = wxString::Format(wxT("%.*f"), NoOfDecimals, calc.Compute() );
            if (NoOfDigits){
                printf("NoOfDigits = %d\n", (int)NoOfDigits);
                wxString t(_("0000000000") );
                t.Append(result);
                result = t.Right(NoOfDecimals + 1 + NoOfDigits);
            }
            if ( (calc.GetLastError() == wxECE_NOERROR) & IsValidNumber )
            {
                 formattokenarray[j] = result;
            }//else
             //   formattokenarray[j] = _("#Error#");
        }
    }
    // finaly glue the seperate tokens back to one sentence
    
    sendFormat = formattokenarray[0];
    for (int j=1 ; j < (int)formattokenarray.GetCount(); j++)
    {
        sendFormat.Append(_(","));
        sendFormat.Append( formattokenarray[j] );
    }
    
    if ( DlgActive )
        plugin-> p_nmeaSendObjectDlg->SetOutputStrTxt(sendFormat);
    else
        plugin->SendNMEASentence(sendFormat);
}

int  nmeaSendObj::ShowModal (wxWindow* parent)
{
    // temp store variables
    wxString temp_FormatString = FormatString;
    SentenceSendMode temp_SendMode = SendMode;

    if( plugin->p_nmeaSendObjectDlg == NULL)
        plugin->p_nmeaSendObjectDlg = new nmeaSendObjectDlg( parent );
    DlgActive = true; // send sentences to dlg insteade of the big wide open.
    plugin->p_nmeaSendObjectDlg->SetSendObjOfThisDlg(this); // tell dlg the object it should use 
    int  r = plugin->p_nmeaSendObjectDlg->ShowModal();
    
    if ( r != wxID_OK ) //return status dlg is not OK set back stored varibles
    {
        SetFormatString(temp_FormatString);
        SendMode = temp_SendMode;
    }
    plugin->p_nmeaSendObjectDlg->Destroy();
    plugin->p_nmeaSendObjectDlg = NULL;
    DlgActive = false;
    return r;
}

void nmeaSendObj::SetSendMode(SentenceSendMode mode)
{
    SendMode = mode;
    if ( SendMode == TIMED )
    {
        if ( p_timer == NULL )
        {
            p_timer = new localTimer();
            p_timer->Create(this);
        }
        p_timer->start(RepeatTime);
    }
    else
        if ( p_timer != NULL )
            p_timer->Stop();
}
void nmeaSendObj::SetRepeatTime( int rtime)
{
    RepeatTime = rtime;
    if ( p_timer != NULL )
        p_timer->start(RepeatTime);
}

//*******************************************************************************************
localTimer::localTimer():wxTimer()
{
}
void localTimer::Create( nmeaSendObj* theObject )
{
    theNmeaSendObj = theObject;
}

localTimer::~localTimer()
{
}

void localTimer::Notify()
{
    theNmeaSendObj->ComputeOutputSentence();    
}

void localTimer::start(int seconds)
{
    wxTimer::Start( seconds * 1000 );
}


//*******************************************************************************************

IMPLEMENT_DYNAMIC_CLASS( PreferenceDlg, wxDialog )


BEGIN_EVENT_TABLE( PreferenceDlg, wxDialog )

    EVT_CHECKBOX( ID_CHECKBOX, PreferenceDlg::OnCheckboxClick )
    EVT_BUTTON( ID_BUTTON_NEW, PreferenceDlg::OnButtonNewClick )
    EVT_BUTTON( ID_BUTTON_EDIT, PreferenceDlg::OnButtonEditClick )
    EVT_BUTTON( ID_BUTTON_DEL, PreferenceDlg::OnButtonDelClick )
    EVT_BUTTON( ID_BUTTON_OK, PreferenceDlg::OnButtonOkClick )
    EVT_LIST_ITEM_SELECTED( ID_LISTCTRL, PreferenceDlg::OnListViewSelected )

END_EVENT_TABLE()


PreferenceDlg::PreferenceDlg()
{
    Init();
}

PreferenceDlg::PreferenceDlg( NmeaConverter_pi* plugin, wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{ 
    Create(parent, id, caption, pos, size, style);
    pi = plugin;
    Init();
    UpdateListCtrFromMap();
}

bool PreferenceDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{

    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    //Centre();
    parentwindow = parent;
    return true;
}

PreferenceDlg::~PreferenceDlg()
{
    pi->prefDlg = NULL;
}

void PreferenceDlg::Init()
{
    itemCheckBoxUseChecksum->SetValue( pi->b_CheckChecksum );
}

void PreferenceDlg::CreateControls()
{    
////@begin PreferenceDlg content construction
    PreferenceDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    itemCheckBoxUseChecksum = new wxCheckBox( itemDialog1, ID_CHECKBOX, _("Block incomming messages with wrong checksum"), wxDefaultPosition, wxDefaultSize, 0 );
    
    itemBoxSizer2->Add(itemCheckBoxUseChecksum, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    
    itemListView = new wxListView( itemDialog1, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL );
    itemBoxSizer2->Add(itemListView, 0, wxGROW|wxALL, 5);
         // Add first column       
        wxListItem col0;
        col0.SetId(0);
        col0.SetWidth(50);
        itemListView->InsertColumn(0, col0); 
        // Add second column
        wxListItem col1;
        col1.SetId(1);
        col1.SetWidth(330);
        itemListView->InsertColumn(1, col1);

    wxPanel* itemPanel5 = new wxPanel( itemDialog1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel5->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    itemBoxSizer2->Add(itemPanel5, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemPanel5->SetSizer(itemBoxSizer6);

    wxButton* itemButton7 = new wxButton( itemPanel5, ID_BUTTON_NEW, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemButtonEdit = new wxButton( itemPanel5, ID_BUTTON_EDIT, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButtonEdit, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    itemButtonEdit->Enable(false);

    itemButtonDel = new wxButton( itemPanel5, ID_BUTTON_DEL, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButtonDel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    itemButtonDel->Enable(false);
    
    wxButton* itemButton10 = new wxButton( itemPanel5, ID_BUTTON_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButton10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

}

void PreferenceDlg::OnCheckboxClick( wxCommandEvent& event )
{
    pi->b_CheckChecksum = itemCheckBoxUseChecksum->GetValue();
    event.Skip();
}
void PreferenceDlg::OnButtonNewClick( wxCommandEvent& event )
{    
   //make new object and add it to list so it will receive nmea messages
   nmeaSendObj* newObj = new nmeaSendObj(pi, wxEmptyString);
   int indexno = pi->AddObjectToMap( newObj );
   
   // if not OK then remove again from list
   if ( newObj->ShowModal( parentwindow) != wxID_OK )
   {
       pi->ObjectMap[indexno]->~nmeaSendObj();//delete object
       pi->ObjectMap.erase(indexno);
   }
    UpdateListCtrFromMap();   
    event.Skip();
}

void PreferenceDlg::OnButtonEditClick( wxCommandEvent& event )
{
    long listi = itemListView->GetFirstSelected();
    wxString indexstr = itemListView->GetItemText(listi);
    long index;
    if(!indexstr.ToLong(&index)) { /* error! */ }
    if ( pi->ObjectMap[index]->ShowModal(parentwindow) == wxID_OK )
        UpdateListCtrFromMap();
    
    event.Skip();
}

void PreferenceDlg::OnButtonDelClick( wxCommandEvent& event )
{
    long listi = itemListView->GetFirstSelected();
    wxString indexstr = itemListView->GetItemText(listi);
    long index;
    if(!indexstr.ToLong(&index)) { /* error! */ }
    pi->ObjectMap[index]->~nmeaSendObj(); //delete object
    pi->ObjectMap.erase(index);
    
    UpdateListCtrFromMap();
    event.Skip();
}

void PreferenceDlg::OnButtonOkClick( wxCommandEvent& event )
{
    this->EndModal( wxID_OK );
    event.Skip();
}
void PreferenceDlg::OnListViewSelected( wxListEvent& event )
{
    UpdateGUI();
    event.Skip();
}
void PreferenceDlg::UpdateListCtrFromMap()
{     
    itemListView->DeleteAllItems();
    for( pi->objit = pi->ObjectMap.begin(); pi->objit != pi->ObjectMap.end(); ++pi->objit )
    {
        long itemIndex = itemListView->InsertItem(0, wxString::Format( wxT("%i"),pi->objit->first ) ); //want this for col. 1
        wxString a = pi->objit->second->GetFormatStr();
        itemListView->SetItem(itemIndex, 1, a );//want this for col. 2       
    }
    UpdateGUI();
}
void PreferenceDlg::UpdateGUI()
{
    if ( itemListView->GetFocusedItem() != -1 ) //something is selected
    {
        itemButtonEdit->Enable(true);
        itemButtonDel->Enable(true);
    }
    else
    {
        itemButtonEdit->Enable(false);
        itemButtonDel->Enable(false);
    }
        
}


bool PreferenceDlg::ShowToolTips()
{
    return true;
}

wxBitmap PreferenceDlg::GetBitmapResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon PreferenceDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin PreferenceDlg icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end PreferenceDlg icon retrieval
}

IMPLEMENT_DYNAMIC_CLASS( nmeaSendObjectDlg, wxDialog )

BEGIN_EVENT_TABLE( nmeaSendObjectDlg, wxDialog )

    EVT_RADIOBUTTON( ID_RADIOBUTTON, nmeaSendObjectDlg::OnRadiobuttonSelected )
    EVT_RADIOBUTTON( ID_RADIOBUTTON1, nmeaSendObjectDlg::OnRadioButtonTimeSelected )
    EVT_SPINCTRL( ID_SPINCTRL, nmeaSendObjectDlg::OnSpinctrlUpdated )
    EVT_TEXT( ID_TEXTCTRL, nmeaSendObjectDlg::OnTextctrlTextUpdated )
    EVT_BUTTON( ID_BUTTON_OK1, nmeaSendObjectDlg::OnButtonOkClick )
    EVT_BUTTON( ID_BUTTON_CANCEL, nmeaSendObjectDlg::OnButtonCancelClick )
    EVT_CHECKBOX( ID_CHECKBOXDEG, nmeaSendObjectDlg::OnUseDegreesClick )
END_EVENT_TABLE()


/*
 * nmeaSendObjectDlg constructors
 */

nmeaSendObjectDlg::nmeaSendObjectDlg()
{
    Init();
}

nmeaSendObjectDlg::nmeaSendObjectDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    
    Create(parent, id, caption, pos, size, style);
    Init();
}

bool nmeaSendObjectDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
    return true;
}

nmeaSendObjectDlg::~nmeaSendObjectDlg()
{
    SendObjOfThisDlg->plugin->p_nmeaSendObjectDlg = NULL;
}

void nmeaSendObjectDlg::Init()
{
    
}

void nmeaSendObjectDlg::CreateControls()
{    
    nmeaSendObjectDlg* itemDialog1 = this;
    
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);

    
    itemRadioButtonVal = new wxRadioButton( itemDialog1, ID_RADIOBUTTON, _("Send after update all variables"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    itemRadioButtonVal->SetValue(true);
    itemBoxSizer2->Add(itemRadioButtonVal, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
    itemBoxSizer2->Add(itemFlexGridSizer4, 0, wxALIGN_LEFT|wxALL, 0);

    itemRadioButtonTime = new wxRadioButton( itemDialog1, ID_RADIOBUTTON1, _("Send every  "), wxDefaultPosition, wxDefaultSize, 0 );
    itemRadioButtonTime->SetValue(false);
    itemFlexGridSizer4->Add(itemRadioButtonTime, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemSpinCtrl = new wxSpinCtrl( itemDialog1, ID_SPINCTRL, wxT("1"), wxDefaultPosition, wxSize(40, -1), wxSP_ARROW_KEYS, 1, 100, 1 );
    itemSpinCtrl->Enable(false);
    itemFlexGridSizer4->Add(itemSpinCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText1 = new wxStaticText( itemDialog1, wxID_STATIC, _("seconds."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemCheckBoxUseDegrees = new wxCheckBox( itemDialog1, ID_CHECKBOXDEG, _("Calculate using degrees"), wxDefaultPosition, wxDefaultSize, 0 );        
    itemBoxSizer2->Add(itemCheckBoxUseDegrees, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemStaticTextSendString = new wxStaticText( itemDialog1, wxID_STATIC, _("Output sentence comes here;-)"), wxPoint(5, 60), wxSize(300, -1), 0 );
    itemStaticTextSendString->SetForegroundColour(wxColour(0, 0, 255));
 //   itemStaticTextSendString->SetFont(wxFont(11, , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemBoxSizer2->Add(itemStaticTextSendString, 0, wxGROW|wxALL, 5);
    
    itemTextCtrlFormatStrCtr = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, wxEmptyString, wxPoint(5, 80), wxSize(300, 75), wxTE_MULTILINE|wxTE_WORDWRAP );
    itemBoxSizer2->Add(itemTextCtrlFormatStrCtr, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer1 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer1->AddButton(itemButton11);

    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer1->AddButton(itemButton12);

    itemStdDialogButtonSizer1->Realize();
    itemStdDialogButtonSizer1->Fit(this);
    itemDialog1->SetSizer(itemBoxSizer2);
    itemBoxSizer2->Fit(this);
}

void nmeaSendObjectDlg::SetSendObjOfThisDlg( nmeaSendObj* object)
{
    SendObjOfThisDlg = object;
    itemTextCtrlFormatStrCtr->SetValue( SendObjOfThisDlg->GetFormatStr() );
    if ( SendObjOfThisDlg->GetSendMode() == ALLVAL )
    { 
        itemRadioButtonVal->SetValue(true);
        itemRadioButtonTime->SetValue(false);
        itemSpinCtrl->Enable(false);
    }
    else
    { 
        itemRadioButtonVal->SetValue(false);
        itemRadioButtonTime->SetValue(true);
        itemSpinCtrl->Enable(true);
    }
    itemSpinCtrl->SetValue( SendObjOfThisDlg->GetRepeatTime() );
    itemCheckBoxUseDegrees->SetValue( SendObjOfThisDlg->UseDegrees );
}

void nmeaSendObjectDlg::SetOutputStrTxt(wxString str)
{
    itemStaticTextSendString->SetLabel( str );
}

void nmeaSendObjectDlg::OnRadiobuttonSelected( wxCommandEvent& event )
{
    itemSpinCtrl->Enable( itemRadioButtonTime->GetValue() ); 
    SendObjOfThisDlg->SetSendMode( ALLVAL );
    event.Skip();
}

void nmeaSendObjectDlg::OnRadioButtonTimeSelected( wxCommandEvent& event )
{
    itemSpinCtrl->Enable( itemRadioButtonTime->GetValue() );
    SendObjOfThisDlg->SetSendMode( TIMED );
    event.Skip();
}

void nmeaSendObjectDlg::OnSpinctrlUpdated( wxSpinEvent& event )
{
    SendObjOfThisDlg->SetRepeatTime( itemSpinCtrl->GetValue() ); 
    event.Skip();
}

void nmeaSendObjectDlg::OnTextctrlTextUpdated( wxCommandEvent& event )
{
    SendObjOfThisDlg->SetFormatString( itemTextCtrlFormatStrCtr->GetValue() );
    event.Skip();
}

void nmeaSendObjectDlg::OnButtonOkClick( wxCommandEvent& event )
{  
    this->EndModal( wxID_OK );
    event.Skip();
}

void nmeaSendObjectDlg::OnButtonCancelClick( wxCommandEvent& event )
{
    this->EndModal( wxID_CANCEL );
    event.Skip();
}
void nmeaSendObjectDlg::OnUseDegreesClick ( wxCommandEvent& event )
{
    SendObjOfThisDlg->UseDegrees = itemCheckBoxUseDegrees->GetValue();
}

bool nmeaSendObjectDlg::ShowToolTips()
{
    return true;
}

;
