// This Person header file was created by [TheAnhDoo]

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;
class Person {
private:
    string name;
    int age;
    string gender;

public:
    //Constructor
    Person();
    Person(string name, int age, string gender);
    //Setter
    void set_Name(string name);
    void set_Age(int age);
    void set_Gender(string gender);
    //Getter
    string get_Gender();
    string get_Name();
    int get_Age();
    //Display
    virtual void display();
};
#endif PERSON_H

