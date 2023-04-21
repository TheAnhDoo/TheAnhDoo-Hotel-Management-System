// This implementation file was created by [TheAnhDo]
// Class Hotel implementation file



#include "Hotel.h"


//Constructor - Read data from the rooms.txt - list room already created before
Hotel::Hotel(){
    // Read room data from rooms.txt file
    ifstream roomFile("rooms.txt");
    string line;
    while (getline(roomFile, line)) {
        stringstream ss(line);
        string name, type, pricePerNightStr, isAvailableStr;
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, pricePerNightStr, ',');
        getline(ss, isAvailableStr, ',');
        double pricePerNight = stod(pricePerNightStr);
        bool isAvailable = (isAvailableStr == "yes");
        Room room(name, type, pricePerNight);
        room.setAvailability(isAvailable);
        rooms.push_back(room);
    }
    roomFile.close();
}



void Hotel::checkIn() {
    // Get customer information
    string name, gender, id, email, phone;
    int age;
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter customer name: \033[0m";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter customer age: \033[0m";
    cin >> age;
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter customer gender: \033[0m";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, gender);
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter customer ID: \033[0m";
    getline(cin, id);
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter customer email: \033[0m";
    getline(cin, email);
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter customer phone number: \033[0m";
    getline(cin, phone);

    // Register new customer
    Customer customer(name, age, gender, id, email, phone);
    customers.push_back(customer);

    // Get room name
    string roomName;
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter room name: \033[0m";
    getline(cin, roomName);

    // Check if room is available
    bool roomFound = false;
    bool roomAvailable = false;
    for (Room& room : rooms) {
        if (room.get_Room_Name() == roomName) {
            roomFound = true;
            if (room.get_Is_Available()) {
                roomAvailable = true;
                break;
            }
        }
    }

    if (!roomFound) {
        cout << "\033[0m\n\t\t\t\033[1m\033[33mRoom Not Found!!! \033[0m" <<endl;
        return;
    }

    if (!roomAvailable) {
        cout << "\033[0m\n\t\t\t\033[1m\033[33mRoom not available, choose another room \033[0m" << endl;

        // Show list of available rooms
        cout << "\033[0m\n\t\t\t\033[1m\033[33mList of available room: \033[0m" << endl;
        cout << "\t\t\t" << setw(15) << "\033[1m\033[31mRoom name" << setw(15) << "Room type" << setw(25) << "Price per night\033[0m" << endl;
        for (Room& room : rooms) {
            if (room.get_Is_Available()) {
                cout << "\t\t\t"
                     << "\033[1;34m" << setw(15) << left << room.get_Room_Name() << "\033[0m"
                     << setw(15) << left << room.get_Room_Type() 
                     << "\033[1;31mVND" << setw(14) << right << fixed << setprecision(2) << room.get_Price_Per_Night() << "\033[0m" << endl;
            }
        }
        return;
    }

    // Get staying days
    int stayingDays;
    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter staying days: \033[0m";
    cin >> stayingDays;
    // Update room availability
    for (Room& room : rooms) {
        if (room.get_Room_Name() == roomName) {
            room.setAvailability(false);
            break;
        }
    }

    // Update rooms.txt file
    ifstream inFile("rooms.txt");
    ofstream outFile("temp.txt");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, type, pricePerNight, isAvailable;
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, pricePerNight, ',');
        getline(ss, isAvailable, ',');
        if (name == roomName) {
            outFile << name << "," << type << "," << pricePerNight << ",no" << endl; // no means not available
        }
        else {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();
    remove("rooms.txt");
    rename("temp.txt", "rooms.txt");

    // Add customer data to customers.txt file
    ofstream file("customers.txt", ios_base::app);
    file << id << "," << stayingDays << "," << roomName << endl;
    file.close();
}
void Hotel::checkOut() {
    // Get customer ID
    string customerId;
    cout << "Enter customer ID: ";
    cin >> customerId;

    // Read customer data from CSV file
    vector<string> lines;
    ifstream inFile("customers.txt");
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Find and remove customer
    bool customerFound = false;
    double totalPrice = 0.0;
    string roomName;
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        stringstream ss(*it);
        string id, stayingDaysStr;
        getline(ss, id, ',');
        getline(ss, stayingDaysStr, ',');
        getline(ss, roomName, ',');
        if (id == customerId) {
            int stayingDays = stoi(stayingDaysStr);
            for (Room& room : rooms) {
                if (room.get_Room_Name() == roomName) {
                    totalPrice = stayingDays * room.get_Price_Per_Night();
                    break;
                }
            }
            lines.erase(it);
            customerFound = true;
            break;
        }
    }

    // Write updated customer data to CSV file
    ofstream outFile("customers.txt");
    for (string& line : lines) {
        outFile << line << endl;
    }
    outFile.close();

    // Update room data in rooms.txt file
    if (customerFound) {
        ifstream inFile("rooms.txt");
        ofstream outFile("temp.txt");
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, type, pricePerNight, isAvailable;
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, pricePerNight, ',');
            getline(ss, isAvailable, ',');
            if (name == roomName) {
                outFile << name << "," << type << "," << pricePerNight << ",yes" << endl; // yes means available
            }
            else {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove("rooms.txt");
        rename("temp.txt", "rooms.txt");
    }

    // Print receipt
    cout << "Total price: " << totalPrice <<" VND" << endl;
}

void Hotel::viewAllRoomStatus() {
    cout << "\n\t\t\t\t\033[1;34mROOM STATUS\033[0m\n";
    cout << "\t-------------------------------------------------------------------\n";
    cout << "\t| \033[1;32mRoom Name\033[0m          \033[1;32mRoom Type\033[0m    \033[1;32mPrice Per Night\033[0m       \033[1;32mAvailability\033[0m |\n";
    for (Room& room : rooms) {
        cout << "\t| " << setw(15) << left << room.get_Room_Name()
            << setw(15) << left << room.get_Room_Type()
            << "\033[1;31mVND" << setw(14) << right << fixed << setprecision(2) << room.get_Price_Per_Night() << "\033[0m"
             <<right <<setw(19) << (room.get_Is_Available() ? "Available" : "Not available") << " |\n";
    }
    cout << "\t-------------------------------------------------------------------\n";
}

void Hotel:: viewCustomerInformation() {
    // Get customer ID
    string customerId;
    cout << "Enter customer ID: ";
    cin >> customerId;

    // Find customer
    bool customerFound = false;
    for (Customer& customer : customers) {
        if (customer.get_Id() == customerId) {
            // Display customer information
            cout << "\n\t\t\t\t\t\t\033[1;34mCUSTOMER INFORMATION\033[0m\n";
            cout << "\t----------------------------------------------------------------------------------------------\n";
            cout << "\t| \033[1;32mName\033[0m\t\t\033[1;32mAge\033[0m\t\t\033[1;32mGender\033[0m\t\t\033[1;32mID\033[0m\t\t\033[1;32mEmail\033[0m\t\t\033[1;32mPhone Number\033[0m |\n";
            cout << "\t| " << setw(15) << left << customer.get_Name()
                << setw(15) << left << customer.get_Age()
                << setw(15) << left << customer.get_Gender()
                << setw(15) << left << customer.get_Id()
                << setw(15) << left << customer.get_Email()
                << setw(15) << left << customer.get_Phone_Number() << " |\n";
            cout << "\t----------------------------------------------------------------------------------------------\n";

            customerFound = true;
            break;
        }
    }

    if (!customerFound) {
        cout << "\033[1;31mCustomer not found\033[0m" << endl;
    }
}
void Hotel::viewAllCustomer() {
    cout << "\n\t\t\t\t\t\t\033[1;34mCUSTOMER INFORMATION\033[0m\n";
    cout << "\t----------------------------------------------------------------------------------------------\n";
    cout << "\t| \033[1;32mName\033[0m\t\t\033[1;32mAge\033[0m\t\t\033[1;32mGender\033[0m\t\t\033[1;32mID\033[0m\t\t\033[1;32mEmail\033[0m\t\t\033[1;32mPhone Number\033[0m |\n";
    for (Customer& customer : customers) {
        cout << "\t| " << setw(15) << left << customer.get_Name()
            << setw(15) << left << customer.get_Age()
            << setw(15) << left << customer.get_Gender()
            << setw(15) << left << customer.get_Id()
            << setw(15) << left << customer.get_Email()
            << setw(15) << left << customer.get_Phone_Number() << " |\n";
    }
    cout << "\t----------------------------------------------------------------------------------------------\n";
}

void Hotel::changeCustomerInformation() {
    // Get customer ID
    string customerId;
    cout << "Enter customer ID: ";
    cin >> customerId;

    // Find customer in customers vector and update information
    bool customerFound = false;
    for (Customer& customer : customers) {
        if (customer.get_Id() == customerId) {
            // Update customer information
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input stream

            int choice = 0;
            while (choice != 6) {
                cout << endl;
                cout << "\033[1m\033[36m";
                cout << "===================================" << endl;
                cout << "=          Edit Customer          =" << endl;
                cout << "===================================" << endl;
                cout << "= 1. Name                         =" << endl;
                cout << "= 2. Age                          =" << endl;
                cout << "= 3. Gender                       =" << endl;
                cout << "= 4. Email                        =" << endl;
                cout << "= 5. Phone number                 =" << endl;
                cout << "= 6. Remove Customer              =" << endl;
                cout << "= 7. Done                         =" << endl;
                cout << "===================================" << endl;
                cout << "\033[0m";

                // Get user choice
                cout << "\033[1m\033[33mEnter your choice (1-6): \033[0m";
                cin >> choice;

                // Perform action based on user choice
                string input;
                switch (choice) {
                case 1:
                    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter new name: \033[0m";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, input);
                    customer.set_Name(input);
                    break;
                case 2:
                    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter new age: \033[0m";
                    cin >> input;
                    customer.set_Age(stoi(input));
                    break;
                case 3:
                    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter new gender: \033[0m";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, input);
                    customer.set_Gender(input);
                    break;
                case 4:
                    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter new email: \033[0m";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, input);
                    customer.set_Email(input);
                    break;
                case 5:
                    cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter new phone number: \033[0m";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, input);
                    customer.set_Phone_Number(input);
                    break;
                case 6:
                    break;
                default:
                    cout << "\n\t\t\t\033[1m\033[35mInvalid choice!!!\033[0m" << endl;
                }
            }
            // Indicate that a customer has been found and updated
            customerFound = true;
            break;
        }
    }

    if (!customerFound) {
        cout << "\n\t\t\t\033[1m\033[35mCustomer not found\033[0m" << endl;
        return;
    }

    // Read customer data from CSV file
    vector<string> lines;
    ifstream inFile("customers.txt");
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Find customer and update information
    for (string& line : lines) {
        stringstream ss(line);
        string id, stayingDaysStr, roomNameStr;
        getline(ss, id, ',');
        getline(ss, stayingDaysStr, ',');
        getline(ss, roomNameStr, ',');

        if (id == customerId) {
            // Find updated customer in customers vector
            for (Customer& customer : customers) {
                if (customer.get_Id() == customerId) {
                    // Update line with new customer information
                    line = id + "," + stayingDaysStr + "," + roomNameStr + "," +
                        customer.get_Name() + "," + to_string(customer.get_Age()) + "," +
                        customer.get_Gender() + "," + customer.get_Email() + "," +
                        customer.get_Phone_Number();
                    break;
                }
            }
            break;
        }
    }

    // Write updated customer data to CSV file
    ofstream outFile("customers.txt");
    for (string& line : lines) {
        outFile << line << endl;
    }
    outFile.close();
}

void Hotel::addRoom() {
    // Get room information
    string roomName, roomType;
    double pricePerNight;
    cout << "\t\t\t\033[1m\033[33mEnter room name: \033[0m";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, roomName);
    cout << "\t\t\t\033[1m\033[33mEnter room type: \033[0m";
    getline(cin, roomType);
    cout << "\t\t\t\033[1m\033[33mEnter price per night: \033[0m";
    cin >> pricePerNight;
    Room room(roomName, roomType, pricePerNight);

    rooms.push_back(room);

    // Write room information to CSV file
    ofstream file;
    file.open("rooms.txt", ios_base::app);
    file << room.get_Room_Name() << "," << room.get_Room_Type() << "," << room.get_Price_Per_Night() << ",yes" << endl; // yes means available
    file.close();
}

void Hotel::mainMenu() {
    int choice;
    do {
        cout << "\033[1m\033[36m";
        cout << "\t\t\t.----------------------------------------." << endl;
        cout << "\t\t\t|             HOTEL MANAGEMENT           |" << endl;
        cout << "\t\t\t|                  NHOM 1                |" << endl;
        cout << "\t\t\t|----------------------------------------|" << endl;
        cout << "\t\t\t| \033[0m\033[1m\033[37m1. Check in       \033[0m\033[1m\033[36m| \033[0m\033[1m\033[37m2. Check out       \033[0m\033[1m\033[36m|" << endl;
        cout << "\t\t\t|----------------------------------------|" << endl;
        cout << "\t\t\t| \033[0m\033[1m\033[37m3. View all rooms \033[0m\033[1m\033[36m| \033[0m\033[1m\033[37m4. View customer   \033[0m\033[1m\033[36m|" << endl;
        cout << "\t\t\t|----------------------------------------|" << endl;
        cout << "\t\t\t| \033[0m\033[1m\033[37m5. Change customer\033[0m\033[1m\033[36m| \033[0m\033[1m\033[37m6. View all        \033[0m\033[1m\033[36m|" << endl;
        cout << "\t\t\t|    \033[0m\033[1m\033[37minformation    \033[0m\033[1m\033[36m|    \033[0m\033[1m\033[37mcustomers       \033[0m\033[1m\033[36m|" << endl;
        cout << "\t\t\t|----------------------------------------|" << endl;
        cout << "\t\t\t| \033[0m\033[1m\033[37m7. Add room       \033[0m\033[1m\033[36m| \033[0m\033[1m\033[37m8. Exit            \033[0m\033[1m\033[36m|" << endl;
        cout << "\t\t\t'----------------------------------------'" << endl;
        cout << "\033[0m\n\t\t\t\033[1m\033[33mEnter your choice: \033[0m";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            checkIn();
            cout << "\n\t\t\t\033[1m\033[35mCheckin complete!! \n\t\t Please press any key to continue...\033[0m" << endl;
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            checkOut();
            cout << "\n\t\t\t\033[1m\033[35mCheckout complete!! \n\t\t Please press any key to continue...\033[0m" << endl;
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            viewAllRoomStatus();
            cout << "\n\t\t\t\033[1m\033[35mPlease press any key to continue...\033[0m" << endl;
            _getch();
            system("cls");
            break;
        case 4:
            system("cls");
            viewCustomerInformation();
            cout << "\n\t\t\t\033[1m\033[35mPlease press any key to continue...\033[0m" << endl;
            _getch();
            system("cls");
            break;

        case 5:
            system("cls");
            changeCustomerInformation();
            cout << "\n\t\t\t\033[1m\033[35mPlease press any key to continue...\033[0m" << endl;
            _getch();
            system("cls");
            break;
        case 6:
            system("cls");
            viewAllCustomer();
            cout << "\n\t\t\t\033[1m\033[35mPlease press any key to continue...\033[0m" << endl;
            _getch();
            system("cls");
            break;
        case 7:
            system("cls");
            addRoom();
            cout << "\n\t\t\t\033[1m\033[35mPlease press any key to continue...\033[0m" << endl;
            _getch();
            system("cls");
            break;
        case 8:
            system("cls");           
            cout << "\n\t\t\t\033[1m\033[35mExiting the program...\033[0m" << endl;
            _getch();
            break;
        default:
            system("cls");
            cout << "\n\t\t\t\033[1m\033[35mInvalid choice.\n\t\t Please press any key to try again.\033[0m" << endl;
            _getch();
            system("cls");
            break;
        }
    } while (choice != 8);
}

