#include <stdio.h>
#include "fir_ceof.h"

const char* file_name = "polyphase_coef.txt";

int main()
{
  FILE *file = fopen(file_name, "w");
  if(file == NULL)
  {
    printf("Unable to open file %s", file_name);
    return 0;
  }

  // Write each element of the array to the txt file
  for(int i = 0; i < BL; i++)
  {
    fprintf(file, "%d\n", B[i]);
  }

  // Close the file
  fclose(file);

  return 1;
}