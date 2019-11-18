/*--------------------------------------------------------------------*
 *    FELT.C  -  Fast Extended Lapped Transform                       *
 *                                                                    *
 *    Algorithm: as described in  Section 5.4.  The MLT can also be   *
 *    computed with this module, by setting k = 1.                    *
 *                                                                    *
 *    This is an orthogonal transform.  All basis functions have      *
 *    unity energy.                                                   *
 *                                                                    *
 *    Author:  Henrique S. Malvar.                                    *
 *    Date:    October 8, 1991.                                       *
 *                                                                    *
 *    Usage:   felt(x, k, logm);   -- direct transform                *
 *             fielt(x, k, logm);  -- inverse transform               *
 *                                                                    *
 *    Arguments:  x (float)   - input and output vector, length M.    *
 *                k (int)     - overlapping factor.                   *
 *                logm (int)  - log (base 2) of vector length M,      *
 *                              e.g., for M = 256 -> logm = 8.        *
 *                                                                    *
 *    Note: this is a causal version.  Thus, there is a delay of      *
 *    (2 * k - 1) M / 2 samples in either felt or fielt.              *
 *    Following a call to felt with a call to fielt will recover      *
 *    the original signal with a total delay of (2 * k - 1) blocks.   *
 *                                                                    *
 *--------------- Structure of the table of cosines ------------------*
 *                                                                    *
 *    tab[k-1][logm-1] : is a pointer to the beginning of the         *
 *    table.  For a given overlapping factor k, and number of         *
 *    subbands M = 2^logm, there are k stages of butterflies          *
 *    (D_0 to D_k-1).  Each stage has m/2 butterflies, and each       *
 *    butterfly is of the form:                                       *
 *                                                                    *
 *                  -c                                                *
 *           x_1  -------  x_1  <--  -c * x_1 + s * x_2               *
 *                 \   /s                                             *
 *                   X            c = cos(ang), s = sin(ang)          *
 *                 /   \s                                             *
 *           x_2  -------  x_2  <--   s * x_1 + c * x_2               *
 *                   c                                                *
 *                                                                    *
 *    Each butterfly can be computed with three multiplies and        *
 *    three adds, in the form                                         *
 *                                                                    *
 *                 -(s+c)                                             *
 *           x_1  --------- x_1                                       *
 *                \   s   /                                           *
 *                 -------                                            *
 *                /  c-s  \                                           *
 *           x_2  --------- x_2                                       *
 *                                                                    *
 *    Thus, for each butterfly, we need three table entries, for:     *
 *    -(s+c), s, and (c-s).  Because there are M/2 butterflies per    *
 *    stage, tab[k-1][logm-1] points to 3 * k * M/2 elements,         *
 *    arranged in the form: the M/2 values of s [sin(ang)] for the    *
 *    M/2 butterflies of D_0, starting at the outermost butterfly;    *
 *    then, the M/2 corresponding values of -(s+c), and the M/2       *
 *    corresponding values of (c-s).  Then, the M/2 values of s for   *
 *    D_1, and so on.  The last M/2 elements are the (c-s) values     *
 *    for D_k-1.                                                      *
 *                                                                    *
 *--------- Structure of the buffers for the delay elements ----------*
 *                                                                    *
 *    After each butterfly in the direct ELT, M/2 elements must go    *
 *    through a delay of z^-2, i.e., a delay of two blocks.  After    *
 *    the last stage, the delay is only z^-1.  Thus, for each stage   *
 *    but the last we need 2 * M/2 storage locations, and M/2         *
 *    locations for the last stage.  We need also M/2 temporary       *
 *    storage locations due to the swapping of the top and bottom     *
 *    halves of the vector just before the DCT-IV.                    *
 *    Therefore, we need k * M locations, and that is the size of the *
 *    area pointed by yt[k-1][logm-1].  The first M locations are     *
 *    for the z^-2 delay after D_k-1, the next M locations are for    *
 *    the z^-2 delay after D_k-2, and so on.  The last M locations    *
 *    have two purposes: the top M/2 locations are for the z^-1       *
 *    delay after D_0, and the bottom M/2 locations are for temporary *
 *    storage, pointed by wk.                                         *
 *                                                                    *
 *--------------------------------------------------------------------*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
 
#define  MAXLOGM     12    /* max ELT block size = 2^MAXLOGM */
#define  MAXK        4     /* max overlapping factor */
#define  PI          3.14159265358979323846
 
void  fdctiv(float *, int);   /* fdctiv prototype */
 
/*--------------------------------------------------------------------*
 *    Error exit for program abortion.                                *
 *--------------------------------------------------------------------*/
 
static   void  error_exit(void)
{
   exit(1);
}
 
/*--------------------------------------------------------------------*
 *    Module to read tables of butterfly coefficients                 *
 *--------------------------------------------------------------------*/
 
static   float    *tab[MAXK][MAXLOGM];
#define  NCHARS   80
 
static   void  read_table(int k, int logm)
{
   int      n, m, m2, nel, gr;
   float    ang, co, si, *s, *spc, *cms;
   FILE     *af;
   char     txt[NCHARS], *tp;
 
   /* Define m */
   m = 1 << logm;
   m2 = m / 2;
 
   nel = 3 * k * m2;
   if ((tab[k-1][logm-1] = (float *) calloc(nel, sizeof(float))) == NULL) {
      printf("Error : FELT : not enough memory for butterfly coeffs.\n");
      error_exit();
   }
 
   /* Read angles into first m/2 elements of each group of 3*m/2
      elements, corresponding to each D_k */
   if ((af = fopen("angelt.txt", "r")) == NULL) {
      printf("Error : FELT : could not open file angelt.txt\n");
      error_exit();
   }
 
   /* Skip lines until the first line for the given  m  &  k */
   nel = 2 * m + 3 * logm + (k - 1) * m2;
   for (n = 1; n < nel; n++) {
      if (fgets(txt, NCHARS-1, af) == NULL) {
         printf("Error : FELT : error reading file angelt.txt\n");
         error_exit();
      }
   }
 
   /* Read angles */
   for (n = 0; n < m2; n++) {
      if (fgets(txt, NCHARS-1, af) == NULL) {
         printf("Error : FELT : error reading file angelt.txt\n");
         error_exit();
      }
      tp = strtok(txt, " ");
      s = tab[k-1][logm-1] + n;
      for (gr = 0; gr < k; gr++) {
         *s = atof(tp);
         tp = strtok(NULL, " ");
         s += 3 * m2;
      }
   }
   fclose(af);
 
   /* Compute sines and cosines */
   s = tab[k-1][logm-1]; spc = s + m2; cms = spc + m2;
   for (gr = 0; gr < k; gr++) {
 
      /* Compute tables */
      for (n = 0; n < m2; n++) {
         ang = *s * PI;
         co = cos(ang); si = sin(ang);
         *s++ = si; *spc++ = - (si + co); *cms++ = co - si;
      }
      s += m; spc += m; cms += m;
   }
}
 
/*--------------------------------------------------------------------*
 *    Direct ELT                                                      *
 *--------------------------------------------------------------------*/
 
void felt(float *x, int k, int logm)
{
   int      n, m, m2, nel, gr;
   float    tmp, *xp1, *xp2, *op1, *y, *yp, *wk;
   float    *s, *spc, *cms;
   static   float   *yt[MAXK][MAXLOGM];
 
   /* Check range of logm */
   if ((logm < 1) || (logm > MAXLOGM)) {
      printf("Error : FELT : logm = %d is out of bounds [%d, %d]\n",
         logm, 1, MAXLOGM);
      error_exit();
   }
 
   /* Check range of k */
   if ((k < 1) || (k > MAXK)) {
      printf("Error : FELT : k = %d is out of bounds [%d, %d]\n",
         k, 1, MAXK);
      error_exit();
   }
 
   /* Define m */
   m = 1 << logm;
   m2 = m / 2;
 
   /* Compute table of butterfly coefficients, if necessary */
   if (tab[k-1][logm-1] == NULL) read_table(k, logm);
 
   /* Allocate space for working vector, if necessary */
   if (yt[k-1][logm-1] == NULL) {
      nel = k * m;
      if ((yt[k-1][logm-1] = (float *) calloc(nel, sizeof(float))) == NULL) {
         printf("Error : FELT : not enough memory for working vector.\n");
         error_exit();
      }
   }
   y  = yt[k-1][logm-1];
   wk = y + k * m - m2;
 
   /* Compute groups of butterflies and delays */
   yp = y;
   s = tab[k-1][logm-1] + (k-1) * 3 * m2;
   spc = s + m2; cms = spc + m2;
   for (gr = k; gr > 0; gr--) {
 
      /* Compute butterfly */
      xp1 = x;
      xp2 = x + m - 1;
      op1 = wk;
      for (n = 0; n < m2; n++) {
         tmp = *s++ * (*xp1 + *xp2);
         *op1++ = *spc++ * *xp1 + tmp;
         *xp2   = *cms++ * *xp2 + tmp;
         xp1++; xp2--;
      }
      n = 2 * m;
      s -= n; spc -= n; cms -= n;
 
      /* Perform delay z^-2 or z^-1 in the last group */
      if (gr == 1) {
         memcpy(x, yp, m2 * sizeof(float));
         memcpy(yp, wk, m2 * sizeof(float));
      } else {
         memcpy(x, yp, m2 * sizeof(float));
         memcpy(yp, yp + m2, m2 * sizeof(float));
         memcpy(yp + m2, wk, m2 * sizeof(float));
      }
      yp += m;
   }
 
   /* Swap top and bottom halfs of  x */
   memcpy(wk, x, m2 * sizeof(float));
   memcpy(x, x + m2, m2 * sizeof(float));
   memcpy(x + m2, wk, m2 * sizeof(float));
 
   /* Compute DCT-IV */
   fdctiv(x, logm);
}
 
/*--------------------------------------------------------------------*
 *    Inverse ELT                                                     *
 *--------------------------------------------------------------------*/
 
void fielt(float *x, int k, int logm)
{
   int      n, m, m2, nel, gr;
   float    tmp, *xp1, *xp2, *op1, *y, *yp, *wk;
   float    *s, *spc, *cms;
   static   float   *yt[MAXK][MAXLOGM];
 
   /* Check range of logm */
   if ((logm < 1) || (logm > MAXLOGM)) {
      printf("Error : FELT : logm = %d is out of bounds [%d, %d]\n",
         logm, 1, MAXLOGM);
      error_exit();
   }
 
   /* Check range of k */
   if ((k < 1) || (k > MAXK)) {
      printf("Error : FELT : k = %d is out of bounds [%d, %d]\n",
         k, 1, MAXK);
      error_exit();
   }
 
   /* Define m */
   m = 1 << logm;
   m2 = m / 2;
 
   /* Compute table of butterfly coefficients, if necessary */
   if (tab[k-1][logm-1] == NULL) read_table(k, logm);
 
   /* Allocate space for working vector, if necessary */
   if (yt[k-1][logm-1] == NULL) {
      nel = k * m;
      if ((yt[k-1][logm-1] = (float *) calloc(nel, sizeof(float))) == NULL) {
         printf("Error : FELT : not enough memory for working vector.\n");
         error_exit();
      }
   }
   y  = yt[k-1][logm-1];
   wk = y + k * m - m2;
 
   /* Compute DCT-IV */
   fdctiv(x, logm);
 
   /* Swap top and bottom halfs of  x */
   memcpy(wk, x, m2 * sizeof(float));
   memcpy(x, x + m2, m2 * sizeof(float));
   memcpy(x + m2, wk, m2 * sizeof(float));
 
   /* Compute groups of delays and butterflies */
   yp = y + (k - 1) * m;
   s = tab[k-1][logm-1]; spc = s + m2; cms = spc + m2;
   for (gr = 0; gr < k; gr++) {
 
      /* Perform delay z^-2 or z^-1 in the first group */
      if (gr == 0) {
         memcpy(wk, yp, m2 * sizeof(float));
         memcpy(yp, x + m2, m2 * sizeof(float));
      } else {
         memcpy(wk, yp, m2 * sizeof(float));
         memcpy(yp, yp + m2, m2 * sizeof(float));
         memcpy(yp + m2, x + m2, m2 * sizeof(float));
      }
      yp -= m;
 
      /* Compute butterfly */
      xp1 = x;
      xp2 = x + m - 1;
      op1 = wk + m2 - 1;
      for (n = 0; n < m2; n++) {
         tmp = *s++ * (*xp1 + *op1);
         *xp1 = *spc++ * *xp1 + tmp;
         *xp2 = *cms++ * *op1 + tmp;
         xp1++; xp2--; op1--;
      }
      s += m; spc += m; cms += m;
   }
}
