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