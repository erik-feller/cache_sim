/*
 * Memory.h
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#ifndef CLASSES_MEMORY_H_
#define CLASSES_MEMORY_H_

#include "Cache.h"

struct memConf{
    unsigned int sendaddr;
    unsigned int ready;
    unsigned int chunktime;
    unsigned int chunksize;
};

class Memory: public Cache {
public:
	Memory(memConf conf);
    //Method to read or write
    unsigned int access(unsigned int blocksize);
	virtual ~Memory();

private:
    struct memConf config; //create config settings

};

#endif /* CLASSES_MEMORY_H_ */
