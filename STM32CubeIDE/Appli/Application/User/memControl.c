/*
 * memControl.c
 *
 *  Created on: Feb 16, 2025
 *      Author: OurBl
 */

#include "memControl.h"

#if(ON_TARGET_TEST)
midiEvent_t* activeMemPoolHead;
midiEvent_t* activeMemPoolTail;
project_t* activeProject;
pattern_t* activePatternHead;
pattern_t* activePatternTail;
track_t* activeTrackHead;
track_t* activeTrackTail;
song_t* activeSongHead;
song_t* activeSongTail;
midiEvent_t* recoveryMemPoolHead;
midiEvent_t* recoveryMemPoolTail;
project_t* recoveryProject;
pattern_t* recoveryPatternHead;
pattern_t* recoveryPatternTail;
track_t* recoveryTrackHead;
track_t* recoveryTrackTail;
song_t* recoverySongHead;
song_t* recoverySongTail;
uint8_t projectCounter = 0;
uint16_t songCounter = 0;
uint16_t patternCounter = 0;
#else
//Static Globals
static midiEvent_t* activeMemPoolHead;
static midiEvent_t* activeMemPoolTail;
static project_t* activeProject;
static pattern_t* activePatternHead;
static pattern_t* activePatternTail;
static track_t* activeTrackHead;
static track_t* activeTrackTail;
static song_t* activeSongHead;
static song_t* activeSongTail;

static midiEvent_t* recoveryMemPoolHead;
static midiEvent_t* recoveryMemPoolTail;
static project_t* recoveryProject;
static pattern_t* recoveryPatternHead;
static pattern_t* recoveryPatternTail;
static track_t* recoveryTrackHead;
static track_t* recoveryTrackTail;
static song_t* recoverySongHead;
static song_t* recoverySongTail;

static uint8_t projectCounter = 0;
static uint16_t songCounter = 0;
static uint16_t patternCounter = 0;
#endif


//This intializes the memory pool of a new project. Creates a fully blank project.
void initMemoryPoolActiveProject()
{
	for(int i = 0; i<=MEM_POOL_SIZE; i++)
	{
		  midiEvent_t *currentMemPoolPtr = MEM_POOL_START_ADDRESS_ACTIVE + (i*sizeof(midiEvent_t));

		  if(i>0)
		  {
			  currentMemPoolPtr->reverseLink = MEM_POOL_START_ADDRESS_ACTIVE + ((i-1)*sizeof(midiEvent_t));
		  }else
		  {
			  activeMemPoolHead = currentMemPoolPtr;
		  }
		  if(i<MEM_POOL_SIZE-1)
		  {
			  currentMemPoolPtr->forwardLink = MEM_POOL_START_ADDRESS_ACTIVE + ((i+1)*sizeof(midiEvent_t));
		  }else
		  {
			  activeMemPoolTail = currentMemPoolPtr;
		  }

		  currentMemPoolPtr->messageTimestamp = 0;
		  currentMemPoolPtr->midiMessage[0] = 0;
		  currentMemPoolPtr->midiMessage[1] = 0;
		  currentMemPoolPtr->midiMessage[2] = 0;
	}
}

void initMemoryPoolRecoveryProject()
{
	for(int i = 0; i<=MEM_POOL_SIZE; i++)
	{
		  midiEvent_t *currentMemPoolPtr = MEM_POOL_START_ADDRESS_RECOVERY + (i*sizeof(midiEvent_t));

		  if(i>0)
		  {
			  currentMemPoolPtr->reverseLink = MEM_POOL_START_ADDRESS_RECOVERY + ((i-1)*sizeof(midiEvent_t));
		  }else
		  {
			  recoveryMemPoolHead = currentMemPoolPtr;
		  }
		  if(i<MEM_POOL_SIZE-1)
		  {
			  currentMemPoolPtr->forwardLink = MEM_POOL_START_ADDRESS_ACTIVE + ((i+1)*sizeof(midiEvent_t));
		  }else
		  {
			  recoveryMemPoolTail = currentMemPoolPtr;
		  }

		  currentMemPoolPtr->messageTimestamp = 0;
		  currentMemPoolPtr->midiMessage[0] = 0;
		  currentMemPoolPtr->midiMessage[1] = 0;
		  currentMemPoolPtr->midiMessage[2] = 0;
	}
}

void saveProject()
{
	memcpy(MEM_POOL_START_ADDRESS_RECOVERY, MEM_POOL_START_ADDRESS_ACTIVE, MEM_POOL_SIZE*sizeof(midiEvent_t));
}

uint8_t activeProjectSpaceAvailiblePercent()
{
	return (((((uint32_t)activeMemPoolTail - (uint32_t)activeMemPoolHead)/sizeof(midiEvent_t))*100)/MEM_POOL_SIZE);
}

uint32_t activeProjectSpaceAvailibleEvents()
{
	return ((uint32_t)activeMemPoolTail - (uint32_t)activeMemPoolHead)/sizeof(midiEvent_t);
}

uint8_t recoveryProjectSpaceAvailiblePercent()
{
	return (((((uint32_t)recoveryMemPoolTail - (uint32_t)recoveryMemPoolHead)/sizeof(midiEvent_t))*100)/MEM_POOL_SIZE);
}

uint32_t recoveryProjectSpaceAvailibleEvents()
{
	return ((uint32_t)recoveryMemPoolTail - (uint32_t)recoveryMemPoolHead)/sizeof(midiEvent_t);
}

//Adding new structures
void newProject()
{
	//a project is about a quarter of the size of a midi event, so we can just move this back one.
    uint32_t replacePointerAddrActive = (uint32_t)activeMemPoolTail; //we need to store the current address before we lose it.
	activeMemPoolTail = activeMemPoolTail->reverseLink;

	uint32_t replacePointerAddrReserve = (uint32_t)recoveryMemPoolTail; //we need to store the current address before we lose it.
	recoveryMemPoolTail = recoveryMemPoolTail->reverseLink;

	project_t* newProjectActive = (project_t*)replacePointerAddrActive;
	project_t* newProjectReserve = (project_t*)replacePointerAddrReserve;

	newProjectActive->projectNumber = projectCounter; //we'll just keep it at this for now. There should be some more internal logic later.
	newProjectReserve->projectNumber = projectCounter;
	projectCounter++;

	newProjectActive->songArrayHead = 0;
	newProjectReserve->songArrayHead = 0;

	newProjectActive->patternArrayHead = 0;
	newProjectReserve->patternArrayHead = 0;


	activeProject = newProjectActive;
	recoveryProject = newProjectReserve;


}

void loadProject()
{
	//this loads a project from the SD card. We'll need SD card code to make that happen
}

void addSong()
{
	uint32_t replacePointerAddrActive = (uint32_t)activeMemPoolTail; //we need to store the current address before we lose it.
	activeMemPoolTail = activeMemPoolTail->reverseLink;

	song_t *newSong = (song_t*)replacePointerAddrActive;
	newSong->songNumber = songCounter;

	song_t* songIterator = activeProject->songArrayHead;

	while(songIterator->nextSong != 0)
	{
		songIterator = (song_t*)songIterator->nextSong;
	}

	songIterator->nextSong = newSong;
	newSong->prevSong = (song_t*)songIterator;
	newSong->nextSong = 0;
	songCounter++;


}

void addPattern_s(song_t hostSong)
{


}

void addPattern_p(project_t hostProject)
{

}

void addTrack(pattern_t hostPattern)
{


}

void addEvent(track_t hostTrack, uint8_t inputMidiMessage[3], uint32_t inputTimestamp)
{

	//take an event out of the memory pool, and make an event out of it.
	activeMemPoolHead->midiMessage[0] = inputMidiMessage[0];
	activeMemPoolHead->midiMessage[1] = inputMidiMessage[1];
	activeMemPoolHead->midiMessage[2] = inputMidiMessage[2];

	activeMemPoolHead->messageTimestamp = inputTimestamp;

	midiEvent_t* futureNewHead = activeMemPoolHead->forwardLink;

	uint8_t inserted = 0;
	midiEvent_t* currentPosition = hostTrack.eventArrayHead;

	while(inserted == 0)
	{
		if(currentPosition->messageTimestamp < inputTimestamp)
		{
			//we need to insert our event before the current event
			activeMemPoolHead->forwardLink = currentPosition;

			if(hostTrack.eventArrayHead == currentPosition)
			{
				//if we're at the front of the line, we only need to make one move.

				hostTrack.eventArrayHead = activeMemPoolHead;

				//no need to mess with reverse links, since we are at the beginning.
			}else
			{
				activeMemPoolHead->reverseLink = currentPosition->reverseLink;
				currentPosition->reverseLink = activeMemPoolHead;
			}
			inserted = 1;
		}else
		{
			//move to the next node
			currentPosition = currentPosition->forwardLink;
		}
	}

	//now that we've gotten all of the stuff figured out, we can release the link from our memory pool.
	activeMemPoolHead = futureNewHead;
}


//recovery system
void recoverSong(song_t targetSong)
{

}

void recoverPattern(pattern_t targetPattern)
{

}

void recoverTrack(track_t targetTrack)
{

}

void recoverEvent(midiEvent_t targetEvent, midiEvent_t inputEvent)
{

}

//this will overwrite the entire active project.
void recoverProject()
{
	memcpy(MEM_POOL_START_ADDRESS_ACTIVE, MEM_POOL_START_ADDRESS_RECOVERY, MEM_POOL_SIZE*sizeof(midiEvent_t));
}

//this will initialize our system with a completely blank project and memory pool.
void initMemorySystemBlank()
{

}
