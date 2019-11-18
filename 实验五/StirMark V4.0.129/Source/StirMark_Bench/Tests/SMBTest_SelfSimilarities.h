 // SMBTest_SelfSimilarities.h: interface for the CSMBTest_SelfSimilarities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SMBTEST_SELFSIMILARITIES_H_)
#define     _SMBTEST_SELFSIMILARITIES_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//STL headers

// Other standard headers

// SMB headers
#include "../SignalProcessing/SMBSP_SelfSimilarities.h"
#include "SMBTestSP.h"



class CSMBTest_SelfSimilarities : public CSMBTestSP
{
public:
  CSMBTest_SelfSimilarities(TCString & in_cstrIniPath, CSMBBench * const in_pbenchInstance);
	virtual ~CSMBTest_SelfSimilarities();


protected:
  CSMBTest_SelfSimilarities();
  virtual CSMBTest  * Clone(void) const { return new CSMBTest_SelfSimilarities(*this); };

  virtual void InitTest(const CSMBImage &in_imgSource);


private:
   virtual void Setup();

  // Sets the parameters of the transform
  // TODO
  virtual void SetParameter(const CSMBImage & in_imgOriginal, double in_par);

  // This changes the image once the parameters of the 
  // transform are set
  virtual void DoTransform(const CSMBImage &  in_imgSource, 
                                 CSMBImage & out_imgAttacked);

  CSMBSP_SelfSimilarities m_ss;
  list<optionsCmd> m_lstoptionsSet;

  CSMBTest_SelfSimilarities & operator =(const CSMBTest_SelfSimilarities in_tst) {};

};

#endif // !defined(_SMBTEST_SELFSIMILARITIES_H_)
