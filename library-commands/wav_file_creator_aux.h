#ifndef _WAV_FILE_CREATOR_AUX_H_
#define _WAV_FILE_CREATOR_AUX_H_
#include "ApplicationData.h"
#include "audio_track_creator_aux.h"

void configure_audio_track_and_wav_file(ApplicationData& app_data);
void fill_channels(ApplicationData& app_data);
void save_wav_file(ApplicationData& app_data);
int wav_file_creator(ApplicationData& app_data);

#endif /* _WAV_FILE_CREATOR_AUX_H_ */