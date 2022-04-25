#ifndef __STRUCT_H_
#define __STRUCT_H_
/* 
    struct.h
    Author: M00776456
    Created: 20/03/22
    Updated: 12/04/22
 */

#include <string>
#include "vehicle.h"

// User defined datatype
struct Node {
  	std::string key;
  	std::string timeIn;
  	Node *parent;
  	Node *left;
  	Node *right;
	int color;
};

struct schIndex {
	Vehicle vehicle;
	std::string date;
};

struct Hash {
    size_t hashIndex;

    Hash(const std::string s, int size) {
		hashIndex = 5381;
		for(auto x: s){
			hashIndex = ((hashIndex << 5) + hashIndex) + x;
		}
        hashIndex = hashIndex % size;
    }
};

struct Time {
	int seconds;
	int minutes;
	int hours;
};

#endif