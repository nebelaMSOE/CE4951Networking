/*
 * packet.h
 *
 *  Created on: Nov 1, 2021
 *      Author: nebela
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <inttypes.h>

void setPreamble(uint8_t preamble);

uint8_t getPreamble();

void setVersion(uint8_t version);

uint8_t getVersion();

void setSource(uint8_t source);

uint8_t getSource();

void setDestination(uint8_t destination);

uint8_t getDestination();

void setLength(uint8_t length);

uint8_t getLength();

void setCRCFlag(uint8_t crcFlag);

uint8_t getCRCFlag();

void setData(char* data);

char* getData();

void setCRC8FCS();

uint8_t getCRC8FCS();



#endif /* PACKET_H_ */
