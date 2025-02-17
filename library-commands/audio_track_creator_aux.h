<<<<<<< HEAD
#ifndef _AUDIO_TRACK_CREATOR_AUX_H_
#define _AUDIO_TRACK_CREATOR_AUX_H_
#include "ApplicationData.h"


void rampup_fill_audio_track(ApplicationData& app_data);
void rampdown_fill_audio_track(ApplicationData& app_data);
void display_audio_track(ApplicationData& app_data);
void fill_audio_track(ApplicationData& app_data);
int audio_track_creator(ApplicationData& app_data);
void sine_fill_audio_track(ApplicationData& app_data);
void sawtooth_fill_audio_track(ApplicationData& app_data);

#endif /* _AUDIO_TRACK_CREATOR_AUX_H_ */
=======
#ifndef AUDIO_TRACK_CREATOR_AUX_H
#define AUDIO_TRACK_CREATOR_AUX_H

#include "ApplicationData.h"
#include "audio_track_creator_aux.h"


// Functions for filling audio tracks with specific patterns
void rampup_fill_audio_track(ApplicationData& app_data);
void rampdown_fill_audio_track(ApplicationData& app_data);
void fill_audio_track(ApplicationData& app_data);
void sine_fill_audio_track(ApplicationData& app_data);
void sawtooth_fill_audio_track(ApplicationData& app_data);

// functions for Reverse Sawtooth
void reverse_sawtooth_fill_audio_track(ApplicationData& app_data); 

// Function for displaying the audio track data
void display_audio_track(ApplicationData& app_data);

// Main function for creating and configuring the audio track
int audio_track_creator(ApplicationData& app_data);

void configure_audio_track(ApplicationData& app_data);

#endif // AUDIO_TRACK_CREATOR_AUX_H
>>>>>>> b63ca74 (curts quads or burts?)
