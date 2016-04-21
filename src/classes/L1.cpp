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
	//is this a kickout?
	if(elemToReplace->valid){
		this->track.kickouts++;
	}

	if(elemToReplace->dirty){
		this->track.dirtyKickouts++;
		//TODO: handle dirty kickout here
	}


	//check the victim cache
	int ret = this->v->swap(elemToReplace->tag, addr.index, addr.tag, addr.index, elemToReplace->dirty);
	switch(ret){
	//miss clean evict
	case 0:
		//no need to do any write back, need to handle the miss
		break;

	//miss dirty evict
	case 1:
		//do dirty kickout and handle miss
		break;

	//hit clean evict
	case 2:
		//just return the hit time
		this->track.hitCount++;
		return this->conf.hitTime;
		break;

	//hit dirty evict
	case 3:
		//return hit time
		this->track.hitCount++;
		return this->conf.hitTime;//TODO: + dirty kickout transfer?
		break;
	}

	//if we make it to this point, the block isn't in the L1 or victim. :(
	int totalTime = this->conf.missTime;

	//transfer the value from the next level (and get time it took to do that)
	totalTime += this->next->transferRead(address);
	this->track.transfers++;


	//TODO: place the thrown out value into victim?

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
	//is this a kickout?
	if(elemToReplace->valid){
		this->track.kickouts++;
	}

	if(elemToReplace->dirty){
		this->track.dirtyKickouts++;
		//TODO: handle dirty kickout here
	}


	//check the victim cache
	int ret = this->v->swap(elemToReplace->tag, addr.index, addr.tag, addr.index, elemToReplace->dirty);
	switch(ret){
	//miss clean evict
	case 0:
		//no need to do any write back, need to handle the miss
		break;

	//miss dirty evict
	case 1:
		//do dirty kickout and handle miss
		break;

	//hit clean evict
	case 2:
		//just return the hit time
		this->track.hitCount++;
		return this->conf.hitTime;
		break;

	//hit dirty evict
	case 3:
		//return hit time
		this->track.hitCount++;
		return this->conf.hitTime;//TODO: + dirty kickout transfer?
		break;
	}


	//if we make it to this point, the block isn't in the L1 cache. :(
	int totalTime = this->conf.missTime;

	//transfer the value from the next level (and get time it took to do that)
	totalTime += this->next->transferWrite(address);
	this->track.transfers++;


	//TODO: place the thrown out value into victim?

	//place the new element into the dictionary and set to dirty
	this->d[toReplace]->update(addr.index,addr.tag);
	this->d[toReplace]->setDirty(addr.index);

	//return the total time it took to do the full operation
	return totalTime;


}


L1::~L1() {
	// TODO: do I need to call ~Cache() here? I don't know...
}

