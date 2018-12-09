/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kimkyu9
 *
 * Created on November 27, 2018, 6:13 PM
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    string line;
    string command;
    string name, status;
    unsigned int IPaddress;
    TreeDB db;
    
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input
    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;  
        if (command == "insert")
        {
            bool check;
            lineStream >> name;
            lineStream >> IPaddress;
            lineStream >> status;
            DBentry *nptr;
            if (status == "active")
            {
                nptr = new DBentry(name, IPaddress, true);
                check = db.insert(nptr);
            }
            else 
            {
                nptr = new DBentry(name, IPaddress, false);
                check = db.insert(nptr);
            }
            if (check == false)
            {
                delete nptr;
                cout << "Error: entry already exists"<< endl;
            }
            else cout << "Success" << endl;
        }
        if (command ==  "find")
        {
            lineStream >> name;
            if (db.find(name) != NULL)
            {
                cout << *db.find(name);
            }
            else cout << "Error: entry does not exist" << endl;
            
        }
        if (command ==  "remove")
        {
            lineStream >> name;
            if (db.remove(name) == true)
            {
                cout<< "Success" << endl;
            }
            else cout << "Error: entry does not exist" << endl;
        }
        if (command == "printall")
        {
            cout << db;
        }
        if (command == "printprobes")
        {
            lineStream >> name;
            if (db.find(name) == NULL)
            {
                cout << "Error: entry does not exist" << endl;
            }
            else db.printProbes();
        }
        if (command ==  "removeall")
        {
            db.clear();
            cout << "Success" << endl;
        }
        if (command ==  "countactive")
        {
            db.countActive();
        }
        if (command ==  "updatestatus")
        {
            DBentry * temp;
            bool error = true;
            lineStream >> name;
            lineStream >> status;
            temp = db.find(name);
            if (temp == NULL)
            {
                cout << "Error: entry does not exist" << endl;
                error = false;
            }
            if (error)
            {
                if (status == "active")
                    temp->setActive(true);
                else temp->setActive(false);
                cout << "Success" << endl;
            }
        }
                
//        // Once the command has been processed, prompt for the
//        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
        
    }
    db.clear();
}