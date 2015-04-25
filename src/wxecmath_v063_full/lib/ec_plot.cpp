
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

#include "ec_plot.h"

    BEGIN_EVENT_TABLE(wxEcPlot, wxWindow)
        EVT_PAINT(wxEcPlot::OnPaint)
        EVT_SIZE(wxEcPlot::OnResize)
    END_EVENT_TABLE()

//------------------------------------------

#define wxEcAbs(a) (((a) < 0) ? -(a) : (a))

static double square(double value)
{
    return value*value;
}

//------------------------------------------

void wxEcAxis::Validate()
{
    double tmp;
    if (MinValue > MaxValue)
    {
        tmp = MaxValue;
        MaxValue = MinValue;
        MinValue = tmp;
    }
    if (MinValue == MaxValue)
    {
        MinValue = -10.0;
        MaxValue = 10.0;
        StepValue = 1.0;
    }
    if (StepValue < 0.0)
        StepValue = -StepValue;
    if (StepValue > MaxValue-MinValue)
        StepValue = (MaxValue-MinValue)/10.0;
}

void wxEcAxis::Recalibrate()
{
    if ((MaxValue - MinValue) / StepValue > wxECD_STEPSMAX)
        StepValue = (MaxValue - MinValue)/wxECD_STEPSMAX;
}

void wxEcAxis::Reset()
{
    MinValue = -10.0;
    MaxValue = 10.0;
    StepValue = 1.0;
}

//------------------------------------------

void wxEcCurve::Validate()
{
    double tmp;
    if (RangeMin > RangeMax)
    {
        tmp = RangeMax;
        RangeMax = RangeMin;
        RangeMin = tmp;
    }
    if (Width < 0)
        Width = 1;
    if (NumPoints == 0)
        NumPoints = wxECD_RESOLUTION;
}

void wxEcCurve::Parse(wxString def, bool isPolar)
{
    /*    Allowed syntaxes are :
            - cartesian :                            1+x
            - cartesian, restricted to a domain :    1+x $ -3 4
            - parametric (x;y$domain) :              1+t ; -1+t^2 $ -10 10
            - polar (r$domain) :                     3+sin(t) $ -pi pi        **AND** isPolar as true, else it will be considerated as cartesian
        Only a curve marked with "Enabled" & "Defined" can be displayed
    */
    wxEcEngine curvcalc;
    wxColour curveColours[18] = {   wxColour(128,128,00),  wxColour(128,128,204), wxColour(00,128,00),   wxColour(128,204,128),
                                    wxColour(204,128,00),  wxColour(204,128,128), wxColour(204,128,204), wxColour(00,204,128),
                                    wxColour(128,128,128), wxColour(00,204,00),   wxColour(00,204,204),  wxColour(00,128,128),
                                    wxColour(204,204,204), wxColour(128,204,00),  wxColour(128,204,204), wxColour(204,204,128),
                                    wxColour(204,204,00),  wxColour(00,128,204)
                                };
    wxString domain, buffer;
    def = def.Trim(false).Trim(true);
    if (def.Len() == 0)
        return;

    //-- Definition
    if (def.Find(wxT('$')) != wxNOT_FOUND)
    {
        domain = def.AfterFirst(wxT('$')).Trim(false);
        def = def.BeforeFirst(wxT('$')).Trim(true);

        if (domain.Find(wxT(' ')) != wxNOT_FOUND)
        {
            this->RangeEnabled = true;
            //-- Evaluates the lower limit
            buffer = domain.BeforeFirst(wxT(' '));
            curvcalc.SetFormula(buffer);
            this->RangeMin = curvcalc.Compute();
            if (curvcalc.GetLastError() != wxECE_NOERROR)
                this->RangeMin = -10.0;
            //-- Evaluate the upper limit
            buffer = domain.AfterFirst(wxT(' '));
            curvcalc.SetFormula(buffer);
            this->RangeMax = curvcalc.Compute();
            if (curvcalc.GetLastError() != wxECE_NOERROR)
                this->RangeMax = 10.0;
        }
    }
    else
        this->RangeEnabled = false;

    //-- Sets type of curve
    if (def.Find(wxT(';')) != wxNOT_FOUND)
        this->Type = wxECT_PARAMETRIC;
    else
        this->Type = wxECT_CARTESIAN;
    if (isPolar)
    {
        this->Type = wxECT_POLAR;
        this->RangeEnabled = true;
    }
    //-- Stores the formula
    if (this->Type == wxECT_PARAMETRIC)
    {
        this->ExpressionX = def.BeforeFirst(wxT(';')).Trim(true).Lower();
        this->ExpressionY = def.AfterFirst(wxT(';')).Trim(false).Lower();
        this->RangeEnabled = true;
    }
    else
        this->ExpressionX = def.Lower();
    this->Colour = curveColours[rand() % 18];
}

bool wxEcCurve::SortCloud()
{
    unsigned int i, j;
    double tmp;

    if (Type != wxECT_CLOUD)
        return false;

    for (i=0 ; i<NumPoints-1 ; i++)
        for (j=0 ; j<NumPoints-1 ; j++)
            if (Cloud[j+1].x < Cloud[j].x)
            {
                //-- X
                tmp = Cloud[j].x;
                Cloud[j].x = Cloud[j+1].x;
                Cloud[j+1].x = tmp;
                //-- Y
                tmp = Cloud[j].y;
                Cloud[j].y = Cloud[j+1].y;
                Cloud[j+1].y = tmp;
            }
    return true;
}

//------------------------------------------

wxEcPlot::wxEcPlot(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
        : wxWindow(parent, id, pos, size, style, wxECD_SOFTWARE)
{
    m_engine = new wxEcEngine();
    m_engine->UseDebug(false);
    m_axisx = wxEcAxis();
    m_axisy = wxEcAxis();
    m_backgroundcolour = *wxWHITE;
    m_axisx.Colour = *wxRED;
    m_axisy.Colour = *wxRED;
    m_gridcolour = wxColour(192,192,192);
    m_reticulecolour = wxColour(192,192,0);
    m_flatborder = true;
    m_gridvisible = true;
    m_gridpolar = false;
    m_axisx.Visible = true;
    m_axisy.Visible = true;
    m_reticulevisible = false;
    m_locked = false;
    m_ymaxfound = 0;
    m_yminfound = 0;
    m_zoomfactor = wxECD_ZOOMFACTOR;
    m_reticule = wxRealPoint(0.0,0.0);
    m_lasttangent.Clear();
    RemoveAllCurves();
}

wxEcPlot::~wxEcPlot()
{
    RemoveAllCurves();
    wxDELETE(m_engine);
}

void wxEcPlot::OnPaint(wxPaintEvent &event)
{
    DoRedraw();
}

void wxEcPlot::OnResize(wxSizeEvent &event)
{
    Refresh();
}

//------------------------------------------

void wxEcPlot::SetUnit(double perpixel, bool forX)
{
    int w, h;
    this->GetSize(&w, &h);
    if (perpixel < 0)
        perpixel = -perpixel;
    if (forX)
    {
        m_axisx.MinValue = -w*perpixel/2.0;
        m_axisx.MaxValue = w*perpixel/2.0;
        m_axisx.Recalibrate();
    }
    else
    {
        m_axisy.MinValue = -h*perpixel/2.0;
        m_axisy.MaxValue = h*perpixel/2.0;
        m_axisy.Recalibrate();
    }
}

wxPoint wxEcPlot::CoupleValueToXY(double X, double Y)
{
    return wxPoint(ValueToX(X), ValueToY(Y));
}

bool wxEcPlot::IsVisible(double X, double Y)
{
    return (X>=m_axisx.MinValue) && (X<=m_axisx.MaxValue) && (Y>=m_axisy.MinValue) && (Y<=m_axisy.MaxValue);
}

int wxEcPlot::ValueToX(double value)
{
    int w, h;
    this->GetSize(&w, &h);
    return (value - m_axisx.MinValue)/XPerPixel();
}

int wxEcPlot::ValueToY(double value)
{
    int w, h;
    this->GetSize(&w, &h);
    return (m_axisy.MaxValue-value)/YPerPixel();
}

double wxEcPlot::XPerPixel()
{
    int w, h;
    this->GetSize(&w, &h);
    if (w == 0)
        return 0;
    else
        return (m_axisx.MaxValue - m_axisx.MinValue)/w;
}

double wxEcPlot::XToValue(int X)
{
    return m_axisx.MinValue + X*XPerPixel();
}

double wxEcPlot::YPerPixel()
{
    int w, h;
    this->GetSize(&w, &h);
    if (h == 0)
        return 0;
    else
        return (m_axisy.MaxValue - m_axisy.MinValue)/h;
}

double wxEcPlot::YToValue(int Y)
{
    int w, h;
    this->GetSize(&w, &h);
    return m_axisy.MinValue + (h-Y)*YPerPixel();
}

//------------------------------------------

void wxEcPlot::DoDrawAxis(wxDC *context)
{
    if (m_locked || (context==NULL))
        return;
    wxPoint axisArrow[3];

    int w, h;
    this->GetSize(&w, &h);
    wxPoint origin = CoupleValueToXY(0,0);

    //-- Background
    if (m_flatborder)
        context->SetPen(wxPen(*wxBLACK, 1, wxSOLID));
    else
        context->SetPen(wxNullPen);
    context->SetBrush(wxBrush(m_backgroundcolour, wxSOLID));
    context->DrawRectangle(0, 0, w, h);

    //-- Grid
    if (m_gridvisible)
    {
        double gridStep;

        context->SetPen(wxPen(m_gridcolour, 1, wxDOT));
        context->SetBrush(*wxTRANSPARENT_BRUSH);
        if (m_gridpolar)
        {
            int i;
            double r, rx, ry, rmax, t;
            wxPoint pointA, pointB;

            //-- Draws the theta-axis every 30°
            r = sqrt(   square(wxMax(wxEcAbs(m_axisx.MinValue), wxEcAbs(m_axisx.MaxValue))) +
                        square(wxMax(wxEcAbs(m_axisy.MinValue), wxEcAbs(m_axisy.MaxValue)))
                    );
            for (i=0 ; i<6 ; i++)
            {
                t = i*M_PI/6;
                pointA = this->CoupleValueToXY(r*cos(t), r*sin(t));
                pointB = this->CoupleValueToXY(-r*cos(t), -r*sin(t));
                context->DrawLine(pointA.x, pointA.y, pointB.x, pointB.y);
            }

            //-- Draws the r-circles references (relative to X only)
            context->SetFont(m_axisy.Font);
            gridStep = m_axisx.StepValue;
            if ((m_axisx.MaxValue - m_axisx.MinValue) / gridStep > wxECD_STEPSMAX)
                gridStep = (m_axisx.MaxValue - m_axisx.MinValue)/wxECD_STEPSMAX;
            rmax = wxMax(wxEcAbs(m_axisx.MinValue), wxEcAbs(m_axisx.MaxValue));
            r = wxMin(0, wxMin(wxEcAbs(m_axisx.MinValue), wxEcAbs(m_axisx.MaxValue)));
            r = ceil((r-gridStep) / gridStep)*gridStep;
            while (r < rmax)
            {
                r += gridStep;
                rx = wxEcAbs(this->ValueToX(r) - origin.x);
                ry = wxEcAbs(this->ValueToY(r) - origin.y);
                context->DrawEllipse(origin.x-rx, origin.y-ry, 2*rx, 2*ry);
                context->DrawText(wxString::Format(m_axisy.Format, r), origin.x+rx+1, origin.y);
            }

        }
        else
        {
            wxPoint textPoint;
            double gridPosition;

            //-- Vertical
            context->SetFont(m_axisx.Font);
            gridStep = m_axisx.StepValue;
            if ((m_axisx.MaxValue - m_axisx.MinValue) / gridStep > wxECD_STEPSMAX)
                gridStep = (m_axisx.MaxValue - m_axisx.MinValue)/wxECD_STEPSMAX;
            gridPosition = ceil((m_axisx.MinValue-gridStep) / gridStep)*gridStep;
            while (gridPosition < m_axisx.MaxValue)
            {
                context->DrawLine(this->ValueToX(gridPosition),0, this->ValueToX(gridPosition),h);
                if (m_axisx.ShowValues)
                {
                    textPoint = this->CoupleValueToXY(gridPosition, 0);
                    context->DrawText(wxString::Format(m_axisx.Format, gridPosition), textPoint.x+1, textPoint.y);
                }
                gridPosition += gridStep;
            }
            //-- Horizontal
            context->SetFont(m_axisy.Font);
            gridStep = m_axisy.StepValue;
            if ((m_axisy.MaxValue - m_axisy.MinValue) / gridStep > wxECD_STEPSMAX)
                gridStep = (m_axisy.MaxValue - m_axisy.MinValue)/wxECD_STEPSMAX;
            gridPosition = ceil((m_axisy.MinValue-gridStep) / gridStep)*gridStep;
            while (gridPosition < m_axisy.MaxValue)
            {
                context->DrawLine(0,this->ValueToY(gridPosition), w,this->ValueToY(gridPosition));
                if (m_axisy.ShowValues)
                {
                    textPoint = this->CoupleValueToXY(0,gridPosition);
                    context->DrawText(wxString::Format(m_axisy.Format, gridPosition), textPoint.x+1, textPoint.y);
                }
                gridPosition += gridStep;
            }
        }
    }

    //-- Axis
    if (m_axisx.Visible)
    {
        context->SetPen(wxPen(m_axisx.Colour, 1, wxSOLID));
        context->DrawLine(0,origin.y, w,origin.y);            //horizontal
    }
    if (m_axisy.Visible)
    {
        context->SetPen(wxPen(m_axisy.Colour, 1, wxSOLID));
        context->DrawLine(origin.x,0, origin.x,h);            //vertical
    }

    //-- Arrows
    context->SetBrush(wxBrush(m_backgroundcolour, wxSOLID));
    if (m_axisy.Visible)
    {
        axisArrow[0] = wxPoint(w, origin.y);
        axisArrow[1] = wxPoint(w-2*m_axisy.ArrowSize, origin.y-m_axisy.ArrowSize);
        axisArrow[2] = wxPoint(w-2*m_axisy.ArrowSize, origin.y+m_axisy.ArrowSize);
        context->DrawPolygon(3, axisArrow);
    }
    if (m_axisx.Visible)
    {
        axisArrow[0] = wxPoint(origin.x, 0);
        axisArrow[1] = wxPoint(origin.x - m_axisx.ArrowSize, 2*m_axisx.ArrowSize);
        axisArrow[2] = wxPoint(origin.x + m_axisx.ArrowSize, 2*m_axisx.ArrowSize);
        context->DrawPolygon(3, axisArrow);
    }

    //-- Border (redo)
    if (m_flatborder)
    {
        context->SetPen(wxPen(*wxBLACK, 1, wxSOLID));
        context->SetBrush(*wxTRANSPARENT_BRUSH);
        context->DrawRectangle(0, 0, w, h);
    }
}

void wxEcPlot::DoDrawCurve(wxDC *context, wxEcCurve *curve)
{
    if (m_locked || (context==NULL) || !curve->Defined || !curve->Enabled)
        return;
    switch (curve->Type)
    {
        case wxECT_PARAMETRIC:
            DoDrawParametricCurve(context, curve);
            return;
        case wxECT_POLAR:
            DoDrawPolarCurve(context, curve);
            return;
        case wxECT_CLOUD:
            DoDrawCloud(context, curve);
            return;
        case wxECT_CARTESIAN:
            //It is the code below
            ;
    }

    int w, h;
    this->GetSize(&w, &h);

    //-- Loads the function
    m_engine->Reset(true, true);
    if (!m_engine->SetFormula(curve->ExpressionX))
        return;

    //-- Set the ranges
    int MinX, MaxX;
    curve->Validate();
    if (curve->RangeEnabled)
    {
        MinX = this->ValueToX(wxMax(m_axisx.MinValue,  curve->RangeMin));
        MaxX = this->ValueToX(wxMin(m_axisx.MaxValue,  curve->RangeMax));
    }
    else
    {
        MinX = 0.0;
        MaxX = w;
    }
    if (MinX > MaxX)
        return;

    //-- Preparation
    int x;
    double y;
    wxPoint anchor, destPoint;
    bool anchorOK = false;

    context->SetPen(wxPen(curve->Colour, curve->Width, wxSOLID));
    for (x=MinX ; x<=MaxX ; x++)
    {
        //-- Computes
        m_engine->SetConstant(wxT("x"), this->XToValue(x));
        y = m_engine->Compute();
        if (m_engine->GetLastError() != wxECE_NOERROR)
        {
            anchorOK = false;
            continue;
        }
        if (!m_ymarker)
        {
            m_ymaxfound = y;
            m_yminfound = y;
            m_ymarker = true;
        }
        if (y > m_ymaxfound) m_ymaxfound = y;
        if (y < m_yminfound) m_yminfound = y;

        //-- Locates the right points
        if (!anchorOK)
            anchor = wxPoint(x, this->ValueToY(y));
        destPoint = wxPoint(x, this->ValueToY(y));

        //-- Draws them
        if (curve->DotStyle)
            context->DrawPoint(destPoint);
        else
        {
            context->DrawLine(anchor.x, anchor.y, destPoint.x, destPoint.y);
            anchor = destPoint;
            anchorOK = true;
        }
    }
}

void wxEcPlot::DoDrawParametricCurve(wxDC *context, wxEcCurve *curve)
{
    if (m_locked || (context==NULL) || (curve==NULL))
        return;
    if (!curve->Defined || !curve->Enabled || ((curve->Type!=wxECT_PARAMETRIC) && (curve->Type!=wxECT_POLAR)) || !curve->RangeEnabled)
        return;
    curve->Validate();

    //-- Preparation
    double r=0, x=0, y=0;
    double t = curve->RangeMin;
    double tstep = (curve->RangeMax - curve->RangeMin)/curve->NumPoints;
    int errorX, errorY;
    wxPoint anchor, destPoint;
    bool anchorOK = false;

    if (curve->Type == wxECT_POLAR)
        m_engine->SetFormula(curve->ExpressionX);    //set just once in polar mode

    context->SetPen(wxPen(curve->Colour, curve->Width, wxSOLID));
    while (t < curve->RangeMax)
    {
        //-- Computes
        m_engine->SetConstant(wxT("t"), t);
        if (curve->Type == wxECT_POLAR)
        {
            r = m_engine->Compute();
            errorX = m_engine->GetLastError();
            errorY = wxECE_NOERROR;
        }
        else
        {
            m_engine->SetFormula(curve->ExpressionX);
            x = m_engine->Compute();
            errorX = m_engine->GetLastError();
            m_engine->SetFormula(curve->ExpressionY);
            y = m_engine->Compute();
            errorY = m_engine->GetLastError();
        }

        //-- Checks
        if ((errorX!=wxECE_NOERROR) || (errorY!=wxECE_NOERROR))
        {
            anchorOK = false;
            goto ParametricNext;
        }
        if (curve->Type == wxECT_POLAR)
        {
            x = r*cos(t);
            y = r*sin(t);
        }
        if (!m_ymarker)
        {
            m_ymaxfound = y;
            m_yminfound = y;
            m_ymarker = true;
        }
        if (y > m_ymaxfound) m_ymaxfound = y;
        if (y < m_yminfound) m_yminfound = y;

        //-- Locates the right points
        if (!anchorOK)
            anchor = wxPoint(this->ValueToX(x), this->ValueToY(y));
        destPoint = wxPoint(this->ValueToX(x), this->ValueToY(y));

        //-- Draws them
        if (curve->DotStyle)
            context->DrawPoint(destPoint);
        else
        {
            context->DrawLine(anchor.x, anchor.y, destPoint.x, destPoint.y);
            anchor = destPoint;
            anchorOK = true;
        }

        //-- Next
ParametricNext:
        t += tstep;
    }
}

void wxEcPlot::DoDrawPolarCurve(wxDC *context, wxEcCurve *curve)
{
    DoDrawParametricCurve(context, curve);
}

void wxEcPlot::DoDrawCloud(wxDC *context, wxEcCurve *curve)
{
    if (m_locked || (context==NULL) || (curve==NULL))
        return;
    if (!curve->Defined || !curve->Enabled || (curve->Type!=wxECT_CLOUD) || (curve->Cloud==NULL))
        return;
    wxRealPoint data;

    //-- Preparation
    wxPoint anchor, destPoint;
    bool anchorOK = false;
    unsigned long i;

    //-- Draws the cloud
    context->SetPen(wxPen(curve->Colour, curve->Width, wxSOLID));
    context->SetBrush(wxBrush(curve->Colour, wxSOLID));
    for (i=0 ; i<curve->NumPoints ; i++)
    {
        //-- Gets data
        data = curve->Cloud[i];
        destPoint = wxPoint(ValueToX(data.x), ValueToY(data.y));
        //-- Draws point & line
        context->DrawRectangle(destPoint.x-1, destPoint.y-1, 3, 3);
        if (!anchorOK)
        {
            anchor = destPoint;
            anchorOK = true;
        }
        else
        {
            if (!curve->DotStyle)
                context->DrawLine(anchor.x, anchor.y, destPoint.x, destPoint.y);
            anchor = destPoint;
        }
        //-- Finds Min/Max
        if (!m_ymarker)
        {
            m_ymaxfound = data.y;
            m_yminfound = data.y;
            m_ymarker = true;
        }
        if (data.y > m_ymaxfound) m_ymaxfound = data.y;
        if (data.y < m_yminfound) m_yminfound = data.y;
    }
}

void wxEcPlot::DoDrawReticule(wxDC *context)
{
    if (!m_reticulevisible || (context==NULL))
        return;
    //-- Initializes
    int w, h;
    this->GetSize(&w, &h);
    wxPoint retPos = wxPoint(this->ValueToX(m_reticule.x), this->ValueToY(m_reticule.y));
    //-- Draws
    context->SetPen(wxPen(m_reticulecolour, 1, wxSHORT_DASH));
    context->DrawLine(retPos.x,0, retPos.x,h);
    context->DrawLine(0,retPos.y, w,retPos.y);
    context->SetBrush(wxBrush(m_reticulecolour, wxSOLID));
    context->DrawEllipse(retPos.x-wxECD_RETICULESIZE, retPos.y-wxECD_RETICULESIZE, 2*wxECD_RETICULESIZE+1, 2*wxECD_RETICULESIZE+1);
}

void wxEcPlot::DoRedraw()
{
    if (m_locked)
        return;
    int i;

    m_ymaxfound = 0.0;
    m_yminfound = 0.0;
    m_ymarker = false;

    wxPaintDC DC(this);
    DoDrawAxis(&DC);
    for (i=0 ; i<wxECD_CURVEMAX ; i++)
        if (m_curves[i].Defined)
        {
            m_engine->DeleteConstant(wxT("x"));
            m_engine->DeleteConstant(wxT("y"));
            m_engine->DeleteConstant(wxT("t"));
            DoDrawCurve(&DC, &(m_curves[i]));
        }
    DoDrawReticule(&DC);
}

bool wxEcPlot::DrawTangent(int index, double wishx)
{
    wxEcCurve *curve = &(m_curves[index]);
    if (!curve->Enabled || !curve->Defined || (curve->Type!=wxECT_CARTESIAN))
        return false;

    //-- Must respect the selected range
    if (curve->RangeEnabled)
    {
        if ((wishx < curve->RangeMin) || (wishx > curve->RangeMax))
            return false;
        if (wishx == curve->RangeMin)
            wishx += wxECD_DXSTEP;
        if (wishx == curve->RangeMax)
            wishx -= wxECD_DXSTEP;
        //dx is computed around the wished point (x-D, x, x+D)
        //so +dx or -dx shall not be out of range
    }

    //-- Computes DX
    double fx, fdx, wishxoriginal = wishx;
    m_engine->SetFormula(curve->ExpressionX);
    if (!m_engine->Derivate(wishx, &fdx, &fx))
        return false;

    //-- Draws the tangent
    wxClientDC context(this);    //because "a wxClientDC must be constructed if an application wishes to paint on the client area of a window from outside an OnPaint event" (WXdocs)
    wxPoint p1, p2;
    m_lasttangent = wxString::Format(wxT("y = %f * x + %f"), fdx, fx-fdx*wishxoriginal);
    p1 = CoupleValueToXY(m_axisx.MinValue, fx + fdx*(m_axisx.MinValue - wishx));
    p2 = CoupleValueToXY(m_axisx.MaxValue, fx + fdx*(m_axisx.MaxValue - wishx));
    context.SetPen(wxPen(wxColour(255-curve->Colour.Red(), 255-curve->Colour.Green(), 255-curve->Colour.Blue()), 1, wxSOLID));
    context.DrawLine(p1.x, p1.y, p2.x, p2.y);
    return true;
}

bool wxEcPlot::DrawDerivative(int index)
{
    wxEcCurve *curve = &(m_curves[index]);
    if (!curve->Enabled || !curve->Defined || (curve->Type!=wxECT_CARTESIAN))
        return false;

    //-- Must respect the selected range
    double from, to, step;
    if (curve->RangeEnabled)
    {
        from = wxMax(curve->RangeMin, m_axisx.MinValue);
        to = wxMin(curve->RangeMax, m_axisx.MaxValue);
    }
    else
    {
        from = m_axisx.MinValue;
        to = m_axisx.MaxValue;
    }
    if (from > to)
        return false;
    step = this->XPerPixel();

    //-- Computes & draws
    double fx, fdx;
    bool anchorOK = false;
    wxPoint anchor, destPoint;

    wxClientDC context(this);
    context.SetPen(wxPen(wxColour(255-curve->Colour.Red(), 255-curve->Colour.Green(), 255-curve->Colour.Blue()), 1, wxSOLID));
    m_engine->SetFormula(curve->ExpressionX);
    while (from < to)
    {
        if (!m_engine->Derivate(from, &fdx, &fx))
        {
            anchorOK = false;
            continue;
        }

        //-- Draws
        if (!anchorOK)
            anchor = wxPoint(this->ValueToX(from), this->ValueToY(fdx));
        destPoint = wxPoint(this->ValueToX(from), this->ValueToY(fdx));

        context.DrawLine(anchor.x, anchor.y, destPoint.x, destPoint.y);
        anchor = destPoint;
        anchorOK = true;
        from += step;
    }
    return true;
}
