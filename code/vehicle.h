#ifndef __VEHICLE_H_
#define __VEHCILE_H_

/* 
    vehicle.h
    Author: M00776456
    Created: 20/03/22
    Updated: 12/04/22
 */

#include <string>

class Vehicle {
    // member variables
    private:
        std::string number; // plate number
        std::string timeIn;
        std::string timeOut;
        std::string parkingCharges;

    // member functions
    public:
        // Constructor
        Vehicle();
        // Deconstructor
        ~Vehicle();

        // Setters and getters
        void setNumber(std::string number);
        std::string getNumber();

        void setTimeIn(std::string timeIn);
        std::string getTimeIn();

        void setTimeOut(std::string timeOut);
        std::string getTimeOut();

        void setParkingCharges(std::string parkingCharges);
        std::string getParkingCharges();
};

#endif