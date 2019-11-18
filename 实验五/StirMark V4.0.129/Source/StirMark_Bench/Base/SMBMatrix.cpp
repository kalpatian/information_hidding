// SMBMatrix.cpp: implementation of the CSMBMatrix class.
//
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers
#include <assert.h>

// SMB headers
#include "SMBMatrix.h"
#include "SMBException.h"
#include "SMBTools.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBMatrix::CSMBMatrix(uint in_nRows, uint in_nCols)
  : m_prgdMatrix(0)
{
  Alloc(in_nRows, in_nCols);
}


CSMBMatrix::~CSMBMatrix()
{
  Clear();
}


void CSMBMatrix::Clear()
{
  if (m_prgdMatrix != 0)
  {
    for (uint i = 0; i < m_nRows; i++)
    {
      delete m_prgdMatrix[i];
    }
    delete m_prgdMatrix;
  }
  m_prgdMatrix = 0;
  m_nCols = 0;
  m_nRows = 0;
}


void CSMBMatrix::Alloc(uint in_nRows, uint in_nCols)
{
  Clear();
  
  m_nRows = in_nRows;
  m_nCols = in_nCols;
  
  // TODO: handle memory allocation error
  m_prgdMatrix = new double*[m_nRows];
  for (uint i = 0; i < m_nRows; i++)
  {
    m_prgdMatrix[i] = new double[m_nCols];
  }
}


void CSMBMatrix::Set(uint in_i, uint in_j, double in_dMaskCoef)
{
  if ((in_i < 0) || (in_i >= m_nRows) || 
      (in_j < 0) || (in_j >= m_nCols))
    SMBThrowNewException("[CSMBMatrix::SetFilter] - Filter coefficient outstide the filter matrix.");

  m_prgdMatrix[in_i][in_j] = in_dMaskCoef;
}

double CSMBMatrix::Get(uint in_i, uint in_j) const
{
  if ((in_i < 0) || (in_i >= m_nRows) || 
      (in_j < 0) || (in_j >= m_nCols))
    SMBThrowNewException("[CSMBMatrix::GetFilter] - Filter coefficient outstide the filter matrix.");

  return m_prgdMatrix[in_i][in_j];
}

CSMBMatrix* CSMBMatrix::Clone(void) const
{
  CSMBMatrix* pfm = new CSMBMatrix(m_nRows, m_nCols);
  assert(pfm != NULL);

  for (uint i = 0; i < m_nRows; i++)
    for (uint j = 0; j < m_nCols; j++)
      pfm->Set(i, j, m_prgdMatrix[i][j]);
  return pfm;
}

CSMBMatrix & CSMBMatrix::operator =(const CSMBMatrix in_mat)
{
  Alloc(in_mat.m_nRows, in_mat.m_nCols);
  for (uint i = 0; i < m_nRows; i++)
    for (uint j = 0; j < m_nCols; j++)
      Set(i, j, in_mat.Get(i, j));
  return *this;
}

CSMBMatrix::CSMBMatrix(const CSMBMatrix &in_mat)
: m_prgdMatrix(0)
{
  Alloc(in_mat.m_nRows, in_mat.m_nCols);
  for (uint i = 0; i < m_nRows; i++)
    for (uint j = 0; j < m_nCols; j++)
      Set(i, j, in_mat.Get(i, j));
}
