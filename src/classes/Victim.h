/*
 * Victim.h
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#ifndef VICTIM_H_
#define VICTIM_H_

#include "Cache.h"

class Victim: public Cache{
public:
	Victim(Cache* nextLevel, struct config conf);
	virtual ~Victim();
};

#endif /* VICTIM_H_ */
