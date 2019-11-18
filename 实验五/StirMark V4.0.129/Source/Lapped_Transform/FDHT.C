/*--------------------------------------------------------------------*
 *    FDHT.C  -  Split-Radix Fast Hartley Transform.                  *
 *                                                                    *
 *    This is a decimation-in-frequency version, using the steps      *
 *    of the algorithm as described in Section 2.5.                   *
 *                                                                    *
 *    Author:  Henrique S. Malvar.                                    *
 *    Date:    October 8, 1991.                                       *
 *                                                                    *
 *    Usage:   fdht(x, logm);   --  for direct or inverse DHT         *
 *                                                                    *
 *    Arguments:  x (float)  - input and output vector, length M;     *
 *                logm (int) - log (base 2) of vector length M,       *
 *                             e.g., for M = 256 -> logm = 8.         *
 *--------------------------------------------------------------------*/
 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
 
#define  MAXLOGM     11    /* max DHT length = 2^MAXLOGM */
#define  TWOPI       6.28318530717958647692
#define  SQHALF      0.707106781186547524401
#define  SQTWO       1.41421356237309504880
 
/*--------------------------------------------------------------------*
 *    Error exit for program abortion.                                *
 *--------------------------------------------------------------------*/
 
static   void  error_exit(void)
{
   exit(1);
}
 
/*--------------------------------------------------------------------*
 *    Data unshuffling according to bit-reversed indexing.            *
 *                                                                    *
 *    Bit reversal is done using Evan's algorithm (Ref: D. M. W.      *
 *    Evans, "An improved digit-reversal permutation algorithm ...",  *
 *    IEEE Trans. ASSP, Aug. 1987, pp. 1120-1125).                    *
 *--------------------------------------------------------------------*/
 
static   int   brseed[256];   /* Evans' seed table */
static   int   brsflg;        /* flag for table building */
 
static void BR_permute(float *x, int logm)
{
   int      i, j, imax, lg2, n;
   int      off, fj, gno, *brp;
   float    tmp, *xp, *xq;
 
   lg2 = logm >> 1;
   n = 1 << lg2;
   if (logm & 1) lg2++;
 
   /* Create seed table if not yet built */
   if (brsflg != logm) {
      brsflg = logm;
      brseed[0] = 0;
      brseed[1] = 1;
      for (j = 2; j <= lg2; j++) {
         imax = 1 << (j - 1);
         for (i = 0; i < imax; i++) {
            brseed[i] <<= 1;
            brseed[i + imax] = brseed[i] + 1;
         }
      }
   }
 
   /* Unshuffling loop */
   for (off = 1; off < n; off++) {
      fj = n * brseed[off]; i = off; j = fj;
      tmp = x[i]; x[i] = x[j]; x[j] = tmp;
      xp = &x[i];
      brp = &brseed[1];
      for (gno = 1; gno < brseed[off]; gno++) {
         xp += n;
         j = fj + *brp++;
         xq = x + j;
         tmp = *xp; *xp = *xq; *xq = tmp;
      }
   }
}
 
/*--------------------------------------------------------------------*
 *    Recursive part of the FHT algorithm.  Not externally            *
 *    callable.                                                       *
 *--------------------------------------------------------------------*/
 
static void dhtrec(float *x, int logm)
{
   static   int      m, m2, m4, m8, nel, n;
   static   float    *x1, *x2, *x3, *x4;
   static   float    *sn, *cpsn, *cmsn, *s3n, *cps3n, *cms3n;
   static   float    tmp1, tmp2, tmp3, ang, c, s;
   static   float    *tab[MAXLOGM];
 
   /* Check range of logm */
   if ((logm < 0) || (logm > MAXLOGM)) {
      printf("Error : FDHT : logm = %d is out of bounds [%d, %d]\n",
         logm, 0, MAXLOGM);
      error_exit();
   }
 
   /* Compute trivial cases */
   if (logm <= 2) {
      if (logm == 2) {  /* length m = 4 */
         x1 = x;  x2 = x + 2;
         tmp1 = *x1 + *x2;
         *x2  = *x1 - *x2;
         *x1  = tmp1;
         x1++;  x2++;
         tmp1 = *x1 + *x2;
         *x2  = *x1 - *x2;
         *x1  = tmp1;
         x1 = x;  x2 = x + 1;
         tmp1 = *x1 + *x2;
         *x2  = *x1 - *x2;
         *x1  = tmp1;
         x1++;  x2++;
         x1++;  x2++;
         tmp1 = *x1 + *x2;
         *x2  = *x1 - *x2;
         *x1  = tmp1;
         return;
      } else if (logm == 1) {  /* length m = 2 */
         x2  = x + 1;
         tmp1 = *x + *x2;
         *x2  = *x - *x2;
         *x   = tmp1;
         return;
      }
      else if (logm == 0) return;   /* length m = 1 */
   }
 
   /* Compute a few constants */
   m = 1 << logm; m2 = m / 2; m4 = m2 / 2; m8 = m4 /2;
 
   /* Build tables of butterfly coefficients, if necessary */
   if ((logm >= 4) && (tab[logm-4] == NULL)) {
 
      /* Allocate memory for tables */
      nel = m8 - 1;
      if ((tab[logm-4] = (float *) calloc(6 * nel, sizeof(float))) == NULL) {
         printf("Error : FDHT : not enough memory for cosine tables.\n");
         error_exit();
      }
 
      /* Initialize pointers */
      sn  = tab[logm-4]; cpsn  = sn + nel;  cmsn  = cpsn + nel;
      s3n = cmsn + nel;  cps3n = s3n + nel; cms3n = cps3n + nel;
 
      /* Compute tables */
      for (n = 1; n < m8; n++) {
         ang = n * TWOPI / m;
         c = cos(ang); s = sin(ang);
         *sn++ = s; *cpsn++ = - (c + s); *cmsn++ = c - s;
         ang = 3 * n * TWOPI / m;
         c = cos(ang); s = sin(ang);
         *s3n++ = s; *cps3n++ = - (c + s); *cms3n++ = c - s;
      }
   }
 
   /* Step 1 */
   x1 = x; x2 = x1 + m2;
   for (n = 0; n < m2; n++) {
      tmp1 = *x1 + *x2;
      *x2  = *x1 - *x2;
      *x1  = tmp1;
      x1++; x2++;
   }
 
   /* Step 2 */
   x1 = x + m2; x2 = x1 + m4;
   for (n = 0; n < m8; n++) {
      tmp1 = *x1 + *x2;
      *x2  = *x1 - *x2;
      *x1  = tmp1;
      x1++; x2--;
   }
 
   /* Step 3 */
   x1 = x + m2 + m4 + 1; x2 = x + m - 1;
   for (n = 1; n < m8; n++) {
      tmp1 = *x2 + *x1;
      *x2  = *x2 - *x1;
      *x1  = tmp1;
      x1++; x2--;
   }
 
   /* Step 4 */
   x[m2 + m8]      *= SQTWO;
   x[m2 + m4 + m8] *= SQTWO;
 
   /* Step 5 */
   if (logm >= 4) {
      nel = m8 - 1;
      sn  = tab[logm-4]; cpsn  = sn + nel;  cmsn  = cpsn + nel;
      s3n = cmsn + nel;  cps3n = s3n + nel; cms3n = cps3n + nel;
   }
   x1 = x + m2;  x2 = x1 + m4;  x3 = x2;  x4 = x + m;
   x1++; x2--; x3++; x4--;
   for (n = 1; n < m8; n++) {
      tmp2 = *sn++ * (*x1 + *x4);
      *x1  = *cmsn++ * *x1 + tmp2;
      tmp3 = *cpsn++ * *x4 + tmp2;
      tmp2 = *s3n++ * (*x2 + *x3);
      *x4  = *cps3n++ * *x3 + tmp2;
      *x3  = *cms3n++ * *x2 + tmp2;
      *x2  = tmp3;
      x1++; x2--; x3++; x4--;
   }
 
   /* Call dhtrec again with half length */
   dhtrec(x, logm-1);
 
   /* Call dhtrec again twice with one quarter length.
      Constants have to be recomputed, because they are static! */
   m = 1 << logm; m2 = m / 2;
   dhtrec(x + m2, logm-2);
   m = 1 << logm; m4 = 3 * (m / 4);
   dhtrec(x + m4, logm-2);
}
 
/*--------------------------------------------------------------------*
 *    Externally callable module.                                     *
 *--------------------------------------------------------------------*/
 
void  fdht(float *x, int logm)
{
   int      i, m;
   float    fac, *xp;
 
   /* Call recursive routine */
   dhtrec(x, logm);
 
   /* Output array unshuffling using bit-reversed indices */
   if (logm > 1) {
      BR_permute(x, logm);
   }
 
   /* Normalization */
   m = 1 << logm;
   fac = sqrt(1.0 / m);
   xp = x;
   for (i = 0; i < m; i++) {
      *xp++ *= fac;
   }
}
