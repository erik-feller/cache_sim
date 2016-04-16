/*
 * L2.h
 *
 *  Created on: Apr 16, 2016
 *      Author: bryan
 */

#ifndef CLASSES_L2_H_
#define CLASSES_L2_H_

#include "Way.h"

class L2: public Way {
public:
	L2(struct config conf);
	virtual ~L2();
};

#endif /* CLASSES_L2_H_ */
