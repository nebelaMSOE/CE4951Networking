/*
 * packet.c
 *
 *  Created on: Nov 1, 2021
 *      Author: nebela
 */

#include <inttypes.h>
#include <stdio.h>
#include "packet.h"

typedef struct
{
	uint8_t preamble;
	uint8_t version;
	uint8_t source;
	uint8_t destination;
	uint8_t length; //value 1 to 255
	uint8_t crcFlag;
	char *data; //between size 1 and 255
	uint8_t crc8FCS;
} PACKET;

static volatile PACKET packetStructure;
static volatile PACKET* packet = &packetStructure;


void setPreamble(uint8_t preamble){
	//packet->preamble = preamble;
	//preamble always 0x55
	packet->preamble = 0x55;
}

uint8_t getPreamble(){
	return packet->preamble;
}

void setVersion(uint8_t version){
	packet->version = version;
}

uint8_t getVersion(){
	return packet->version;
}

void setSource(uint8_t source){
	packet->source = source;
}

uint8_t getSource(){
	return packet->source;
}

void setDestination(uint8_t destination){
	packet->destination = destination;
}


uint8_t getDestination(){
	return packet->destination;
}

void setLength(uint8_t length){
	packet->length = length;
}

uint8_t getLength(){
	return packet->length;
}

void setCRCFlag(uint8_t crcFlag){
	packet->crcFlag = crcFlag;
}

uint8_t getCRCFlag(){
	return packet->crcFlag;
}

void setData(char* data){
	packet->data = data;
}

char* getData(){
	return packet->data;
}

void setCRC8FCS(){
	uint8_t val = 0;

	uint8_t * pos = (uint8_t *) packet->data;
	uint8_t * end = pos + packet->length;

	while (pos < end) {
		val = CRC_TABLE[val ^ *pos];
		pos++;
	}

	packet->crc8FCS = val;
}

uint8_t getCRC8FCS(){
	return packet->crc8FCS;
}
