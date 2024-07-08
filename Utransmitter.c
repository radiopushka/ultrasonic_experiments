#include "Utransmitter.h"
#include "frequencymanager.c"

//frequency in khz, 1 is 1 khz
void amplitude_modulate(short* input, short* output,int length, float freq){

  int i;

  int freqi = get_index_for_frequency(freq);
  if(freqi == -1){
    add_frequency(freq);
    freqi = get_index_for_frequency(freq);
  }
// amplitude modulation
  for(i = 0; i < length; i++){
    output[i] = (periods[freqi][i] * (24575 + input[i]*0.25));
  }

}
void amplitude_demodulate(short* input, short* output, int length, float freq, double gain){


  int i;

  int freqi = get_index_for_frequency(freq);
  if(freqi == -1){
    add_frequency(freq);
    freqi = get_index_for_frequency(freq);
  }

  double sin;
  double cos;

  //fourier transform
  for( i = 0; i < length; i++){
    sin = input[i] * periods[freqi][i];
    cos = input[i] * cosine[freqi][i];
    output[i] = ( (sin + cos) * gain );

  }

}
