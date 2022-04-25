/* 
    vehicle.cpp
    Author: M00776456
    Created: 20/03/22
    Updated: 12/04/22
 */

#include "vehicle.h"
#include <string>
#include <ctime>

// Constructor
Vehicle::Vehicle(){

}

// Deconstructor
Vehicle::~Vehicle()
{

}

void Vehicle::setNumber(std::string number)
{
    this->number = number;
}

std::string Vehicle::getNumber()
{
    return number;
}

void Vehicle::setTimeIn(std::string timeIn)
{
    this->timeIn = timeIn;
}

std::string Vehicle::getTimeIn()
{
    return timeIn;
}

void Vehicle::setTimeOut(std::string timeOut)
{
    this->timeOut = timeOut;
}

std::string Vehicle::getTimeOut()
{
    return timeOut;
}

void Vehicle::setParkingCharges(std::string parkingCharges)
{
    this->parkingCharges = parkingCharges;
}

std::string Vehicle::getParkingCharges()
{
    return parkingCharges;
}