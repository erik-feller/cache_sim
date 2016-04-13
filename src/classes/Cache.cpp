/*
 * Cache.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "Cache.h"



Cache::Cache(Cache* nextLevel, struct config conf) {

	//store the next level of the cache
	this->next = nextLevel;
	this->conf = conf;

	//create the victim cache
	this->v = new Victim();

	//create the dictionary(s)
	//the list to hold the pointers to dictionaries
	this->d = new Dictionary *[conf.assoc];
	//populate them
	for(int i=0;i<conf.assoc;++i){
		this->d[i] = new Dictionary(conf.cacheSize/conf.blockSize/conf.assoc);
	}

	//create the LRU(s) if needed
	if(conf.assoc != 1){
		//somehow setup LRU to work on all of the indexes??? IDK..
	}

}

Cache::~Cache() {

	//delete victim cache
	delete this->v;

	//delete dictionaries
	for(int i=0;i<conf.assoc;++i){
		delete this->d[i];
	}
	//delete list of dictionaries
	delete this->d;

}

