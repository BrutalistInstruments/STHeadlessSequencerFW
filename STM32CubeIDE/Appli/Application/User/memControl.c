/*
 * memControl.c
 *
 *  Created on: Feb 16, 2025
 *      Author: OurBl
 */

#include "memControl.h"



//Static Globals

static midiEvent_t* activeMemPoolHead;
static midiEvent_t* activeMemPoolTail;
static project_t* activeProject;
static pattern_t* activePatternHead;
static pattern_t* activePatternTail;
static track_t* activeTrackHead;
static track_t* activeTrackTail;

static midiEvent_t* recoveryMemPoolHead;
static midiEvent_t* recoveryMemPoolTail;
static project_t* recoveryProject;
static pattern_t* recoveryPatternHead;
static pattern_t* recoveryPatternTail;
static track_t* recoveryTrackHead;
static track_t* recoveryTrackTail;

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

}

void loadProject()
{
	//this loads a project from the SD card. We'll need SD card code to make that happen
}

void addSong()
{


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

	bool inserted = false;
	midiEvent_t* currentPosition = hostTrack->eventArrayHead;

	while(inserted == false)
	{
		if(currentPosition->messageTimestamp < inputTimestamp)
		{
			//we need to insert our event before the current event
			activeMemPoolHead->forwardLink = currentPosition;

			if(hostTrack->eventArrayHead == currentPosition)
			{
				//if we're at the front of the line, we only need to make one move.

				hostTrack->eventArrayHead = inputEvent;
				//no need to mess with reverse links, since we are at the beginning.
			}else
			{
				activeMemPoolHead->reverseLink = currentPosition->reverseLink;
				currentPosition->reverseLink = activeMemPoolHead;
			}
			inserted = true;
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

void recoverEvent(midiEvent_t targetEvent)
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
