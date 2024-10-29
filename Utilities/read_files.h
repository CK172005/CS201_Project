#ifndef Read_file
#define Read_file


#include<bits/stdc++.h>
#include <dirent.h>
#include <sys/types.h>
#include "../Utilities/BTree.h"
using namespace std;


long long convertIntoNumber(string num){
    long long ans=0;
    string temp;
    for(int i=0;i<5;i++){
        temp.push_back(num[i]);
    }
    long long firstFive=((stoi)(temp));
    firstFive=firstFive*1000000;
    ans+=firstFive;
    string temp2;
    for(int i=5;i<11;i++){
        temp2.push_back(num[i]);
    }
    long long lastSixDigit=(stoi)(temp2);
    ans+=lastSixDigit;
    return ans;
}


BTree* read_Data() {
   DIR *dr;
   struct dirent *en;
   BTree* root=new BTree();
   dr = opendir("database"); 
    if (dr == nullptr) {
        cerr << "Could not open current directory" << endl;
        return NULL; // Use EXIT_FAILURE for error exit codes
    }
    if (dr) {
      while ((en = readdir(dr)) != NULL) {
        if((string)(en->d_name)!="." && (string)(en->d_name)!=".."){
            string fileName=en->d_name;
            fileName.erase(11,14);
            long long number=convertIntoNumber(fileName);
            root->insert(number);
        }
      }
      closedir(dr); 
    }
    return root;
}


#endif