/*
 * L1.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: bryan
 */

#include "L1.h"



L1::L1(L2* nextLevel, struct config conf): Way(conf) {

	//store the location of the L2 cache
	this->next = nextLevel;

}


int L1::read(unsigned long long int address){

	//add to the total requests
	this->track.totalReq++;


	//grab tag/index from address
	struct address addr = this->makeTagIndex(address);

	//check each way to see if it is in the cache
	for(int i=0;i<this->conf.assoc;++i){
		if(this->d[i]->check(addr.index,addr.tag)){

			//add to the hits
			this->track.hitCount++;

			if (this->lru != NULL){
				//update the lru
				this->lru[addr.index]->update(i);
			}

			//return the hit time
			return this->conf.hitTime;
		}
	}

	//not in the L1 cache
	this->track.missCount++;

	//find the thing that we are going to be throwing away (in L1 primary cache)
	int toReplace = 0;
	if(this->lru != NULL){
		toReplace = this->lru[addr.index]->fetch();
	}

	//get the cache elem in question
	struct cacheElem* elemToReplace = this->d[toReplace]->getItem(addr.index);

	//init dirty delay
	int dirtyDelay = 0;

	//if the thing we are evicting from L1 is valid...
	if(elemToReplace->valid){

		//check the victim cache
		int ret = this->v->swap(elemToReplace->tag, addr.index, addr.tag, addr.index, elemToReplace->dirty);

		struct VcacheElem* dirtyElem;
		unsigned long long int dirtyAddr;
		switch(ret){
		//miss clean evict
		case 0:
			//no need to do any write back, need to handle the miss
			dirtyElem = this->v->check_dirt();
			if (dirtyElem == NULL){
				//invalid kickout, so don't need to do anything.
				break;
			}
			else{
				//this is a standard kickout
				this->track.kickouts++;
			}
			break;

		//miss dirty evict
		case 1:
			//do dirty kickout and handle miss
			this->track.dirtyKickouts++;
			//TODO: dirty kickout here!
			dirtyElem = this->v->check_dirt();
			dirtyAddr = this->makeKickoutAddr(dirtyElem->tag, dirtyElem->index);
			dirtyDelay = this->next->dirtyKickout(dirtyAddr);
			break;

		//hit clean evict
		case 2:
			//just return the hit time
			this->track.vcHitCount++;
			return this->conf.hitTime;
			break;

		//hit dirty evict
		case 3:
			//return hit time
			this->track.vcHitCount++;
			return this->conf.hitTime;
			break;
		}
	}

	//if we make it to this point, the block isn't in the L1 or victim. :(
	int totalTime = this->conf.missTime;
    totalTime += this->conf.hitTime;
    totalTime += dirtyDelay;

	//transfer the value from the next level (and get time it took to do that)
	totalTime += this->next->transferRead(address);
	this->track.transfers++;


	//place the new element into the dictionary
	this->d[toReplace]->update(addr.index,addr.tag);

	//return the total time it took to do the full operation
	return totalTime;

}


int L1::write(unsigned long long int address){

	//add to the total requests
	this->track.totalReq++;

	//grab tag/index from address
	struct address addr = this->makeTagIndex(address);

	//check each way to see if it is in the cache
	for(int i=0;i<this->conf.assoc;++i){
		if(this->d[i]->check(addr.index,addr.tag)){

			if (this->lru != NULL){
				//update the lru
				this->lru[addr.index]->update(i);
			}
			//hit
			this->track.hitCount++;

			//set to dirty
			this->d[i]->setDirty(addr.index);
			//return the hit time
			return this->conf.hitTime;
		}
	}

	//miss L1
	this->track.missCount++;


	//find the thing that we are going to be throwing away (in L1 primary cache)
	int toReplace = 0;
	if(this->lru != NULL){
		toReplace = this->lru[addr.index]->fetch();
	}

	//get the cache elem in question
	struct cacheElem* elemToReplace = this->d[toReplace]->getItem(addr.index);


	//init dirty delay
	int dirtyDelay = 0;

	//if the thing we are evicting from L1 is valid...
	if(elemToReplace->valid){

		//check the victim cache
		int ret = this->v->swap(elemToReplace->tag, addr.index, addr.tag, addr.index, elemToReplace->dirty);
		struct VcacheElem* dirtyElem;
		unsigned long long int dirtyAddr;
		switch(ret){
		//the kickout was invalid?
		//miss clean evict
		case 0:
			//no need to do any write back, need to handle the miss
			dirtyElem = this->v->check_dirt();
			if (dirtyElem == NULL){
				//invalid kickout, so don't need to do anything.
				break;
			}
			else{
				//this is a standard kickout
				this->track.kickouts++;
			}
			break;

		//miss dirty evict
		case 1:
			//do dirty kickout and handle miss
			this->track.dirtyKickouts++;
			//TODO: dirty kickout here!
			dirtyElem = this->v->check_dirt();
			dirtyAddr = this->makeKickoutAddr(dirtyElem->tag, dirtyElem->index);
			dirtyDelay = this->next->dirtyKickout(dirtyAddr);
			break;

		//hit clean evict
		case 2:
			//just return the hit time
			this->track.vcHitCount++;
			return this->conf.hitTime;
			break;

		//hit dirty evict
		case 3:
			//return hit time
			this->track.vcHitCount++;
			return this->conf.hitTime;
			break;
		}
	}


	//if we make it to this point, the block isn't in the L1 cache. :(
	int totalTime = this->conf.missTime;
	totalTime += this->conf.hitTime;
	totalTime += dirtyDelay;

	//transfer the value from the next level (and get time it took to do that)
	totalTime += this->next->transferWrite(address);
	this->track.transfers++;

	//place the new element into the dictionary and set to dirty
	this->d[toReplace]->update(addr.index,addr.tag);
	this->d[toReplace]->setDirty(addr.index);

	//return the total time it took to do the full operation
	return totalTime;

}

unsigned long long int L1::makeKickoutAddr(unsigned long long int tag, unsigned int index){

	//get the field sizes
	int sizeBlockOffset = log2(this->conf.blockSize);
	int sizeIndex = log2(this->conf.cacheSize/this->conf.blockSize/this->conf.assoc);
	int sizeTag = 64 - sizeIndex - sizeBlockOffset;

	//shift around the index to get rid of insignificant bits
	int indexShift = log2(this->next->conf.blockSize / this->conf.blockSize);
	index = (index >> indexShift) << indexShift;

	//init the return addr
	unsigned long long int retAddr = 0;

	//shift in the tag
	retAddr = retAddr | (tag << (sizeIndex + sizeBlockOffset));

	//shift in the index
	retAddr = retAddr | ((unsigned long long int) index << sizeBlockOffset);

	return retAddr;
}


L1::~L1() {
	//nothing to do here!
}

