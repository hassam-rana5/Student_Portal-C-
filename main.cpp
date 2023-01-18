#include<iostream>
#include"Tree.h"
#include"Tree.cpp"
#include<cstring>
#include <sstream>
#include <fstream>
#include<iomanip>
#include<stdlib.h>
int main()
{

    Login log;
   // log.signup();// run it first if you run this program first otherwise do comment this statement
    GUI gui;
    log.open();
    string user;
    string pass;
    cout<<"Enter username : ";
    cin>>user;
    cout<<"Enter password : ";
    pass = getPassword();

    for (int i = 0; i < 3; ++i) {
        if(log.login(user,pass))
            gui.menu();
        else
        {
			system("CLS");
			cout<<"please enter valid username or password"<<endl;
			cout<<"Enter username : ";
			cin>>user;
			cout<<"Enter password : ";
			pass = getPassword();
		}
    }

    return 0;
}

