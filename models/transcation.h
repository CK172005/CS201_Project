#ifndef Transcation_H
#define Transcation_H

#include<bits/stdc++.h>
#include <regex>
#include <chrono>
#include <ctime> 
// #include "../Utilities/fetchUser.cpp"
#include "../Utilities/write_file.h"
using namespace std;




class Transcation_Node{
    public:
    int money=0;
    User* fromUser;
    User* ToUser;
    string Transcation_Id;
    tm date_and_time;
    Transcation_Node* previousNode=NULL;
    Transcation_Node* nextNode=NULL;
    public:
    // Transcation_Node(int money, string from_user_account, string to_user_account){
    //     User* from_user=getUserDetails(from_user_account);
    //     User* to_user=getUserDetails(to_user_account);
    //     // Adding Information
    //     this->money=money;
    //     this->fromUser=from_user;
    //     this->ToUser=to_user;
    // }
    Transcation_Node(int money, User* from_user, User* to_user){
        // Adding Information
        this->money=money;
        this->fromUser=from_user;
        this->ToUser=to_user;
    }
    void generateTranscationId(){
        string transcation_id;
        tm dateTime=this->date_and_time;
        transcation_id+=(to_string)(dateTime.tm_year+1900);
        transcation_id+=(to_string)(dateTime.tm_mon+1);
        transcation_id+=(to_string)(dateTime.tm_mday);
        transcation_id+=(to_string)(dateTime.tm_hour);
        transcation_id+=(to_string)(dateTime.tm_min);
        transcation_id+=(to_string)(dateTime.tm_sec);
        for(int i=0;i<5;i++){
            transcation_id+=fromUser->Account_Number[i];
            transcation_id+=ToUser->Account_Number[i];
        }
        this->Transcation_Id=transcation_id;

    }
};


class Transcation{
    public:
    Transcation_Node* head;
    Transcation_Node* tail;
    
    Transcation(){
        head=NULL;
        tail=NULL;
    }
    void insertTranscation(Transcation_Node* newTranscation){
        if(head==NULL){
            head=newTranscation;
            tail=newTranscation;
        }
        tail->nextNode=newTranscation;
        newTranscation->previousNode=tail;
        newTranscation->nextNode=NULL;
        tail=newTranscation;
    }
    void displayTranscation(){
        Transcation_Node* curr=head;
        if(curr==NULL){
            return;
        }
        while(curr){
                cout<<"Transcation Id: "<<curr->Transcation_Id<<endl;
                cout<<"Money: "<<curr->money<<endl;
                cout<<"From User: "<<curr->fromUser->Account_Number<<endl;
                cout<<"To User: "<<curr->ToUser->Account_Number<<endl;
                cout<<"Date: "<<put_time(&curr->date_and_time,"%d/%m/%Y")<<endl;
                cout<<"Time: "<<put_time(&curr->date_and_time,"%H:%M:%S")<<endl;
                cout<<endl;
                curr=curr->nextNode;
        }
    }

};

void writeTranscationInFile(User* new_user){
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
        outputFile << "Transcation: ";
        Transcation_Node* curr=new_user->transcation_history->head;
        while(curr){
            outputFile <<endl;
            outputFile <<"Transcation Id: "<<curr->Transcation_Id<<endl;
            outputFile <<"Money: "<<curr->money<<endl;
            outputFile <<"From User: "<<curr->fromUser->Account_Number<<endl;
            outputFile <<"To User: "<<curr->ToUser->Account_Number<<endl;
            outputFile <<"Date: "<<put_time(&curr->date_and_time,"%d/%m/%Y")<<endl;
            outputFile <<"Time: "<<put_time(&curr->date_and_time,"%H:%M:%S")<<endl;
            outputFile <<endl;
            curr=curr->nextNode;
        }

        outputFile.close();
    } else {
        cerr << "Unable to open file\n";
    }
}

void do_Transcation(int money,User* from_user,User* to_user){
    if(from_user->account_balance<money){
        cout<<"Transcation can not happen Please deposit money into your account.";
        return ;
    }
    from_user->account_balance = from_user->account_balance - money;
    to_user->account_balance = to_user->account_balance + money;

    Transcation_Node* newTranscation =new Transcation_Node(money,from_user,to_user);
    newTranscation->generateTranscationId();
    cout<<newTranscation->Transcation_Id<<endl;
    from_user->transcation_history->insertTranscation(newTranscation);
    to_user->transcation_history->insertTranscation(newTranscation);

    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&now_time_t);
    newTranscation->date_and_time=local_tm;

    writeTranscationInFile(from_user);
    writeTranscationInFile(to_user);
}

#endif 
