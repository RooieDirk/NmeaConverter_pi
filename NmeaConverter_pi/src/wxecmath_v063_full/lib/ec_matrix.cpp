
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

#include "ec_matrix.h"

//------------------------------------------

wxEcMatrix::wxEcMatrix(unsigned int line, unsigned column, double* data)
{
    m_data = (double*) malloc(1*sizeof(double));
    m_databackup = (double*) malloc(1*sizeof(double));
    SetDimensionality(line, column);
    Clear();
    if (data != NULL)
        Copy(data, m_data, line*column);
}

wxEcMatrix::wxEcMatrix()
{
    wxEcMatrix(3, 3, NULL);
}

wxEcMatrix::~wxEcMatrix()
{
    Destroy();
}

void wxEcMatrix::Destroy()
{
    wxDELETE(m_databackup);
    wxDELETE(m_data);
    m_line = 0;
    m_column = 0;
}

wxString wxEcMatrix::DumpAsString()
{
    wxString result;
    unsigned int i, j, counter=0;

    result.Empty();
    for (i=0 ; i<m_line ; i++)
    {
        result.Append(wxT("| "));
        for (j=0 ; j<m_column ; j++)
            result.Append(wxString::Format(wxT("%.5f "), m_data[counter++]));
        result.Append(wxT("|"));
        if (i < m_line-1)
            result.Append(wxT("\n"));
    }
    return result;
}

void wxEcMatrix::Copy(double *source, double *destination, unsigned int count)
{
    unsigned int i;
    for (i=0 ; i<count ; i++)
        destination[i] = source[i];
}

void wxEcMatrix::CopyFromMatrix(wxEcMatrix& source)
{
    SetDimensionality(source.GetDimensionality());
    Copy(source.GetData(), m_data, m_line*m_column);
}

//------------------------------------------

void wxEcMatrix::SetDimensionality(wxEcUPoint size)
{
    SetDimensionality(size.x, size.y);
}

void wxEcMatrix::SetDimensionality(unsigned int line, unsigned column)
{
    unsigned int i;

    //-- Saves the dimensions
    if ((line == 0) || (column == 0))
    {
        line = 3;
        column = 3;
    }

    //-- Reallocates memory if needed
    if ((m_line != line) || (m_column != column))
    {
        wxDELETE(m_data);           
        m_data = (double*) malloc(line*column*sizeof(double));
        wxDELETE(m_databackup);     
        m_databackup = (double*) malloc(line*column*sizeof(double));
    }

    //-- Initialization
    m_line = line;
    m_column = column;
    for (i=0 ; i<m_line*m_column ; i++)
        m_data[i] = 0.0;
}

wxEcUPoint wxEcMatrix::GetDimensionality()
{
    return wxEcUPoint(m_line, m_column);
}

bool wxEcMatrix::IsSameDimensionality(wxEcMatrix* ref)
{
    if (ref == NULL)
        return false;
    else
        return (GetDimensionality() == ref->GetDimensionality());
}

bool wxEcMatrix::SetValue(unsigned int line, unsigned int column, double value, bool checkboundaries)
{
    double *pointer = GetCellPointer(line, column, checkboundaries);
    if (pointer != NULL)
    {
        *pointer = value;
        return true;
    }
    else
        return false;
}

double wxEcMatrix::GetValue(unsigned int line, unsigned int column, bool checkboundaries)
{
    double *pointer = GetCellPointer(line, column, checkboundaries);
    return (pointer == NULL ? 0.0 : *pointer);
}

double* wxEcMatrix::GetCellPointer(unsigned int line, unsigned int column, bool checkboundaries)
{
    if (!checkboundaries)
        return m_data + (line-1)*m_column + (column-1);
    else
        if (wxEcBetween(line,1,m_line) && wxEcBetween(column,1,m_column))
            return m_data + (line-1)*m_column + (column-1);
        else
            return NULL;
}

bool wxEcMatrix::ExchangeLines(unsigned int line1, unsigned int line2)
{
    double *from, *to, tmp;
    unsigned int k;

    from = GetCellPointer(line1, 1);
    to = GetCellPointer(line2, 1);
    if ((from == 0) || (to == 0))
        return false;

    for (k=0 ; k<m_column ; k++)
    {
        tmp = from[k];
        from[k] = to[k];
        to[k] = tmp;
    }
    return true;
}

bool wxEcMatrix::ExchangeColumns(unsigned int column1, unsigned int column2)
{
    double *from, *to, tmp;
    unsigned int k;

    if (!wxEcBetween(column1,1,m_column) || !wxEcBetween(column2,1,m_column))
        return false;

    for (k=0 ; k<m_line ; k++)
    {
        from = GetCellPointer(k+1, column1);
        to = GetCellPointer(k+1, column2);

        tmp = *from;
        *from = *to;
        *to = tmp;
    }
    return true;
}

//------------------------------------------

void wxEcMatrix::Clear(double defaultvalue)
{
    unsigned int k;
    for (k=0 ; k<m_line*m_column ; k++)
        m_data[k] = defaultvalue;
}

bool wxEcMatrix::Identity()
{
    unsigned int i, j, counter=0;
    if (m_line != m_column)
        return false;

    //-- Sets the diagonal
    for (i=0 ; i<m_line ; i++)
        for (j=0 ; j<m_column ; j++)
            m_data[counter++] = (i==j ? 1 : 0);
    return true;
}

bool wxEcMatrix::Hadamard()
{
    unsigned int k;
    if (m_line != m_column)
        return false;
    else
    {
        Clear(1.0);
        if (m_column > 1)
            for (k=2 ; k<=m_column ; k++)
            {
                SetValue(k, k, -1, false);
                SetValue(m_line, k, -1, false);
                SetValue(k, m_column, -1, false);
            }
        return true;
    }
}

bool wxEcMatrix::Hilbert()
{
    unsigned int i, j;
    if (m_line != m_column)
        return false;
    else
    {
        for (i=1 ; i<=m_line ; i++)
            for (j=1 ; j<=m_column ; j++)
                SetValue(i, j, 1.0/((double)i+(double)j-1.0), false);
        return true;
    }
}

bool wxEcMatrix::GaussianFilter(unsigned char radius, double sigma)
{
    int px, py;
    if ((sigma == 0.0) || (radius == 0))
        return false;
    SetDimensionality(2*radius+1, 2*radius+1);
    for (px=-radius ; px<=radius ; px++)
        for (py=-radius ; py<=radius ; py++)
            SetValue(radius+1+px, radius+1+py, exp(-(px*px+py*py)/(2*sigma*sigma))/(2*M_PI*sigma*sigma), false);
    return true;
}

bool wxEcMatrix::LaplacianOfGaussianFilter(unsigned char radius, double sigma)
{
    int px, py;
    if ((sigma == 0.0) || (radius == 0))
        return false;
    SetDimensionality(2*radius+1, 2*radius+1);
    for (px=-radius ; px<=radius ; px++)
        for (py=-radius ; py<=radius ; py++)
            SetValue(radius+1+px, radius+1+py, -(1-(px*px+py*py)/(2*sigma*sigma))*exp(-(px*px+py*py)/(2*sigma*sigma))/(M_PI*sigma*sigma*sigma*sigma), false);
    return true;
}

void wxEcMatrix::Transpose()
{
    unsigned int i, j, counter=0, tmp, index;

    //-- Transposes data
    for (j=1 ; j<=m_column ; j++)
    {
        index = j-1;
        for (i=1 ; i<=m_line ; i++)
        {
            m_databackup[counter++] = m_data[index];
            index += m_column;
        }
    }
    PopData();

    //-- Switches the new dimensions
    tmp = m_line;
    m_line = m_column;
    m_column = tmp;
}

void wxEcMatrix::Factor(double factor)
{
    unsigned int k;
    for (k=0 ; k<m_line*m_column ; k++)
        m_data[k] *= factor;
}

void wxEcMatrix::AddConstant(double constant)
{
    unsigned int k;
    for (k=0 ; k<m_line*m_column ; k++)
        m_data[k] += constant;
}

double wxEcMatrix::Sum()
{
    unsigned int k;
    double result=0;
    for (k=0 ; k<m_line*m_column ; k++)
        result += m_data[k];
    return result;
}

unsigned int wxEcMatrix::ReplaceValue(double oldvalue, double newvalue)
{
    unsigned int k, counter = 0;
    for (k=0 ; k<m_line*m_column ; k++)
        if (m_data[k] == oldvalue)
        {
            m_data[k] = newvalue;
            counter++;
        }
    return counter;
}

    double wxEcMatrix::RecurseDeterminant(wxEcMatrix* matrix, bool root)
    {
        wxEcUPoint size;
        wxEcMatrix *subLeft = NULL, *subRight = NULL;
        double *pointer = NULL, result;
        unsigned int i;
        char xsign = 1;

        //-- Computes known determinants
        size = matrix->GetDimensionality();
        if (size.x != size.y)
            return 0.0;
        pointer = matrix->GetData();
        if (size.x == 1)
        {
            result = pointer[0];
            if (!root)
                wxDELETE(matrix);
            return result;
        }
        if (size.x == 2)
        {
            result = pointer[0]*pointer[3] - pointer[2]*pointer[1];
            if (!root)
                wxDELETE(matrix);
            return result;
        }

        //-- Generic formula for NxN matrixes
        result = 0.0;
        xsign = 1;
        for (i=1 ; i<=size.y ; i++)
        {
            if (i == 1)
                result += xsign * pointer[i-1] * RecurseDeterminant(matrix->SubMatrix(2, 2, size.x-1, size.y-1));
            else
                if (i == size.y)
                    result += xsign * pointer[i-1] * RecurseDeterminant(matrix->SubMatrix(2, 1, size.x-1, size.y-1));
                else
                {
                    subLeft = matrix->SubMatrix(2, 1, size.x-1, i-1);
                    subRight = matrix->SubMatrix(2, i+1, size.x-1, size.y-i);
                    subLeft->Join(*subRight);
                    wxDELETE(subRight);
                    result += xsign * pointer[i-1] * RecurseDeterminant(subLeft);
                    //wxDELETE(subLeft);
                }
            xsign = -xsign;
        }
        if (!root)
            wxDELETE(matrix);
        return result;
    }

double wxEcMatrix::Determinant()
{
    return RecurseDeterminant(this, true);
}

bool wxEcMatrix::GaussianElimination(wxEcMatrix* solution)
{
    unsigned int cursor, kline, kcolumn;
    double m, *p;
    wxEcMatrix *sub = NULL;

    //-- Checks the dimensions
    if (m_line+1 != m_column)
        return false;

    //-- Does a solution exists ?
    sub = SubMatrix(1, 1, m_line, m_line);
    m = sub->Determinant();
    wxDELETE(sub);
    if (m == 0.0)
        return false;

    //-- Downward
    for (cursor=1 ; cursor<=m_line ; cursor++)
    {
        //-- Pivot must be 1
        m = GetValue(cursor, cursor, false);
        if (m != 1.0)
            for (kcolumn=cursor ; kcolumn<=m_column ; kcolumn++)
                SetValue(cursor, kcolumn, GetValue(cursor,kcolumn)/m);

        //-- Then, we change the other lines
        if (cursor != m_line)
            for (kline=1 ; kline<=m_line ; kline++)
                if (kline != cursor)
                {
                    m = - GetValue(kline, cursor, false) / GetValue(cursor, cursor, false);
                    for (kcolumn=cursor ; kcolumn<=m_column ; kcolumn++)
                        SetValue(kline, kcolumn, GetValue(kline, kcolumn, false) + m*GetValue(cursor, kcolumn, false), false);
                }
        //DEBUG: wxMessageDialog(NULL, wxT("Step:\n")+DumpAsString()).ShowModal();
    }

    //-- Upward
    for (cursor=m_line ; cursor>=1 ; cursor--)
        for (kline=1 ; kline<cursor ; kline++)
        {
            m = - GetValue(kline, cursor, false) / GetValue(cursor, cursor, false);
            for (kcolumn=1 ; kcolumn<=m_column ; kcolumn++)
                SetValue(kline, kcolumn, GetValue(kline, kcolumn, false) + m*GetValue(cursor, kcolumn, false), false);
        }

    //-- Returns the answer
    if ((solution != NULL) && (solution != this))
    {
        solution->SetDimensionality(m_line, 1);
        p = solution->GetData();
        for (kline=1 ; kline<=m_line ; kline++)
            p[kline-1] = GetValue(kline, m_column, false);
    }

    return true;
}

wxEcMatrix* wxEcMatrix::SubMatrix(unsigned int topline, unsigned int leftcolumn, unsigned int nbline, unsigned int nbcolumn)
{
    unsigned int i, j;
    wxEcMatrix *result;

    //-- Verification
    if ( !wxEcBetween(topline, 1, m_line)      || !wxEcBetween(topline+nbline-1, 1, m_line)        ||
         !wxEcBetween(leftcolumn, 1, m_column) || !wxEcBetween(leftcolumn+nbcolumn-1, 1, m_column)
    )
        return NULL;

    //-- Submatrix
    result = new wxEcMatrix(nbline, nbcolumn);
        for (i=1 ; i<=nbline ; i++)
            for (j=1 ; j<=nbcolumn ; j++)
                result->SetValue(i, j, GetValue(topline+i-1, leftcolumn+j-1, false), false);
    return result;
}

bool wxEcMatrix::Join(wxEcMatrix& matrix)
{
    wxEcUPoint size;
    double *fromA, *fromB, *result = NULL;
    unsigned int i, j, counter;

    //-- Checks
    size = matrix.GetDimensionality();
    if (m_line != size.x)
        return false;

    //-- Initialization
    fromA = m_data;
    fromB = matrix.GetData();
    counter = 0;

    //-- Action !
    result = (double*) malloc(m_line*(m_column+size.y)*sizeof(double));
        for (i=0 ; i<m_line ; i++)
        {
            //- Copy
            for (j=0 ; j<m_column ; j++)
                result[counter++] = fromA[j];
            for (j=0 ; j<size.y ; j++)
                result[counter++] = fromB[j];
            //- Next line
            fromA += m_column;
            fromB += size.y;
        }
        //- Stores the result
        SetDimensionality(m_line, m_column+size.y);
        Copy(result, m_data, m_line*(m_column+size.y));
    free(result);
    return true;
}
