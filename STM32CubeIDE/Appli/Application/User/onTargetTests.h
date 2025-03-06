/*
 * onTargetTests.h
 *
 *  Created on: Mar 2, 2025
 *      Author: OurBl
 */

#ifndef APPLICATION_USER_ONTARGETTESTS_H_
#define APPLICATION_USER_ONTARGETTESTS_H_

#include <stdint.h>
#include "HSQStructs.h"
#include "memControl.h"

#define bool uint8_t
#define true 1
#define false 0

bool runTests();
uint8_t blankMemoryChecker(midiEvent_t *head, midiEvent_t *tail);
void testErrorState();


bool memControlTest1();
bool memControlTest2();
bool memControlTest3();
bool memControlTest4();
bool memControlTest5();
bool memControlTest6();
bool memControlTest7();
bool memControlTest8();
void eraseMemory();




#endif /* APPLICATION_USER_ONTARGETTESTS_H_ */
