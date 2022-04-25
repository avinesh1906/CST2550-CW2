#ifndef __SEPARATECHAINING_H_
#define __SEPARATECHAINING_H_
/* 
    separateChaining.h
    Author: M00776456
    Created: 30/03/22
    Updated: 12/04/22
*/
#include <vector>
#include "struct.h"	
#include <iostream>
#include <fstream>

class SeparateChainingHash{
	private:
		size_t size;
		// a vector containing a list of vectors
		std::vector<std::vector<schIndex>> list;

	public:
		SeparateChainingHash(size_t size);
		~SeparateChainingHash();

		/* 
			To determine the hash value of the date
			@param date is used to calculate the hash index
			@return int
		*/
		int hashingFunction(std::string date);

		/* 
			To add a vehicle to the separate chaining data structure
			@param vehicle represents the vehicle to be entered and 
			date represents the date to which vector the vehicle should
			be added to
		*/
		void add(Vehicle vehicle, std::string date);

		/* 
			To return the list of vehicles of a specific date
			@date represents the date of the history to be extracted
			@param std::string
		*/
		std::string get(std::string date);

		/* 
			To save the content of the separate chaining to the file
			@param filename represents the name of the file 
		*/
		void saveToFile(std::string filename);
};

#endif