/*
 * L1.h
 *
 *  Created on: Apr 16, 2016
 *      Author: bryan
 */

#ifndef CLASSES_L1_H_
#define CLASSES_L1_H_

#include "Way.h"
#include "L2.h"

using namespace std;


class L1: public Way {
public:
	L1(L2* nextLevel, struct config conf);
	int read(unsigned long long int address);
	int write(unsigned long long int address);
	virtual ~L1();

private:
	unsigned long long int makeKickoutAddr(unsigned long long int tag, unsigned int index);
	L2* next;

};


#endif /* CLASSES_L1_H_ */
