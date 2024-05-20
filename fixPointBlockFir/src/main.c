#include <stdio.h>
#include <stdlib.h>
#include "../inc/firCoef.h"
#include "../inc/fixedPointBlockFir.h"

#define C_NUM_BLOCK_DATA 80

Int16 w[C_NUM_TAPS];        // Circular buffer.
Int16 x[C_NUM_BLOCK_DATA],  // Input block data.
      y[C_NUM_BLOCK_DATA];  // Output block data.

int main(){
    FILE *fpIn1, *fpOut1,
         *fpIn2, *fpOut2;     // Input and output file pointers.

    Int8 dataTmp[2 * C_NUM_BLOCK_DATA];    // Temporary variable to store 1B input and output data.

    Int8 key;

    printf("Example -- fixed-point block FIR filtering\n");

    fpIn1 = fopen("../data/input.pcm", "rb");
    fpIn2 = fopen("../data/input.wav", "rb");

    if(fpIn1 != NULL){
        fpOut1 = fopen("../data/output.pcm", "wb");
    }
    else{
        perror("Error while opening input PCM file!");
        return 1;
    }
    
    if(fpIn2 != NULL){
        Uint8 wavHeader[44];
        fpOut2 = fopen("../data/output.wav", "wb");
        fread(wavHeader, sizeof(Int8), 44, fpIn2);  // Read header form input wav file.
        fwrite(wavHeader, sizeof(Int8), 44, fpOut2); // Write read header to output wav file.
    }
    else
        printf("Unable to open WAV file. Program will continue wirking with PCM!");

    // printf("Enter 1 for PCM and 2 for WAV file\n");
    // scanf("%d", &key);

    // if(key == 1){
    //     fpIn    = fopen("../data/input.pcm", "rb");
    //     fpOut   = fopen("../data/output.pcm", "wb");
    // }
    // else if(key == 2){
    //     fpIn    = fopen("../data/input.wav", "rb");
    //     fpOut   = fopen("../data/output.wav", "wb");
    // }
    // else{
    //     perror("Invalid key entered!");
    //     return 1;
    // }

    // if(fpIn == NULL){
    //     perror("Error while opening input file!");
    //     return 1;
    // }
    // else if(fpOut == NULL){
    //     perror("Error while opening output file!");
    //     return 1;
    // }

    // if(key == 2){
    //     Uint8 wavHeader[44];
    //     fread(wavHeader, sizeof(Int8), 44, fpIn);  // Read header form input wav file.
    //     fwrite(wavHeader, sizeof(Int8), 44, fpOut); // Write read header to output wav file.
    // }

    /* Initializing circular buffer (w) to zero. */
    for(Uint16 i = 0; i < C_NUM_TAPS; i++){
        w[i] = 0;
    }

    while(fread(dataTmp, sizeof(Int8), 2 * C_NUM_BLOCK_DATA, fpIn1) == 2 * C_NUM_BLOCK_DATA){

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

        /* Write output to the output files. */
        fwrite(dataTmp, sizeof(Int8), 2 * C_NUM_BLOCK_DATA, fpOut1);
        fwrite(dataTmp, sizeof(Int8), 2 * C_NUM_BLOCK_DATA, fpOut2);
    }

    /* Close files. */
    fclose(fpIn1);
    fclose(fpIn2);
    fclose(fpOut1);
    fclose(fpOut2);

    return 0;
}