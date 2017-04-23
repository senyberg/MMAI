#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <stdint.h>
#include <stdbool.h>
 
#include "sndfile.h"
#include "portaudio.h"
#include "reverb.h"
 
 
 
typedef struct
{
    sf_count_t buffer;
    int left;
    int right;
}   
paTestData;
 
float *buffer, *outbuffer;
 
#define FRAMES_PER_BUFFER (64)
 
  
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
                          {
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    unsigned long i;
 
    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer;
 
    for( i=0; i<framesPerBuffer; i++ ){
        *out++ = buffer[data->right++];
        *out++ = buffer[data->left++];
 
        if(data->left >= data->buffer || data->right >= data->buffer){
            data->left = 0;
            data->right = 0;
            return paAbort;
        }
    }
 
    return paContinue;
}
 
 
int main (int argc, char *argv[]){
    char *inputfilename, *outputfilename;
    SF_INFO sfinfo, sfinfo_out;
    SNDFILE *outfile, *infile;

    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;
    paTestData data;
 
    // initialize portaudio and read output device
    err = Pa_Initialize();
    outputParameters.device = Pa_GetDefaultOutputDevice();
 
    // check arguments ok
    if (argc < 2) {
        printf("Expected Input and Ouput\n");
        Pa_Terminate();
        return 1;
    }
 
    // define arguments
    outputfilename = argv [2];
    inputfilename  = argv [1];
 
    // define infile and outfile
    infile = sf_open(inputfilename, SFM_READ, &sfinfo);
    memcpy(&sfinfo_out, &sfinfo, sizeof(sfinfo));
    outfile = sf_open(outputfilename, SFM_WRITE, &sfinfo_out);


    int samples = sfinfo.samplerate;
    int channels = sfinfo.channels;
    int frames = sfinfo.frames;
  
    // allocate memory for buffer and read input
    buffer = malloc(sfinfo.channels * sfinfo.frames * sizeof(float));
    outbuffer = malloc(sfinfo.channels * sfinfo.frames * sizeof(float));
    if (buffer == NULL) {
        printf("Could not allocate memory for data\n");
        sf_close(infile);
        return 1;
    } 
    sf_readf_float(infile, buffer, sfinfo.frames);
    sf_close(infile);
    data.buffer = sfinfo.frames;

    //apply reverb
    reverb(buffer, &outbuffer, samples, channels, frames);
    
    // save to output file
    printf("Saving output to file: %s", outputfilename);
    sfinfo_out.frames = sfinfo.frames;
    sf_writef_float(outfile, outbuffer, sfinfo_out.frames);
    sf_write_sync(outfile);
    sf_close(outfile);
 
    // define output parameters
    outputParameters.channelCount = sfinfo.channels;       
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
 
    // open stream
    err = Pa_OpenStream(
                &stream,
                NULL,
                &outputParameters,
                sfinfo.samplerate,
                FRAMES_PER_BUFFER,
                paClipOff,
                patestCallback, 
                &data );
  
    // check for errors on stream   
    if (err != paNoError){
        Pa_Terminate();
        free(buffer);
        return 1;
    }
 
    // start strean
    err = Pa_StartStream(stream);
     
    // sleep for 5sec (needs to be adjusted, might stop before file finished)
    Pa_Sleep(5000);
 
    // stop, close and terminate
    err = Pa_StopStream(stream);
    err = Pa_CloseStream(stream);
    Pa_Terminate();
 
    free(buffer);
    return 0 ;
}
