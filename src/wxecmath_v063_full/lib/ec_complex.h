
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
 * \file ec_complex.h
 * \brief Manages complex numbers
 * \author ecrucru
 * \version 0.6.3
 * \date January 2009
 *
 * This file defines a class to manage complex numbers. They have a real
 * and imaginary part. Operators are provided to make operations.
 *
 * New functions are also added : cos, sin... defined in the complex domain.
 * The reference is http://functions.wolfram.com/ElementaryFunctions/
 */

#ifndef ec_complex_h
#define ec_complex_h

//------------------------------------------

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "ec_defs.h"

//------------------------------------------

/** \class wxEcComplex
 * \brief A complex number
 *
 * A complex number is internally represented like cartesian coordinates, ie a+ib.
 * If you want to use a polar representation, have a look to the following code :
 * \code
 *   {
 *      wxEcComplex a(r*cos(theta), r*sin(theta)), b, c;
 *      b.Re = r * cos(theta);
 *      b.Im = r * sin(theta);
 *      c.FromPolar(r, theta);
 *   }
 * \endcode
 */
class WXDLLEXPORT wxEcComplex
{
    public:
        double Re;          /**< The real part of the number. */
        double Im;          /**< The imaginary part of the number. */

        /** The default constructor with initialization to zero.
         */
        wxEcComplex() : Re(0.0), Im(0.0) {}
        /** The extended constructor.
         * \param real The real part.
         * \param imaginary The imaginary part.
         */
        wxEcComplex(double real, double imaginary) : Re(real), Im(imaginary) {}
        /** Sets the value of the complex number from a polar couple (r,theta).
         */
        void FromPolar(double r, double theta)
        {
            Re = r*cos(theta);
            Im = r*sin(theta);
        }
        /** Returns the absolute value of the complex number.
         */
        double Modulus()
        {
            return sqrt(Re*Re + Im*Im);
        }
        /** Return the argument of the complex number.
         * \remarks (0,0) will return 0 even if the value should be undefined.
         */
        double Argument()
        {
            double buffer;
            if ((Re == 0.0) && (Im == 0.0))
                return 0.0;
            else if (Re == 0.0)
                return (Im > 0.0 ? M_PI/2.0 : -M_PI/2.0);
            else if (Im == 0.0)
                return (Re > 0.0 ? 0.0 : M_PI);
            else
            {   // damned !
                buffer = atan(Im/Re);
                if (Re < 0.0)
                    if (Im > 0.0)
                        buffer += M_PI;
                    else
                        buffer -= M_PI;
                return buffer;
            }
        }
        /** Returns the complex conjugate of the complex number.
         */
        wxEcComplex Conjugate()
        {
            return wxEcComplex(Re, -Im);
        }
        /** Displays the complex number as string.
         * \param usePolarNotation \a false will return a+ib, \a true will return r.e^ti
         */
        wxString AsString(bool usePolarNotation = false)
        {
            if (usePolarNotation)
                return wxString::Format(wxT("%f*e^%fi"), Modulus(), Argument());
            else
                return wxString::Format(wxT("%f%s%fi"), Re, (Im < 0.0 ? wxEmptyString : wxT("+")), Im);
        }

        //------------------------------------------

        /** Operator to sum two complex numbers. */
        wxEcComplex operator+(const wxEcComplex& complex) const { return wxEcComplex(Re+complex.Re, Im+complex.Im); }
        /** Operator to substract two complex numbers. */
        wxEcComplex operator-(const wxEcComplex& complex) const { return wxEcComplex(Re-complex.Re, Im-complex.Im); }
        /** Operator to multiply two complex numbers. */
        wxEcComplex operator*(const wxEcComplex& complex) const { return wxEcComplex(Re*complex.Re - Im*complex.Im, Im*complex.Re + Re*complex.Im); }
        /** Operator to divide two complex numbers. Check against division by zero is not performed. */
        wxEcComplex operator/(const wxEcComplex& complex) const { return wxEcComplex((Re*complex.Re + Im*complex.Im)/(complex.Re*complex.Re + complex.Im*complex.Im), (Im*complex.Re - Re*complex.Im)/(complex.Re*complex.Re + complex.Im*complex.Im)); }
        /** Operator to compare two complex numbers. It checks if Re==Re and Im==Im. */
        bool operator==(const wxEcComplex& complex) const { return ((Re==complex.Re) && (Im==complex.Im)); }
        /** Operator to compare two complex numbers. It checks if Re!=Re or Im!=Im. */
        bool operator!=(const wxEcComplex& complex) const { return ((Re!=complex.Re) || (Im!=complex.Im)); }
};

//------------------------------------------

    static double sign(double value)
    {
        return (value<0.0 ? -1.0 : 1.0);
    }

    /** Square elevation. */
    static wxEcComplex sqr(wxEcComplex cpx)
    {
        return cpx*cpx;
    }

    /** Root square in the complex domain. */
    static wxEcComplex sqrt(wxEcComplex cpx)
    {
        return wxEcComplex(sqrt(2.0*(cpx.Modulus()+cpx.Re))/2.0 , sign(cpx.Im)*sqrt(2.0*(cpx.Modulus()-cpx.Re))/2.0);
    }

    /** Exponential function in the complex domain. */
    static wxEcComplex exp(wxEcComplex cpx)
    {
        return wxEcComplex(exp(cpx.Re)*cos(cpx.Im) , exp(cpx.Re)*sin(cpx.Im));
    }

    /** Natural logarithm in the complex domain.
     * \remarks The library uses log() commonly used in C++.
     */
    static wxEcComplex log(wxEcComplex cpx)
    {
        return wxEcComplex(log(cpx.Re*cpx.Re + cpx.Im*cpx.Im)/2.0 , sign(cpx.Im)*M_PI/2.0 - atan(cpx.Re/cpx.Im));
    }

    /** Cosine in the complex domain. */
    static wxEcComplex cos(wxEcComplex cpx)
    {
        return wxEcComplex(cos(cpx.Re)*cosh(cpx.Im) , -sin(cpx.Re)*sinh(cpx.Im));
    }

    /** Sine in the complex domain. */
    static wxEcComplex sin(wxEcComplex cpx)
    {
        return wxEcComplex(sin(cpx.Re)*cosh(cpx.Im) , cos(cpx.Re)*sinh(cpx.Im));
    }

    /** Tangent in the complex domain. */
    static wxEcComplex tan(wxEcComplex cpx)
    {
        return wxEcComplex(sin(2.0*cpx.Re)/(cos(2.0*cpx.Re)+cosh(2.0*cpx.Im)) , sinh(2.0*cpx.Im)/(cos(2.0*cpx.Re)+cosh(2.0*cpx.Im)));
    }

    /** Cosecant in the complex domain. */
    static wxEcComplex csc(wxEcComplex cpx)
    {
        return wxEcComplex(-2.0*cosh(cpx.Im)*sin(cpx.Re)/(cos(2.0*cpx.Re)-cosh(2.0*cpx.Im)) , 2.0*cos(cpx.Re)*sinh(cpx.Im)/(cos(2.0*cpx.Re)-cosh(2.0*cpx.Im)));
    }

    /** Secant in the complex domain. */
    static wxEcComplex sec(wxEcComplex cpx)
    {
        return wxEcComplex(2.0*cos(cpx.Re)*cosh(cpx.Im)/(cos(2.0*cpx.Re)+cosh(2.0*cpx.Im)) , 2.0*sin(cpx.Re)*sinh(cpx.Im)/(cos(2.0*cpx.Re)+cosh(2.0*cpx.Im)));
    }

    /** Cotangent in the complex domain. */
    static wxEcComplex cot(wxEcComplex cpx)
    {
        return wxEcComplex(-sin(2.0*cpx.Re)/(cos(2.0*cpx.Re)-cosh(2.0*cpx.Im)) , sinh(2.0*cpx.Im)/(cos(2.0*cpx.Re)-cosh(2.0*cpx.Im)));
    }

    /** Hyperbolic cosine in the complex domain. */
    static wxEcComplex cosh(wxEcComplex cpx)
    {
        return wxEcComplex(cos(cpx.Im)*cosh(cpx.Re) , sin(cpx.Im)*sinh(cpx.Re));
    }

    /** Hyperbolic sine in the complex domain. */
    static wxEcComplex sinh(wxEcComplex cpx)
    {
        return wxEcComplex(cos(cpx.Im)*sinh(cpx.Re) , cosh(cpx.Re)*sin(cpx.Im));
    }

    /** Hyperbolic tangent in the complex domain. */
    static wxEcComplex tanh(wxEcComplex cpx)
    {
        return wxEcComplex(sinh(2.0*cpx.Re)/(cos(2.0*cpx.Im)+cosh(2.0*cpx.Re)) , sin(2.0*cpx.Im)/(cos(2.0*cpx.Im)+cosh(2.0*cpx.Re)));
    }

    /** Hyperbolic cosecant in the complex domain. */
    static wxEcComplex csch(wxEcComplex cpx)
    {
        return wxEcComplex(-2.0*cos(cpx.Im)*sinh(cpx.Re)/(cos(2.0*cpx.Im)-cosh(2.0*cpx.Re)) , 2.0*cosh(cpx.Re)*sin(cpx.Im)/(cos(2.0*cpx.Im)-cosh(2.0*cpx.Re)));
    }

    /** Hyperbolic secant in the complex domain. */
    static wxEcComplex sech(wxEcComplex cpx)
    {
        return wxEcComplex(2.0*cos(cpx.Im)*cosh(cpx.Re)/(cos(2.0*cpx.Im)+cosh(2.0*cpx.Re)) , -2.0*sin(cpx.Im)*sinh(cpx.Re)/(cos(2.0*cpx.Im)+cosh(2.0*cpx.Re)));
    }

    /** Hyperbolic cotangent in the complex domain. */
    static wxEcComplex coth(wxEcComplex cpx)
    {
        return wxEcComplex(-sinh(2.0*cpx.Re)/(cos(2.0*cpx.Im)-cosh(2.0*cpx.Re)) , sin(2.0*cpx.Im)/(cos(2.0*cpx.Im)-cosh(2.0*cpx.Re)));
    }

#endif
