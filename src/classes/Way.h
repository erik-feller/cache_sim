/*
 * Way.h
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#ifndef CLASSES_WAY_H_
#define CLASSES_WAY_H_

#include "Cache.h"

//a full address, split into index, tag, block offset, and byte offset
struct address{
	unsigned int index;
	unsigned long long int tag;
	unsigned int byteOffset;
	unsigned int blockOffset;
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


class Way: public Cache {
public:
	Way(struct config conf);
	int read(unsigned long long address);
	virtual ~Way();

private:
	struct address makeTagIndex(unsigned long long int address);

	//the config
	struct config conf;

	//important members
	Victim* v;			//victim cache
	LRU** lru;			//list of lru's indexed by index value
	Dictionary** d;		//list of dictionaries indexed by way
};

#endif /* CLASSES_WAY_H_ */
