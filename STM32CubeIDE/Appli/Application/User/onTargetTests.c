/*
 * onTargetTests.c
 *
 *  Created on: Mar 2, 2025
 *      Author: OurBl
 */

#include "onTargetTests.h"
//#include <stdbool.h> //This doesn't seen to work for some reason

extern midiEvent_t* activeMemPoolHead;
extern midiEvent_t* activeMemPoolTail;
//extern track_t* activeTrackHead;
extern project_t* activeProject;

//this is our test runner on target.
//if any tests fail, it returns a 0.
bool runTests()
{
	memControlTest1();
	memControlTest2();
	memControlTest3();
	memControlTest4();
	return true;
}


//This is where our tests should end up if they fail. Check the call stack to see which test you are in that failed.
void testErrorState()
{
	while(1);

}



//take in the head and tail of blank memory, and check that it is blank.
uint8_t blankMemoryChecker(midiEvent_t *head, midiEvent_t *tail)
{
	int moveCounter = 0;

	while((uint32_t)head != (uint32_t)tail)
	{
		//this is an assert. We'll write an assert function later.
		if(head->messageTimestamp != 0 ||
				head->midiMessage[0] != 0 ||
				head->midiMessage[1] != 0 ||
				head->midiMessage[2] != 0)
		{
			testErrorState();
		}

		if((head->forwardLink != ((uint32_t)head + 16)) && ((uint32_t)head != (uint32_t)tail))
		{
			testErrorState();
		}

		if(head->reverseLink != ((uint32_t)head-16) && (moveCounter != 0))
		{
			testErrorState();
		}

		if(moveCounter == 0 && head->reverseLink != 0)
		{
			testErrorState();
		}

		if(tail->forwardLink != 0)
		{
			testErrorState();
		}

		head = head->forwardLink;
		moveCounter++;
	}

	//if tail sits somewhere in active memory, make sure we have moved the same amount of times
	if((uint32_t)head > MEM_POOL_START_ADDRESS_ACTIVE && (uint32_t)head < MEM_POOL_START_ADDRESS_RECOVERY)
	{
		if(moveCounter != activeProjectSpaceAvailibleEvents())
		{
			testErrorState();
		}

	}else
	{
		if(moveCounter != recoveryProjectSpaceAvailibleEvents())
		{
			testErrorState();
		}

	}
	return 1;
}

//initalize project and memory structure.
bool memControlTest1()
{
	//init structure
	initMemoryPoolActiveProject();
	initMemoryPoolRecoveryProject();


	//check to make sure that everything is working
	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
		return false;
	}


	newProject();

	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
			return false;
	}

	return true;
}

//insert event into track
bool memControlTest2()
{
	//for now, we'll just use the first track that we just made
	track_t* trackToTest = activeProject->patternArrayHead->trackArray;

	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
			return false;
	}

	uint8_t midiMessage[] = {0x71, 0x3C, 0x7F}; //middle C, played on channel 1, full velocity

	addEvent(trackToTest, midiMessage, 5000);

	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
			return false;
	}

	if(trackToTest->eventArrayHead->messageTimestamp != 5000)
	{
		return false;
	}

	if(trackToTest->eventArrayHead->midiMessage[0] != 0x71)
	{
		return false;
	}

	if(trackToTest->eventArrayHead->midiMessage[0] != 0x3C)
	{
		return false;
	}

	if(trackToTest->eventArrayHead->midiMessage[0] != 0x7F)
	{
		return false;
	}

	return true;

}

//insert track into pattern
bool memControlTest3()
{
	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
			return false;
	}

	addTrack(activeProject->patternArrayHead);

	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
			return false;
	}

	track_t* trackToTest = &(activeProject->patternArrayHead->trackArray[1]); //we should already have a track, we're adding a second one.

	if(	trackToTest->channel != 0 ||
	trackToTest->eventArrayHead != 0 ||
	trackToTest->forwardLink != 0 ||
	trackToTest->outPort != 0 ||
	trackToTest->playHead != 0)
	{
		return false;

	}


	return true;

}

//insert pattern into project
bool memControlTest4()
{
	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
			return false;
	}


	void addPattern_p(activeProject);

	if(!blankMemoryChecker(activeMemPoolHead, activeMemPoolTail))
	{
			return false;
	}

//We should probably look at some other stuff here too.

	return false;
}

//insert Pattern into song, song exists
bool memControlTest5()
{
	return false;
}

//insert song
bool memControlTest6()
{
	return false;
}

//pattern insert into song, no song exists
bool memControlTest7()
{
	return false;
}

//random insert test
bool memControlTest8()
{
	return false;
}

//de-initialize any allocated memory. Erase full SDRAM chip.
void eraseMemory()
{


}



