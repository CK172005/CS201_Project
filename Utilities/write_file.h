#ifndef Write_file
#define Write_file

#include<bits/stdc++.h>
#include "../models/User.h"
using namespace std;

void writeInFile(User* new_user){
    // Adding the user to the database.
    string fileName="database/"+ new_user->Account_Number + ".txt";
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << "Name: " << new_user->name << "\n";
        outputFile << "DOB: " << new_user->dob << "\n";
        outputFile << "Phone Number: " << new_user->phone_Number << "\n";
        outputFile << "Address: " << new_user->Address << "\n";
        outputFile << "Account Number: " << new_user->Account_Number << "\n";
        outputFile << "Age: "<<new_user->age<<endl;
        outputFile << "Balance: "<<new_user->account_balance<<endl;

        outputFile.close();
    } else {
        cerr << "Unable to open file\n";
    }
}

#endif