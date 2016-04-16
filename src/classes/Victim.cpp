/*
 * Victim.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan&erik
 */

#include "Victim.h"
#include <cstddef>

Victim::Victim() {
	// TODO Auto-generated constructor stub
    VicNode* thead = new VicNode;
    thead->next = NULL;
    thead->address = 0;
    thead->dirty = true;
    VicNode* curr = thead;
    for(int i = 0; i < 7; ++i){
        curr->next = new VicNode;
        curr = curr->next;
        curr->next = NULL;
        curr->address = 0;
        curr->dirty = true;
    }
    this->head = thead;
}

bool Victim::check(unsigned long long int addr){
    // TODO add code to check for an address
    VicNode* curr = this->head;
    while(curr->address != addr){
       //check to see if at the end of viccache
       if(curr->next == NULL){
           return false;
       }
       else{
           curr = curr->next;
       }
    }
    this->reorder(addr);
    return true;
}

bool Victim::swap(unsigned long long int oldAddr, unsigned long long int newAddr){
    //check to see if addr is actually in cache
    if(!this->check(oldAddr)){
       return false; 
    }
    else{
        //Delete the oldAddr node
        VicNode* curr = this->head;
        VicNode* before = NULL;
        while(curr->address != oldAddr){
            before = curr;
            curr = curr->next;
        }
        //check to see if oldAddr is already at the top.
        if(before!=NULL){
            before->next = curr->next;
        }
        delete(curr);

        //create a new node and append it to the head
        VicNode* tnew = new VicNode;
            
}

bool Victim::push(unsigned long long int newAddr){
    //TODO delete the old item add the new one
}

void Victim::reorder(unsigned long long int target){
    //TODO place the targe on top of the victim cache
}

Victim::~Victim() {
	// TODO Auto-generated destructor stub
    VicNode* curr = this->head;
    VicNode* ahead = curr->next;
    while(ahead != NULL){
        delete curr;
        curr = ahead;
        ahead = curr->next;
    }
    delete curr;
}

