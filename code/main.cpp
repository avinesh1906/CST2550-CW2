/* 
    main.cpp
    Author: M00776456
    Created: 20/03/22
    Updated: 17/04/22
 */
#include "main.h"

typedef RedBlackTree* rbtPtr;
typedef SeparateChainingHash* schPtr;

int main(int argc, char* argv[]){
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0]
              << " <filename>\n";
        exit(1);
    }
    int capacity = loadCapacity(argv[1]);

    RedBlackTree redBlackTree;
    SeparateChainingHash separateChaining(capacity + 1); 

    loadFile(argv[1], &redBlackTree, &separateChaining);
    mainMenu(argv[1], &redBlackTree, &separateChaining);
}

void mainMenu(std::string filename, rbtPtr redBlackTree, 
                schPtr separateChaining){
    int option = 0;
    // loop until correct input enterd
    do {
        // menu
        std::cout << std::endl << "******** Main Menu ********" 
        << std::endl;
        std::cout << "1. Process entering vehicle" << std::endl;
        std::cout << "2. Process existing vehicle" << std::endl;
        std::cout << "3. View Report" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << std::endl << "Enter your choice: ";

        std::cin >> option;

        // enter entering time
        if(option == 1){
            std::cout << "\x1B[2J\x1B[H"; 
            std::cout << std::endl <<
             "******** Process entering vehicle ********" 
                      << std::endl;  
            entering(redBlackTree);
        // Enter existing time
        } else if (option == 2) {
            // clear the screen
            std::cout << "\x1B[2J\x1B[H";
            std::cout << std::endl <<
             "******** Process existing vehicle ********" 
                      << std::endl;  
            exiting(redBlackTree, separateChaining);
        // View Report
        } else if (option == 3) {
            // clear the screen
            std::cout << "\x1B[2J\x1B[H";
            std::cout << std::endl << "******** View report ********" 
                      << std::endl;  
            report(separateChaining);
        // quit
        } else if (option == 4) {
            // function call quit()
            quit(filename, redBlackTree, separateChaining);

        // error message if invalid input entered
        } else if (option != 4) {
            std::cout << std::endl << 
            "Invalid choice. Please enter 1,2,3 or 4 only" 
            << std::endl;
        }
    } while(option!= 4);
}

void entering(rbtPtr redBlackTree){
    std::string plate;
    Vehicle newVehicle;

    // ignore/clear the input buffer
    std::cin.ignore();

    do{
        plate="";
        // Prompt to input plate number
        std::cout << "Enter the vehicle's plate number: ";
        // Input strings with blank spaces
        std::getline(std::cin, plate);

        if(!verifyPlate(plate)){
            std::cout << "Please enter a valid plate number!" << std::endl;
            std::cout << "The format is two letters, two numbers,"  
            "a space and three further letters." << std::endl;
        }
    } while(!verifyPlate(plate));


    // check if plate number already exists
    if (redBlackTree->nodePresent(plate) == 0){
        std::cout << "This vehicle by the plate number " << 
        plate << " is already in the parking lot" << std::endl;

    } else {
        newVehicle.setNumber(plate);
        newVehicle.setTimeIn(genereateTime());
        redBlackTree->insert(newVehicle);
        std::cout << "Successfully added vehicle " << plate << std::endl;
        
    }

}

void exiting(rbtPtr redBlackTree, schPtr separateChaining){
    std::string plate;
    Vehicle tempVehicle;

    // ignore/clear the input buffer
    std::cin.ignore();

    do{
        // Prompt to input plate number
        std::cout << "Enter the existing vehicle's plate number: ";
        // Input strings with blank spaces
        std::getline(std::cin, plate);

        if(!verifyPlate(plate)){
            std::cout << "Please enter a valid plate number!" << std::endl;
            std::cout << "The format is two letters, two numbers,"  
            "a space and three further letters." << std::endl;
        }
    } while(!verifyPlate(plate));

    // check if plate number already exists
    if (redBlackTree->nodePresent(plate) == 1){
        std::cout << "This vehicle by the plate number " << 
        plate << " is not in the parking lot" << std::endl;
    } else {
        // extract the details from the redBlackTreee
        NodePtr tempNode = redBlackTree->searchTree(plate);
        std::string timeOut = genereateTime();
        // append the details to a temporary variable
        tempVehicle.setNumber(tempNode->key);
        tempVehicle.setTimeIn(tempNode->timeIn);
        tempVehicle.setTimeOut(timeOut);
        tempVehicle.setParkingCharges(calculateFee(tempNode->timeIn, 
                                                    timeOut));

        // add the details to the separateChaining algo
        separateChaining->add(tempVehicle, generateDate());

        // delete the node from the redblackTree
        redBlackTree->deleteNode(plate);

        std::cout << "Successfully removed vehicle " << plate << std::endl;
    }
}

void report(schPtr separateChaining){
    std::string date;

    do{
        // Prompt to view report according to a specific date
        std::cout << 
        "For which date do you want to view the report? (DD/MM/YYYY) ";
        std::cin >> date;

        if(!verifyDate(date)){
            std::cout << "Please enter a valid date!" << std::endl;
            std::cout << "The format is DD/MM/YYYY"
            " E.g: 02/04/2022" << std::endl;
        }
    } while(!verifyDate(date));

    // display the specific date's report
    std::cout << separateChaining->get(date);
}

void quit(std::string filename, rbtPtr redBlackTree, 
            schPtr separateChaining){
    saveFromSCH(filename, separateChaining);
    saveFromRBT(filename, redBlackTree);

    separateChaining = nullptr;
    redBlackTree = nullptr;

    delete separateChaining;
    delete redBlackTree;

    std::cout << "Bye Bye" << std::endl;
    exit(0);
}

std::string genereateTime(){
    // current date/time based on current system
    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::string hour = std::to_string(ltm->tm_hour);
    std::string mins = std::to_string(ltm->tm_min);
    std::string secs = std::to_string(ltm->tm_sec);

    // checks if hour, minute and seconds are less than 10
    if((ltm->tm_hour) < 10){
        hour = "0" + std::to_string(ltm->tm_hour);
    }
    if((ltm->tm_min) < 10){
        mins = "0" + std::to_string(ltm->tm_min);
    }
    if((ltm->tm_sec) < 10){
        secs = "0" + std::to_string(ltm->tm_sec);
    }

    std::string time = hour + ":" + mins + ":" + secs;

    return time;
}

std::string generateDate(){
    // current date/time based on current system
    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::string month = std::to_string(1+ ltm->tm_mon);
    std::string day = std::to_string(ltm->tm_mday);

    // check if month/day are less than 10
    if((1+ ltm->tm_mon) < 10){
        month = "0" + std::to_string(1+ ltm->tm_mon);
    }
    if((ltm->tm_mday) < 10){
        day = "0" + std::to_string(ltm->tm_mday);
    }
    
    std::string date = day + "/" + month + "/" 
                    + std::to_string(1900 + ltm->tm_year);

    return date;
}

int loadCapacity(std::string filename){
    std::ifstream myFile(filename);
    std::string myText;
    int separateChainingCapacity = 0;

    std::getline(myFile, myText); // skip the first line

    // loop until last line
    while (std::getline(myFile, myText)){
        if(isdigit(myText[myText.length() - 2])){
            separateChainingCapacity += 1;
        }
    }
    // set default size 1009 if less than 1009
    if (separateChainingCapacity < 1009){
        return 1009;
    }
    return nextPrime(separateChainingCapacity);

}

int nextPrime(int capacity)
{
 
    // Base case
    if (capacity <= 1)
        return 2;
 
    int prime = capacity;
    bool found = false;
 
    // Loop continuously until isPrime returns
    // true for a number greater than capacity
    while (!found){
        prime++;
 
        if (isPrime(prime))
            found = true;
    }
 
    return prime;
}

bool isPrime(int capacity)
{
    // Corner cases
    if (capacity <= 1)  return false;
    if (capacity <= 3)  return true;
   
    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (capacity%2 == 0 || capacity%3 == 0) return false;
   
    for (int i=5; i*i<=capacity; i=i+6)
        if (capacity%i == 0 || capacity%(i+2) == 0)
           return false;
   
    return true;
}
 
 
void loadFile(std::string filename, rbtPtr redBlackTree, 
            schPtr separateChaining){
    std::ifstream myFile(filename);
    std::string myText;
    // regex value
    std::regex regex(", |,");

    std::getline(myFile, myText); // skip the first line

    // loop until last line
    while (std::getline(myFile, myText)){
        Vehicle tempVehicle;
        // split the string according to the regex value
        std::vector<std::string> out(
                    std::sregex_token_iterator(myText.begin(), 
                    myText.end(), regex, -1),
                    std::sregex_token_iterator()
                    );

        // check if "-" is in the string
        if(out[3].find("-") != std::string::npos){
            // insert into the red black tree
            tempVehicle.setNumber(out[1]);
            tempVehicle.setTimeIn(out[2]);
            redBlackTree->insert(tempVehicle);
        } else {
            tempVehicle.setNumber(out[1]);
            tempVehicle.setTimeIn(out[2]);
            tempVehicle.setTimeOut(out[3]);
            tempVehicle.setParkingCharges(calculateFee(out[2], out[3]));

            separateChaining->add(tempVehicle, out[0]);
        }
    }
}

std::string calculateFee(std::string timeIn, std::string timeOut){
    int diff_sec = calculateDiffSec(timeIn, timeOut);
    std::string parking_charges;

    if(diff_sec > (8 * 3600)){
        parking_charges = "£30.00";
    }

    if(diff_sec <= (8 * 3600)){
        parking_charges = "£15.00";
    }

    if(diff_sec <= (4 * 3600)){
        parking_charges = "£5.00";
    }

    if(diff_sec <= (2 * 3600)){
        parking_charges = "£3.00";
    }

    if(diff_sec <= (3600)){
        parking_charges = "£1.50";
    }

    if(diff_sec < (30 * 60)){
        parking_charges = "FREE";

    }
    return parking_charges;
}

int calculateDiffSec(std::string timeIn, std::string timeOut){
    Time time1, time2;
    std::regex regex(":");

    // split the string using the delimeter
    std::vector<std::string> in(
                    std::sregex_token_iterator(timeIn.begin(), 
                    timeIn.end(), regex, -1),
                    std::sregex_token_iterator()
                    );
    std::vector<std::string> out(
                    std::sregex_token_iterator(timeOut.begin(), 
                    timeOut.end(), regex, -1),
                    std::sregex_token_iterator()
                    );

    time1.hours = std::stoi(in[0]);
    time1.minutes = std::stoi(in[1]);
    time1.seconds = std::stoi(in[2]);

    time2.hours = std::stoi(out[0]);
    time2.minutes = std::stoi(out[1]);
    time2.seconds = std::stoi(out[2]);
    
    if(time1.seconds > time2.seconds){
        time2.minutes--;
        time2.seconds += 60;
    }

    int diff_sec = time2.seconds - time1.seconds;

    if(time1.minutes > time2.minutes){
        time2.hours--;
        time2.minutes += 60;
    }

    int diff_minute = time2.minutes - time1.minutes;
    int diff_hour = time2.hours - time1.hours;

    diff_sec += (diff_hour * 60 * 60 ) + (diff_minute * 60);

    return diff_sec;
}

void saveFromSCH(std::string filename, schPtr separateChaining){
    separateChaining->saveToFile(filename);
}

void saveFromRBT(std::string filename, rbtPtr redBlackTree){
    redBlackTree->saveTree(filename, generateDate());
}

bool verifyPlate(std::string number){
    std::string pattern = "^([A-Z]{2}[0-9]{2} [A-Z]{3})$";
    std::regex str_exp(pattern);
    // check if matches the pattern
    if (regex_match (number, str_exp)){
        return true;
    } 
    return false;
}

bool verifyDate(std::string date){
    std::string pattern = "(0[1-9]|[12][0-9]|3[01])[\\/\\-](0[1-9]|1[012])"\
                            "[\\/\\-]\\d{4}";

    std::regex str_exp(pattern);
    // check if matches the pattern
    if (regex_match (date, str_exp)){
        return true;
    } 
    return false;
}