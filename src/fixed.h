#ifndef FIXED_H
#define FIXED_H

#define FIXED_RESOLUTION (8)

#define FIXED_TO_INT(F) ((F) >> FIXED_RESOLUTION)
#define INT_TO_FIXED(I) ((I) << FIXED_RESOLUTION)

#define FIXED_MULT(A, B) (((A) * (B)) >> FIXED_RESOLUTION)
#define FIXED_DIV(A, B) (((fixed_t) (A) * (1 << FIXED_RESOLUTION)) / (B))

#define FIXED_SQRT(F) (_isqrt((F) * (1 << FIXED_RESOLUTION)))

#define FIXED_ONE INT_TO_FIXED(1)

typedef int fixed_t;

#endif
