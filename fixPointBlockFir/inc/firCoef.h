#ifndef FIRCEOF_H
#define FIRCEOF_H

#include "tistdtypes.h"

#define C_NUM_TAPS  48

Int16 firCoefFixedPoint[C_NUM_TAPS]={
(Int16)(-0.0011606*32767.0),(Int16)(0.005235*32767.0),  (Int16)(0.0019751*32767.0), (Int16)(-0.0010696*32767.0),
(Int16)(0.00070486*32767.0),(Int16)(-0.0023019*32767.0),(Int16)(-0.0085149*32767.0),(Int16)(0.0032251*32767.0),
(Int16)(0.019339*32767.0),  (Int16)(0.0019924*32767.0), (Int16)(-0.024454*32767.0), (Int16)(-0.00927*32767.0),
(Int16)(0.015833*32767.0),  (Int16)(0.0056414*32767.0), (Int16)(0.0040532*32767.0), (Int16)(0.022213*32767.0),
(Int16)(-0.018912*32767.0), (Int16)(-0.074497*32767.0), (Int16)(0.0079832*32767.0), (Int16)(0.13193*32767.0),
(Int16)(0.03699*32767.0),   (Int16)(-0.16479*32767.0),  (Int16)(-0.10113*32767.0),  (Int16)(0.15292*32767.0),
(Int16)(0.15292*32767.0),   (Int16)(-0.10113*32767.0),  (Int16)(-0.16479*32767.0),  (Int16)(0.03699*32767.0),
(Int16)(0.13193*32767.0),   (Int16)(0.0079832*32767.0), (Int16)(-0.074497*32767.0), (Int16)(-0.018912*32767.0),
(Int16)(0.022213*32767.0),  (Int16)(0.0040532*32767.0), (Int16)(0.0056414*32767.0), (Int16)(0.015833*32767.0),
(Int16)(-0.00927*32767.0),  (Int16)(-0.024454*32767.0), (Int16)(0.0019924*32767.0), (Int16)(0.019339*32767.0),
(Int16)(0.0032251*32767.0), (Int16)(-0.0085149*32767.0),(Int16)(-0.0023019*32767.0),(Int16)(0.00070486*32767.0),
(Int16)(-0.0010696*32767.0),(Int16)(0.0019751*32767.0), (Int16)(0.005235*32767.0),  (Int16)(-0.0011606*32767.0)
};

#endif // FIRCEOF_H