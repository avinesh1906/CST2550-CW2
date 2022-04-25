#ifndef __MAIN_H_
#define __MAIN_H_

/* 
    main.h
    Author: M00776456
    Created: 20/03/22
    Updated: 14/04/22
 */


#include "redBlackTree.h"
#include "separateChaining.h"
#include "struct.h"

#include <string>
#include <iostream>
#include <string>
#include <ctime>
#include <regex>

typedef RedBlackTree* rbtPtr;
typedef SeparateChainingHash* schPtr;

/* 
    To display the main menu to choose between 
    vehicles entering, existing or view specific report
    @param filename represents the name of the file inserted
    in the command line, redBlackTree represents the pointer to the
    redBlackTree variable declared in main and separateChaining represents
    the pointer to the separateChaining variable declared in main
 */
void mainMenu(std::string filename, rbtPtr redBlackTree, 
    schPtr separateChaining);

/* 
    To enter the time of entering vehicles along with other details
    @param nredBlackTree represents the pointer to the
    redBlackTree variable declared in main
 */
void entering(rbtPtr redBlackTree);

/* 
    To enter the time of a specific existing vehicles
    @param redBlackTree represents the pointer to the
    redBlackTree variable declared in main and separateChaining 
    represents the pointer to the separateChaining variable 
    declared in main
 */
void exiting(rbtPtr redBlackTree, schPtr separateChaining);

/* 
    To generate a report for a specific date
    @param separateChaining represents the pointer to the 
    separateChaining variable declared in main
 */
void report(schPtr separateChaining);

/* 
    Exit the program
    @param filename represents the name of the file inserted
    in the command line, redBlackTree represents the pointer to the
    redBlackTree variable declared in main and separateChaining represents
    the pointer to the separateChaining variable declared in main
 */
void quit(std::string filename, rbtPtr redBlackTree, 
            schPtr separateChaining);

/* 
    Function to generate the current time
    @param no parameter
    @return std::string
*/
std::string genereateTime();

/* 
    Function to generate the current date
    @param no parameter
    @return std::string
*/
std::string generateDate();

/* 
    Function to load the file and calculate the 
    capacity for the hash table
    @param filename will be the filename to be loaded
    @return int
*/
int loadCapacity(std::string filename);

/* 
    Function to load the file and insert into the
    data structures
    @param filename represents the name of the file inserted
    in the command line, redBlackTree represents the pointer to the
    redBlackTree variable declared in main and separateChaining represents
    the pointer to the separateChaining variable declared in main
*/
void loadFile(std::string filename, rbtPtr redBlackTree, 
            schPtr separateChaining);

/* 
    To calculate the parking charge
    @param timeIn represents the entering time of the vehicle and
    timeOut represents the existing time of the vehicle
    @return std::string 
*/
std::string calculateFee(std::string timeIn, std::string timeOut);

/* 
    To calculate the difference in secs betweeen the two times
    @param timeIn represents the entering time of the vehicle and
    timeOut represents the existing time of the vehicle
    @return int 
*/
int calculateDiffSec(std::string timeIn, std::string timeOut);

/* 
    To save the data from the RBT into the text file
    when quiting
    @param  filename represents the name of the file inserted
    in the command line and redBlackTree represents the pointer to the 
    declared redBlackTree in the main.
*/
void saveFromRBT(std::string filename,  rbtPtr redBlackTree);

/* 
    To save the data from the separate chaining hash table
    into the text file when quiting
    @param  filename represents the name of the file inserted
    in the command line and separateChaining represents the pointer to the 
    declared separateChaining in the main.
*/
void saveFromSCH(std::string filename,schPtr separateChaining);

/* 
    To check whether the plate number entered is the UK format
    @param number represents the plate number of the vehicle
    @return bool
*/
bool verifyPlate(std::string number);


/* 
    To check whether the date entered is in in a correct format
    @param date represents the date entered
    @return bool
*/
bool verifyDate(std::string date);

/* 
    Function to return the smallest prime number greater than capacity
    @param capacity represents the capacity of the inputfile
    @return int
*/
int nextPrime(int capacity);

/* 
    Function that returns true if capacity is prime else 
    returns false
    @param capacity represents the capacity of the inputfile
    @return bool
*/
bool isPrime(int capacity);

#endif