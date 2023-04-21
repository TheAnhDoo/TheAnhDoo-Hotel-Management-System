// This implementation file was created by [TheAnhDo]
// Class Person implementation file

#include "Person.h"

using namespace std;
//Constructor
Person::Person() : name(""), age(0), gender("") {}

Person::Person(string name, int age, string gender)
    : name(name), age(age), gender(gender) {}
//Setter
void Person::set_Name(string name) {
    this->name = name;
}

void Person::set_Age(int age) {
    this->age = age;
}

void Person::set_Gender(string gender) {
    this->gender = gender;
}
//Getter
string Person::get_Gender() {
    return this->gender;
}

string Person::get_Name() {
    return this->name;
}

int Person::get_Age() {
    return this->age;
}
//Display
void Person::display() {
    cout << this->name;
    cout << this->age;
    cout << this->gender;
}