/* 
    separateChaining.h
    Author: M00776456
    Created: 30/03/22
    Updated: 16/04/22
*/
#include "separateChaining.h"

SeparateChainingHash::SeparateChainingHash(size_t size){
    list = std::vector<std::vector<schIndex>>(size);
    this->size = size;
}

SeparateChainingHash::~SeparateChainingHash(){}

int SeparateChainingHash::hashingFunction(std::string date){
    // calculate the hash value
    Hash hashing(date, size);
    return hashing.hashIndex;
}

void SeparateChainingHash::add(Vehicle vehicle, std::string date){	
	schIndex index;
	index.vehicle = vehicle;
	index.date = date;
	// add to the list
	list[hashingFunction(date)].push_back(index);	
}

std::string SeparateChainingHash::get(std::string date){
	int hashIndex = hashingFunction(date);
	std::string returnString = " VRN \t\t TIME-IN\t TIME-OUT\t Parking Charges\n"; 
	if (list[hashIndex].size() == 0){
		returnString = "No record for " + date + ".\n";
	} else {
		// loop through the list depending on the hash index
		for (long unsigned int i = 0; i < list[hashIndex].size(); i++){
			schIndex index = list[hashIndex][i];
			Vehicle vehicle = index.vehicle;
			returnString += vehicle.getNumber() + "\t" + 
			vehicle.getTimeIn() + "\t" + vehicle.getTimeOut()
			+ "\t" + vehicle.getParkingCharges() +"\n";   
		}
	}
	return returnString;
}

void SeparateChainingHash::saveToFile(std::string filename){
	std::ofstream MyFile(filename, std::ofstream::trunc);
	
	MyFile << "DATE, VRN, TIME-IN, TIME-OUT";
	MyFile << "\n";
	// loop through the list
	for(long unsigned int i = 0; i < list.size(); i++){
		std::string text = "";
		// check if the list inside the main list is empty
		if(list[i].size() != 0){
			for(long unsigned int j = 0; j < list[i].size(); j++){
				schIndex index = list[i][j];
				Vehicle vehicle = index.vehicle;

				text = index.date + ", " + vehicle.getNumber() + ", " +
					vehicle.getTimeIn() + ", " + 
					vehicle.getTimeOut();
				MyFile << text; 
				MyFile << "\n";    
			}
		}
	}    			
}