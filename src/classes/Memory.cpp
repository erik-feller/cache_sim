/*
 * Memory.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#include "Memory.h"


Memory::Memory(memConf conf) {
    this->config = conf;
}

unsigned int Memory::access(unsigned int blocksize){
    //Return the access time
    return (this->config.sendaddr+this->config.ready+(this->config.chunktime*(blocksize/this->config.chunksize)));
}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
    delete(&(this->config));
}

