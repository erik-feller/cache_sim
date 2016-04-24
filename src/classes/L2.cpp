/*
 * L2.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: bryan
 */

#include "L2.h"

L2::L2(Memory* nextLevel, struct config conf, struct L2TransConfig transConf): Way(conf){

	//store the parameters
	this->next = nextLevel;
	this->transConf = transConf;
	this->blockTransferTime = transConf.transferTime * (transConf.L1BlockSize / transConf.busWidth);
}


int L2::transferRead(unsigned long long int address){

	//check the main cache...
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

			//TODO: L2 return hit time + transfer time?
			return this->conf.hitTime + this->blockTransferTime;
		}
	}

	//miss
	this->track.missCount++;
//	this->track.transfers++;


	//it isn't in the main cache, look in victim...
	//find the thing that we are going to be throwing away (in L2 primary cache)
	int toReplace = 0;
	if(this->lru != NULL){
		toReplace = this->lru[addr.index]->fetch();
	}

	//get the cache elem in question
	struct cacheElem* elemToReplace = this->d[toReplace]->getItem(addr.index);
	//is this a kickout?
	if(elemToReplace->valid){
		this->track.kickouts++;
	}

//	if(elemToReplace->dirty){
//		this->track.dirtyKickouts++;
//		//TODO: handle dirty kickout here
//	}

	int dirtyDelay = 0;

	if(elemToReplace->valid){

		//check the victim cache
		int ret = this->v->swap(elemToReplace->tag, addr.index, addr.tag, addr.index, elemToReplace->dirty);

		struct VcacheElem* dirtyElem;
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
			dirtyDelay = this->next->access(this->conf.blockSize);
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
			this->d[toReplace]->setDirty(addr.index);
			return this->conf.hitTime;
			break;
		}
	}


	//if we make it to this point, the block isn't in the L2 cache. :(
	this->track.transfers++;
	int totalTime = this->conf.missTime;
	totalTime += dirtyDelay;
	totalTime += this->blockTransferTime;
    totalTime += this->conf.hitTime;

	//transfer the value from the next level (and get time it took to do that)
	//TODO: uncomment this for the analog memory function
	totalTime += this->next->access(conf.blockSize);


	//TODO: place the thrown out value into victim?

	//place the new element into the dictionary
	this->d[toReplace]->update(addr.index,addr.tag);

	//return the total time it took to do the full operation
	return totalTime;

}


int L2::transferWrite(unsigned long long int address){

	//I'm pretty certain that this is exactly the same as a transfer read...
	return transferRead(address);
}


int L2::dirtyKickout(unsigned long long int address){

	//check the main cache...
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

			this->d[i]->setDirty(addr.index);
			return this->conf.hitTime + this->blockTransferTime;
		}
	}


	//miss L2
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
			dirtyDelay += this->next->access(this->conf.blockSize);
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
			this->d[toReplace]->setDirty(addr.index);
			return this->conf.hitTime;
			break;
		}
	}


	//if we make it to this point, the block isn't in the L1 cache. :(
	int totalTime = this->conf.missTime;
	totalTime += this->conf.hitTime;
	totalTime += this->blockTransferTime;
	totalTime += dirtyDelay;

	//transfer the value from the next level (and get time it took to do that)
	totalTime += this->next->access(this->conf.blockSize);
	this->track.transfers++;

	//place the new element into the dictionary and set to dirty
	this->d[toReplace]->update(addr.index,addr.tag);
	this->d[toReplace]->setDirty(addr.index);

	//return the total time it took to do the full operation
	return totalTime;
}




L2::~L2() {
	// TODO: do I need to call ~Cache() here? I don't know...
}

