// This Hotel header file was created by [TheAnhDoo]

#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<sstream>
#include <iomanip>
#include <conio.h>

#include "Room.h"
#include "Customer.h"

using namespace std;
class Hotel {
private: 
    vector<Room> rooms;
    vector<Customer> customers;

public:
    // Constructors
    Hotel();
  

    // Hotel management methods
    void checkIn();
    void checkOut();
    void viewAllRoomStatus();
    void viewCustomerInformation();
    void viewAllCustomer();
    void changeCustomerInformation();
    void addRoom();
    void mainMenu();
};

#endif //HOTEL_H


