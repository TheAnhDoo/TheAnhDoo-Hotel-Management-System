// This Room header file was created by [TheAnhDoo]

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>

using namespace std;

// Room class
class Room {
private:
    string roomName;
    string roomType;
    double pricePerNight;
    bool isAvailable;

public:
    //Constructor
    Room(string roomName, string roomType, double pricePerNight);
    //Getter
    string get_Room_Name();
  
    string get_Room_Type();

    double get_Price_Per_Night();

    bool get_Is_Available();

    //Setter
    void setAvailability(bool availability);
};
#endif //ROOM_H