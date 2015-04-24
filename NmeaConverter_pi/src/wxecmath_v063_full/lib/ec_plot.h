
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
 * \file ec_plot.h
 * \brief Includes the area to draw curves
 * \author ecrucru
 * \version 0.6.3
 * \date September 2008
 *
 * To use a wxEcPlot, you must include wxEcEngine in your project.
 */

#ifndef ec_plot_h
#define ec_plot_h

//------------------------------------------

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/colour.h"
#include "wx/window.h"
#include "ec_defs.h"
#include "ec_engine.h"

//------------------------------------------

/** \class wxEcAxis
 *  \brief Describes an axis.
 */
class WXDLLEXPORT wxEcAxis
{
    public:
        double MinValue;        /**< The minimal value of the axis. */
        double MaxValue;        /**< The maximal value of the axis. */
        double StepValue;       /**< The interval between two graduations. */
        wxString Format;        /**< The format used to display floating values as text. */
        bool Visible;           /**< The visibility of the axis (considered by wxEcPlot). */
        wxColour Colour;        /**< The colour of the axis. */
        bool ShowValues;        /**< The visibility of the text of the axis. */
        wxFont Font;            /**< The font used to display the text. */
        int ArrowSize;          /**< */

        /** The default constructor.
         * \param min The lower limit of the axis.
         * \param max The upper limit of the axis.
         * \param step The interval between two graduations.
         * \param colour The colour of the axis.
         * \param visible The visibility of the axis.
         * \param showvalues The visibility of the text of the axis.
         * \remarks Format, Font and ArrowSize is automatically defined ;
         */
        wxEcAxis(double min = -10.0, double max = 10.0, double step = 2.0, wxColour colour = *wxRED, bool visible = true, bool showvalues=true)
            : MinValue(min), MaxValue(max), StepValue(step), Colour(colour), Visible(visible),
              ShowValues(showvalues), Format(wxT("%.1f")), ArrowSize(6),
              Font(wxFont(8, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false)) { }
        /** The default destructor.
         */
        ~wxEcAxis() { }
        /** Corrects the axis to make it useful without generating unexpected bugs.
         *  The call is required when you define an axis from a user's input that
         *  you have not checked beforehand.
         */
        void Validate();
        /** Makes so that a reasonable number of graduations will be displayed.
         */
        void Recalibrate();
        /** Resets the MinValue, MaxValue and StepValue to their default value.
         */
        void Reset();
};

//------------------------------------------

/** \class wxEcCurve
 *  \brief Defines a curve and its display.
 */
class WXDLLEXPORT wxEcCurve
{
    public:
        bool Defined;               /**< Marks if a curve should be considerated. */
        bool Enabled;               /**< If disabled, the curve won't be displayed. */
        wxString ExpressionX,       /**< The expression used for \a wxECT_CARTESIAN, \a wxECT_PARAMETRIC and \a wxECT_POLAR. */
                 ExpressionY;       /**< The complementary expression needed for \a wxECT_PARAMETRIC. */
        int Type;                   /**< The type of curve.
                                     * \see ec_defs.h (wxECT_*)
                                     */
        wxColour Colour;            /**< The colour used for the display. */
        int Width;                  /**< Pen's width for the curve. */
        bool DotStyle;              /**< The Y-coordinate will be a single point. No line is used to link to the previous computed point. */
        bool RangeEnabled;          /**< This marks the curve to be restricted to a specific domain delimited with RangeMin and RangeMax.
                                     *   If the type of curve is wxECT_PARAMETRIC or wxECT_POLAR, this value shall be \a true.
                                     */
        double RangeMin;            /**< The lower limit, for X or T. To be taken into consideration, RangeEnabled must be \a true. */
        double RangeMax;            /**< The upper limit, for X or T. To be taken into consideration, RangeEnabled must be \a true. */
        unsigned long NumPoints;    /**< The resolution to draw parametric and polar curves, or the number of points for a point cloud. */
        wxRealPoint *Cloud;         /**< Pointer to an array containing the points. Determine the number of points in wxEcCurve::NumPoints. */

        /** The default constructor. The curve is by default Defined and Enabled.
         */
        wxEcCurve(      wxString formulaX = wxEmptyString,
                        wxString formulaY = wxEmptyString,
                        int typeofcurve = wxECT_CARTESIAN,
                        wxColour pencolour = *wxBLUE,
                        int boldness = 2,
                        bool usedots = false,
                        bool userange = false,
                        double minrange = -10.0,
                        double maxrange = 10.0,
                        unsigned long numpoints = wxECD_RESOLUTION,
                        wxRealPoint* data = NULL)
            :
                        Defined(true), Enabled(true),
                        ExpressionX(formulaX),
                        ExpressionY(formulaY),
                        Type(typeofcurve),
                        Colour(pencolour),
                        Width(boldness),
                        DotStyle(usedots),
                        RangeEnabled(userange),
                        RangeMin(minrange),
                        RangeMax(maxrange),
                        NumPoints(numpoints),
                        Cloud(data)
            {}
        /** The default destructor.
         */
        ~wxEcCurve() {}

        /** Validates the curve to make it useful without generating unexpected bugs.
         *  The call is only required when you define a curve from a user's input that
         *  you have not checked beforehand.
         */
        void Validate();
        /** Parses a formula and applies the parameters. See the \ref syntax "HowTo" to know more about.
         * \param def The definition.
         * \param isPolar Indicates if the input is expected to define a \a wxECT_POLAR curve.
         * \remarks A colour is randomly chosen among a set of colours. You can edit it with wxEcCurve::Colour.
         */
        void Parse(wxString def, bool isPolar = false);
        /** Sorts the cloud to draw it in the right order.
         *  \a NumPoints is used to determine how many points to sort.
         *  The sorting technique used is bubble sort.
         * \return \a true if the data has been sorted.
         */
        bool SortCloud();
};

//------------------------------------------

/** \class wxEcPlot
 *  \brief The component which draws the curves.
 *
 * wxEcPlot is a component derived from \a wxWindow. It has a canvas on which you
 * can draw. Most of the time, the curves are drawn when a onPaint event occurs.
 * If you call \a wxWindowDC(myPlot), it is possible to draw on the client area.
 *
 * Before using the component, you must be aware that most of the methods does NOT
 * refresh the component automatically. So you must call wxEcPlot::Refresh() to
 * see any modification. The aim is to have better performances.
 */
class WXDLLEXPORT wxEcPlot : public wxWindow
{
    DECLARE_EVENT_TABLE()
    private:
        wxEcEngine *m_engine;
        wxEcAxis m_axisx, m_axisy;
        wxEcCurve m_curves[wxECD_CURVEMAX];
        wxColour m_backgroundcolour, m_gridcolour, m_reticulecolour;
        bool m_gridvisible, m_gridpolar, m_flatborder, m_reticulevisible;
        wxRealPoint m_reticule;
        bool m_locked;
        double m_ymaxfound, m_yminfound, m_zoomfactor;
        bool m_ymarker;
        wxString m_lasttangent;

        void DoDrawAxis(wxDC *context);
        void DoDrawCurve(wxDC *context, wxEcCurve *curve);
        void DoDrawParametricCurve(wxDC *context, wxEcCurve *curve);
        void DoDrawPolarCurve(wxDC *context, wxEcCurve *curve);
        void DoDrawCloud(wxDC *context, wxEcCurve *curve);
        void DoDrawReticule(wxDC *context);
        void DoRedraw();

    public:
        //-- Herited functions (to make them documented by Doxygen)
        /** Refreshes the component and processes the queued messages.
         * \warning This function is overriden from wxWindow and will cause wxTheApp->Yield() to be called.
         *          If wxEcPlot doesn't do so, you will never able to call FitYAxis(), GetYMin() and GetYMax()
         *          correctly in a busy process.
         * \remark Update() is not overriden.
         */
        void Refresh()
        {
            wxWindow::Refresh();
            wxTheApp->Yield();
        }

        //-- Normal behaviour
        /** The default constructor.
         * \param parent The parent of the component. Can be a wxFrame, a wxDialog, a wxPanel...
         * \param id The unique identifier.
         * \param pos The default position.
         * \param size The default size.
         * \param style The style (see \a wxWindow).
         */
        wxEcPlot(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);
        /** The default destructor.
         */
        ~wxEcPlot();
        /** Locks or unlocks the automatic refresh.
         * \param state \a true to lock, \a false to unlock.
         */
        void Lock(bool state = true) { m_locked = state; }
        /** Resets the component, but colours are not affected. All the curves will be deleted.
         */
        void Reset()
        {
            m_ymarker = false;
            RemoveAllCurves();
            SetDefaultGrid();
            m_axisx.Visible = true;
            m_axisy.Visible = true;
            m_gridvisible = true;
            m_reticulevisible = false;
            Lock(false);
            Refresh();
        }
        /** Returns the equation you obtained at the last call of DrawTangent().
         */
        wxString GetLastTangentEquation() { return m_lasttangent; }
        /** Draws a temporary tangent.
         * \param index The identifier of the curve (obtained with AddCurve()).
         * \param position The X-coordinate where the tangent shall be drawn.
         * \return \a true on success, \a false on failure.
         * \remarks It only works with \a wxECT_CARTESIAN.
         * \see GetLastTangentEquation()
         */
        bool DrawTangent(int index, double position);
        /** Draws in entire but temporarily the derivative of a curve, restricted on the correct domain.
         * \param index The identifier of the curve (obtained with AddCurve()).
         * \return \a true on success, \a false on failure.
         * \remarks It only works with \a wxECT_CARTESIAN.
         * \see wxEcEngine::Derivate()
         */
        bool DrawDerivative(int index);

        //-- Curves
        /** Adds a new curve.
         * \param curve An object defining the curve to add.
         * \return \a wxNOT_FOUND if memory is exceeded, a positive or null value on success.
         */
        int AddCurve(wxEcCurve curve)
        {
            int i;
            for (i=0 ; i<wxECD_CURVEMAX ; i++)
                if (!m_curves[i].Defined)
                    if (SetCurve(i, &curve))
                        return i;
                    else
                        return wxNOT_FOUND;
            return wxNOT_FOUND;
        }
        /** Returns the number of curves currently defined.
         */
        int CountCurve()
        {
            int i, result = 0;
            for (i=0 ; i<wxECD_CURVEMAX ; i++)
                if (m_curves[i].Defined)
                    result++;
            return result;
        }
        /** Removes the curve specified by its identifier.
         * \param index The identifier of the curve (obtained with AddCurve()).
         */
        void DeleteCurve(int index)
        {
            m_curves[index].Defined = false;
            m_curves[index].Enabled = false;
            m_curves[index].ExpressionX.Clear();
            m_curves[index].ExpressionY.Clear();
        }
        /** Enables or disables the curve specified by its identifier.
         * \param index The identifier of the curve (obtained with AddCurve()).
         * \param state \a true to enable, \a false to disable.
         */
        void EnableCurve(int index, bool state)
        {
            m_curves[index].Enabled = state;
        }
        /** Returns a curve.
         * \param index The identifier of the curve (obtained with AddCurve()).
         * \return The curve "as is" : defined or not, enabled or not.
         */
        wxEcCurve* GetCurve(int index)
        {
            return &(m_curves[index]);
        }
        /** Sets a new curve at the given index.
         * \param index The position to edit.
         * \param curve The pointer to the new curve.
         */
        bool SetCurve(int index, wxEcCurve *curve)
        {
            if (curve == NULL)
                return false;
            if (curve->Type != wxECT_CLOUD)
            {
                m_engine->Simplify(&(curve->ExpressionX));
                if (!m_engine->IsValid(&(curve->ExpressionX)))
                    return false;
                m_engine->Simplify(&(curve->ExpressionY));
                if ((curve->Type==wxECT_PARAMETRIC) && !m_engine->IsValid(&(curve->ExpressionY)))
                    return false;
            }
            m_curves[index] = *curve;
            m_curves[index].Defined = true;
            return true;
        }
        /** Deletes all the curves.
         * \remarks This function call DeleteCurve() \a wxECD_CURVEMAX times.
         */
        void RemoveAllCurves()
        {
            int i;
            for (i=0 ; i<wxECD_CURVEMAX ; i++)
                DeleteCurve(i);
            //m_lasttangent.Clear(); It is not necessarily useful
        }

        //-- Conversions
        /** Converts floating values into coordinates of the plan.
         *  The result depends on how the axis are defined (see SetAxis()).
         * \param X The X-coordinate.
         * \param Y The Y-coordinate.
         * \return A structure containing X and Y converted.
         */
        wxPoint CoupleValueToXY(double X, double Y);
        /** Indicates if the point (x,y) relative to the axis is visible.
         * \param X The X-coordinate.
         * \param Y The Y-coordinate.
         * \return \a true if the point belongs to the visible client area, \a false if the point is out of range
         */
        bool IsVisible(double X, double Y);
        /** Sets the unit per pixel.
         * \param perpixel The value per pixel (can be retrieved from XPerPixel() and YPerPixel())
         * \param forX If \a true, X-axis will be modified, else it will be the Y-axis.
         * \remarks If the control is resized, this function will not be recalled.
         */
        void SetUnit(double perpixel, bool forX);
        /** Converts a value using the system of coordinates of the control, relative to X.
         * \remarks The result can be outer than the physical limits.
         */
        int ValueToX(double value);
        /** Converts a value using the system of coordinates of the control, relative to Y.
         * \remarks The result can be outer than the physical limits.
         */
        int ValueToY(double value);
        /** Gives the interval represented by 1 pixel on the X-axis.
         */
        double XPerPixel();
        /** Converts a physical coordinate into the corresponding value, relative to the X-axis.
         */
        double XToValue(int X);
        /** Gives the interval represented by 1 pixel on the Y-axis.
         */
        double YPerPixel();
        /** Converts a physical coordinate into the corresponding value, relative to the Y-axis.
         */
        double YToValue(int Y);

        //-- Background & Axis
        /** Gets the colour of the background.
         */
        inline wxColour GetBackgroundColour() { return m_backgroundcolour; }
        /** Sets the colour of the background.
         */
        inline void SetBackgroundColour(wxColour value) { m_backgroundcolour = value; }
        /** Indicates if the control have a black border.
         */
        inline bool GetFlatBorder() { return m_flatborder; };
        /** Sets a solid border to the control, or not.
         */
        inline void SetFlatBorder(bool value) { m_flatborder = value; }
        /** Resets the grid.
         */
        void SetDefaultGrid()
        {
            wxEcAxis defaultAxis;
            m_axisx = defaultAxis;
            m_axisy = defaultAxis;
            m_gridpolar = false;
        }
        /** Returns the visibility of the grid
         */
        inline bool GetGridVisible() { return m_gridvisible; }
        /** Sets the visibility of the grid
         */
        inline void SetGridVisible(bool value) { m_gridvisible = value; }
        /** Returns \a true if the grid is polar.
         */
        inline bool GetGridPolar() { return m_gridpolar; }
        /** Defines a polar mode (\a true) or a cartesian mode (\a false)
         */
        inline void SetGridPolar(bool value) { m_gridpolar = value; }
        /** Gets the colour of the grid.
         */
        inline wxColour GetGridColour() { return m_gridcolour; }
        /** Sets the colour of the grid
         */
        inline void SetGridColour(wxColour value) { m_gridcolour = value; }

        /** Gives a pointer to the axis currently used for X or Y.
         * \param forX true returns for X, false returns for Y
         */
        inline wxEcAxis* GetAxis(bool forX) { return (forX ? &m_axisx : &m_axisy); }
        /** Applies a new configuration to the designed axis.
         * \param axis The new definition.
         * \param forX If \a true, X-axis will be modified, else it will be the Y-axis.
         */
        inline void SetAxis(wxEcAxis axis, bool forX=true) { if (forX) m_axisx = axis; else m_axisy = axis; }
        /** Fits the Y-axis to make all the enabled curves visible.
         *  You cannot use this function if the curves have not been drawn at least one time.
         *  Use Refresh() to do so.
         * \return \a true if the Y-axis has been modified, else \a false.
         * \see GetYMin()
         * \see GetYMax()
         * \see FitXAxis()
         */
        bool FitYAxis()
        {
            if (m_ymarker)
            {
                m_axisy.MaxValue = m_ymaxfound;
                m_axisy.MinValue = m_yminfound;
                m_axisy.Validate();
                m_axisy.Recalibrate();
                return true;
            }
            else
                return false;
        }
        /** By considering all the curves defined as \a wxECT_CLOUD, this function sets the X-coordinate
         *  to allow the cloud to be correctly visible. To fit the second coordinate, use wxEcPlot::FitYAxis().
         * \remarks This function doesn't care of other curves not typed as \a wxECT_CLOUD. In this case,
         *          compare the new value of the axis with the old one.
         * \return \a true if the axis has been edited, else \a false.
         */
        bool FitXAxis()
        {
            wxRealPoint point;
            double newMin=0.0, newMax=0.0;
            bool initialized = false;
            unsigned int i, j;

            //-- Action !
            for (i=0 ; i<wxECD_CURVEMAX ; i++)
                if ((m_curves[i].Defined) && (m_curves[i].Type==wxECT_CLOUD) && (m_curves[i].NumPoints>1))
                    for (j=0 ; j<m_curves[i].NumPoints ; j++)
                    {
                        point = m_curves[i].Cloud[j];
                        if (!initialized)
                        {
                            newMin = point.x;
                            newMax = point.x;
                            initialized = true;
                        }
                        if (point.x < newMin) newMin = point.x;
                        if (point.x > newMax) newMax = point.x;
                    }

            //-- Result
            if (/*initialized && */ (newMin < newMax))
            {
                m_axisx.MinValue = newMin;
                m_axisx.MaxValue = newMax;
                m_axisx.Validate();
                m_axisx.Recalibrate();
                return true;
            }
            else
                return false;
        }
        /** Returns the maximal value of Y found during the last refresh.
         * \see FitYAxis()
         */
        inline double GetYMax() { if (m_ymarker) return m_ymaxfound; else return 0; }
        /** Returns the minimal value of Y found during the last refresh.
         * \see FitYAxis()
         */
        inline double GetYMin() { if (m_ymarker) return m_yminfound; else return 0; }
        /** This function solves YPerPixel()=XPerPixel(). The grid will look like
         *  squares and right angles are possible.
         * \param symetrical If \a false, Ymax will be adjusted.
         *                   If \a true, Ymax and Ymin will be edited, and Ymin = -Ymin.
         * \remarks Y-axis will be made symmetrical compared to zero.
         */
        void Orthonormalize(bool symetrical = true)
        {
            int w, h;
            this->GetSize(&w, &h);
            double unit = XPerPixel();
            if (symetrical)
            {
                m_axisy.MaxValue = unit*h/2;
                m_axisy.MinValue = -unit*h/2;
            }
            else
                m_axisy.MaxValue = m_axisy.MinValue + unit*h;
        }
        /** Returns the current zoom factor.
         */
        double GetZoomFactor() { return m_zoomfactor; }
        /** Changes the zoom factor. The default value is \a wxECD_ZOOMFACTOR defined in ec_defs.h
         * \return \a true on success, \a false if the factor is not correct.
         */
        bool SetZoomFactor(double value = wxECD_ZOOMFACTOR)
        {
            if (value<=0)
                return false;
            m_zoomfactor = value;
            return true;
        }
        /** Zooms out.
         * \see SetZoomFactor()
         */
        void Unzoom()
        {
            m_axisx.MinValue *= m_zoomfactor;
            m_axisx.MaxValue *= m_zoomfactor;
            m_axisx.Recalibrate();
            m_axisy.MinValue *= m_zoomfactor;
            m_axisy.MaxValue *= m_zoomfactor;
            m_axisy.Recalibrate();
        }
        /** Zooms in.
         * \see SetZoomFactor()
         */
        void Zoom()
        {
            m_axisx.MinValue /= m_zoomfactor;
            m_axisx.MaxValue /= m_zoomfactor;
            m_axisx.Recalibrate();
            m_axisy.MinValue /= m_zoomfactor;
            m_axisy.MaxValue /= m_zoomfactor;
            m_axisy.Recalibrate();
        }

        //-- Reticule
        /** Sets the position of the reticule, relative to the axis.
         * \param x The X-coordinate.
         * \param y The Y-coordinate.
         */
        inline void SetReticule(double x, double y) { m_reticule = wxRealPoint(x,y); }
        /** Gets the visibility of the reticule.
         */
        inline bool GetReticuleVisible() { return m_reticulevisible; }
        /** Sets the visibility of the reticule.
         */
        inline void SetReticuleVisible(bool value) { m_reticulevisible = value; }
        /** Gets the colour of the reticule.
         */
        inline wxColour GetReticuleColour() { return m_reticulecolour; }
        /** Sets the colour of the grid.
         */
        inline void SetReticuleColour(wxColour value) { m_reticulecolour = value; }

        //-- Events
        /** The event when a repaint is called.
         */
        void OnPaint(wxPaintEvent &event);
        /** The event when the control is resized.
         */
        void OnResize(wxSizeEvent &event);
};

#endif
