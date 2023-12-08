#include <stdio.h>
#include <stdlib.h>
#include "../inc/firCoef.h"
#include "../inc/fixedPointBlockFir.h"

#define C_NUM_BLOCK_DATA 80

Int16 w[C_NUM_TAPS];        // Circular buffer.
Int16 x[C_NUM_BLOCK_DATA],  // Input block data.
      y[C_NUM_BLOCK_DATA];  // Output block data.

void main(){
    FILE *fpIn, *fpOut;     // Input and output file pointers.

    Int8 dataTmp[2 * C_NUM_BLOCK_DATA];    // Temporary variable to store 1B input and output data.

    Int8 key;

    printf("Example -- fixed-point block FIR filtering\n");
    printf("Enter 1 for PCM and 2 for WAV file\n");
    scanf("%d", &key);

    if(key == 1){
        fpIn    = fopen("../data/input.pcm", "rb");
        fpOut   = fopen("../data/output.pcm", "wb");
    }
    else if(key == 2){
        fpIn    = fopen("../data/input.wav", "rb");
        fpOut   = fopen("../data/output.wav", "wb");
    }
    else{
        perror("Invalid key entered!");
        exit(0);
    }

    if(fpIn == NULL){
        perror("Error while opening input file!");
        exit(0);
    }
    else if(fpOut == NULL){
        perror("Error while opening output file!");
        exit(0);
    }

    if(key == 2){
        Uint8 wavHeader[44];
        fread(wavHeader, sizeof(Int8), 44, fpIn);  // Read header form input wav file.
        fwrite(wavHeader, sizeof(Int8), 44, fpOut); // Write read header to output wav file.
    }

    /* Initializing circular buffer (w) to zero. */
    for(Uint16 i = 0; i < C_NUM_TAPS; i++){
        w[i] = 0;
    }

    while(fread(dataTmp, sizeof(Int8), 2 * C_NUM_BLOCK_DATA, fpIn) == 2 * C_NUM_BLOCK_DATA){

        /* Converting 1B input data into int16. Data is little-endian. */
        for(Uint16 j = 0, i = 0; i < C_NUM_BLOCK_DATA; i++){
            x[i] = (dataTmp[j] & 0xFF) | (dataTmp[j + 1] << 8);
            j += 2;
        }

        /* Filtering x by fixPointBlockFir(). */
        fixedPointBlockFir(x, C_NUM_BLOCK_DATA, firCoefFixedPoint, C_NUM_TAPS, y, w);

        /* Converting int16 output data into 1B. Data is little-endian. */
        for(Uint16 j = 0, i = 0; i < C_NUM_BLOCK_DATA; i++){
            dataTmp[j]      = (y[i] & 0xFF);
            dataTmp[j + 1]  = ((y[i] >> 8) & 0xFF);
            j += 2; 
        }

        /* Write output to the output file. */
        fwrite(dataTmp, sizeof(Int8), 2 * C_NUM_BLOCK_DATA, fpOut);
    }

    /* Close files. */
    fclose(fpIn);
    fclose(fpOut);
}