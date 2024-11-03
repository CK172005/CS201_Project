#include<bits/stdc++.h>
#include "./Utilities/registerUser.h"
#include "./Utilities/loginUser.h"
#include "./models/Transcation.h"
#include "./Utilities/fetchUser.h"
#include "./models/employee.h"
using namespace std;

int main(){
    primeFiller(15000);
    cout<<"...........................................\n";
    cout<<"     Welcome to Bank Management System     \n";
    cout<<"...........................................\n";

    char in = 'L';
    while(in != 'Q' ){
        char input;
        cout<<"Press E for Employee"<<endl<<"Press U for User"<<endl<<"Press Q for Exit\n";
        cin>>input;
        if (input == 'U' || input == 'u'){
                cout<<"-------------------------------------------\n";
                cout<<"|          Welcome User Portal              |\n";
                cout<<"--------------------------------------------\n";

                char choice;
                cout<<"Press C to create Account"<<endl;
                cout<<"Press L to login your Account\n";
                cin>>choice;

                if (choice == 'L' || choice == 'l'){

                    User* user1=loginUser();
                    getUserTranscation(user1);
                    if (user1 == NULL){
                        continue;
                    }
                    char pi = 'P';
                    while (pi != 'B'){

                        cout<<"\nPress I to show User Details"<<endl;
                        cout<<"Press C to check Balance"<<endl;
                        cout<<"Press D to deposit Cash"<<endl;
                        cout<<"Press W to Withdraw Cash"<<endl;
                        cout<<"Press T for Transections"<<endl;
                        cout<<"Press H to show Transection History\n";
                        cout<<"Press B for Back\n";

                        char process;
                        cin>>process;
                        if (process == 'I' || process == 'i'){

                            cout<<"Account holder Name : "<<user1->name<<endl;
                            cout<<"Account Number      : "<<user1->Account_Number<<endl;
                            cout<<"Address             : "<<user1->Address<<endl;
                            cout<<"phone number        : "<<user1->phone_Number<<endl;
                            cout<<"DOB(dd/mm/yyyy)     : "<<user1->dob<<endl;
                            cout<<"Age                 : "<<user1->age<<endl;
                            cout<<"Current Balance     : "<<user1->account_balance<<"\n";
                        }

                        else if (process == 'C' || process == 'c'){

                            cout<<"Account holder Name : "<<user1->name<<endl;
                            cout<<"Account Number      : "<<user1->Account_Number<<endl;
                            cout<<"Current Balance     : "<<user1->account_balance<<"\n";
                        }

                        else if (process == 'D' || process == 'd' ){
                            int deposit_money;
                            cout<<"Enter the Ammount you want to deposit:\n";
                            cin>>deposit_money;
                            do_Transcation(deposit_money,user1,user1);
                            user1->depositMoney(deposit_money);
                            writeTranscationInFile(user1);

                            cout<<"Rs. "<<deposit_money<<" deposited to your Current Account.";
                            cout<<"\nCurrent Balance: "<<user1->account_balance<<"\n";

                        }

                        else if (process == 'W' || process == 'w'){
                            int withdraw_money;
                            cout<<"Enter the Ammount you want to withdraw:\n";
                            cin>>withdraw_money;
                            if(user1->account_balance<withdraw_money){
                                    cout<<"Withdraw can not happen ,Please deposit money into your account.\n";
                            }
                            else{
                                do_Transcation(withdraw_money,user1,user1);
                                user1->withdrawMoney(withdraw_money);
                                writeTranscationInFile(user1);
                                cout<<"\nCurrent Balance: "<<user1->account_balance<<"\n";
                            }

                        }

                        else if (process == 'T' || process == 't'){
                            string reciver_acc_no;
                            User* user2=NULL;
                            char delta = 'd';
                            while(delta != 'x'){
                                cout<<"Enter the Recivers Account No.: \n";
                                cin>>reciver_acc_no;
                                if(reciver_acc_no=="B" || reciver_acc_no=="b"){
                                    delta = 'x';
                                }
                                else if (reciver_acc_no.size() == 11 && convertToLongLong(reciver_acc_no)){
                                    user2 = getUser(reciver_acc_no);
                                    if (user2 != NULL){
                                        delta = 'x';
                                        break;
                                    }
                                   
                                }
                                else{
                                    cout<<"Invalid Account number\n";
                                }
                            }                       
                            if(user2!=NULL){
                                int transection_ammount;
                                cout<<"Enter the ammount you want to send to recivers account:";
                                cin>>transection_ammount;
                                if (user1->account_balance<transection_ammount){
                                    cout<<"Transection can not happen ,Please deposit money into your account.\n";
                                }
                                else{
                                    string password;
                                    for (int i = 1; i<= 3; i++){
                                        cout<<"Enter the Password";
                                        password = getHiddenInput();
                                        if (password == user1->password){
                                            char ch;
                                            cout<<"Are you sure you want to proceed the transection,if yes press 'Y' ,else 'N': ";
                                            cin>>ch;
                                            if (ch == 'Y' || ch == 'y'){
                                                do_Transcation(transection_ammount,user1,user2);
                                                cout<<"Current Balance: "<<user1->account_balance<<"\n";
                                                cout<<"Transcation Id: "<<user1->transcation_history->tail->Transcation_Id<<endl;
                                                cout<<"Money: "<<user1->transcation_history->tail->money<<endl;
                                                cout<<"From User: "<<user1->transcation_history->tail->fromUser->Account_Number<<endl;
                                                cout<<"To User: "<<user1->transcation_history->tail->ToUser->Account_Number<<endl;
                                                cout<<"Date: "<<put_time(&user1->transcation_history->tail->date_and_time,"%d/%m/%Y")<<endl;
                                                cout<<"Time: "<<put_time(&user1->transcation_history->tail->date_and_time,"%H:%M:%S")<<endl;
                                                cout<<endl;
                                                break;
                                            }
                                            else if (ch == 'N' || ch == 'n'){
                                                cout<<"Transection not proceed\n";
                                                break;
                                            }
                                        }
                                        else {
                                            cout<<"Incorrect password";
                                            continue;
                                        }
                                    }
                                }
                            }
                        }

                        else if (process == 'H' || process == 'h'){
                            cout<<"Your Transcation History: "<<endl;
                            user1->transcation_history->displayTranscation();
                        }

                        else if (process == 'B' || process == 'b'){
                            pi = 'B';
                        }

                    }
                }
                else if (choice == 'C' || choice == 'c'){
                    registerUser();
                }
        }
        else if(input =='E'){
            bool logined=loginEmployee();
            if(logined==true){
                char choice='A';
                while(choice!='Q'){
                    cout<<"Please Enter D to show all the account present"<<endl;
                    cout<<"Please Enter M to show all the minor accounts"<<endl;
                    cout<<"Please Enter S to search the user"<<endl;
                    cout<<"Please Enter Q to Quit."<<endl;
                    cin>>choice;
                    if(choice=='Q'){
                        break;
                    }
                    else if(choice =='D'){
                        displayAccounts();
                    }
                    else if(choice == 'M'){
                        displayMinor();
                    }
                    else if(choice =='S'){
                        string accountNumber;
                        cout<<"Enter the account Number you want to search: ";
                        cin>>accountNumber;
                        User* user=getUser(accountNumber);
                        if(user==NULL){
                            cout<<"User does not Exist."<<endl;
                        }
                        else{
                            char c='T';
                            cout<<"Please Enter I to see all information of user"<<endl;
                            cout<<"Please enter C to check Balance: "<<endl;
                            cout<<"Please enter D to delete User: "<<endl;
                            cout<<"Please enter H to see transcation history: "<<endl;
                            cout<<"Please enter Q to quit: "<<endl;
                            while(c!='Q'){
                                cin>>c;
                                if(c=='C' || c=='c'){
                                    cout<<"User has Account Balance: "<<user->account_balance<<endl;
                                }
                                else if(c=='D' || c=='d'){
                                    string fileName="database/"+user->Account_Number+".txt";
                                    if (remove(fileName.c_str()) == 0) {
                                        cout << "user deleted successfully." << endl;
                                        break;
                                    } else {
                                        cerr << "Error while deleting user.." << endl;
                                    }
                                }
                                else if(c=='H' || c=='h'){
                                    user->transcation_history->displayTranscation();
                                }
                                else if(c=='I' || c=='i'){
                                    cout<<"Account holder Name : "<<user->name<<endl;
                                    cout<<"Account Number      : "<<user->Account_Number<<endl;
                                    cout<<"Address             : "<<user->Address<<endl;
                                    cout<<"phone number        : "<<user->phone_Number<<endl;
                                    cout<<"DOB(dd/mm/yyyy)     : "<<user->dob<<endl;
                                    cout<<"Age                 : "<<user->age<<endl;
                                    cout<<"Current Balance     : "<<user->account_balance<<"\n";
                                    
                                }

                            }
                        }
                    }
                }
                
            }
        }
        else if(input =='Q' || input == 'q'){
            in ='Q';
        }
        cout<<"\n";
    }
}


