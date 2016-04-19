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
    VcacheElem* temp = new VcacheElem;
    temp->dirty = false; 
    temp->valid = false;
    temp->tag = 0;
    temp->index = 0;
    thead->element = temp;
    VicNode* curr = thead;
    for(int i = 0; i < 7; ++i){
        curr->next = new VicNode;
        curr = curr->next;
        curr->next = NULL;
        temp = new VcacheElem;
        temp->dirty = false;
        temp->valid = false;
        temp->tag = 0;
        temp->index = 0;
        curr->element = temp;
    }
    this->head = thead;
}

bool Victim::check(unsigned long long int tarTag, unsigned int tarIndex){
    // TODO add code to check for an address
    VicNode* curr = this->head;
    while((curr->element->tag != tarTag) || (curr->element->index != tarIndex){
       //check to see if at the end of viccache
       if(curr->next == NULL){
           return false;
       }
       else{
           curr = curr->next;
       }
    }
    if(curr->element->valid){
        return true;
    }
    return false;
}

bool Victim::swap(unsigned long long int oldTag, unsigned int oldIndex, unsigned long long int newTag, unsigned int newIndex){
    //check to see if addr is actually in cache
    if(!this->check(oldTag, oldIndex)){
       this->push(newTag, newIndex);
       return false; 
    }
    else{
        //Delete the oldAddr node
        VicNode* curr = this->head;
        VicNode* before = NULL;
        while((curr->element->tag != oldTag) || (curr->element->index != oldIndex)){
            before = curr;
            curr = curr->next;
        }
        //check to see if oldAddr is already at the top.
        if(before!=NULL){
            before->next = curr->next;
        }
        //create a new node and append it to the head
        VicNode* tnew = head;
        curr->element->tag = newTag;
        curr->element->index = newIndex;
        curr->element->valid = true;
        curr->element->dirty = true;
        curr->next = tnew;
        this->head = curr;
    }
    return true;
        
}

bool Victim::push(unsigned long long int tarTag, unsigned int tarIndex){
    //pushes a new item onto the stack discarding the least recently used one.
    //delete the last item
    VicNode* curr = this->head;
    VicNode* before = NULL;
    while(curr->next != NULL){
        before = curr;
        curr = curr->next;
    }
    before->next = NULL;
    curr->next = this->head;
    this->head = curr;
    curr->element->tag = tarTag;
    curr->element->index = tarIndex;
    curr->element->valid = true;
    curr->element->dirty = true;
    return true;
        
}

void Victim::reorder(unsigned long long int tarTag, unsigned int tarIndex){
    //TODO place the targe on top of the victim cache
    VicNode* curr = this->head;
    VicNode* before = NULL;
    while(curr->element->tag != tarTag && curr->element->index != tarIndex && curr->next != NULL){
        before = curr; 
        curr = curr->next;
    }
    //if before == NULL then the its the first buffer element
    if(before == NULL){
        return;
    }
    else{
        before->next = curr->next;
        curr->next = this->head;
        this->head = curr;
    }
}

Victim::~Victim() {
	// TODO Auto-generated destructor stub
    VicNode* curr = this->head;
    VicNode* ahead = curr->next;
    while(ahead != NULL){
        delete(curr->element);
        delete(curr);
        curr = ahead;
        ahead = curr->next;
    }
    delete curr;
}

