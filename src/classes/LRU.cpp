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
        headt->next = NULL;
        this->head = headt;
        LruNode* last = headt;
        for(unsigned int i = 2; i <= num_ways; ++i){
            LruNode* tmp = new LruNode;
            tmp->way = i;
            tmp->next = NULL;
            last->next = tmp;
            last = tmp;
        }
    }

}

LRU::~LRU() {
    //Set up handles for walking thru
    LruNode* current = NULL; //set up current node
    LruNode* ahead = head; //set ahead to fall into head pointer
    //loop through deleting the 
    while(ahead != NULL){
        //Delete current node and move on
        current = ahead;
        ahead = current->next;
        delete current;
    }
}

void LRU::update(int t_way){
    LruNode* back = NULL;
    LruNode* curr = head;
    while((curr->way != t_way) && (curr->next != NULL)){
        //step through the LRU until the way is found
        back = curr;
        curr = curr->next;
    }
    if(back == NULL){
        //The buffer is already correct
        return;
    }
    else{
        back->next = curr->next;
        curr->next = head;
        head = curr;
    }

}

int LRU::fetch(){
   //Search to determine which way to kick 
   LruNode* curr = this->head;
   int way;
   while(curr->next != NULL){
       way = curr->way;
       curr = curr->next;
   }
   return way;
}
