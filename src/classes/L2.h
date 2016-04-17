/*
 * L2.h
 *
 *  Created on: Apr 16, 2016
 *      Author: bryan
 */

#ifndef CLASSES_L2_H_
#define CLASSES_L2_H_

#include "Way.h"
#include "Memory.h"

struct L2TransConfig{
	int transferTime;
	int busWidth;
	int L1BlockSize;
};



class L2: public Way {
public:
	L2(Memory* nextLevel, struct config conf, struct L2TransConfig transConf);
	int transferRead(unsigned long long int address);
	int transferWrite(unsigned long long int address);
	virtual ~L2();

private:
	//some private members
	Memory* next;
	struct L2TransConfig transConf;
	int blockTransferTime;
};

#endif /* CLASSES_L2_H_ */
