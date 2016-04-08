/*
 * LRU.h
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#ifndef LRU_H_
#define LRU_H_

class LRU {
private:
    LruNode * head;
public:
	LRU();
	virtual ~LRU(unsigned int num_ways);
    void update(unsigned int t_way);
    unsigned int fetch();
};

struct LruNode{
    unsigned int way;
    LruNode * next;
}

#endif /* LRU_H_ */
