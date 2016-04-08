/*
 * Cache.h
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <map>
using namespace std;

struct cacheElem{
	unsigned int tag;
	bool valid;
	bool dirty;
};



class Dictionary {
public:
	//constructor that initializes it with the correct number of indexes
	Dictionary(unsigned int nIndexes);
	//checks to see if a certain index contains the tag (valid)
	bool check(unsigned int index, unsigned int tag);
	//change the specified index to the new tag
	void update(unsigned int index, unsigned int tag);
	//flush the cache
	void flush(void);

	virtual ~Dictionary();

private:
	unsigned int nIndexes;
	//the actual dictionary, where the key is the 'index'
	map<unsigned int, struct cacheElem *> dict;
};

#endif /* DICTIONARY_H_ */
