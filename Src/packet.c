/*
 * packet.c
 *
 *  Created on: Nov 1, 2021
 *      Author: nebela
 */

#include <inttypes.h>
#include <stdio.h>
#include "packet.h"
#include <string.h>

volatile PACKET packetStructure;
volatile PACKET* packet = &packetStructure;


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
//	packet->data = data;
	strcpy((char* ) &packet->inner[6], data);
}

char* getData(){
//	return packet->data;
	return (char*) &packet->inner[6];
}

void setCRC8FCS(){
	uint8_t crc8FCS_offset = packet->length + 7;
	if(packet->crcFlag == 1){
		uint8_t val = 0;

		uint8_t * pos = (uint8_t *) packet->data;
		uint8_t * end = pos + packet->length;

		while (pos < end) {
			val = CRC_TABLE[val ^ *pos];
			pos++;
		}

		packet->inner[crc8FCS_offset] = val;
	} else {
		packet->inner[crc8FCS_offset] = 0xAA;
	}
}

uint8_t getCRC8FCS(){
	uint8_t crc8FCS_offset = packet->length + 7;
	return packet->inner[crc8FCS_offset];
}
