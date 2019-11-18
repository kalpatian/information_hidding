// SMBTest_SelfSimilarities.cpp: implementation of the CSMBTest_SelfSimilarities class.
//
//////////////////////////////////////////////////////////////////////

// STL headers

// Other standard headers
#include <assert.h>

// SMB headers
#include "SMBTest_SelfSimilarities.h"
#include "../Base/SMBImage.h"
#include "../Base/SMBTools.h"
#include "../Base/SMBError.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBTest_SelfSimilarities::CSMBTest_SelfSimilarities()
: CSMBTestSP()
{
  Setup();
}


CSMBTest_SelfSimilarities::CSMBTest_SelfSimilarities(TCString & in_cstrIniPath, CSMBBench * const in_pbenchInstance)
  : CSMBTestSP(in_cstrIniPath, in_pbenchInstance)
{
  Setup();
}


CSMBTest_SelfSimilarities::~CSMBTest_SelfSimilarities()
{

}


void CSMBTest_SelfSimilarities::Setup()
{
  m_strTestName = "Test_SelfSimilarities";
  m_strTestTag  = "SS";
}



//////////////////////////////////////////////////////////////////////

void CSMBTest_SelfSimilarities::InitTest(const CSMBImage &in_imgSource)
{
  list<TString> lststrValues;

  optionsCmd option;

  int n = 1;
  int count;

  // Parameter set looks like: set1=hsv 001 s 60

  while ( (count = ParseProfileListString(m_strTestName,
					TString("set") + CSMBString(n),
					m_strIniFilePath,
					lststrValues)) )
  {
    assert(count >= 3);

    // Determines colour space
    if (lststrValues.front() == "rgb")
			option.colorSpace = SS_RGB;
		else if (lststrValues.front() == "yuv")
			option.colorSpace = SS_YUV;
		else if (lststrValues.front() == "hsv")
			option.colorSpace = SS_HSV;
		else if (lststrValues.front() == "lab")
			option.colorSpace = SS_LAB;
		else if (lststrValues.front() == "xyz")
			option.colorSpace = SS_XYZ;
		else
    {
      SMBWarning(TString("[CSMBTest_SelfSimilarities::InitTest] - Invalid colour space in parameter set ") + n);
      continue;
    }
    lststrValues.pop_front();
    
    // Determines the channel to be attacked
    if (lststrValues.front().length() != 3)
    {
      SMBWarning(TString("[CSMBTest_SelfSimilarities::InitTest] - Invalid attack mask in parameter set ") + n);
      continue;
    }
    option.c1_flag = lststrValues.front().c_str()[0] == '1' ? SS_ATTACK : SS_NO_ATTACK;
    option.c2_flag = lststrValues.front().c_str()[1] == '1' ? SS_ATTACK : SS_NO_ATTACK;
    option.c3_flag = lststrValues.front().c_str()[2] == '1' ? SS_ATTACK : SS_NO_ATTACK;
    lststrValues.pop_front();

    // Determines attack type
    if (lststrValues.front() == "x")
      // Exchange the colour channel of original and watermarked image
		  option.type = SS_SWITCH;
	  else if (lststrValues.front() == "s")
		  // Dewatermarking by swappping in the spatial domain
		  option.type = SS_SPATIAL;
    else if (lststrValues.front() == "h")
    {
		  // Dewatermarking by swappping in the wavelet domain
      SMBWarning(TString("[CSMBTest_SelfSimilarities::InitTest] - Attack in wavelet domain not supported ") + n);
      //option.type = SS_WAVELET;
      continue;
    }
    else
    {
      SMBWarning(TString("[CSMBTest_SelfSimilarities::InitTest] - Invalid attack type in parameter set ") + n);
      continue;
    }
    lststrValues.pop_front();

    // Some attacks require a percentage argument
    if (option.type != SS_SWITCH)
    {
      if (count != 4)
      {
        SMBWarning(TString("[CSMBTest_SelfSimilarities::InitTest] - Percentage missing in parameter set ") + n);
        continue;
      }
      option.percent = atoi(lststrValues.front());
		  if (option.percent > 100 || option.percent < 0)
      {
        SMBWarning(TString("[CSMBTest_SelfSimilarities::InitTest] - Percentage invalid in parameter set ") + n);
        continue;
      }
    }

    m_lstoptionsSet.push_back(option);
    m_lstdpValueSet.push_back(n++);
  }
}



//////////////////////////////////////////////////////////////////////
// Main functions
//////////////////////////////////////////////////////////////////////

void CSMBTest_SelfSimilarities::SetParameter(const CSMBImage &in_imgOriginal, double in_par)
{
  int n = 1;
  list<optionsCmd>::iterator optionsSet = m_lstoptionsSet.begin();
  while (n++ < in_par) optionsSet++;

  m_ss.SetParameter((optionsCmd) *optionsSet);
};
  
void CSMBTest_SelfSimilarities::DoTransform(const CSMBImage  &in_imgSource, 
                                                  CSMBImage &out_imgAttacked)
{
  m_ss(in_imgSource, out_imgAttacked);
}
