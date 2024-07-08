#include "Utransmitter.h"
#include "alsa/alsa.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argn){
  init_f_manager(1500, 48000);
  int status = setup_alsa("default", "default", 1500);

  printf(" alsa status %d\n",status);
  if( status < 0)
    return 0;

  short* input = malloc(sizeof(short) * (1500));
  short* output = malloc(sizeof(short) * (1500));
  int error = 0;
  while( error != -1){
    error = aread(input);

    if(argn > 1)
      amplitude_demodulate(input,output,1500,20,400);
    else
      amplitude_modulate(input, output,1500,20);

    awrite(output);

  }

  clean_f_manager();

  free(input);
  free(output);
  free_alsa();

  return 0;
}
