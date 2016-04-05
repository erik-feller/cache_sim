/*
 * LRU.h
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#ifndef LRU_H_
#define LRU_H_

class LRU {
public:
	LRU();
	virtual ~LRU();
};

struct LruNode{
    unsigned int way;
    LruNode * next;
}

#endif /* LRU_H_ */
