/*
 * Cache.h
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#ifndef CACHE_H_
#define CACHE_H_

#include <map>
#include <string>
#include "LRU.h"
#include "Dictionary.h"


using namespace std;

struct config{
	int blockSize;
	int cacheSize;
	int assoc;
	int hitTime;
	int missTime;
};




class Cache {
public:
	Cache(Cache* nextLevel, struct config conf);
	virtual ~Cache();

private:
	//the next level in the cache
	Cache* next;


	//data tracking member variables
	unsigned long long int hitCount;
	unsigned long long int missCount;
	unsigned long long int kickouts;
	unsigned long long int dirtyKickouts;
	unsigned long long int transfers;
	unsigned long long int vcHitCount;



};

#endif /* CACHE_H_ */
