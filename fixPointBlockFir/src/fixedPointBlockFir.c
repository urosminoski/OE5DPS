#include "../inc/fixedPointBlockFir.h"

/* Define DSP system memory map */
#pragma CODE_SECTION(fixedPointBlockFir, ".text:fir");

void fixedPointBlockFir(Int16 *x, Int16 blkSize,
                        Int16 *h, Int16 order,
                        Int16 *y,
                        Int16 *w)
{
    // Int16 k = *index; // static Int16 k=0;
    static Int16 k=0;
    Int16 *c;
    Int32 sum;                  // Output of FIR filter.

    /* Iterate through block. */
    for(Int16 j=0; j<blkSize; j++)
    {
        w[k] = *x++;
        c = h;
        sum = 0;
        for(Int16 i=0; i<order; i++)
        {
            sum += *c++ * (Int32)w[k++]; 

            /* Simulating circular buffer. */
            if(k == order)
                k = 0;
        }
        sum += 0x4000;              // Rounding.
        *y++ = (Int16)(sum >> 15);  // Cutting off lower 16 bits, and scaling to [-1, 1-2^15].

        /* Simulating circular buffer. */
        if(k-- == 0){
            k = order - 1;
        }
    }
    // *index = k;     // Update index of circular buffer, where next input will be stored.
}