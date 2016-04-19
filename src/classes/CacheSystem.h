/*
 * CacheSystem.h
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#ifndef CACHESYSTEM_H_
#define CACHESYSTEM_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "L1.h"
#include "L2.h"
#include "Memory.h"

using namespace std;

struct sysAnalytics{
	unsigned long long int numReads;
	unsigned long long int numWrites;
	unsigned long long int numInst;
	unsigned long long int execTime;
};


class CacheSystem {
public:
	CacheSystem(map<string,int> conf);
	void newInstruction(char op, unsigned long long int address, unsigned int numBytes);
	void reportCost(void);
	virtual ~CacheSystem();

private:
	//get a list of addresses based on the base address and the number of bytes requested
	vector<unsigned long long int> getAddrList(unsigned long long int address, unsigned int numBytes);

	//data analytics stuff...
	struct sysAnalytics track;

	//cost stuff...
	void calcCost(map<string,int> conf);
	int costL1;
	int costL2;
	int costMem;
	int costTotal;


	//make the levels of the cache
	Memory* mem;
	L2* L2_cache;
	L1* L1d_cache;
	L1* L1i_cache;


	//figure out the number of calls to the L1 cache to make

};

#endif /* CACHESYSTEM_H_ */
