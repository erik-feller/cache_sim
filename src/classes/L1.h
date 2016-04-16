/*
 * L1.h
 *
 *  Created on: Apr 16, 2016
 *      Author: bryan
 */

#ifndef CLASSES_L1_H_
#define CLASSES_L1_H_

#include "Way.h"

using namespace std;

class L1: public Way {
public:
	L1(struct config conf);
	virtual ~L1();
};


#endif /* CLASSES_L1_H_ */
