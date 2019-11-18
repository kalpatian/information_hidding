//////////////////////////////////////////////////////////////////////
// StirMark Benchmark - SMBRandomNumberGenerator.cpp
//
// Contents: Implementation of the CSMBRandomNumberGenerator class
//
// Purpose:  See SMBRandomNumberGenerator.h
//
// Created:  Fabien A. P. Petitcolas, Microsoft Research, March 2000
//
// Modified: Frederic Raynal - Oct 2001 : 
//             unix advanced drand48() function is used, rather than rand()
//
// History:
//
// Copyright (c) 2000-2002, Microsoft Research Ltd , Institut National
// de Recherche en Informatique et Automatique (INRIA), Institut Eurécom
// and the Integrated Publication and Information Systems Institute at
// GMD - Forschungszentrum Informationstechnik GmbH (GMD-IPSI).
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted for non-commercial research and academic
// use only, provided that the following conditions are met:
// 
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer. Each
//   individual file must retain its own copyright notice.
// 
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions, the following disclaimer and the
//   list of contributors in the documentation and/or other materials
//   provided with the distribution.
// 
// - Modification of the program or portion of it is allowed provided
//   that the modified files carry prominent notices stating where and
//   when they have been changed. If you do modify this program you
//   should send to the contributors a general description of the changes
//   and send them a copy of your changes at their request. By sending
//   any changes to this program to the contributors, you are granting a
//   license on such changes under the same terms and conditions as
//   provided in this license agreement. However, the contributors are
//   under no obligation to accept your changes.
// 
// - All non-commercial advertising materials mentioning features or use
//   of this software must display the following acknowledgement:
// 
//     This product includes software developed by Microsoft Research
//     Ltd, Institut National de Recherche en Informatique et Automatique
//     (INRIA), Institut Eurécom and the Integrated Publication and
//     Information Systems Institute at GMD - Forschungszentrum
//     Informationstechnik GmbH (GMD-IPSI).
// 
// - Neither name of Microsoft Research Ltd, INRIA, Eurécom and GMD-IPSI
//   nor the names of their contributors may be used to endorse or
//   promote products derived from this software without specific prior
//   written permission.
// 
// - If you use StirMark Benchmark for your research, please cite:
// 
//     Fabien A. P. Petitcolas, Martin Steinebach, Frédéric Raynal, Jana
//     Dittmann, Caroline Fontaine, Nazim Fatès. A public automated
//     web-based evaluation service for watermarking schemes: StirMark
//     Benchmark. In Ping Wah Wong and Edward J. Delp, editors,
//     proceedings of electronic imaging, security and watermarking of
//     multimedia contents III, vol. 4314, San Jose, California, U.S.A.,
//     20-26 January 2001. The Society for imaging science and
//     technology (I.S.&T.) and the international Society for optical
//     engineering (SPIE). ISSN 0277-786X.
// 
// and
// 
//     Fabien A. P. Petitcolas. Watermarking schemes
//     evaluation. I.E.E.E. Signal Processing, vol. 17, no. 5,
//     pp. 58-64, September 2000.
// 
// THIS SOFTWARE IS NOT INTENDED FOR ANY COMMERCIAL APPLICATION AND IS
// PROVIDED BY MICROSOFT RESEARCH LTD, INRIA, EURÉCOM, GMD-IPSI AND
// CONTRIBUTORS 'AS IS', WITH ALL FAULTS AND ANY EXPRESS OR IMPLIED
// REPRESENTATIONS OR WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE, TITLE OR NONINFRINGEMENT OF INTELLECTUAL
// PROPERTY ARE DISCLAIMED. IN NO EVENT SHALL MICROSOFT RESEARCH LTD,
// INRIA, EURÉCOM, GMD-IPSI OR THEIR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
// IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// THE USE OF THIS SOFTWARE FOR CIRCUMVENTING WITHOUT AUTHORITY ANY
// EFFECTIVE TECHNOLOGICAL MEASURES DESIGNED TO PROTECT ANY COPYRIGHTS OR
// ANY RIGHTS RELATED TO COPYRIGHT AS PROVIDED BY LAW OR THE SUI GENERIS
// RIGHT PROVIDED BY SOME COUNTRIES IS STRICTLY PROHIBITED.
//
// $Header: /home/cvs/StirmarkBench/StirMark_Bench/Base/SMBRandomNumberGenerator.cpp,v 1.15 2002/04/19 10:23:55 petitcolas Exp $
//////////////////////////////////////////////////////////////////////



// STL headers

// Other standard headers
#include <time.h>
#include <stdlib.h>
#include <assert.h>

// SMB Headers
#include "SMBRandomNumberGenerator.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMBRandomNumberGenerator::CSMBRandomNumberGenerator(unsigned in_uSeed /* = 0 */)
{
  SetSeed(in_uSeed);
}


CSMBRandomNumberGenerator::~CSMBRandomNumberGenerator()
{

}


//////////////////////////////////////////////////////////////////////
// Set the seed of the random number generator. If in_uSeed is null
// the default seed (the current time in this implementation) is used

void CSMBRandomNumberGenerator::SetSeed(unsigned in_uSeed)
{
#ifdef WIN32
  if (in_uSeed)
    srand(in_uSeed);
  else
    srand((unsigned) (time(NULL)));
#endif

#ifdef __UNIX__
  if (in_uSeed)
    srand48(in_uSeed);
  else {
    time_t seed; /* Initial value used for random function. Generated 
		    with time() function.*/
    time(&seed);
    srand48(seed);
  }
#endif
}


void CSMBRandomNumberGenerator::SetRange(double in_min, double in_max)
{
  assert(in_min <= in_max);

  if (in_max < in_min)
  {
    m_dRangeMin = in_max;
    m_dRangeMax = in_min;
  }
  else
  {
    m_dRangeMin  = in_min;
    m_dRangeMax  = in_max;
  }
  m_dRangeSpan = m_dRangeMax - m_dRangeMin;
}


int CSMBRandomNumberGenerator::GetInt(void) const
{

#ifdef WIN32
  // TODO: There are certainly better ones...
  // TODO: Does not work if several are used at the same time...
  return rand();
#endif
#ifdef __UNIX__
  return (int)(drand48() * RAND_MAX);
#endif
}


double CSMBRandomNumberGenerator::GetDouble(void) const
{
#ifdef WIN32
  // TODO: There are certainly better ones...
  // TODO: Does not work if several are used at the same time...
  return ((double)rand() / RAND_MAX) * 2.0 - 1.0;
#endif
#ifdef __UNIX__
  return drand48();
#endif
}


double CSMBRandomNumberGenerator::GetDoubleInRange(void) const
{
  // TODO: Does not work if several are used at the same time...
  return (m_dRangeSpan * GetDouble() + m_dRangeMin);
}


//////////////////////////////////////////////////////////////////////

void CSMBRandomNumberGenerator::FillBuffer(char * inout_pchBuffer,
                                           long      in_cchBufferLength)
{
#ifdef WIN32
  SetRange(0, 255);

  for(long i = 0; i < in_cchBufferLength; i++)
    inout_pchBuffer[i] = (char)GetDoubleInRange();
#endif /* WIN32 */

#ifdef __UNIX__
  for(long i = 0; i < in_cchBufferLength; i++)
    inout_pchBuffer[i] = (char)(drand48() * 255);
#endif /* __UNIX__ */ 
}

