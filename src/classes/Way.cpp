/*
 * Way.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#include "Way.h"

Way::Way(struct config conf){
	//store the next level of the cache

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
	else{
		this->lru = NULL;
	}

}


int Way::read(unsigned long long int address){

	//grab tag/index from address
	struct address addr = this->makeTagIndex(address);

	//check each way to see if it is in the cache
	for(int i=0;i<this->conf.assoc;++i){
		if(this->d[i]->check(addr.index,addr.tag)){

			//update the lru
			this->lru[addr.index]->update(i);

			//return the hit time
			return this->conf.hitTime;
		}
	}

	//check the victim cache
//	if(this->v->check(address)){
//		//TODO: do the replacement thing
//
//		return this->conf.hitTime;
//	}


	//if we make it to this point, the block isn't in the cache. :(
	int totalTime = this->conf.missTime;

	//do stuff with the victim cache (throw away the bottom of the stack

	//transfer the value from the next level (and get time to do that)

	//place the thrown out value into victim

	return totalTime;


}

struct address Way::makeTagIndex(unsigned long long int address){
	//split the original address into a tag and an index

	//initialize
	struct address ret;

	//get the sizes of things
	int sizeByteOffset = 2;
	int sizeBlockOffset = log2(this->conf.blockSize);
	int sizeIndex = log2(this->conf.cacheSize/this->conf.blockSize/this->conf.assoc);
	int sizeTag = 64 - sizeByteOffset - sizeIndex - sizeBlockOffset;

	//shift things around to get the values
	ret.tag = address >> (sizeByteOffset + sizeBlockOffset + sizeIndex);
	ret.index = (address << sizeTag) >> (sizeTag+sizeByteOffset+sizeBlockOffset);
	ret.blockOffset = (address << (sizeTag+sizeIndex)) >> (sizeTag+sizeIndex+sizeByteOffset);
	ret.byteOffset = (address << (sizeTag+sizeIndex+sizeBlockOffset)) >> (sizeTag+sizeIndex+sizeBlockOffset);

	return ret;


}


Way::~Way() {

	//delete victim cache
	delete this->v;

	//delete dictionaries
	for(int i=0;i<conf.assoc;++i){
		delete this->d[i];
	}
	//delete list of dictionaries
	delete this->d;


	if (this->lru != NULL){
		//delete the lru's
		for(int i=0; i<this->conf.numIndexes; ++i){
			delete this->lru[i];
		}

		//delete the list of lru's
		delete this->lru;
	}
}

