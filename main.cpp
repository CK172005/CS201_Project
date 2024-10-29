#include<bits/stdc++.h>
#include "./Utilities/write_file.h"
#include "./models/Transcation.h"
using namespace std;



int main(){
    User* newUser=new User("Hello","10/12/2005","10934011","dfjhaoij");
    User* newUser2=new User("World","12/10/2000","34214209348","djkafkdjfoiw");
    writeInFile(newUser);
    writeInFile(newUser2);
    newUser->depositMoney(10000);

    newUser->transcation_history=new Transcation();
    newUser2->transcation_history=new Transcation();

    do_Transcation(1000,newUser,newUser2);
    do_Transcation(500,newUser2,newUser);

    cout<<"New User 2 Transcation"<<endl;
    newUser2->transcation_history->displayTranscation();
    cout<<"New user Transcation"<<endl;
    newUser->transcation_history->displayTranscation();
    
}


