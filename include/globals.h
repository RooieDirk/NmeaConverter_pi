/******************************************************************************
 * $Id: testplugin_pi.h,v 1.0 2015/01/28 01:54:37 jongough Exp $
 *
 * Project:  OpenCPN
 * Purpose:  OpenCPN General Drawing Plugin
 * Author:   Jon Gough
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *   $EMAIL$   *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
 ***************************************************************************
 */
#ifndef _TPGLOBALS_H_
#define _TPGLOBALS_H_

class tpicons;
class tpControlDialogImpl;

#define testplugin_POSITION -1
#define ID_NONE -1
//    Constants for right click menus

#define SELTYPE_UNKNOWN             0x0001
#define SELTYPE_ODPOINT             0x0002
#define SELTYPE_PATHSEGMENT         0x0004
#define SELTYPE_PATHCREATE          0x0008
#define SELTYPE_BOUNDARYLIST        0x0010
#define SELTYPE_PIL                 0x0020
#define TYPE_PATHMGR_PATH_DLG       0x0040
#define TYPE_PATHMGR_POINT_DLG      0x0080
#define TYPE_PATHMGR_LAYER_DLG      0x0100


// Needed for ocpndc.cpp to compile. Normally would be in glChartCanvas.cpp
extern float g_GLMinSymbolLineWidth;


#endif
