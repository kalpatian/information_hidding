 // SMBMatrix.h: interface for the CSMBMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SMBMATRIX_H_)
#define _SMBMATRIX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// STL headers

// Other standard headers

// SMB headers
#include "../Base/StirMarkBenchmark.h"
#include "../Base/SMBPtrWrapper.h"


class CSMBMatrix 
{
  friend CSMBPtrWrapper<CSMBMatrix>;

public:
	CSMBMatrix(uint in_nCols, uint in_nRows);
  CSMBMatrix(const CSMBMatrix &  in_mat);
	virtual ~CSMBMatrix();

  CSMBMatrix & operator =(const CSMBMatrix in_mat);

  void   Set(uint in_i, uint in_j, double in_dMaskCoef);
  double Get(uint in_i, uint in_j) const;

  long Width()  const { return m_nCols; }
  long Height() const { return m_nRows; }
 

protected:
  CSMBMatrix* Clone(void) const;
  void Alloc(uint in_nRows, uint in_nCols);
  void Clear(void);

private:
	double **m_prgdMatrix;
  uint     m_nCols;
  uint     m_nRows;

  CSMBMatrix();
};

#endif // !defined(_SMBMATRIX_H_)
