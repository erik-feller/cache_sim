/*
 * CacheSystem.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "CacheSystem.h"

CacheSystem::CacheSystem(map<string,int> conf) {








	//calculate cost of system
	//L1
	this->L1Cost = (conf["L1_cache_size"] / 4096) * 100;
	if (conf["L1_assoc"] != 1){
		this->L1Cost += (conf["L1_assoc"] / 2) *100;
	}
	//L2
	this->L2Cost = (conf["L2_cache_size"] / 16384) * 50;
	if (conf["L2_assoc"] != 1){
		this->L2Cost += (conf["L2_assoc"] / 2) * 50;
	}
	//memory
	int memLatencyCost = 50;
	if (conf["mem_ready"] != 50){
		memLatencyCost += 200*(50/conf["mem_ready"]/2);
	}
	int memBandCost = 25;
	if (conf["mem_chunksize"] != 8){
		memBandCost += 100*((conf["mem_chunksize"]/8)-1);
	}
	this->memCost = memLatencyCost + memBandCost;

	//total cost
	this->totalCost = this->L1Cost + this->L2Cost + this->memCost;



}

void CacheSystem::reportCost(void) {
	cout << "L1 cache cost (Icache $" << this->L1Cost <<
			") + (Dcache $" << this->L1Cost << ") = $" << this->L1Cost*2 << endl;
	cout << "L2 cache cost = $" << this->L2Cost;
	cout << "; Memory cost = $" << this->memCost;
	cout << "; Total cost = $" << this->totalCost << endl;

}

CacheSystem::~CacheSystem() {
	// TODO Auto-generated destructor stub
}

