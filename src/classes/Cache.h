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
#include <math.h>

#include "LRU.h"
#include "Dictionary.h"
#include "Victim.h"

using namespace std;


//struct for data tracking stuff
struct analyitcs{
	unsigned long long int totalReq;
	unsigned long long int hitCount;
	unsigned long long int missCount;
	unsigned long long int kickouts;
	unsigned long long int dirtyKickouts;
	unsigned long long int transfers;
	unsigned long long int vcHitCount;
};


//cache abstract class
class Cache {
public:
	//constructor
	Cache();

	//get data analytics?
	void getTrackingData(void);
	//destructor
	virtual ~Cache();

	//data tracking
	struct analyitcs track;

private:


};

#endif /* CACHE_H_ */
