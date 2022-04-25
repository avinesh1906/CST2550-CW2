/* 
    testing.cpp
    Author: M00776456
    Created: 20/03/22
    Updated: 
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream>

#include "separateChaining.h"
#include "redBlackTree.h"
#include "main.h"

typedef RedBlackTree* rbtPtr;

/* Helper function to check if is in red black tree*/
bool checkExist(rbtPtr redBlackTree, std::string key){
    if (redBlackTree->nodePresent(key) == 0){
        return true;
    }
    return false;
}

TEST_CASE("test Vehicle", "[Vehicle()]"){
    Vehicle vehicle;
    vehicle.setNumber("XS21 SBG");
    vehicle.setTimeIn("10:21:10");
    vehicle.setTimeOut("11:00:12");
    vehicle.setParkingCharges("FREE");

    REQUIRE(vehicle.getNumber() == "XS21 SBG");
    REQUIRE(vehicle.getTimeIn() == "10:21:10");
    REQUIRE(vehicle.getTimeOut() != "12:00:12");
    REQUIRE(vehicle.getParkingCharges() != "£1.50");
}

TEST_CASE("test hashing functions", "[SeparateChainingHash()]"){
    SeparateChainingHash separateChaining(10);

    int hashIndex = separateChaining.hashingFunction("12/01/2014");
    REQUIRE(hashIndex < 1000);    
}

TEST_CASE("test add in Separate Chaining", "[SeparateChainingHash()]"){
    SeparateChainingHash separateChaining(25);
    Vehicle vehicle;

    std::string date = "14/05/2022";

    vehicle.setNumber("XS21 SBG");
    vehicle.setTimeIn("10:21:10");
    vehicle.setTimeOut("11:00:12");
    vehicle.setParkingCharges("FREE");

    separateChaining.add(vehicle, date);
    std::string string1 = separateChaining.get(date);
    std::string string2 = " VRN \t\t TIME-IN\t TIME-OUT\t Parking Charges\n"
                        "XS21 SBG\t10:21:10\t11:00:12\tFREE\n";

    REQUIRE(string1 == string2);
}

TEST_CASE("test add in Red-Black Tree", "RedBlackTree[]"){
    RedBlackTree redBlackTree;
    Vehicle vehicle;

    std::string plate = "XS21 SBG";

    vehicle.setNumber(plate);
    vehicle.setTimeIn("10:21:10");

    redBlackTree.insert(vehicle);

    REQUIRE(checkExist(&redBlackTree, plate));
}

TEST_CASE("test delete in Red-Black Tree", "RedBlackTree[]"){
    RedBlackTree redBlackTree;
    Vehicle vehicle;

    std::string plate = "XS21 SBG";

    vehicle.setNumber(plate);
    vehicle.setTimeIn("10:21:10");

    redBlackTree.insert(vehicle);

    redBlackTree.deleteNode(plate);

    REQUIRE_FALSE(checkExist(&redBlackTree, plate));
}

TEST_CASE("Test verifyDate"){
    std::string date1 = "17/12/2022";
    std::string date2 = "22/444/22";

    REQUIRE(verifyDate(date1));
    REQUIRE_FALSE(verifyDate(date2));
}

// TEST_CASE("Test verifyPlate"){
//     std::string plate1 = "QA12 ACV";
//     std::string plate2 = "QAQ12 ACV";

//     REQUIRE(verifyPlate(plate1));
//     REQUIRE_FALSE(verifyPlate(plate2));
// }

// TEST_CASE("Test calculateDiffSec"){
//     std::string timeIn = "10:00:00";
//     std::string timeOut = "10:30:00";

//     int timeDiff = 1800;

//     REQUIRE(calculateDiffSec(timeIn, timeOut) == timeDiff);
// }

// TEST_CASE("Test calculateFee"){
//     std::string timeIn = "10:00:00";
//     std::string timeOut = "11:30:00";  

//     std::string parkingCharges = "£3.00";

//     REQUIRE(calculateFee(timeIn, timeOut) == parkingCharges);
// }