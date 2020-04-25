
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

/*--------------------------------------------------------------------------------------
 * This file is also the root of the documentation. Comments do not interfer with the
 * software. They are taken into consideration only by Doxygen, a generator of docs.
--------------------------------------------------------------------------------------*/

/** @mainpage wxEcMath
 *
 * \a wxEcMath is a tiny library to link to your software. It gives you the means to handle
 * mathematical objects : expressions, curves, complex numbers and matrixes. The rich samples
 * provided will help you to set up a new project very quickly.
 *
 * The four main interests of \a wxEcMath are :
 *      - interesting features, principally the parser of mathematical expressions
 *      - multi-platform
 *      - support of ANSI and UNICODE
 *      - rich documentation and samples
 *
 * The intended audience is developers and researchers.
 *
 * To use the library, you must write your software using the \a wxWidgets framework.
 * You must also be aware of the terms under which the library is released (see below).
 *
 * \section topics Topics
 *      - \subpage overview     "Overview"
 *      - \subpage naming       "Naming convention of the constants"
 *      - \subpage syntax       "Syntax to load a curve"
 *      - \subpage funclist     "Supported functions"
 *      - \subpage samples      "Samples"
 *      - \subpage license      "License"
 *      .
 * See online : http://sourceforge.net/projects/wxecmath/
 */

/** \page overview Overview
 *
 * \a wxEcMath is the name given to the library, which contains sub-classes.
 * You really need to know wxEcEngine, wxEcPlot, wxEcComplex and wxEcMatrix.
 *
 * To compile the library, you just need to include it in your workspace.
 * There is no makefile, and no shared library.
 *
 * Depending on your needs, you will have to include header files. New
 * names begin with prefix "wxEc". If you don't need a class, don't include
 * the associated header file.
 * \code
 *      #define wxECM_USEDEBUG
 *      #include "ec_defs.h"        //always required !
 *      #include "ec_engine.h"
 *      #include "ec_plot.h"
 *      #include "ec_complex.h"
 *      #include "ec_matrix.h"
 * \endcode
 * \see wxECM_USEDEBUG
 *
 * To perform a simple computation, it is not harder than :
 * \code
 *  {
 *      double result;
 *      wxEcEngine calc;
 *      if (calc.SetFormula(wxT("3+4")))
 *      {
 *          result = calc.Compute();
 *          if (calc.GetLastError() == wxECE_NOERROR)
 *              ; //well done !
 *          else
 *              wxLogError(calc.TranslateError(calc.GetLastError()));
 *              //better luck next time !
 *      }
 *      else
 *          wxLogError(calc.TranslateError(calc.GetLastError()));
 *  }
 * \endcode
 *
 * To create a plot, do like other common components :
 * \code
 *  {
 *      wxEcPlot *m_plot;
 *      ...
 *      m_plot = new wxEcPlot(this, wxID_ANY, wxDefaultPostion, wxDefaultSize);
 *      m_yourSizer->Add(m_plot, 1, wxEXPAND|wxALL, 5);
 *  }
 * \endcode
 *
 * To draw a curve, you have to create a new object :
 * \code
 *  {
 *      wxEcPlot *m_plot; //assumed correctly initialized by you
 *      int curveID;
 *      wxEcCurve newcurve;
 *      newcurve.Parse(wxT("sqr(x)/10 $ -7 4*pi"));
 *      curveID = m_plot->AddCurve(newcurve);
 *      m_plot->Refresh();
 *  }
 * \endcode
 *
 * \remarks \ref samples "Samples" detail various types of wxEcCurve.
 * Explore the code and find the use of wxEcPlot::AddCurve().
 *
 * If you want to use complex numbers, it is not complicated :
 * \code
 *  {
 *      wxEcComplex a(4,3), b(-1,0), c, d;
 *      c = a + b;
 *      d = a * c;
 *      b.Re = d.Im;
 *      //...
 *  }
 * \endcode
 *
 * When using matrixes, you will have to initialize each cell before being able to operate.
 * Automated fills can be managed by wxEcMatrix::Clear(), wxEcMatrix::Factor() and
 * wxEcMatrix::AddConstant().
 * \code
 *  {
 *      wxEcMatrix matA(2,2), matB(2,1), matC;
 *      matA.SetValue(1,1, 1.0);      //the first parameter is the n-th line
 *      matA.SetValue(1,2, 2.0);      //the second paramater is the n-th column
 *      matA.SetValue(2,1, 3.0);      //the third parameter is the value of the designated cell
 *      matA.SetValue(2,2, 4.0);
 *      matB.SetValue(1,1, 5.0);
 *      matB.SetValue(2,1, -6.0);
 *      matC = matA * matB;
 *      wxMessageDialog(NULL, matC.DumpAsString()).ShowModal();
 *  }
 * \endcode
 * \warning A matrix stores values in double format. At C++ compilation, make sure your values
 *          won't be considered as integer values. Thus, you must write "my_matrix.Clear(2.0/3.0)"
 *          not "my_matrix.Clear(2/3)". In case of doubt, wxEcMatrix::DumpAsString() can show
 *          you the content of the matrix.
 */

/** \page naming Naming convention
 *
 * Symbols included in wxEcMath have a magic prefix named "wxEc" or "wxEC".
 * The first one defines a class or a structure. The second one
 * represents a definition or an enumeration.
 *
 * wxEC is attached another letter following this syntax : wxEC(key)_(name)
 *  - key :
 *      - A : angle
 *      - D : definition
 *      - E : error
 *      - M : mode
 *      - T : type of curve
 *      .
 *  - name : written in uppercase
 *  .
 *
 * Definitions are stored in "ec_defs.h".
 */

/** \page syntax Syntax to load a curve
 *
 * With wxEcPlot, you can draw 4 types of curves :
 *      - cartesian : y = f(x) marked as \a wxECT_CARTESIAN.
 *      - parametric : x = f(t) and y = f(t) marked as \a wxECT_PARAMETRIC.
 *      - polar : r = f(t) marked as \a wxECT_POLAR.
 *      - cloud : array of (x,y) as \a wxECT_CLOUD.
 *      .
 *
 * To parse a formula automatically, a syntax must be adopted. You can restrict the definition
 * of the curve by using wildcards. Because of \a theta, parametric and polar curves will be
 * restricted in any case.
 *      - cartesian normal : "3*x+2"
 *      - cartesian restricted : "sqr(x) $ -5 5"
 *      - parametric : "t+2 ; t/2 $ -pi pi"
 *      - polar : "t $ 0 2*pi"
 *      - cloud : (unapplicable)
 *      .
 *
 * These strings must be parsed using wxEcCurve::Parse(), but you can also define a wxEcCurve
 * on your own via the constructor or the methods (required for wxECT_CLOUD).
 * \warning If the expression is polar, wxEcCurve::Parse() takes a second parameter !
 * Else it will be considered as being parametric.
 *
 * As you can see :
 *      - ";" delimits the two members of an equation.
 *      - "$" defines a domain, min and max are separated with a space.
 *      - if these characters are not found, the expression will be treated as a non-restricted cartesian curve.
 *      .
 * If no domain is given, default values will be chosen. The use of the range will be set accordingly.
 *
 * When you parse an expression, a default colour is randomly chosen among twenty pre-defined colours.
 * It is a good thing to randomize this automatic choice in your \a wxApp::OnInit() :
 * \code
 *  srand(time(NULL));
 * \endcode
 *
 * When dealing with a point cloud, you will have to define the curve on your own (data, style, color...).
 * Let's see how to do with a shortened sample :
 * \code
 *  #include "ec_defs.h"
 *  #include "ec_engine.h"
 *  #include "ec_plot.h"
 *
 *  class myShortenedClass
 *  {
 *      private:
 *          wxEcPlot *m_plot;
 *          wxRealPoint m_cloud[10];
 *          void CreateCloud()
 *          {
 *              wxEcCurve curve(wxEmptyString, wxEmptyString, wxECT_CLOUD, *wxRED, 1, false, false, 0, 10, 10, &(m_cloud[0]));
 *              m_plot->AddCurve(curve);
 *          }
 *  }
 * \endcode
 *
 * As the cloud uses a pointer, any modification in \a m_cloud will affect the plot.
 * Do use wxEcPlot::Refresh() to update your view. It is not sure it will be performed automatically.
 *
 * \warning The number of points declared in wxEcCurve::NumPoints must be lower or equal than
 * the capacity of your buffer. If not, it will result in unexpected bugs.
 */

/** \page funclist Supported functions in wxEcMath
 *
 * The library is able to interpret several functions. Their length cannot be longer than 4 characters.
 * Indeed wxEcEngine::Function2ID() converts the name (8 or 16 bits per char) into an integer (32 bits).
 * We assumed it should be faster to interpret.
 *
 * \section normalfuncs Normal functions
 *      - abs : the absolute value, it removes the sign
 *      - ceil : the smallest integer greater than or equal to x
 *      - cub : x^3, safe way to compute such an exponent
 *      - deg : converts from radian to degree
 *      - exp : the exponential value
 *      - hvi : Heaviside's function, =0 if x<0, =1 if x>=0
 *      - int : the largest integer less than or equal to x
 *      - inv : inverts, 1/x
 *      - floor : not supported, see \a int
 *      - ln : the neperian logarithm
 *      - lnep : see \a ln
 *      - log : the logarithm base 10
 *      - rad : converts from degree to radian
 *      - sgn : the sign, -1 or +1. Zero returns +1.
 *      - sqr : x^2, safe way to compute such an exponent
 *      - sqrt : the root square
 *      .
 *
 * \section trigofuncs Trigonometric functions
 *      - acos : the secant (inverse of cosine)
 *      - acsh : the inverse of the hyperbolic cosine
 *      - asin : the cosecant (inverse of sine)
 *      - asnh : the inverse of the hyperbolic sine
 *      - atan : the cotangent (inverse of tangent)
 *      - atnh : the inverse of the hyperbolic tangent
 *      - cos : the cosine
 *      - cosh : the hyperbolic cosine
 *      - sin : the sine
 *      - sinc : the cardinal sine (radian)
 *      - sinh : the hyperbolic sine
 *      - tan : the tangent
 *      - tanh : the hyperbolic tangent
 *      .
 *
 * \section complexfuncs Overriden functions in the complex domain
 * These functions are not supported by wxEcEngine. Their use is dedicated
 * to C++ developers who use our wxEcComplex class to handle complex numbers.
 *
 * The definition of these functions is explicitely written in ec_complex.h.
 * So you must include this file before being able to use them.
 * \code
 *     #include "ec_complex.h"
 * \endcode
 *
 * List :
 *      - sqrt : the root square
 *      - exp : the exponential value
 *      - log : the natural logarithm (don't confuse with LN which is not overriden)
 *      - cos : cosine
 *      - sin : sine
 *      - tan : tangent
 *      - csc : cosecant
 *      - sec : secant
 *      - cot : cotangent
 *      - cosh : hyperbolic cosine
 *      - sinh : hyperbolic sine
 *      - tanh : hyperbolic tangent
 *      - csch : hyperbolic cosecant
 *      - sech : hyperbolic secant
 *      - coth : hyperbolic cotangent
 *      .
 */

/** \page samples Samples
 *
 * Samples are provided to show various possible uses of the library.
 *
 * They are sorted in a dedicated folder :
 *
 *      - console :
 *          - wxEcEngine
 *          .
 *      - histogram :
 *          - wxEcPlot : wxECT_CLOUD
 *          .
 *      - inline :
 *          - wxEcEngine
 *          .
 *      - mandelbrot :
 *          - wxEcComplex : operations, modulus, argument
 *          - wxEcPlot : wxECT_CLOUD
 *          .
 *      - matrix
 *          - wxEcMatrix
 *          - wxEcPlot : wxECT_CLOUD
 *          .
 *      - plot :
 *          - wxEcEngine
 *          - wxEcPlot : wxECT_CARTESIAN, wxECT_PARAMETRIC, wxECT_POLAR
 *          - wxEcComplex : modulus, argument
 *          .
 *      - speedtest :
 *          - wxEcEngine
 *          .
 *      - visualcalc :
 *          - wxEcEngine
 *          .
 *      .
 */

/** \page license License
 *
 * \a wxEcMath is released under the terms of the "GNU General Public License version 2".
 *
 * The official download center is SourceForge.net
 *
 * \pre
 *  wxEcMath - version 0.6.3 <br>
 *  Copyright (C) 2008-2010, http://sourceforge.net/projects/wxecmath/
 *
 * \pre
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 * \pre
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * \pre
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

//--------------------------------------------------------------------------------------

/**
 * \file ec_defs.h
 * \brief Definition of the simpliest classes and constants
 * \author ecrucru
 * \version 0.6.3
 * \date August 2008
 *
 * Implements the definition of core elements needed by the wxEcMath classes.
 * Before compiling a release, please take a look to wxECM_USEDEBUG. This can
 * increase the performances of your software very significantly.
 */

#ifndef ec_defs_h
#define ec_defs_h

    #if wxUSE_UNICODE
        #pragma message("wxEcMath - Compilation mode: UNICODE")
        #define uniCStr wc_str
    #else
        #pragma message("wxEcMath - Compilation mode: ANSI")
        #define uniCStr c_str
    #endif

//--------------- MODES --------------------

/** \def wxECM_USEDEBUG
 * When defined, extra features are compiled inside wxEcEngine. They were implemented
 * during the development of wxEcMath to track bugs. For a lambda-user, there is no
 * need to use them (performances would be more than 2 times slower).
 *
 * To enable these features without editing the library, you can write :
 * \code
 *      #define  wxECM_USEDEBUG
 *      #include "ec_defs.h"
 *      #include "ec_engine.h"
 * \endcode
 *
 * But it is really better to define wxECM_USEDEBUG as a preprocessor definition.
 * Thus it will apply to the whole project. You can do by editing the settings of
 * the project, or by adding /DwxECM_USEDEBUG=1 in the command line.
 *
 * \see wxEcEngine
 * \see wxEcEngine::LogAction()
 * \see wxEcEngine::GetLog()
 */
//DOXYGEN: #define wxECM_USEDEBUG

//--------------- COPYRIGHT ----------------

/** \def wxECD_SOFTWARE
 * Name of the software.
 */
#define        wxECD_SOFTWARE               wxT("wxEcMath")
/** \def wxECD_URL
 * Internet address where you can download the software.
 */
#define        wxECD_URL                    wxT("http://sourceforge.net/projects/wxecmath/")
/** \def wxECD_VERSION
 * Version of the software currently used.
 */
#define        wxECD_VERSION                wxT("0.6.3")
/** \def wxECD_AVERAGESPEED
 * Average computations you can make in 1 second.
 * Allows you to predict the time needed in complex algorithms.
 * The value depends on \a wxECM_USEDEBUG.
 *
 * \remarks The formula chosen to evaluate the speed is "(1+sqrt(5))/2-2*cos(2*pi/5)".
 * Depending on the length of your formula, you won't get exactly this speed. Maybe more, maybe less.
 * However this value should be representative of most of cases.
 *
 * \see wxECM_USEDEBUG
 */
#ifdef wxECM_USEDEBUG
    #define    wxECD_AVERAGESPEED           9000        //per second, arbitrary because the function to evaluate can be complex
#else
    #define    wxECD_AVERAGESPEED           29000
#endif

//--------------- ENGINE -------------------

/** \def wxECD_OPERATORS
 * All the operators supported, ordered by mathematical priority.
 */
#define        wxECD_OPERATORS              wxT("^/*-+")
/** \def wxECD_ALPHABET
 * All the letters of the alphabet, written in lowercase (a-z).
 */
#define        wxECD_ALPHABET               wxT("abcdefghijklmnopqrstuvwxyz")
/** \def wxECD_NUMERIC
 * All the numbers supported (0-9).
 */
#define        wxECD_NUMERIC                wxT("0123456789")
/** \def wxECD_EXTRASYMBOLS
 * Extra symbols available when evaluated.
 */
#define        wxECD_EXTRASYMBOLS           wxT("().#")
/** \def wxECD_PERMITTED
 * Allowed ANSI characters are defined here.
 * Since 0.6.1, you can define a constant with the name of your choice.
 * It means you can use a chinese or japanese name if you have enabled "UNICODE".
 * This choice is automatically performed.
 */
#define        wxECD_PERMITTED              wxT("abcdefghijklmnopqrstuvwxyz0123456789^/*-+().#")
/** \def wxECD_STACKMAX
 * Maximal number of constants you may define.
 *
 * Maximal number of entities that an inline expression may contain (a+b*c = 3 entities).
 */
#define        wxECD_STACKMAX               128


/** \struct wxEcPosition
 *  \brief Stores an expression and two indexes (From/To)
 *
 * This structure is only used by wxEcEngine to mark the position of two brackets in an expression.
 * Normally, you are not expected to need this resource.
 * \see wxEcEngine
 */
typedef struct wxEcPosition
{
    long From;              /**< Beginning of the tagged area. */
    long To;                /**< End of the tagged area. */
    wxString Function;      /**< The expression. */
} wxEcPosition;

/** \struct wxEcConstMap
 *  \brief It is a wxHashMap(string -> double) which can manage a list of constants.
 *
 * Since version 0.6.1, wxHashMap is the new system used to manage constants.
 * Before, an array of 128 cells was used. New performances have not been probed.
 */
WX_DECLARE_STRING_HASH_MAP(double, wxEcConstMap);

/** Error codes returned by wxEcEngine::Compute().
 * \see wxEcEngine::GetLastError()
 */
enum
{
    wxECE_NOERROR = 0,      /**< No error. */
    wxECE_SYNTAX,           /**< The syntax is not correct. */
    wxECE_UNDEFCONSTANT,    /**< The constant is not defined. */
    wxECE_MEMORYEXCEEDED,   /**< The maximal number of constants/curves that you may define is reached.
                                 \see wxECD_STACKMAX */
    wxECE_DIVBYZERO,        /**< Division by zero */
    wxECE_DOMAINERROR,      /**< The function is not defined for the given value. */
    wxECE_UNKNOWNFUNC,      /**< The name of the function is unknown. */
    wxECE_STACKERROR,       /**< The expression is too long to be evaluated.
                                 \see wxECD_STACKMAX */
    wxECE_UNCOMPUTABLE      /**< Generic error. */
};

/** Trigonometric modes. Radian is the default mode.
 * \see wxEcEngine::GetTrigonometricMode()
 * \see wxEcEngine::SetTrigonometricMode()
 */
enum
{
    wxECA_RADIAN = 0,       /**< Radian. */
    wxECA_DEGREE,           /**< Degree. */
    wxECA_GRADIAN           /**< Gradian. */
};

//--------------- PLOT ---------------------

/** \def wxECD_CURVEMAX
 * Maximal number of curves you can define.
 * \see wxEcPlot::AddCurve()
 */
#define        wxECD_CURVEMAX               64
/** \def wxECD_STEPSMAX
 * Maximal number of graduations a plot may contain.
 */
#define        wxECD_STEPSMAX               30
/** \def wxECD_RESOLUTION
 * Default number of points used to draw a parametric or a polar curve.
 * The value applies to a curve, not to all the curves loaded in a wxEcPlot.
 * \see wxEcCurve::NumPoints
 */
#define        wxECD_RESOLUTION             500
/** \def wxECD_DXSTEP
 * The step used to approximate the derivative of a curve at a given point.
 * \see wxEcPlot::DrawDerivative()
 */
#define        wxECD_DXSTEP                 0.0001
/** \def wxECD_RETICULESIZE
 * The radius of the reticule.
 * \see wxEcPlot::SetReticule()
 */
#define        wxECD_RETICULESIZE           3
/** \def wxECD_ZOOMFACTOR
 * The default zoom factor.
 * \see wxEcPlot::SetZoomFactor()
 */
#define        wxECD_ZOOMFACTOR             1.5


/** Types of curves you can draw.
 * \see wxEcCurve
 */
enum
{
    wxECT_CARTESIAN = 0,    /**< Cartesian: y = f(x) */
    wxECT_PARAMETRIC,       /**< Parametric: x = f(t) && y = f(t) */
    wxECT_POLAR,            /**< Polar : r = f(t) */
    wxECT_CLOUD               /**< Graphical representation : data from experiments, evolution of the stock exchange...*/
};

//--------------- FUNCS --------------------

// static bool wxEcBetween(unsigned int value, unsigned int lowlimit, unsigned int highlimit)
// {
//     return ((lowlimit<=value) && (value<=highlimit));
// }

//------------------------------------------

/** \class wxEcUPoint
 *  \brief Stores 2 unsigned integers.
 *
 * This class is similar to wxPoint but stores unsigned values
 * and arithmetic operators have been removed.
 */
class WXDLLEXPORT wxEcUPoint
{
    public:
        unsigned int x;     /**< X. */
        unsigned int y;     /**< Y. */
        /** The default constructor. */
        wxEcUPoint() : x(0), y(0) { }
        /** The constructor with initialization. */
        wxEcUPoint(unsigned int newx, unsigned int newy) : x(newx), y(newy) { }
        /** Compares two unsigned points. */
        bool operator==(const wxEcUPoint& up) { return ((x==up.x) && (y==up.y)); }
};

#endif
