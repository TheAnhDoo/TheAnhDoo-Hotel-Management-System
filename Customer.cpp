// This implementation file was created by [TheAnhDo]
// Class Customer implementation file

#include "Customer.h"

//Constructor
Customer::Customer() : Person(), id(""), email(""), phone_Number("") {}

Customer::Customer(string name, int age, string gender, string id, string email, string phone_Number)
    : Person(name, age, gender), id(id), email(email), phone_Number(phone_Number) {}
//Setter
void Customer::set_Id(string id) {
    this->id = id;
}

void Customer::set_Email(string email) {
    this->email = email;
}

void Customer::set_Phone_Number(string phone_Number) {
    this->phone_Number = phone_Number;
}
//Getter
string Customer::get_Phone_Number() {
    return this->phone_Number;
}

string Customer::get_Id() {
    return this->id;
}

string Customer::get_Email() {
    return this->email;
}
void Customer::display() {
    Person::display();
    cout << this->id;
    cout << this->email;
    cout << this->phone_Number;
}