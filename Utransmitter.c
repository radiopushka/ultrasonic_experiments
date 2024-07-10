#include "Utransmitter.h"
#include "frequencymanager.c"

//frequency in khz, 1 is 1 khz
void amplitude_modulate(short* input, short* output,int length, float freq, double gain){

  int i;
  double coeff = gain * 0.25;

  int freqi = get_index_for_frequency(freq);
  if(freqi == -1){
    add_frequency(freq);
    freqi = get_index_for_frequency(freq);
  }
// amplitude modulation
  for(i = 0; i < length; i++){
    output[i] = (periods[freqi][i] * (24575 + input[i] * coeff));
  }

}

double shift_coeff = 0;
double maxg = 0;
double ming = 0;

void amplitude_demodulate(short* input, short* output, int length, float freq, double gain){


  int i;

  int freqi = get_index_for_frequency(freq);
  if(freqi == -1){
    add_frequency(freq);
    freqi = get_index_for_frequency(freq);
  }

  double sin;
  double cos;

  double max = -24575;
  double min = 24575;
  double demod;

  //fourier transform
  for( i = 0; i < length; i++){
    sin = input[i] * periods[freqi][i];
    cos = input[i] * cosine[freqi][i];

    demod = sin + cos;

    if(demod > max)
      max = demod;

    if(demod < min)
      min = demod;

    

    output[i] = ( (demod + shift_coeff) * gain );

  }
  if(ming == maxg){
    ming = min;
    maxg = max;
  }else {
    ming = (ming + min)/2;
    maxg = (maxg + max)/2;
  }
  shift_coeff = -((maxg - ming)/2 + ming);

}
