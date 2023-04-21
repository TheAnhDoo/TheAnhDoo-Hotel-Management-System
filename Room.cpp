// This implementation file was created by [TheAnhDo]
// Class Room implementation file

#include "Room.h"

//Constructoer
Room::Room(string roomName, string roomType, double pricePerNight) {
    this->roomName = roomName;
    this->roomType = roomType;
    this->pricePerNight = pricePerNight;
    this->isAvailable = true;
}
//Getter
string Room::get_Room_Name() {
    return roomName;
}

string Room::get_Room_Type() {
    return roomType;
}

double Room::get_Price_Per_Night() {
    return pricePerNight;
}

bool Room::get_Is_Available() {
    return isAvailable;
}
//Setter
void Room::setAvailability(bool availability) {
    isAvailable = availability;
}