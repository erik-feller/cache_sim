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

using namespace std;


class CacheSystem {
public:
	CacheSystem(map<string,int> conf);
	void reportCost(void);
	virtual ~CacheSystem();

private:
	//data analytics stuff...


	//cost stuff...
	void calcCost(map<string,int> conf);
	int L1Cost;
	int L2Cost;
	int memCost;
	int totalCost;
	//probably some other stuff. I don't know
};

#endif /* CACHESYSTEM_H_ */
