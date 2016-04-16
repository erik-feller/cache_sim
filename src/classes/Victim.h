/*
 * Victim.h
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#ifndef VICTIM_H_
#define VICTIM_H_

#include "Dictionary.h"

class Victim{
public:
	Victim();
	//returns if an item is present in the victim cache, and the location (-1 if not in, otherwise [0-7]
	int check(unsigned long long int address);
	//replace an entry in the victim cache
	void replace(int location, unsigned long long int newAddr);


	virtual ~Victim();


private:

	//dirty kickout

	//i dont know...


	//the entries of the victim cache
	unsigned long long int entries[8];

};

#endif /* VICTIM_H_ */
