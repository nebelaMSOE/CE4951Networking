/*
 * tuner.c
 *
 *  Created on: Feb 11, 2020
 *      Author: navinj
 *
 *  Function definitions in using the reference tuner
 *  Includes static helper functions
 */

#include <inttypes.h>
#include "tuner.h"
#include "timer.h"
#include "delay.h"
#include "lcd.h"
#include "keypad.h"
#include "rotary.h"

/*
 * Current note being used by the tuner
 */
static NOTE currentNote = C4;

/*
 * Gets the frequency of a note
 *
 * note: NOTE enum to get frequency from
 */
static uint32_t getFreq(NOTE note);

/*
 * Gets the Name of a note
 *
 * note: NOTE enum to get name from
 */
static char* getNoteName(NOTE note);

/*
 * Sets the note, printing the set not name to the lcd
 *
 * note: NOTE enum to set
 */
static void setNote(NOTE note);

/*
 * Startup sequence of the tuner, including title and instructions
 */
static void startup();

/*
 * Tuner sequence including all function calls to run tuner
 *
 * Called from main function
 */
void tuner_sequence(){

	timer_init();
	keypad_init();
	lcd_init();
	rotary_init();

	currentNote = C4;

	uint8_t speakerState = 0;
	uint8_t rotaryState = 0;
	timer_setSound(getFreq(currentNote));

	startup();

	while (1){
		uint8_t key = keypad_getKey();
		if (key == 4){
			if (speakerState == 0){
				timer_play();
				speakerState = 1;
				lcd_clear();
				lcd_printString("Speaker On");
			} else {
				timer_stop();
				speakerState = 0;
				lcd_clear();
				lcd_printString("Speaker Off");
			}
		}
		if (key == 8){
			if (rotaryState == 0){
				rotary_enable();
				rotaryState = 1;
				lcd_clear();
				lcd_printString("Dial On");
			} else {
				rotary_disable();
				rotaryState = 0;
				lcd_clear();
				lcd_printString("Dial Off");
			}
		}
		if(key == 12){
			lcd_clear();
			rotary_disable();
			rotaryState = 0;
			lcd_clear();
			lcd_printString("Note Index");
			lcd_setPosition(0, 1);
			lcd_printString("Adjustment Mode");
			delay_1s(2);
			lcd_clear();
			NOTE newNote = 0;
			lcd_printString("Enter Octave: ");
			lcd_setPosition(0, 0);

			uint8_t octKey = keypad_getKey();
			lcd_printChar(keypad_getChar(octKey));
			delay_1ms(500);
			if (keypad_getNum(octKey) > 8){
				newNote += (12*8);
			} else {
				newNote += (12*keypad_getNum(octKey));
			}

			lcd_clear();
			lcd_printString("Enter Index:");
			lcd_setPosition(0, 0);

			uint8_t noteIndex = 0;
			uint8_t ind1 = keypad_getKey();
			lcd_printChar(keypad_getChar(ind1));
			noteIndex += (keypad_getNum(ind1)*10);

			uint8_t ind2 = keypad_getKey();
			lcd_printChar(keypad_getChar(ind2));
			noteIndex += (keypad_getNum(ind2));
			if (noteIndex > 11){
				noteIndex = 11;
			}

			newNote += noteIndex;
			delay_1ms(500);
			currentNote = newNote;
			setNote(currentNote);
		}
		if (key == 16){
			rotary_disable();
			rotaryState = 0;
			lcd_clear();
			lcd_printString("Frequency");
			lcd_setPosition(0, 1);
			lcd_printString("Adjustment Mode");
			delay_1s(2);
			uint32_t freq = 0;
			lcd_clear();
			lcd_printString("Enter Freq:");
			lcd_setPosition(0, 0);

			uint8_t in1 = keypad_getKey();
			lcd_printChar(keypad_getChar(in1));
			freq += (keypad_getNum(in1)*1000);

			uint8_t in2 = keypad_getKey();
			lcd_printChar(keypad_getChar(in2));
			freq += (keypad_getNum(in2)*100);

			uint8_t in3 = keypad_getKey();
			lcd_printChar(keypad_getChar(in3));
			freq += (keypad_getNum(in3)*10);

			uint8_t in4 = keypad_getKey();
			lcd_printChar(keypad_getChar(in4));
			freq += (keypad_getNum(in4));

			delay_1ms(500);
			timer_setSound(freq);
			lcd_clear();
			lcd_printString("Current Freq:");
			lcd_setPosition(0, 0);
			lcd_printNum(freq);
			lcd_printString("Hz");
		}
	}
}

/*
 * Steps up the note being played by the speaker
 */
void tuner_stepUp(){
	if (currentNote != Eb8){
		currentNote++;
	}
	setNote(currentNote);
}

/*
 * Steps down the note being played by the speaker
 */
void tuner_stepDown(){
	if (currentNote != C0){
		currentNote--;
	}
	setNote(currentNote);
}

static void startup(){
	lcd_clear();
	lcd_printString("Reference Tuner");
	lcd_setPosition(0, 0);
	lcd_printString("Ver 1.0");
	delay_1s(2);

	lcd_clear();
	lcd_printString("Created by:");
	lcd_setPosition(0, 4);
	lcd_printString("Josh Navin");
	delay_1s(2);

	lcd_clear();
	lcd_printString("Instructions:");
	delay_1s(2);

	lcd_clear();
	lcd_printString("A-Toggle Sound");
	delay_1s(2);

	lcd_clear();
	lcd_printString("B-Dial Toggle");
	delay_1s(2);

	lcd_clear();
	lcd_printString("C-Set Using");
	lcd_setPosition(0, 0);
	lcd_printString("Note Index");
	delay_1s(2);

	lcd_clear();
	lcd_printString("D-Set Using");
	lcd_setPosition(0, 0);
	lcd_printString("Frequency");
	delay_1s(2);

	lcd_clear();
}

static void setNote(NOTE note){
	lcd_clear();
	lcd_printString("Current Note: ");
	lcd_setPosition(0, 0);
	lcd_printString(getNoteName(note));
	timer_setSound(getFreq(note));
}

static uint32_t getFreq(NOTE note){
	uint32_t frequency = 1000;

	switch(note)
	{
	case C0: frequency = 16; break;
	case Db0: frequency = 17; break;
	case D0: frequency = 18; break;
	case Eb0: frequency = 19; break;
	case E0: frequency = 21; break;
	case F0: frequency = 22; break;
	case Gb0: frequency = 23; break;
	case G0: frequency = 25; break;
	case Ab0: frequency = 26; break;
	case LA0: frequency = 28; break;
	case Bb0: frequency = 29; break;
	case B0: frequency = 31; break;
	case C1: frequency = 33; break;
	case Db1: frequency = 35; break;
	case D1: frequency = 37; break;
	case Eb1: frequency = 39; break;
	case E1: frequency = 41; break;
	case F1: frequency = 44; break;
	case Gb1: frequency = 46; break;
	case G1: frequency = 49; break;
	case Ab1: frequency = 52; break;
	case LA1: frequency = 55; break;
	case Bb1: frequency = 58; break;
	case B1: frequency = 62; break;
	case C2: frequency = 65; break;
	case Db2: frequency = 69; break;
	case D2: frequency = 73; break;
	case Eb2: frequency = 78; break;
	case E2: frequency = 82; break;
	case F2: frequency = 87; break;
	case Gb2: frequency = 93; break;
	case G2: frequency = 98; break;
	case Ab2: frequency = 104; break;
	case LA2: frequency = 110; break;
	case Bb2: frequency = 117; break;
	case B2: frequency = 123; break;
	case C3: frequency = 131; break;
	case Db3: frequency = 139; break;
	case D3: frequency = 147; break;
	case Eb3: frequency = 156; break;
	case E3: frequency = 165; break;
	case F3: frequency = 175; break;
	case Gb3: frequency = 185; break;
	case G3: frequency = 196; break;
	case Ab3: frequency = 208; break;
	case LA3: frequency = 220; break;
	case Bb3: frequency = 233; break;
	case B3: frequency = 247; break;
	case C4: frequency = 262; break;
	case Db4: frequency = 277; break;
	case D4: frequency = 294; break;
	case Eb4: frequency = 311; break;
	case E4: frequency = 330; break;
	case F4: frequency = 349; break;
	case Gb4: frequency = 370; break;
	case G4: frequency = 392; break;
	case Ab4: frequency = 415; break;
	case LA4: frequency = 440; break;
	case Bb4: frequency = 466; break;
	case B4: frequency = 494; break;
	case C5: frequency = 523; break;
	case Db5: frequency = 554; break;
	case D5: frequency = 587; break;
	case Eb5: frequency = 622; break;
	case E5: frequency = 659; break;
	case F5: frequency = 698; break;
	case Gb5: frequency = 740; break;
	case G5: frequency = 784; break;
	case Ab5: frequency = 831; break;
	case LA5: frequency = 880; break;
	case Bb5: frequency = 932; break;
	case B5: frequency = 988; break;
	case C6: frequency = 1047; break;
	case Db6: frequency = 1109; break;
	case D6: frequency = 1175; break;
	case Eb6: frequency = 1245; break;
	case E6: frequency = 1319; break;
	case F6: frequency = 1397; break;
	case Gb6: frequency = 1480; break;
	case G6: frequency = 1568; break;
	case Ab6: frequency = 1661; break;
	case LA6: frequency = 1760; break;
	case Bb6: frequency = 1865; break;
	case B6: frequency = 1976; break;
	case C7: frequency = 2093; break;
	case Db7: frequency = 2217; break;
	case D7: frequency = 2349; break;
	case Eb7: frequency = 2489; break;
	case E7: frequency = 2637; break;
	case F7: frequency = 2794; break;
	case Gb7: frequency = 2960; break;
	case G7: frequency = 3136; break;
	case Ab7: frequency = 3322; break;
	case LA7: frequency = 3520; break;
	case Bb7: frequency = 3729; break;
	case B7: frequency = 3951; break;
	case C8: frequency = 4186; break;
	case Db8: frequency = 4435; break;
	case D8: frequency = 4699; break;
	case Eb8: frequency = 4978; break;
	}

	return frequency;
}

static char* getNoteName(NOTE note){
	char* notename = "null";

	switch(note)
	{
	case C0: notename = "C0"; break;
	case Db0: notename = "Db0"; break;
	case D0: notename = "D0"; break;
	case Eb0: notename = "Eb0"; break;
	case E0: notename = "E0"; break;
	case F0: notename = "F0"; break;
	case Gb0: notename = "Gb0"; break;
	case G0: notename = "G0"; break;
	case Ab0: notename = "Ab0"; break;
	case LA0: notename = "LA0"; break;
	case Bb0: notename = "Bb0"; break;
	case B0: notename = "B0"; break;
	case C1: notename = "C1"; break;
	case Db1: notename = "Db1"; break;
	case D1: notename = "D1"; break;
	case Eb1: notename = "Eb1"; break;
	case E1: notename = "E1"; break;
	case F1: notename = "F1"; break;
	case Gb1: notename = "Gb1"; break;
	case G1: notename = "G1"; break;
	case Ab1: notename = "Ab1"; break;
	case LA1: notename = "LA1"; break;
	case Bb1: notename = "Bb1"; break;
	case B1: notename = "B1"; break;
	case C2: notename = "C2"; break;
	case Db2: notename = "Db2"; break;
	case D2: notename = "D2"; break;
	case Eb2: notename = "Eb2"; break;
	case E2: notename = "E2"; break;
	case F2: notename = "F2"; break;
	case Gb2: notename = "Gb2"; break;
	case G2: notename = "G2"; break;
	case Ab2: notename = "Ab2"; break;
	case LA2: notename = "LA2"; break;
	case Bb2: notename = "Bb2"; break;
	case B2: notename = "B2"; break;
	case C3: notename = "C3"; break;
	case Db3: notename = "Db3"; break;
	case D3: notename = "D3"; break;
	case Eb3: notename = "Eb3"; break;
	case E3: notename = "E3"; break;
	case F3: notename = "F3"; break;
	case Gb3: notename = "Gb3"; break;
	case G3: notename = "G3"; break;
	case Ab3: notename = "Ab3"; break;
	case LA3: notename = "LA3"; break;
	case Bb3: notename = "Bb3"; break;
	case B3: notename = "B3"; break;
	case C4: notename = "C4"; break;
	case Db4: notename = "Db4"; break;
	case D4: notename = "D4"; break;
	case Eb4: notename = "Eb4"; break;
	case E4: notename = "E4"; break;
	case F4: notename = "F4"; break;
	case Gb4: notename = "Gb4"; break;
	case G4: notename = "G4"; break;
	case Ab4: notename = "Ab4"; break;
	case LA4: notename = "LA4"; break;
	case Bb4: notename = "Bb4"; break;
	case B4: notename = "B4"; break;
	case C5: notename = "C5"; break;
	case Db5: notename = "Db5"; break;
	case D5: notename = "D5"; break;
	case Eb5: notename = "Eb5"; break;
	case E5: notename = "E5"; break;
	case F5: notename = "F5"; break;
	case Gb5: notename = "Gb5"; break;
	case G5: notename = "G5"; break;
	case Ab5: notename = "Ab5"; break;
	case LA5: notename = "LA5"; break;
	case Bb5: notename = "Bb5"; break;
	case B5: notename = "B5"; break;
	case C6: notename = "C6"; break;
	case Db6: notename = "Db6"; break;
	case D6: notename = "D6"; break;
	case Eb6: notename = "Eb5"; break;
	case E6: notename = "E6"; break;
	case F6: notename = "F6"; break;
	case Gb6: notename = "Gb6"; break;
	case G6: notename = "G6"; break;
	case Ab6: notename = "Ab6"; break;
	case LA6: notename = "LA6"; break;
	case Bb6: notename = "Bb6"; break;
	case B6: notename = "B6"; break;
	case C7: notename = "C7"; break;
	case Db7: notename = "Db7"; break;
	case D7: notename = "D7"; break;
	case Eb7: notename = "Eb7"; break;
	case E7: notename = "E7"; break;
	case F7: notename = "F7"; break;
	case Gb7: notename = "Gb7"; break;
	case G7: notename = "G7"; break;
	case Ab7: notename = "Ab7"; break;
	case LA7: notename = "LA7"; break;
	case Bb7: notename = "Bb7"; break;
	case B7: notename = "B7"; break;
	case C8: notename = "C8"; break;
	case Db8: notename = "Db8"; break;
	case D8: notename = "D8"; break;
	case Eb8: notename = "Eb8"; break;
	}

	return notename;
}
