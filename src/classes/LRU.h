/*
 * LRU.h
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#ifndef LRU_H_
#define LRU_H_


struct LruNode{
    unsigned int way;
    LruNode * next;
};


class LRU {
private:
    struct LruNode * head;
public:
	LRU();
	virtual ~LRU();
    void update(unsigned int t_way);
    unsigned int fetch();
};


#endif /* LRU_H_ */
