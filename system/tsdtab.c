/*tsdtab.c - tsdtab*/
#include "xinu.h"
/*----------------------------------
* tsdtab - is a global varibale
*-----------------------------------
*/
struct ts_disptb tsdtab[20] = {
  {0,13 ,200},
  {0,13 ,200},
  {0,13 ,200},
  {0,14,160},
  {1,14,160},
  {2,14,160},
  {3,14,160},
  {4,15,120 },
  {5,15,120},
  {6,15,120 },
  {7,16,80},
  {8,16,80},
  {9,16,80 },
  {10,17,80 },
  {11,17,80 },
  {12,17,80 },
  {13,18,40 },
  {14,18,40 },
  {15,18,40 },
  {16,19,20 }
};
