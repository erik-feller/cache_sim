/*
 * Memory.h
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#ifndef CLASSES_MEMORY_H_
#define CLASSES_MEMORY_H_

#include "Cache.h"

class Memory: public Cache {
public:
	Memory(Cache* nextLevel, struct config conf);
	virtual ~Memory();
};

#endif /* CLASSES_MEMORY_H_ */
