#ifndef LOOKUP_H
#define LOOKUP_H

#include "../fixed.h"

#define FIXED_SIN(n) (sin_table[(n % 360)])
#define FIXED_COS(n) (cos_table[(n % 360)])

#endif
