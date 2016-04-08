/*
 * LRU.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "LRU.h"

//LRU::LRU(unsigned int num_ways) {
//	// TODO create a data structure for the buffer
//    if(num_ways <= 0){
//        printf("Invalid number of ways given");
//        return
//    }
//    else if(num_ways == 1){
//        printf("Theres really no point in having an LRU for a 1 way cache");
//        return
//    }
//    else{
//        headt = new LruNode;
//        headt.way = 1;
//        headt.next = NULL;
//        LruNode* last = &head;
//        for(i = 2; i <= num_ways; ++i){
//            tmp = new LruNode;
//            tmp.way = i;
//            tmp.next = NULL;
//            *last.next = &tmp;
//            last = &tmp;
//        }
//    }
//
//}
//
//LRU::~LRU() {
//	// TODO Auto-generated destructor stub
//    LruNode* ahead = &head;
//    while(ahead != NULL){
//        LruNode* current = ahead;
//        ahead = current.next;
//        delete current;
//    }
//}
//
//LRU::void update(unsigned int t_way){
//    LruNode* back = NULL;
//    LruNode* ahead = NULL;
//    LruNode* curr = head;
//    while(*curr.way != t_way){
//
//    }
//    if(curr == &head){
//        //The buffer is alread correct
//        return;
//    }
//    else{
//        *back.next = ahead;
//        *curr.next = head;
//        head = curr;
//    }
//
//}
//
//LRU::unsigned int fetch(){
//
//}

