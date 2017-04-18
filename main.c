#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include "sndfile.h"
#include "portaudio.h"


int main (int argc, char *argv[]) {
    printf("WAV read test\n");
    if (argc != 2) {
        fprintf(stderr, "Expected WAV file as argument\n");
        return 1;
    }

    SF_INFO sndInfo;
    SNDFILE *sndFile = sf_open(argv[1], SFM_READ, &sndInfo);
    if (sndFile == NULL) {
        fprintf(stderr, "Error reading source file '%s': %s\n", argv[1],
                sf_strerror(sndFile));
        return 1;
    }

    float *buffer = malloc(sndInfo.frames * sizeof(float));
    if (buffer == NULL) {
        fprintf(stderr, "Could not allocate memory for data\n");
        sf_close(sndFile);
        return 1;
    }

    long numFrames = sf_readf_float(sndFile, buffer, sndInfo.frames);

    if (numFrames != sndInfo.frames) {
        fprintf(stderr, "Did not read enough frames for source \n");
        sf_close(sndFile);
        free(buffer);
        return 1;
    }

    printf("Read %ld frames from %s, Sample rate: %d, Length: %fs\n",
            numFrames, argv[1], sndInfo.samplerate,
            (float)numFrames/sndInfo.samplerate);
    sf_close(sndFile);
    free(buffer);
    return 0;
} 
