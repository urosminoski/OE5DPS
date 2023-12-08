#ifndef FIXEDPOINTBLOCKFIR_H
#define FIXEDPOINTBLOCKFIR_H

#include "tistdtypes.h"

void fixedPointBlockFir(Int16 *x, Int16 blkSize,
                        Int16 *h, Int16 order,
                        Int16 *y,
                        Int16 *w);

#endif // FIXEDPOINTBLOCKFIR_H