/*
 * Victim.h
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan
 */

#ifndef VICTIM_H_
#define VICTIM_H_

#include "Dictionary.h"

struct VcacheElem{
    unsigned long long int tag;
    unsigned int index;
    bool valid;
    bool dirty;
};

struct VicNode{
    VcacheElem* element;
    VicNode* next;
};

class Victim{
public:
    //Creator
	Victim();
	//replace an entry in the victim cache
	bool swap(unsigned long long int oldTag, unsigned int oldIndex, unsigned long long int newTag, unsigned int newIndex);
    //destructor
	virtual ~Victim();


private:
    
    VicNode* head;
    //returns if an item is present in the victim cache, and the location (-1 if not in, otherwise [0-7]
	bool check(unsigned long long int tarTag, unsigned int tarIndex);
    //Add item to the chache. Kickout the least recent member
    bool push(unsigned long long int tarTag, unsigned int tarIndex);
	//dirty kickout
    //re-order
    void reorder();
    //check for addr

	//i dont know...



};

#endif /* VICTIM_H_ */
