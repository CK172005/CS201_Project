#ifndef Transcation_H
#define Transcation_H

#include<bits/stdc++.h>
#include <regex>
#include <chrono>
#include <ctime> 
#include "../models/User.h"
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
    Transcation_Node(int money,User* from_user,User* to_user){
        if(from_user->account_balance<money){
            cout<<"Transcation can not happen Please deposit money into your account.";
            return ;
        }
        this->money=money;
        this->fromUser=from_user;
        this->ToUser=to_user;
        auto now = chrono::system_clock::now();
        time_t now_time_t = chrono::system_clock::to_time_t(now);
        tm local_tm = *localtime(&now_time_t);
        this->date_and_time=local_tm;
        from_user->account_balance = from_user->account_balance - money;
        to_user->account_balance = to_user->account_balance + money;
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
    void insertTranscation(int money,User* from_user,User* to_user){
        Transcation_Node* newTranscation =new Transcation_Node(money,from_user,to_user);
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
        while(curr){
                cout<<"Money: "<<curr->money<<endl;
                cout<<"From User: "<<curr->fromUser->name<<endl;
                cout<<"To User: "<<curr->ToUser->name<<endl;
                cout<<"Date: "<<put_time(&curr->date_and_time,"%d/%m/%Y")<<endl;
                cout<<"Time: "<<put_time(&curr->date_and_time,"%H:%M:%S")<<endl;
                cout<<endl;
                curr=curr->nextNode;
        }
    }

};

#endif 