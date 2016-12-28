#ifndef Structlib_h
#define Structlib_h

#include <WString.h>

typedef struct {
  int id;                                                                           // This structure stores data and statistics for
  unsigned long results[7][10];                                                     // up to 7 users (size of our project group)
  int check;                                                                        // 1 if passed, 0 if failed
  float average[7];
  float variance[7];
//  int Test = 0;
//  int blob;
//  int check = 0;
}userdatas;

#endif
