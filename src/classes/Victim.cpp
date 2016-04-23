/*
 * Victim.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: bryan & erik
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
 *
 *  NOTE: The input is not sanitized to deal with invalid input. So if a cache element is invalid,
 *  DO NOT run swap with those values.
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
    //Create a point for tracking
    VicNode* curr = this->head;
    //Loop through looking to see if there is a valid match for the target
    while(curr->next != NULL){
       if(curr->element->tag == tarTag && curr->element->index == tarIndex && curr->element->valid){
           return true;
       }
       //Step forward throught the list
       curr = curr->next;
    }
    //Check the last element in the VC
    if(curr->element->tag == tarTag && curr->element->index == tarIndex && curr->element->valid){
           return true;
    }
    //If we make it through the whole list then we know that the member is not present
    return false;
}

unsigned int Victim::swap(unsigned long long int oldTag, unsigned int oldIndex, unsigned long long int newTag, unsigned int newIndex, bool tarD){
    //set up return val default state of 2 assumes a clean kick
    unsigned int retval;
    //check to see if addr is actually in cache
    if(!this->check(oldTag, oldIndex)){
       //run push and determine if the element kicked is dirty
       if(this->push(newTag, newIndex, tarD)){
           //return 1 for a dirty kickout
           retval = 1;
       }
       else{
           //return 0 for non dirty kickout
           retval = 0;
       }
       return retval; 
    }
    else{
        //set up some pointers to track position
        VicNode* curr = this->head;
        VicNode* before = NULL;
        //while loop to look for the target element.
        while(curr->next != NULL){
            //If there is a match break out of the loop otherwise increment through the list
            if(curr->element->tag == oldTag && curr->element->index == oldIndex){
                break;
            }
            before = curr;
            curr = curr->next;
        }
        //If handle is not the first element, make it so
        if(before != NULL){
            before->next = curr->next;
            curr->next = this->head;
            this->head = curr;
        }
        //set up the vic if the evicted member is dirty
        if(curr->element->dirty){
            this->vic->tag = curr->element->tag;
            this->vic->index = curr->element->index;
            this->vic->dirty = true;
            this->vic->valid = true;
            retval = 3;
        }
        else{
            this->vic->valid = false;
            retval = 2;
        }
        //Now change the values in curr
        curr->element->tag = newTag;
        curr->element->index = newIndex;
        curr->element->valid = true;
        curr->element->dirty = tarD;
        return retval;

    }
        
}

bool Victim::push(unsigned long long int tarTag, unsigned int tarIndex, bool tarD){
    //pushes a new item onto the stack discarding the least recently used one.
    //delete the last item
    //set up retval
    bool retval;
    //Set up tracking pointers
    VicNode* curr = this->head;
    VicNode* before = NULL;
    //step through until end
    while(curr->next != NULL){
        before = curr;
        curr = curr->next;
    }
    //Terminate the Victim Cache
    before->next = NULL;
    //if the kicked member was dirty set the vic
    if(curr->element->dirty){
        this->vic->tag = curr->element->tag;
        this->vic->index = curr->element->index;
        this->vic->valid = true;
        this->vic->dirty = true;
        retval = true;
    }
    //Otherwise invalidate the dirty kicked element
    else{
        this->vic->valid = false;
        retval = false;
    }
    //put the last element at the head
    curr->next = this->head;
    this->head = curr;
    //Set the new values into the new head
    curr->element->tag = tarTag;
    curr->element->index = tarIndex;
    curr->element->valid = true;
    curr->element->dirty = tarD;
    return retval;
        
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

