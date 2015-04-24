
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
 * \file ec_matrix.h
 * \brief Matrix manager
 * \author ecrucru
 * \version 0.6.3
 * \date February 2009
 *
 * The matrix is a represented by a 1-dimension array of doubles.
 * So, if you change the dimensions of the matrix, it will be filled
 * with zeros because data will not be realigned.
 *
 * If you know wxImage, please note that wxEcMatrix uses the same internal
 * representation. It was not designed as is, but it appears coincidently
 * that it is so.
 *
 * \warning
 * For developers, the first line or column is represented by number "1".
 * However, internally (in the library), the first offset is "0". So be
 * careful when you deal with arrays or embedded functions in wxEcMatrix !
 */

#ifndef ec_matrix_h
#define ec_matrix_h

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

/** \class wxEcMatrix
 *  \brief Handles a matrix with basic operations.
 */
class WXDLLEXPORT wxEcMatrix
{
    private:
        unsigned int m_line, m_column;
        double *m_data, *m_databackup;

        void Copy(double *source, double *destination, unsigned int count);
        void PushData(){ Copy(m_data, m_databackup, m_line*m_column); }
        void PopData() { Copy(m_databackup, m_data, m_line*m_column); }
        double RecurseDeterminant(wxEcMatrix* matrix, bool root = false);

    public:

        /** The default constructor. Matrix will be nulled or duplicated from *data.
         * \param line Number of lines.
         * \param column Number of columns.
         * \param data Pointer to an array[] of doubles which will be recopied
         *             to initialize the object. Parameter is ignored if NULL.
         */
        wxEcMatrix(unsigned int line, unsigned column, double* data = NULL);
        wxEcMatrix();
        /** The default destructor.
         */
        ~wxEcMatrix();
        /** Frees the matrix, causing the memory to be freed.
         */
        void Destroy();
        /** Returns the matrix in a string. Ends of lines are composed with #10.
         */
        wxString DumpAsString();
        /** Duplicates the data obtained from an external matrix.
         * \param source The matrix from which data will be extracted.
         */
        void CopyFromMatrix(wxEcMatrix& source);

        /** Set the new dimensions of the matrix. This one will be filled with 0.
         * \param line New number of lines.
         * \param column New number of columns.
         * \warning If \a line or \a column is null, the dimension will be forced to 3x3.
         */
        void SetDimensionality(unsigned int line, unsigned column);
        /** Another way to change the size of the matrix.
         * \param size A size encoded as wxEcUPoint.
         */
        void SetDimensionality(wxEcUPoint size);
        /** Returns the current dimensions as wxEcUPoint.
         * \return \a X is the number of lines, Y is the number of columns.
         */
        wxEcUPoint GetDimensionality();
        /** Compares the dimensions of the current matrix with the ones of \a ref.
         * \return \a true if the dimensions are equal, else \a false.
         */
        bool IsSameDimensionality(wxEcMatrix* ref);
        /** Sets the value of a cell of the matrix.
         * \param line The line starting from 1.
         * \param column The column starting from 1.
         * \param value The value to store at the given coordinate.
         * \param checkboundaries If \a true, parameters will be checked against errors.
         */
        bool SetValue(unsigned int line, unsigned int column, double value, bool checkboundaries = true);
        /** Gets the value of a cell.
         * \param line The line starting from 1.
         * \param column The column starting from 1.
         * \param checkboundaries If \a true, parameters will be checked against errors.
         * \return The value as \a double, 0 if not found.
         */
        double GetValue(unsigned int line, unsigned int column, bool checkboundaries = true);
        /** Gets a pointer of the desired cell of the matrix.
         * \param line The line starting from 1.
         * \param column The column starting from 1.
         * \param checkboundaries By default, the boundaries are checked. For many functions will not do it, just for speed.
         * \return NULL if the coordinates are not correct, else the right pointer.
         * \remarks The next cell is not "pointer+1" but "pointer+sizeof(double)".
         */
        double* GetCellPointer(unsigned int line, unsigned int column, bool checkboundaries = true);
        /** Returns a pointer of the one-dimension array containing the data.
         *  The orientation is top->bottom and left->right.
         */
        inline double* GetData() { return m_data; }
        /** Copies values into the matrix from an external source of data.
         * \remarks The same amount of cells will be copied. Make sure your array
         *          is of the right dimension. Once done, you can destroy your array
         *          because no link will be established.
         */
        inline void SetData(double* source) { Copy(source, m_data, m_line*m_column); }
        /** Exchange two lines.
         * \param line1 The first line starting from 1.
         * \param line2 The second line starting from 1.
         * \return \a true on success, else \a false.
         */
        bool ExchangeLines(unsigned int line1, unsigned int line2);
        /** Exchange two columns.
         * \param column1 The first column starting from 1.
         * \param column2 The second column starting from 1.
         * \return \a true on success, else \a false.
         */
        bool ExchangeColumns(unsigned int column1, unsigned int column2);

        /** Fills the matrix with zeros (by default) or with the parameter.
         * \param defaultvalue New value of the cells.
         */
        void Clear(double defaultvalue = 0.0);
        /** Square matrix with ones on the main diagonal and zeros elsewhere.
         * \return \a true if the matrix is square, else \a false.
         */
        bool Identity();
        /** Sets the matrix as defined by Hadamard. The matrix is symetrical
         * \return \a true on success if the matrix is square, else \a false
         */
        bool Hadamard();
        /** Sets the matrix as defined by Hilbert. The matrix is symetrical.
         * \return \a true on success if the matrix is square, else \a false
         */
        bool Hilbert();
        /** A gaussian filter is a matrix obtained with the gaussian function.
         *  The result is symetrical.
         * \see http://en.wikipedia.org/wiki/Gaussian_blur
         * \param radius The dimension of the square matrix will be 2*radius+1.
         * \param sigma A deviation used for the calculation.
         * \return \a true if the matrix has been correctly initialized, else \a false.
         */
        bool GaussianFilter(unsigned char radius, double sigma);
        /** A laplacian of gaussian filter is related to GaussianFilter()
         *  and is implemented when processing images digitally.
         * \param radius The dimension of the square matrix will be 2*radius+1.
         * \param sigma A deviation used for the calculation.
         * \return \a true if the matrix has been correctly initialized, else \a false.
         */
        bool LaplacianOfGaussianFilter(unsigned char radius, double sigma);
        /** Transposes the matrix : lines and columns will be inverted.
         */
        void Transpose();
        /** Applies a factor to each cell of the matrix.
         * \param factor The factor used to adjust the values.
         */
        void Factor(double factor);
        /** Adds a constant to each cell of the matrix.
         * \param constant The value to add.
         */
        void AddConstant(double constant);
        /** Sums the values contained in the matrix.
         */
        double Sum();
        /** Replace a value by another one, applicable to the whole matrix.
         * \return The number of cells replaced.
         */
        unsigned int ReplaceValue(double oldvalue, double newvalue);
        /** Computes the determinant of the matrix. It must be square.
         * \return The determinant, or 0 if the matrix is not square.
         * \remarks This function allocates a lot of memory because of wxEcMatrix::SubMatrix.
         *          The function frees the memory, so be careful depending on how big the matrix is.
         */
        double Determinant();
        /** Gaussian elimination is an algotithm solving systems of linear equations.
         *  The last column of the matrix should be the result of each equation.
         *  The determinant of the system will be calculated : if equal to 0, the function
         *  will return false because there is an infinite amount of solutions.
         * \see http://en.wikipedia.org/wiki/Gaussian_elimination
         * \param solution A pointer to a matrix that will contain the result if not NULL.
         *                 This parameter cannot be \a this.
         * \return \a true on success, else \a false.
         * \see wxEcMatrix::Determinant()
         */
        bool GaussianElimination(wxEcMatrix* solution = NULL);
        /** Returns the submatrix of a matrix.
         * \param topline Position of the first line, starting from 1.
         * \param leftcolumn Position of the first column, starting from 1.
         * \param nbline Number of lines the submatrix will contain.
         * \param nbcolumn Number of columns the submatrix will contain.
         * \return The allocated submatrix given by its pointer.
         *         If the parameters are incorrect, the result will be NULL.
         * \warning You must free the result once you don't need it anymore.
         */
        wxEcMatrix* SubMatrix(unsigned int topline, unsigned int leftcolumn, unsigned int nbline, unsigned int nbcolumn);
        /** This function sticks a matrix to the right-hand size of the current matrix.
         *  Diagram : Join([A],[B]) --> [AB]. The number of lines must be equal.
         * \param matrix Matrix to stick.
         * \return \a true on success, \a false if the dimensions are not correct.
         * \see Operator <<
         */
        bool Join(wxEcMatrix& matrix);

        /** This function is equivalent to "matrix = filter * matrix" but is safer
         *  in the sense that no new wxEcMatrix is allocated. This function is useful
         *  when dealing with linear transformations. The current matrix will be edited.
         * \param matrix A pointer related to the filter to apply.
         */
        void ApplyMatrix(wxEcMatrix* matrix)
        {
            unsigned int i, j, k;
            wxEcUPoint sizeA;
            double value;

            sizeA = matrix->GetDimensionality();
            if (sizeA.y == m_line)
            {
                PushData();
                for (i=1 ; i<=m_line ; i++)
                    for (j=1 ; j<=m_column ; j++)
                    {
                        value = 0.0;
                        for (k=1 ; k<=sizeA.y ; k++)
                            value += matrix->GetValue(i,k) * GetValue(k,j);
                        m_databackup[(i-1)*m_column + (j-1)] = value;
                    }
                PopData();
            }
        }
        /** Convolution of two matrixes of the same size is a special multiplication, it returns a double.
         *  Currently, you can't convolve matrixes of different size.
         * \see http://en.wikipedia.org/wiki/Convolution
         * \param lefthandside Matrix used to convolve.
         * \return The result of the computation as a double.
         */
        double Convolve(wxEcMatrix* lefthandside)
        {
            unsigned int k;
            double result;
            wxEcUPoint sizeA;
            double *fromA;

            if (lefthandside == NULL)
                return 0.0;
            if (!IsSameDimensionality(lefthandside))
                return 0.0;

            result = 0.0;
            fromA = lefthandside->GetCellPointer(1, 1, false);
            for (k=0 ; k<m_line*m_column ; k++)
                result += fromA[k] * m_data[m_line*m_column-k-1];

            return result;
        }
        /** Sums two matrixes. If the dimensions are not the same, nothing will happen.
         * \remarks This operator is optimized for speed. No boundaries check is performed.
         */
        wxEcMatrix operator+(wxEcMatrix& mat)
        {
            unsigned int k;
            wxEcMatrix result;
            double *fromB, *toR;

            if (IsSameDimensionality(&mat))
            {
                result.SetDimensionality(m_line, m_column);
                fromB = mat.GetData();
                toR = result.GetData();
                for (k=0 ; k<m_line*m_column ; k++)
                    toR[k] = m_data[k] + fromB[k];
            }
            return result;
        }
        /** Substract two matrixes of the same dimensions. Else no operation will occur.
         * \remarks This operator is optimized for speed. No boundaries check is performed.
         */
        wxEcMatrix operator-(wxEcMatrix& mat)
        {
            unsigned int k;
            wxEcMatrix result;
            double *fromB, *toR;

            if (IsSameDimensionality(&mat))
            {
                result.SetDimensionality(m_line, m_column);
                fromB = mat.GetData();
                toR = result.GetData();
                for (k=0 ; k<m_line*m_column ; k++)
                    toR[k] = m_data[k] - fromB[k];
            }
            return result;
        }
        /** Multiply two matrixes and return an instancied result.
         *  The number of columns of the left one must be the number
         *  of lines of the right one. Else no operation will occur.
         * \remarks This operator is optimized for speed. No boundaries check is performed.
         */
        wxEcMatrix operator*(wxEcMatrix& mat)
        {
            unsigned int i, j, k;
            wxEcUPoint sizeB;
            wxEcMatrix result;
            double *fromB, *toR, value;

            sizeB = mat.GetDimensionality();
            if (m_column == sizeB.x)
            {
                result.SetDimensionality(sizeB.x, sizeB.y);
                fromB = mat.GetData();
                toR = result.GetData();
                for (i=1 ; i<=sizeB.x ; i++)
                    for (j=1 ; j<=sizeB.y ; j++)
                    {
                        value = 0.0;
                        for (k=1 ; k<=m_column ; k++)
                            value += m_data[(i-1)*m_column + (k-1)] * fromB[(k-1)*sizeB.y + (j-1)];
                        toR[(i-1)*sizeB.y + (j-1)] = value;
                    }
            }
            return result;
        }
        /** \see wxEcMatrix::Join()
         */
        void operator<<(wxEcMatrix& mat)
        {
            Join(mat);
        }
        /** Compares two matrixes.
         */
        bool operator==(wxEcMatrix& mat)
        {
            double *pA, *pB;
            unsigned int k;

            if (!IsSameDimensionality(&mat))
                return false;
            pA = m_data;
            pB = mat.GetData();
            for (k=0 ; k<m_line*m_column ; k++)
                if (pA[k] != pB[k])
                    return false;
            return true;
        }
        /** Compares two matrixes.
         */
        bool operator!=(wxEcMatrix& mat)
        {
            return !(*this == mat);
        }
};

#endif
