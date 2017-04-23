
#ifndef __REVERB_H
#define __REVERB_H

#include "sndfile.h"


void reverb(float *buffer, float **outbuffer, int samples, int channels, int frames);


#endif
