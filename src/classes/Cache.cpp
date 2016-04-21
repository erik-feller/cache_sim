/*
 * Cache.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "Cache.h"



Cache::Cache() {
	//nothing special here...
	this->initTracking();
}

void Cache::initTracking(void){
	this->track.dirtyKickouts=0;
	this->track.hitCount = 0;
	this->track.kickouts = 0;
	this->track.missCount = 0;
	this->track.name = "";
	this->track.totalReq = 0;
	this->track.transfers = 0;
	this->track.vcHitCount  = 0;
}

Cache::~Cache() {
	//again, nothing special
}

void Cache::getTrackingData(void){
	//calculate percentages
	float hitRate = ((float)this->track.hitCount / this->track.totalReq) *100;
	float missRate = ((float)this->track.missCount / this->track.totalReq) *100;


	cout << "Memory Level: " << this->track.name << endl;
	cout << "  " << "Hit Count = " << this->track.hitCount << "  Miss Count = " << this->track.missCount << endl;
	cout << "  " << "Total Requests = " << this->track.totalReq << endl;
	cout << "  " << "Hit Rate = " << hitRate << "%  Miss Rate = " << missRate << "%" << endl;
	cout << "  " << "Kickouts = " << this->track.kickouts << "  Dirty Kickouts = " << this->track.dirtyKickouts << endl;
	cout << "  " << "Transfers = " << this->track.transfers << endl;
	cout << "  " << "VC Hit Count = " << this->track.vcHitCount << endl;
	cout << endl;
}




