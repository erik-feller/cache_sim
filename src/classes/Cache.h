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
#include "Victim.h"

using namespace std;

//a full address, split into index and tag
struct address{
	unsigned long long int index;
	unsigned long long int tag;
};


//struct for all configuration stuff
struct config{
	string name;
	int blockSize;
	int cacheSize;
	int assoc;
	int hitTime;
	int missTime;
	int numIndexes;
};

//struct for data tracking stuff
struct analyitcs{
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
	Cache(Cache* nextLevel, struct config conf);
	//time it takes to write (intended to be recursive)
	virtual int write(unsigned long long address) = 0;
	//time it takes to read (intended to be recursive)
	virtual int read(unsigned long long address) = 0;

	//transfer data?
	virtual void transfer() = 0;
	//get data analytics?
	void getTrackingData(void);
	//destructor
	virtual ~Cache();

private:
	//dirty kickout on a write
	virtual void dirtyKickout(void) = 0;
	//makes a tag-index pair from an address
	struct address makeTagIndex(unsigned long long address);

	//the next level in the cache
	Cache* next;

	//the config
	struct config conf;

	//important members
	Victim* v;			//victim cache
	LRU** lru;			//list of lru's indexed by index value
	Dictionary** d;		//list of dictionaries indexed by way

	//data tracking
	struct analyitcs track;

};

#endif /* CACHE_H_ */
