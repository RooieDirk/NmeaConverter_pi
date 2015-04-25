
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

/*------------------------------------------
 *
 *  According to wxImage::XYToIndex() :
 *
 *           _ _ _ _ _ x € [0 .. width-1]
 *          |
 *          |
 *          |    + (x,y)
 *          |
 *          |
 *          y € [0 .. height-1]
 *
------------------------------------------*/

#include "vision.h"

//------------------------------------------

wxVisionManager::wxVisionManager()
{
    //Don't call "wxVisionManager::wxVisionManager(wxEmptyString)".
    //It will generate a SIGSEGV signal under Linux -> Segmentation fault.
    OpenImage(wxEmptyString);
    undobuffer = NULL;
    undobuffersize = -1;
}

wxVisionManager::wxVisionManager(wxString filename)
{
    OpenImage(filename);
    undobuffer = NULL;
    undobuffersize = -1;
}

wxVisionManager::~wxVisionManager()
{
}

void wxVisionManager::BackupImage(unsigned char *source, unsigned char *destination, unsigned int count)
{
    unsigned int i;
    for (i=0 ; i<count ; i++)
        destination[i] = source[i];
}

//------------------------------------------

    /** TODO: Not used. Unstable. */
    static void ConvertRGB2HSL(unsigned char* red, unsigned char* green, unsigned char* blue)
    {
        unsigned char R, G, B, vMin, vMax;
        R = *red;
        G = *green;
        B = *blue;

        //-- HUE
        if ((R>=G) && (G>=B))   *red = 255*60*(0+(G-B)/(R-B))/360;
        if ((G>=R) && (R>=B))   *red = 255*60*(1+(R-B)/(G-B))/360;
        if ((G>=B) && (B>=R))   *red = 255*60*(2+(B-R)/(G-R))/360;
        if ((B>G)  && (G>R))    *red = 255*60*(3+(G-R)/(B-R))/360;
        if ((B>R)  && (R>=G))   *red = 255*60*(4+(R-G)/(B-G))/360;
        if ((R>=B) && (B>G))    *red = 255*60*(5+(B-G)/(R-G))/360;

        //-- SATURATION
        vMin = R;   if (G < vMin) vMin = G;     if (B < vMin) vMin = B;
        vMax = R;   if (G > vMin) vMax = G;     if (B > vMin) vMax = B;
        *green = (vMin + vMax)/2;

        //-- LIGHTNESS
        if (vMin == vMax)
            *blue = 0;
        else
            if (*green <= 128)
                *blue = 255 * (vMax - vMin) / (2 * *green);
            else
                *blue = 255 * (vMax - vMin) / (510 - 2* *green);
    }

    static int pow2int(int value)
    {
        return value*value;
    }

    void wxVisionManager::AdjustRange(int* red, int* green, int* blue)
    {
        //-- Lower limit
        if (*red < 0) *red = 0;
        if (*green < 0) *green = 0;
        if (*blue < 0) *blue = 0;
        //-- Upper limit
        if (*red > 255) *red = 255;
        if (*green > 255) *green = 255;
        if (*blue > 255) *blue = 255;
    }

//------------------------------------------

void wxVisionManager::PrepareUndo()
{
    int h, w, k;
    unsigned char *data;
    h = m_image.GetHeight();
    w = m_image.GetWidth();
    data = m_image.GetData();

    if (undobuffersize != 3*h*w)
    {
        undobuffer = (unsigned char*) realloc(undobuffer, 3*h*w*sizeof(unsigned char));
        undobuffersize = 3*h*w;
    }
    for (k=0 ; k<3*h*w ; k++)
        undobuffer[k] = data[k];
}

void wxVisionManager::Undo()
{
    int h, w, k;
    unsigned char *data;
    h = m_image.GetHeight();
    w = m_image.GetWidth();
    data = m_image.GetData();

    if (undobuffersize != 3*h*w)
        return;
    for (k=0 ; k<3*h*w ; k++)
        data[k] = undobuffer[k];
}

//------------------------------------------

void wxVisionManager::OpenImage(wxString filename)
{
    if (wxFileExists(filename))
    {
        m_image.LoadFile(filename);
        PrepareUndo();
        ComputeHistogram();
    }
}

wxImage* wxVisionManager::GetImage()
{
    return &m_image;
}

wxEcMatrix* wxVisionManager::GetFilter()
{
    return &m_filter;
}

void wxVisionManager::ResetHistogram()
{
    int i;
    for (i=0 ; i<256 ; i++)
    {
        histoR[i].x = i;        histoR[i].y = 0;
        histoG[i].x = i;        histoG[i].y = 0;
        histoB[i].x = i;        histoB[i].y = 0;
        histoN[i].x = i;        histoN[i].y = 0;
    }
}

void wxVisionManager::ComputeHistogram()
{
    int k, R, G, B;
    unsigned char *data;
    ResetHistogram();

    //-- Computes the histogram
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        R = data[0];
        G = data[1];
        B = data[2];

        histoR[R].y++;
        histoG[G].y++;
        histoB[B].y++;
        histoN[(299*R + 587*G + 114*B)/1000].y++;

        data += 3*sizeof(unsigned char);
    }
}

wxRealPoint* wxVisionManager::GetRedData()
{
    return &(histoR[0]);
}

wxRealPoint* wxVisionManager::GetGreenData()
{
    return &(histoG[0]);
}

wxRealPoint* wxVisionManager::GetBlueData()
{
    return &(histoB[0]);
}

wxRealPoint* wxVisionManager::GetGreyData()
{
    return &(histoN[0]);
}

//------------------------------------------

void wxVisionManager::KickColour(int colourmask)
{
    int k;
    unsigned char *data, R, G, B;

    PrepareUndo();
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        //-- Gets
        R = data[0];
        G = data[1];
        B = data[2];
        //-- Changes
        if (colourmask & wxCL_RED)   R = 0;
        if (colourmask & wxCL_GREEN) G = 0;
        if (colourmask & wxCL_BLUE)  B = 0;
        //-- Sets
        data[0] = R;
        data[1] = G;
        data[2] = B;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::GreyScale()
{
    int k;
    unsigned char *data, gray;

    PrepareUndo();
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        gray = (299*data[0] + 587*data[1] + 114*data[2])/1000;
        //-- Sets
        data[0] = gray;
        data[1] = gray;
        data[2] = gray;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Generalize(int colourmask)
{
    int k;
    unsigned char *data, offset;

    PrepareUndo();
    offset = 0;
    if (colourmask & wxCL_GREEN) offset = 1;
    else if (colourmask & wxCL_BLUE) offset = 2;
    
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        data[0] = data[offset];
        data[1] = data[offset];
        data[2] = data[offset];
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::UseBlack(unsigned char threshold)
{
    int k;
    unsigned char *data;

    PrepareUndo();
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        if (wxEcBetween(data[0], 0, 15) && wxEcBetween(data[1], 0, threshold) && wxEcBetween(data[2], 0, threshold))
        {
            data[0] = 0;
            data[1] = 0;
            data[2] = 0;
        }
        else
        {
            data[0] = 255;
            data[1] = 255;
            data[2] = 255;
        }
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Inverse()
{
    int k;
    unsigned char *data;

    PrepareUndo();
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        data[0] = 255 - data[0];
        data[1] = 255 - data[1];
        data[2] = 255 - data[2];
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::RotateColours()
{
    int k;
    unsigned char *data, tmp;

    PrepareUndo();
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        tmp = data[2];
        data[2] = data[1];
        data[1] = data[0];
        data[0] = tmp;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Equalization(unsigned char vmin, unsigned char vmax)
{
    int k;
    unsigned char *data, R, G, B, tmp;

    PrepareUndo();
    if (vmax<vmin)
    {
        tmp = vmax;
        vmax = vmin;
        vmin = tmp;
    }

    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        //-- Gets colours
        R = data[0];
        G = data[1];
        B = data[2];

        //-- Computes new values
        if (wxEcBetween(R, vmin, vmax))
            R = (255*(R-vmin))/(vmax-vmin);
        else
            R = (R < vmin ? 0 : 255);

        if (wxEcBetween(G, vmin, vmax)) 
            G = (255*(G-vmin))/(vmax-vmin);
        else
            G = (G < vmin ? 0 : 255);

        if (wxEcBetween(B, vmin, vmax)) 
            B = (255*(B-vmin))/(vmax-vmin);
        else
            B = (B < vmin ? 0 : 255);

        //-- Sets colours
        data[0] = R;
        data[1] = G;
        data[2] = B;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Binarization(unsigned char threshold, int usecase)
{
    int k;
    unsigned char *data;

    PrepareUndo();
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        if (usecase == OP_DIRECT)
        {
            data[0] = (data[0] >= threshold ? 255 : 0);
            data[1] = (data[1] >= threshold ? 255 : 0);
            data[2] = (data[2] >= threshold ? 255 : 0);
        }
        else //it is not the fastest algorithm
        {
            data[0] = (data[0] < threshold ? 0 : 255);
            data[1] = (data[1] < threshold ? 0 : 255);
            data[2] = (data[2] < threshold ? 0 : 255);
        }
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Luminosity(int offset)
{
    int k, R, G, B;
    unsigned char *data;

    PrepareUndo();
    if (offset == 0)    return;
    if (offset > 255)   offset = 255;
    if (offset < -255)  offset = -255;

    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        //-- Gets
        R = data[0] + offset*sizeof(unsigned char);
        G = data[1] + offset*sizeof(unsigned char);
        B = data[2] + offset*sizeof(unsigned char);
        //-- Checks
        if (R>255) R = 255; if (R<0) R = 0;
        if (G>255) G = 255; if (G<0) G = 0;
        if (B>255) B = 255; if (B<0) B = 0;
        //-- Sets
        data[0] = R;
        data[1] = G;
        data[2] = B;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Rgb2YCbCr()
{
    int k, R, G, B;
    unsigned char *data;
    wxEcMatrix filter(3,3), vector(3,1);

    //-- Initialization
    //Reference: http://www.w3.org/Graphics/JPEG/jfif3.pdf
    filter.SetValue(1,1,  0.2990);      filter.SetValue(1,2,  0.5870);      filter.SetValue(1,3,  0.1140);
    filter.SetValue(2,1, -0.1687);      filter.SetValue(2,2, -0.3313);      filter.SetValue(2,3,  0.5000);
    filter.SetValue(3,1,  0.5000);      filter.SetValue(3,2, -0.4187);      filter.SetValue(3,3, -0.0813);
    PrepareUndo();

    //-- Action !
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        //-- Gets
        vector.SetValue(1,1, data[0]); //R
        vector.SetValue(2,1, data[1]); //G
        vector.SetValue(3,1, data[2]); //B
        vector.ApplyMatrix(&filter);
        //-- Checks
        R = vector.GetValue(1,1,false);
        G = 128 + (int)vector.GetValue(2,1,false);
        B = 128 + (int)vector.GetValue(3,1,false);
        AdjustRange(&R, &G, &B);
        //-- Sets
        data[0] = R;
        data[1] = G;
        data[2] = B;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::YCbCr2Rgb()
{
    int k, R, G, B;
    unsigned char *data;
    wxEcMatrix filter(3,3), vector(3,1);

    //-- Initialization

    filter.SetValue(1,1, 1);    filter.SetValue(1,2, 0);        filter.SetValue(1,3, 1.4020);
    filter.SetValue(2,1, 1);    filter.SetValue(2,2, -.3441);   filter.SetValue(2,3, -.7141);
    filter.SetValue(3,1, 1);    filter.SetValue(3,2, 1.7720);   filter.SetValue(3,3, -.0001);
    PrepareUndo();

    //-- Action !
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        //-- Gets
        vector.SetValue(1,1, data[0]);       //R
        vector.SetValue(2,1, data[1] - 128); //G
        vector.SetValue(3,1, data[2] - 128); //B
        vector.ApplyMatrix(&filter);
        //-- Checks
        R = vector.GetValue(1,1,false);
        G = vector.GetValue(2,1,false);
        B = vector.GetValue(3,1,false);
        AdjustRange(&R, &G, &B);
        //-- Sets
        data[0] = R;
        data[1] = G;
        data[2] = B;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Rgb2Yiq()
{
    int k, R, G, B;
    unsigned char *data;
    wxEcMatrix filter(3,3), vector(3,1);

    //-- Initialization
    filter.SetValue(1,1, 0.299);        filter.SetValue(1,2,  0.587);       filter.SetValue(1,3,  0.114);
    filter.SetValue(2,1, 0.596);        filter.SetValue(2,2, -0.274);       filter.SetValue(2,3, -0.322);
    filter.SetValue(3,1, 0.212);        filter.SetValue(3,2, -0.523);       filter.SetValue(3,3,  0.311);
    PrepareUndo();

    //-- Action !
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        //-- Gets
        vector.SetValue(1,1, data[0]); //R
        vector.SetValue(2,1, data[1]); //G
        vector.SetValue(3,1, data[2]); //B
        vector.ApplyMatrix(&filter);
        //-- Checks
        R = vector.GetValue(1,1,false);
        G = 128 + vector.GetValue(2,1,false);
        B = 128 + vector.GetValue(3,1,false);
        AdjustRange(&R, &G, &B);
        //-- Sets
        data[0] = R;
        data[1] = G;
        data[2] = B;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Yiq2Rgb()
{
    int k, R, G, B;
    unsigned char *data;
    wxEcMatrix filter(3,3), vector(3,1);

    //-- Initialization
    filter.SetValue(1,1, 0.9740);       filter.SetValue(1,2,  0.9619);      filter.SetValue(1,3,  0.6389);
    filter.SetValue(2,1, 1.0074);       filter.SetValue(2,2, -0.2734);      filter.SetValue(2,3, -0.6523);
    filter.SetValue(3,1, 1.0301);       filter.SetValue(3,2, -1.1154);      filter.SetValue(3,3,  1.6830);
    PrepareUndo();

    //-- Action !
    data = m_image.GetData();
    for (k=0 ; k<m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        //-- Gets
        vector.SetValue(1,1, data[0]);       //R
        vector.SetValue(2,1, data[1] - 128); //G
        vector.SetValue(3,1, data[2] - 128); //B
        vector.ApplyMatrix(&filter);
        //-- Checks
        R = vector.GetValue(1,1);
        G = vector.GetValue(2,1);
        B = vector.GetValue(3,1);
        AdjustRange(&R, &G, &B);
        //-- Sets
        data[0] = R;
        data[1] = G;
        data[2] = B;
        data += 3*sizeof(unsigned char);
    }
}

void wxVisionManager::Dilate(wxEcMatrix& tool)
{
    //This code is redundant with wxVisionManager::Erode()

    //-- Initialization
    wxEcUPoint size;
    int k, mx, my, i, j;
    unsigned int x, y;
    unsigned char *from, *to;
    wxImage result;

    //-- Preparation
    PrepareUndo();
        result.Create(m_image.GetWidth(), m_image.GetHeight());
        from = m_image.GetData();
        to = result.GetData();
        for (k=0 ; k<3*m_image.GetWidth()*m_image.GetHeight() ; k++)
        {
            *to = *from;
            to++; from++;
        }
    size = tool.GetDimensionality();
    mx = (size.x-1) / 2;
    my = (size.y-1) / 2;

    //-- Action !
    for (i=mx ; i<=m_image.GetWidth()-mx ; i++)
        for (j=my ; j<=m_image.GetHeight()-my ; j++)
            if ((m_image.GetRed(i,j)==0) && (m_image.GetGreen(i,j)==0) && (m_image.GetBlue(i,j)==0))
                for (x=1 ; x<=size.x ; x++)
                    for (y=1 ; y<=size.y ; y++)
                        if (tool.GetValue(x,y) > 0)
                            result.SetRGB(i-mx+x-1, j-my+y-1, 0, 0, 0);

    //-- Result
    from = result.GetData();
    to = m_image.GetData();
    for (k=0 ; k<3*m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        *to = *from;
        to++; from++;
    }
}

void wxVisionManager::Erode(wxEcMatrix& tool)
{
    //This code is redundant with wxVisionManager::Dilate()

    //-- Initialization
    wxEcUPoint size;
    int k, mx, my, i, j;
    unsigned int x, y;
    unsigned char *from, *to;
    wxImage result;

    //-- Preparation
    PrepareUndo();
        result.Create(m_image.GetWidth(), m_image.GetHeight());
        from = m_image.GetData();
        to = result.GetData();
        for (k=0 ; k<3*m_image.GetWidth()*m_image.GetHeight() ; k++)
        {
            *to = *from;
            to++; from++;
        }
    size = tool.GetDimensionality();
    mx = (size.x-1) / 2;
    my = (size.y-1) / 2;

    //-- Action !
    for (i=mx ; i<=m_image.GetWidth()-mx ; i++)
        for (j=my ; j<=m_image.GetHeight()-my ; j++)
            if ((m_image.GetRed(i,j)==255) && (m_image.GetGreen(i,j)==255) && (m_image.GetBlue(i,j)==255))
                for (x=1 ; x<=size.x ; x++)
                    for (y=1 ; y<=size.y ; y++)
                        if (tool.GetValue(x,y) > 0)
                            result.SetRGB(i-mx+x-1, j-my+y-1, 255, 255, 255);

    //-- Result
    from = result.GetData();
    to = m_image.GetData();
    for (k=0 ; k<3*m_image.GetWidth()*m_image.GetHeight() ; k++)
    {
        *to = *from;
        to++; from++;
    }
}

bool wxVisionManager::ApplyFilter(int whattodo)
{
    wxEcUPoint matsize;
    int ray, px, py, R, G, B;
    unsigned int i, j, k, w, h;
    double tmp;
    wxEcMatrix *pointR, *pointG, *pointB;
    wxImage Ioutput;

    //-- Checks the size
    matsize = m_filter.GetDimensionality();
    if ((matsize.x != matsize.y) || (matsize.x % 2 == 0))
        return false;

    //-- Initialization
    if (whattodo == OP_AUTOTRANSPOSE)
    {
        m_tfilter.SetDimensionality(matsize.x, matsize.y);
        for (k=0 ; k<matsize.x*matsize.y ; k++)
            m_tfilter.GetData()[k] = ((double*)m_filter.GetData())[k];
        m_tfilter.Transpose();
    }

    wxMessageDialog(NULL, wxString::Format(wxT("Your first filter is :\n\n%s"), m_filter.DumpAsString().c_str()), wxT("Information"), wxOK|wxICON_INFORMATION).ShowModal();
    if (whattodo != OP_NOTHING)
        wxMessageDialog(NULL, wxString::Format(wxT("Your second filter is :\n\n%s"), m_tfilter.DumpAsString().c_str()), wxT("Information"), wxOK|wxICON_INFORMATION).ShowModal();
    tmp = m_filter.Sum();
    if ((whattodo==OP_NOTHING) && ((tmp<=0.999) || ((tmp >= 1.001))))
        wxMessageDialog(NULL, wxString::Format(wxT("Your filter is not normalized : the sum of the coefficients is not 1, but %f.\n\nConsequently, any value outside [0..255] will be truncated."), tmp), wxT("Warning"), wxOK|wxICON_WARNING).ShowModal();

    //-- Action !
    ray = (matsize.x-1)/2;
    h = m_image.GetHeight();
    w = m_image.GetWidth();
    Ioutput.Create(w,h,true);
    BackupImage(m_image.GetData(), Ioutput.GetData(), 3*w*h);
    pointR = new wxEcMatrix(matsize.x, matsize.y);
    pointG = new wxEcMatrix(matsize.x, matsize.y);
    pointB = new wxEcMatrix(matsize.x, matsize.y);

    //-- Computes
    for (j=ray ; j<h-ray ; j++)                     //vertical
        for (i=ray ; i<w-ray ; i++)                 //horizontal
        {
            //-- Fills the cache
            for (px=-ray ; px<=ray ; px++)
                for (py=-ray ; py<=ray ; py++)
                {
                    pointR->SetValue(py+ray+1, px+ray+1, m_image.GetRed(i+px, j+py));
                    pointG->SetValue(py+ray+1, px+ray+1, m_image.GetGreen(i+px, j+py));
                    pointB->SetValue(py+ray+1, px+ray+1, m_image.GetBlue(i+px, j+py));
                }

            //-- Convolution
            if (whattodo == OP_NOTHING)
            {
                R = pointR->Convolve(&m_filter);
                G = pointG->Convolve(&m_filter);
                B = pointB->Convolve(&m_filter);
            }
            else
            {
                R = sqrt(pow2int(pointR->Convolve(&m_filter)) + pow2int(pointR->Convolve(&m_tfilter)));
                G = sqrt(pow2int(pointG->Convolve(&m_filter)) + pow2int(pointG->Convolve(&m_tfilter)));
                B = sqrt(pow2int(pointB->Convolve(&m_filter)) + pow2int(pointB->Convolve(&m_tfilter)));
            }
            AdjustRange(&R, &G, &B);
            Ioutput.SetRGB(i, j, R, G, B);
        }

    //-- Finalization
    BackupImage(Ioutput.GetData(), m_image.GetData(), 3*w*h);
    wxDELETE(pointB);
    wxDELETE(pointG);
    wxDELETE(pointR);
    return true;
}

bool wxVisionManager::RunFilter()
{
    PrepareUndo();
    return ApplyFilter(OP_NOTHING);
}

bool wxVisionManager::LowPass(unsigned char radius)
{
    if (radius == 0)
        return false;
    PrepareUndo();
    m_filter.SetDimensionality(2*radius+1, 2*radius+1);
    m_filter.Clear(1.0/((double)(2*radius+1)*(double)(2*radius+1)));
    return ApplyFilter(OP_NOTHING);
}

bool wxVisionManager::GaussianSmoothing(unsigned char radius, double sigma)
{
    if (m_filter.GaussianFilter(radius, sigma))
    {
        PrepareUndo();
        return ApplyFilter(OP_NOTHING);
    }
    else
        return false;    
}

bool wxVisionManager::Laplacian(bool smoothing, unsigned char radius, double sigma)
{
    PrepareUndo();
    if (!smoothing)
    {
        m_filter.SetDimensionality(3,3);
        m_filter.SetValue(1,2,1);
        m_filter.SetValue(2,1,1);
        m_filter.SetValue(2,2,-4);
        m_filter.SetValue(2,3,1);
        m_filter.SetValue(3,2,1);
    }
    else
    {
        if (!m_filter.LaplacianOfGaussianFilter(radius, sigma))
            return false;
    }
    return ApplyFilter(OP_NOTHING);
}

bool wxVisionManager::Prewitt()
{
    PrepareUndo();
    m_filter.SetDimensionality(3,3);
    m_filter.SetValue(1,1,-1);
    m_filter.SetValue(1,2,-1);
    m_filter.SetValue(1,3,-1);
    m_filter.SetValue(2,1,0);
    m_filter.SetValue(2,2,0);
    m_filter.SetValue(2,3,0);
    m_filter.SetValue(3,1,1);
    m_filter.SetValue(3,2,1);
    m_filter.SetValue(3,3,1);
    return ApplyFilter(OP_AUTOTRANSPOSE);
}

bool wxVisionManager::Sobel()
{
    PrepareUndo();
    m_filter.SetDimensionality(3,3);
    m_filter.SetValue(1,1,1);
    m_filter.SetValue(1,2,0);
    m_filter.SetValue(1,3,-1);
    m_filter.SetValue(2,1,2);
    m_filter.SetValue(2,2,0);
    m_filter.SetValue(2,3,-2);
    m_filter.SetValue(3,1,1);
    m_filter.SetValue(3,2,0);
    m_filter.SetValue(3,3,-1);
    return ApplyFilter(OP_AUTOTRANSPOSE);
}

bool wxVisionManager::Edges()
{
    PrepareUndo();
    m_filter.SetDimensionality(3,3);
    m_filter.SetValue(1,2,-1);
    m_filter.SetValue(2,1,-1);
    m_filter.SetValue(2,2,5);
    m_filter.SetValue(2,3,-1);
    m_filter.SetValue(3,2,-1);
    return ApplyFilter(OP_NOTHING);
}

bool wxVisionManager::DrawEdges()
{
    PrepareUndo();
    m_filter.SetDimensionality(3,3);
    m_filter.SetValue(1,1,2);
    m_filter.SetValue(1,2,-1);
    m_filter.SetValue(1,3,2);
    m_filter.SetValue(2,1,-1);
    m_filter.SetValue(2,2,-3);
    m_filter.SetValue(2,3,-1);
    m_filter.SetValue(3,1,2);
    m_filter.SetValue(3,2,-1);
    m_filter.SetValue(3,3,2);
    return ApplyFilter(OP_NOTHING);
}

bool wxVisionManager::Rise()
{
    PrepareUndo();
    m_filter.SetDimensionality(3,3);
    m_filter.SetValue(1,1,-2);
    m_filter.SetValue(1,2,-1);
    m_filter.SetValue(2,1,-1);
    m_filter.SetValue(2,2,1);
    m_filter.SetValue(2,3,1);
    m_filter.SetValue(3,2,1);
    m_filter.SetValue(3,3,2);
    return ApplyFilter(OP_NOTHING);
}

    void wxVisionManager::BubbleSort(unsigned char* ldata, unsigned int len)
    {
        unsigned int i, j;
        unsigned char tmp;
        for (i=0 ; i<len-1 ; i++)
            for (j=0 ; j<len-1 ; j++)
                if (ldata[j+1] < ldata[j])
                {
                    tmp = ldata[j];
                    ldata[j] = ldata[j+1];
                    ldata[j+1] = tmp;
                }
    }

bool wxVisionManager::Median(unsigned char radius)
{
    if (radius == 0)
        return false;

    unsigned char *bufferR, *bufferG, *bufferB;
    int w, h, counter;
    int i, j, px, py;
    wxImage Ioutput;

    //-- Initialization
    h = m_image.GetHeight();
    w = m_image.GetWidth();
    Ioutput.Create(w,h,true);
    BackupImage(m_image.GetData(), Ioutput.GetData(), 3*w*h);
    PrepareUndo();
    bufferR = (unsigned char*) malloc((2*radius+1)*(2*radius+1)*sizeof(unsigned char));
    bufferG = (unsigned char*) malloc((2*radius+1)*(2*radius+1)*sizeof(unsigned char));
    bufferB = (unsigned char*) malloc((2*radius+1)*(2*radius+1)*sizeof(unsigned char));
    for (j=radius ; j<h-radius ; j++)           //vertical
        for (i=radius ; i<w-radius ; i++)       //horizontal
        {
            //-- Fills the cache
            counter = 0;
            for (px=-radius ; px<=radius ; px++)
                for (py=-radius ; py<=radius ; py++)
                {
                    bufferR[counter] = m_image.GetRed(i+px, j+py);
                    bufferG[counter] = m_image.GetGreen(i+px, j+py);
                    bufferB[counter] = m_image.GetBlue(i+px, j+py);
                    counter++;
                }

            //-- Sorts the list
            BubbleSort(bufferR, (2*radius+1)*(2*radius+1));
            BubbleSort(bufferG, (2*radius+1)*(2*radius+1));
            BubbleSort(bufferB, (2*radius+1)*(2*radius+1));

            //-- Finds the median
            counter = 2*radius*(radius+1);
            Ioutput.SetRGB(i, j, bufferR[counter], bufferG[counter], bufferB[counter]);
        }
    BackupImage(Ioutput.GetData(), m_image.GetData(), 3*w*h);
    wxDELETE(bufferB);
    wxDELETE(bufferG);
    wxDELETE(bufferR);
    return true;
}
