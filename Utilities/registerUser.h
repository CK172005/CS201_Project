#ifndef REGISTER_USER
#define REGISTER_USER

#include <bits/stdc++.h>
#include "../models/User.h"
#include "../Utilities/write_file.h"
using namespace std;


bool checkUserExist(User* new_user){
    DIR *dr;
    struct dirent *en;
    dr = opendir("database"); 
    if (dr == nullptr) {
        cerr << "Could not open current directory" << endl;
        return false; // Use EXIT_FAILURE for error exit codes
    }
    if (dr) {
      while ((en = readdir(dr)) != NULL) {
        if((string)(en->d_name)!="." && (string)(en->d_name)!=".."){
            string fileName="database/";
            fileName+=en->d_name;
            ifstream inputFile(fileName);
            // Check if the file was opened successfully
            if (!inputFile) {
                cerr << "Unable to open file" << endl;
                return false; // Exit with an error code
            }

            string line;

            map<string,string> keyValues;
            
            // Read the file line by line
            while (getline(inputFile, line)) {
                if (line.empty() || line[0] == '#') {
                    continue;
                }
                size_t delimiterPos = line.find(':');
                if (delimiterPos != std::string::npos) {
                    // Extract key and value
                    string key = line.substr(0, delimiterPos);
                    string value = line.substr(delimiterPos + 1);

                    // Trim whitespace (optional)
                    key.erase(key.find_last_not_of(" \n\r\t") + 1);
                    value.erase(0, value.find_first_not_of(" \n\r\t"));
                    keyValues[key]=value;
                }
            }
            if(new_user->name==keyValues["Name"] && new_user->dob==keyValues["DOB"] && new_user->phone_Number==keyValues["Phone Number"]){
                return true;
            }

            inputFile.close(); // Close the file

        }
      }
      closedir(dr); 
    }
    return false;
}

void registerUser(){
    string name,dob,phoneNumber,address;
    cout<<"Enter the User Name: ";
    cin>>name;

    cout<<"Enter your Phone Number: ";
    cin>>phoneNumber;

    cout<<"Enter your Date of Birth: ";
    cin>>dob;

    cout<<"Enter your Address: ";
    cin>>address;

    User* new_user=new User(name,dob,phoneNumber,address);

    if(checkUserExist(new_user)){
        cout<<"User Exist"<<endl;
        return;
    }
    new_user->generateAccountNumber();
    new_user->setPassword();
    writeInFile(new_user);
    
}


#endif //REGISTER_USER