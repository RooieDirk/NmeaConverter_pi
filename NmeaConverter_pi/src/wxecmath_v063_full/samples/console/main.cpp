
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

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

//------------------------------------------

// You may setup your project to include "wxECM_USEDEBUG" in the command line

#include "wx/file.h"
#include "../../lib/ec_defs.h"
#include "../../lib/ec_engine.h"

#define wxCONSOLEBUFFER        4096

#ifdef wxUSE_UNICODE
    #define uniPrint wprintf
    #define uniScan  wscanf
#else
    #define uniPrint printf
    #define uniScan  scanf
#endif

//------------------------------------------

size_t ProcessPipe()
{
    //-- Initialization
    wxEcEngine *calc;
    wxString *data;
    wxChar stdinBuffer[wxCONSOLEBUFFER+1];
    wxFile fInput, fOutput;
    size_t numRead, exitCode;

    //-- Computes
    fInput.Attach(wxFile::fd_stdin);
    numRead = fInput.Read(&stdinBuffer, wxCONSOLEBUFFER);
    if ((numRead>0) && (numRead<=wxCONSOLEBUFFER))
    {
        stdinBuffer[numRead] = (wxChar) 0;
        data = new wxString(stdinBuffer);
        *data = data->BeforeFirst(wxT('\r'));
        *data = data->BeforeFirst(wxT('\n'));
            calc = new wxEcEngine();
            calc->UseDebug(false);
                calc->SetFormula(*data);
                *data = wxString::Format(wxT("%f"), calc->Compute());
                exitCode = calc->GetLastError();

                //-- Output
                fOutput.Attach(wxFile::fd_stdout);
                fOutput.Write(*data);
                fOutput.Close();
            wxDELETE(calc);
        wxDELETE(data);
    }
    fInput.Detach();
    return exitCode;
}

size_t ProcessConsole()
{
    //-- Initialization
    wxChar userBuffer[wxCONSOLEBUFFER+1];
    wxString userBufferStr;
    wxEcEngine *calc;
    wxArrayString calcDump;
    double result;
    #ifdef wxECM_USEDEBUG
        unsigned int i;
    #endif

    //-- Computes
    calc = new wxEcEngine();
    calc->UseDebug(true);

    uniPrint(wxT("\n\
  %s %s - Sample: console\n\
  %s\n\n\
***********************************************************\n\n\
   \"exit\" to quit, \"ans\" to call the last result.\n\
   Never use space character !\n\n\n"), wxECD_SOFTWARE, wxECD_VERSION, wxECD_URL);

RedoConsole:
        uniPrint(wxT("> "));
        fflush(stdin);
        uniScan(wxT("%s"), &userBuffer);

        if ((userBuffer[0]!=wxT('e')) || (userBuffer[1]!=wxT('x')) || (userBuffer[2]!=wxT('i')) || (userBuffer[3]!=wxT('t')))
        {
            userBufferStr = wxString(userBuffer);
            if (userBufferStr.StartsWith(wxT("-")))
                uniPrint(wxT("! Make sure you didn't want to write \"ans-this\"\n"));
            else
                if (userBufferStr.StartsWith(wxT("+")) || userBufferStr.StartsWith(wxT("/")) || userBufferStr.StartsWith(wxT("*")))
                {
                    userBufferStr = wxT("ans") + userBufferStr;
                    uniPrint(wxT("! \"ans\" added automatically\n"), result);
                }
            calc->SetFormula(userBufferStr);
            if (calc->GetLastError() == wxECE_NOERROR)
            {
                result = calc->Compute();
                if (calc->GetLastError() == wxECE_NOERROR)
                    calc->SetConstant(wxT("ans"), result);
            }
            else
                result = 0.0;

            #ifdef wxECM_USEDEBUG
                uniPrint(wxT("\n"));
                calcDump = calc->GetLog();
                for (i=0 ; i<calcDump.GetCount() ; i++)
                    uniPrint(wxT("     | %s\n"), calcDump.Item(i).Trim(false).Trim(true).c_str());
                uniPrint(wxT("     |\n     | %s\n     | Tip : %s\n\nResult = %f\n\n"), calc->TranslateError(calc->GetLastError()).c_str(), calc->GetIndicator().c_str(), result);
            #else
                if (calc->GetLastError() == wxECE_NOERROR)
                    uniPrint(wxT("< %f\n\n"), result);
                else
                    uniPrint(wxT("X %s\n\n"), calc->TranslateError(calc->GetLastError()).c_str());
            #endif
            goto RedoConsole;
        }

    wxDELETE(calc);
    return 0;
}

int main(int argc, char* argv[])
{
    return ProcessConsole();

    //To use as a pipe interpreter, replace with:     return ProcessPipe();
}
