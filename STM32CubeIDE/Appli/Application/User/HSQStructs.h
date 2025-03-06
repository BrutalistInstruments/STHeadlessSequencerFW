/*
 * HSQStructs.h
 *
 *  Created on: Oct 26, 2024
 *      Author: HalWork
 */

#ifndef APPLICATION_USER_HSQSTRUCTS_H_
#define APPLICATION_USER_HSQSTRUCTS_H_

#include <stdint.h>


//In hierarchical order

#define DEFAULT_BPM 120
#define DEFAULT_SWING 0

typedef struct midiEvent_t
{
	uint8_t midiMessage[3];
	uint32_t messageTimestamp;
	struct midiEvent_t* forwardLink;
	struct midiEvent_t* reverseLink;
}midiEvent_t;

typedef struct track_t
{
	uint8_t outPort;
	uint8_t channel;
	midiEvent_t* eventArrayHead;
	midiEvent_t* playHead;
	struct track_t* forwardLink;
}track_t;

typedef struct pattern_t
{
	uint16_t patternNumber;
	uint16_t BPM;
	uint8_t swing;
	uint8_t trackMute;
	uint8_t trackSolo;
	track_t* trackArray;
	struct pattern_t *patternForwardLink;
	struct pattern_t *patternReverseLink;
	struct pattern_t *songForwardLink;
	struct pattern_t *songReverseLink;
}pattern_t;

typedef struct
{
	uint16_t songNumber; //this probably won't stick around, just padding the struct size a bit.
	pattern_t* patternArray;
	struct song_t* nextSong;
	struct song_t* prevSong;
	//there should be some kind of arrangement data here also.
	//I'm not 100% sure how we want to tackle that yet.

}song_t;


typedef struct
{
	uint16_t projectNumber; //padding for memory check
	song_t* songArrayHead;
	pattern_t* patternArrayHead;

}project_t;




#endif /* APPLICATION_USER_HSQSTRUCTS_H_ */
