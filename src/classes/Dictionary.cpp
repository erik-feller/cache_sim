/*
 * Cache.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "Dictionary.h"

//TODO: need to figure out how to utilize the dirty bit

//constructor...
Dictionary::Dictionary(unsigned int nIndexes) {

	//populate the dictionary from 0-nIndexes
	for (unsigned int i=0; i<=nIndexes; ++i){
		//create the new cache element
		this->dict[i] = new struct cacheElem;

		//set default values
		this->dict[i]->tag = 0;
		this->dict[i]->valid = false;
		this->dict[i]->dirty = false;
	}

	//set the number of indexes (for future use)
	this->nIndexes = nIndexes;
}

//checks to see if a certain index contains the tag (valid)
bool Dictionary::check(unsigned int index, unsigned int checkTag){

	//grab the cache element
	struct cacheElem * elem = this->dict[index];

	//is the element valid?
	if (elem->valid == false){
		return false;
	}

	//is the tag correct?
	if (elem->tag != checkTag){
		//does not equal the tag
		return false;
	}
	else{
		//the cache element's tag equals the desired tag
		return true;
	}
}

//change the specified index to the new tag
void Dictionary::update(unsigned int index, unsigned int newTag){

	//grab the cache element
	struct cacheElem * elem = this->dict[index];

	//set the new value in the dictionary
	elem->tag = newTag;

	//set valid bit
	elem->valid = true;
}

//flush the cache
void Dictionary::flush(void){

	//set all of the valid bits to false
	for (unsigned int i=0; i<=this->nIndexes; ++i){
		this->dict[i]->valid = false;
	}
}

//destructor
Dictionary::~Dictionary() {

	//clean up the dictionary
	for (unsigned int i=0; i<this->nIndexes; ++i){
		delete this->dict[i];
	}
}

