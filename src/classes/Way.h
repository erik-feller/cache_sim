/*
 * Way.h
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#ifndef CLASSES_WAY_H_
#define CLASSES_WAY_H_

#include "Cache.h"

class Way: public Cache {
public:
	Way(Cache* nextLevel, struct config conf);
	virtual ~Way();
};

#endif /* CLASSES_WAY_H_ */
