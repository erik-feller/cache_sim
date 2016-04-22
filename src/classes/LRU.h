/*
 * LRU.h
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#ifndef LRU_H_
#define LRU_H_

struct LruNode{
    int way;
    LruNode *next;
};

class LRU {
private:
    LruNode *head;
public:
	LRU(int num_ways);
	virtual ~LRU();
    void update(int t_way);
    int fetch();
};



#endif /* LRU_H_ */
