#ifndef User_H
#define User_H

#include<bits/stdc++.h>
#include "../Utilities/ageCalculator.cpp"
#include "../Utilities/read_files.cpp"
using namespace std;

class User{
    public:
    string name="";
    string dob="";
    string phone_Number="";
    string Account_Number="";
    string Address="";
    int age=0;
    int account_balance=0; 
    tm* createdTime;
    
    private:
        string password="";


    public:
    User(string name,string dob,string phone_Number,string Address){
        this->name=name;
        this->dob=dob;
        this->phone_Number=phone_Number;
        this->Address=Address;
        auto now = chrono::system_clock::now();
    
        // Convert to time_t for easy handling
        time_t now_c = chrono::system_clock::to_time_t(now);
        
        // Store the current date and time
        tm* local_time = localtime(&now_c);
        this->createdTime=local_time;
        this->age=ageCalculator(dob);
        this->generateAccountNumber();
        this->setPassword();

        // Adding the user to the database.
        string fileName="database/"+ this->Account_Number + ".txt";
        ofstream outputFile(fileName);
        if (outputFile.is_open()) {
            outputFile << "Name: " << this->name << "\n";
            outputFile << "DOB: " << this->dob << "\n";
            outputFile << "Phone Number: " << this->phone_Number << "\n";
            outputFile << "Address: " << this->Address << "\n";
            outputFile << "Account Number: " << this->Account_Number << "\n";

            outputFile.close();
        } else {
            cerr << "Unable to open file\n";
        }


    }
    void generateAccountNumber(){
        string characters="0123456789";
        bool done=false;
        BTree* root=read_Data();
        while(done!=true){
            string accountNumber;
            for(int i=0;i<11;i++){
                char characterToPush=characters[rand()%characters.size()];
                accountNumber.push_back(characterToPush);
            }
            if(root->search(convertIntoNumber(accountNumber))==false){
                this->Account_Number=accountNumber;
                done=true;
            }
        }
    }
    void setPassword(){
        cout<<"Enter the 6 digit password: ";
        string pasword;
        cin>>password;
        while(password.length()!=6){
            cout<<"Please enter the password of 6 digit."<<endl;
            cin>>password;
        }
        cout<<"Are you sure you want to add this password?"<<endl;
        cout<<"Enter Y for yes and N for no."<<endl;
        string confirmation;
        cin>>confirmation;
        if(confirmation=="Y" || confirmation=="y"){
            this->password=password;
        }
        else{
            setPassword();
        }

    }
    void changePhoneNumber(string newNumber){
        cout<<"Are you sure you want to change the Phone Number?"<<endl;
        cout<<"Enter Y for yes and N for no."<<endl;
        string confirmation;
        cin>>confirmation;
        if(confirmation=="Y" || confirmation=="y"){
            this->phone_Number=newNumber;
        }
    }
    void changePassword(string newPassword){
        cout<<"Are you sure you want to change the password?"<<endl;
        cout<<"Enter Y for yes and N for no."<<endl;
        string confirmation;
        cin>>confirmation;
        if(confirmation=="Y" || confirmation=="y"){
            this->password=newPassword;
        }
    }
    void depositMoney(int moneyToDeposit){
        this->account_balance=this->account_balance+moneyToDeposit;
    }
    void withdrawMoney(int moneyToWithDraw){
        this->account_balance=this->account_balance-moneyToWithDraw;
    }
};

#endif