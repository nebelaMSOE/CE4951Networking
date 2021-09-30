/*
 * tuner.h
 *
 *  Created on: Feb 11, 2020
 *      Author: navinj
 *
 * 	Function declaration of reference tuner functions
 */

#ifndef TUNER_H_
#define TUNER_H_

#include <inttypes.h>

/*
 * Defines all needed notes for use in playing sounds
 */
typedef enum {C0, Db0, D0, Eb0, E0, F0, Gb0, G0, Ab0, LA0, Bb0, B0,
	C1, Db1, D1, Eb1, E1, F1, Gb1, G1, Ab1, LA1, Bb1, B1,
	C2, Db2, D2, Eb2, E2, F2, Gb2, G2, Ab2, LA2, Bb2, B2,
	C3, Db3, D3, Eb3, E3, F3, Gb3, G3, Ab3, LA3, Bb3, B3,
	C4, Db4, D4, Eb4, E4, F4, Gb4, G4, Ab4, LA4, Bb4, B4,
	C5, Db5, D5, Eb5, E5, F5, Gb5, G5, Ab5, LA5, Bb5, B5,
	C6, Db6, D6, Eb6, E6, F6, Gb6, G6, Ab6, LA6, Bb6, B6,
	C7, Db7, D7, Eb7, E7, F7, Gb7, G7, Ab7, LA7, Bb7, B7,
	C8, Db8, D8, Eb8} NOTE;

/*
 * Main tuner sequence, runs all functionality from user input
 */
void tuner_sequence();

/*
 * Steps up the note played by the speaker
 */
void tuner_stepUp();

/*
 * Steps down the note played by the speaker
 */
void tuner_stepDown();

#endif /* TUNER_H_ */
