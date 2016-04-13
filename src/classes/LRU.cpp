/*
 * LRU.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "LRU.h"
#include <cstddef>

LRU::LRU(int num_ways) {
	// TODO create a data structure for the buffer
    if(num_ways <= 0){
        //printf("Invalid number of ways given");
        return;
    }
    else if(num_ways == 1){
        //printf("Theres really no point in having an LRU for a 1 way cache");
        return;
    }
    else{
        LruNode* headt = new LruNode;
        headt->way = 1;
        headt->next = nullptr;
        this->head = headt;
        LruNode* last = nullptr;
        for(int i = 2; i <= num_ways; ++i){
            LruNode* tmp = new LruNode;
            tmp->way = i;
            tmp->next = nullptr;
            last->next = tmp;
            last = tmp;
        }
    }

}

LRU::~LRU() {
	// TODO Auto-generated destructor stub
    LruNode* current = nullptr; //set up current node
    LruNode* ahead = head; //set ahead to fall into head pointer
    while(ahead != nullptr){
        //Delete current node and move on
        current = ahead;
        ahead = current->next;
        delete current;
    }
}

void LRU::update(int t_way){
    LruNode* back = nullptr;
    LruNode* curr = head;
    LruNode* ahead = curr->next; 
    while(curr->way != t_way && ahead != nullptr){
        //step through the LRU until the way is found
        back = curr;
        curr = ahead;
        ahead = curr->next;
    }
    if(curr == head){
        //The buffer is already correct
        return;
    }
    else{
        back->next = ahead;
        curr->next = head;
        head = curr;
    }

}

int LRU::fetch(){
   //Search to determine which way to kick 
   LruNode* curr = this->head;
   while(curr->next != nullptr){
       curr = curr->next;
   }