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

	this->conf.numIndexes = conf.cacheSize/conf.blockSize/conf.assoc;

	//create the dictionary(s)
	//the list to hold the pointers to dictionaries
	this->d = new Dictionary *[conf.assoc];
	//populate them
	for(int i=0;i<conf.assoc;++i){
		this->d[i] = new Dictionary(this->conf.numIndexes);
	}

	//create the LRU(s) if needed
	if(conf.assoc != 1){
		this->lru = new LRU *[this->conf.numIndexes];
		for(int i=0; i<this->conf.numIndexes; ++i){
			this->lru[i] = new LRU(conf.assoc);
		}
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

	//delete the lru's
	for(int i=0; i<this->conf.numIndexes; ++i){
		delete this->lru[i];
	}

	//delete the list of lru's
	delete this->lru;

}

