
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

#ifndef vision_h
#define vision_h

//------------------------------------------

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "../../lib/ec_defs.h"
#include "../../lib/ec_matrix.h"

//------------------------------------------

#define wxCL_RED    1
#define wxCL_GREEN  2
#define wxCL_BLUE   4
#define wxCL_GREY   8

enum {
    OP_NOTHING = 1,
    OP_AUTOTRANSPOSE,
    OP_ADDCUSTOMFILTER,
    OP_DIRECT,
    OP_INDIRECT
};

class wxVisionManager
{
    private:
        wxImage m_image;
        wxEcMatrix m_filter, m_tfilter;

        unsigned char *undobuffer;
        int undobuffersize;
        wxRealPoint histoR[256], histoG[256], histoB[256], histoN[256];

        void PrepareUndo();
        bool ApplyFilter(int whattodo = OP_NOTHING);
        void BubbleSort(unsigned char* ldata, unsigned int len);
        void AdjustRange(int* red, int* green, int* blue);

    public:
        wxVisionManager();
        wxVisionManager(wxString filename);
        ~wxVisionManager();
        void BackupImage(unsigned char *source, unsigned char *destination, unsigned int count);

        void Undo();

        void OpenImage(wxString filename);
        wxImage* GetImage();
        wxEcMatrix* GetFilter();
        void ResetHistogram();
        void ComputeHistogram();
        wxRealPoint* GetRedData();
        wxRealPoint* GetGreenData();
        wxRealPoint* GetBlueData();
        wxRealPoint* GetGreyData();

        void KickColour(int colourmask);
        void GreyScale();
        void Generalize(int colourmask);
        void UseBlack(unsigned char threshold = 30);
        void Inverse();
        void RotateColours();
        void Equalization(unsigned char vmin, unsigned char vmax);
        void Binarization(unsigned char threshold, int usecase);
        void Luminosity(int offset);
        void Rgb2YCbCr();
        void YCbCr2Rgb();
        void Rgb2Yiq();
        void Yiq2Rgb();

        void Dilate(wxEcMatrix& tool);
        void Erode(wxEcMatrix& tool);

        bool RunFilter();
        bool LowPass(unsigned char radius);
        bool GaussianSmoothing(unsigned char radius, double sigma);
        bool Laplacian(bool smoothing = false, unsigned char radius = 2, double sigma = 0.8);
        bool Prewitt();
        bool Sobel();
        bool Edges();
        bool DrawEdges();
        bool Rise();
        bool Median(unsigned char radius);
};

#endif
