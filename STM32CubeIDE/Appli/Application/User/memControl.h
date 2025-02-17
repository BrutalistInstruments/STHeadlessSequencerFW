/*
 * memControl.h
 *
 *  Created on: Feb 16, 2025
 *      Author: OurBl
 */

#ifndef APPLICATION_USER_MEMCONTROL_H_
#define APPLICATION_USER_MEMCONTROL_H_

#include "HSQStructs.h"
#include <stdint.h>

#define MEM_POOL_SIZE 1000000U //this is the size in Midi Events
#define MEM_POOL_START_ADDRESS_ACTIVE 0x90000000

#define MEM_POOL_START_ADDRESS_RECOVERY 0x90F42410 //1000000 * 16bytes = 0x00F4 2400


//memory pool control
void initMemoryPoolActiveProject();
void initMemoryPoolRecoveryProject();
void saveProject();
uint8_t activeProjectSpaceAvailiblePercent();
uint32_t activeProjectSpaceAvailibleEvents();
uint8_t recoveryProjectSpaceAvailiblePercent();
uint32_t recoveryProjectSpaceAvailibleEvents();

//Adding new structures
void newProject();
void loadProject();
void addSong();
void addPattern_s(song_t hostSong);
void addPattern_p(project_t hostProject);
void addTrack(pattern_t hostPattern);
void addEvent(track_t hostTrack, uint8_t inputMidiMessage[3], uint32_t inputTimestamp);


//recovery system
void recoverSong(song_t targetSong);
void recoverPattern(pattern_t targetPattern);
void recoverTrack(track_t targetTrack);
void recoverEvent(midiEvent_t targetEvent, midiEvent_t inputEvent);
void recoverProject();

//High level initialization
void initMemorySystemBlank();



#endif /* APPLICATION_USER_MEMCONTROL_H_ */
