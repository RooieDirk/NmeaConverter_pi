
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

/**
 * \file xh_wxecplot.h
 * \brief XRC support for wxEcPlot
 * \author ecrucru
 * \version 0.6.3
 * \date March 2009
 *
 * This header is useful to register class wxEcPlot into the XRC parser.
 * XRC is an XML file containing information about the user interface of
 * your software.
 */

#ifndef XH_WXECPLOT_H
#define XH_WXECPLOT_H

    #if wxUSE_XRC

//------------------------------------------

        #include "wx/wxprec.h"
        #ifdef __BORLANDC__
            #pragma hdrstop
        #endif
        #ifndef WX_PRECOMP
            #include "wx/wx.h"
        #endif

        #include "wx/xrc/xmlres.h"
        #include "xh_wxecplot.h"

//------------------------------------------

        /** \class wxEcPlotXmlHandler
         *  \brief Support for XRC.
         *
         * This class won't be activated if wxUSE_XRC is not equal to 1.
         */
        class WXDLLIMPEXP_XRC wxEcPlotXmlHandler : public wxXmlResourceHandler
        {
            DECLARE_DYNAMIC_CLASS(wxEcPlotXmlHandler)

            public:
                /** The default constructor.
                 */
                wxEcPlotXmlHandler();
                /** Allocates a new resource.
                 */
                virtual wxObject *DoCreateResource();
                /** Returns \a true if the XML node corresponds to wxEcPlot.
                 */
                virtual bool CanHandle(wxXmlNode *node);
        };

    #endif

#endif
