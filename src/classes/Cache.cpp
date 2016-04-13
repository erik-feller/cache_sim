/*
 * Cache.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "Cache.h"

#include "Victim.h"

Cache::Cache(Cache* nextLevel, struct config conf) {

	//store the next level of the cache
	this->next = nextLevel;

	//create the victim cache


	//create the dictionary(s)

	//create the LRU(s)

}

Cache::~Cache() {
	// TODO Auto-generated destructor stub
}

