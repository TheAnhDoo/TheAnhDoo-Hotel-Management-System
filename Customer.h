// This Customer header file was created by [TheAnhDoo]

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "Room.h"
#include <iostream>
#include <string>

using namespace std;
// Customer class
class Customer : public Person {
private:
    string id;
    string email;
    string phone_Number;

public:
    //Constructor
    Customer();
    Customer(string name, int age,string gender, string id, string email, string phone_Number);
    //Setter
    void set_Id(string id);
    void set_Email(string email);
    void set_Phone_Number(string phone_Number);
    //Getter
    string get_Phone_Number(); 
    string get_Id();
    string get_Email();
    void display();
};
#endif // CUSTOMER_H