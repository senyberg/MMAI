#include "reverb.h"
#include <stdint.h>

void reverb(float *buffer, float **outbuffer, int samples, int channels, int frames)
{
    int delayMilliseconds = 500;
    int delaySamples = (int)((float)delayMilliseconds * samples);
    int i, j;

    for (i = 0; i < 2; i++)
    {
        for(j = 0; j < samples; j++) {
            *outbuffer = &buffer[i+samples];
        }
    }
}
