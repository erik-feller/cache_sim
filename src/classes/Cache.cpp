/*
 * Cache.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "Cache.h"



Cache::Cache() {
	//nothing special here...
}

Cache::~Cache() {
	//again, nothing special
}

void Cache::getTrackingData(void){
	//calculate percentages
	float hitRate = (this->track.hitCount / this->track.totalReq) *100;
	float missRate = (this->track.missCount / this->track.totalReq) *100;


	cout << "Memory Level: " << this->track.name << endl;
	cout << "  " << "Hit Count = " << this->track.hitCount << "  Miss Count = " << this->track.missCount << endl;
	cout << "  " << "Total Requests = " << this->track.totalReq << endl;
	cout << "  " << "Hit Rate = " << hitRate << "%  Miss Rate = " << missRate << "%" << endl;
	cout << "  " << "Kickouts = " << this->track.kickouts << "  Dirty Kickouts = " << this->track.dirtyKickouts << endl;
	cout << "  " << "Transfers = " << this->track.transfers << endl;
	cout << "  " << "VC Hit Count = " << this->track.vcHitCount << endl;
}




