/*
 * Victim.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan&erik
 *      
 *  Only run the swap function which will automatically determine if the requested block is present as 
 *  well as determine if the kickout was dirty. it will return an integer from 0-3 and the output is
 *  encoded as follows
 *
 *      0 - VC miss, clean member evicted
 *      1 - VC miss, dirty member evicted
 *      2 - VC hit, clean member evicted
 *      3 - VC hit, dirty member evicted
 *
 *  After a 1 or 2 is returned, the functhion check_dirt should be called to retrieve the information
 *  from the most recently evicted member of the VC. This will return a null if this member is invalid
 */

#include "Victim.h"
#include <cstddef>

Victim::Victim() {
    //Create a node for head and set the point to null
    VicNode* thead = new VicNode;
    thead->next = NULL;
    //Build up the VcacheElement for head
    VcacheElem* temp = new VcacheElem;
    temp->dirty = false; 
    temp->valid = false;
    temp->tag = 0;
    temp->index = 0;
    thead->element = temp;
    //Set up for the for loop to create the remaining elems
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
    //setup the dirty placeholder element
    VcacheElem* temp_ele = new VcacheElem;
    temp_ele->valid = false;
    this->vic = temp_ele;
}

VcacheElem* Victim::check_dirt(){
    //return the dirty kickout address unless invalid, then null
    if(this->vic->valid == false){
        return NULL;
    }
    else{
        //returns pointer to vic
        return this->vic;
    }
}

bool Victim::check(unsigned long long int tarTag, unsigned int tarIndex){
    // TODO add code to check for an address
    VicNode* curr = this->head;
    while((curr->element->tag != tarTag) || (curr->element->index != tarIndex)){
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

unsigned int Victim::swap(unsigned long long int oldTag, unsigned int oldIndex, unsigned long long int newTag, unsigned int newIndex, bool tarD){
    //set up return val
    unsigned int retval = 3;
    //check to see if addr is actually in cache
    if(!this->check(oldTag, oldIndex)){
       if(this->push(newTag, newIndex, tarD)){
           retval = 1;
       }
       else{
           retval = 0;
       }
       return retval; 
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
        //set up the vic if the evicted member is dirty
        if(curr->element->dirty){
            this->vic->tag = curr->element->tag;
            this->vic->index = curr->element->index;
            this->vic->dirty = true;
            this->vic->valid = true;
            retval = 4;
        }
        else{
            this->vic->valid = false;
        }
        //Now move curr
        curr->element->tag = newTag;
        curr->element->index = newIndex;
        curr->element->valid = true;
        curr->element->dirty = tarD;
        curr->next = tnew;
        this->head = curr;
    }
    return true;
        
}

bool Victim::push(unsigned long long int tarTag, unsigned int tarIndex, bool tarD){
    //pushes a new item onto the stack discarding the least recently used one.
    //delete the last item
    //set up retval
    bool retval = false;
    VicNode* curr = this->head;
    VicNode* before = NULL;
    while(curr->next != NULL){
        before = curr;
        curr = curr->next;
    }
    before->next = NULL;
    //if the kicked member was dirty set the vic
    if(curr->element->dirty){
        this->vic->tag = curr->element->tag;
        this->vic->index = curr->element->index;
        this->vic->valid = true;
        this->vic->dirty = true;
        retval = true;
    }
    else{
        this->vic->valid = false;
    }
    curr->next = this->head;
    this->head = curr;
    curr->element->tag = tarTag;
    curr->element->index = tarIndex;
    curr->element->valid = true;
    curr->element->dirty = tarD;
    return retval;
        
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
    delete vic;
}

