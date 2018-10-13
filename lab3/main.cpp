//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray = NULL;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

void compCom (string com, string arg);
void compArg (string arg);

int main() {

    string line;
    string command;
    string name, type, temp;
    int maxShape, locx, locy, sizex, sizey, angle, cnt = 0;
    
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input
    while (!cin.eof()) {
        bool legit = false;
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        for(int i = 1; i < 7; i++)
        {
            if (command == keyWordsList[i])
            {
                legit = false;
                if (i==1 && cnt == 0)
                {
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    lineStream >> maxShape;
                    if (lineStream.fail() || maxShape < 1)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }
                    lineStream >> skipws;
                    if (!lineStream.eof())
                    {
                        cout << "Error: too many arguments" << endl;
                        break;
                    }
                    cout << "New database: max shapes is " << maxShape << endl;
                    cnt++;
                    legit = true;
                    break;
                }
                else if (cnt > 0 && i==1)
                {
                    cout<< i << endl;
                    cout << "youve done this already" << endl;
                    break;
                }
                else if (i==2)
                {
                    bool flag = false;
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    
                    lineStream >> name;
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    for (int j = 1; j < 7; j++)
                    {
                        if(name == keyWordsList[j])
                        {
                            cout << "Error: invalid shape name" << endl;
                            flag = true;
                            break;
                        }
                    }
                    for (int j = 0; j < 3; j++)
                    {
                        if (name == shapeTypesList[j])
                        {
                            cout << "Error: invalid shape type" << endl;
                            flag = true;
                            break;
                        }
                    }
                    for (int j = 0; j < maxShape; j++)
                    {
                        if (shapesArray[j] != NULL && name == shapesArray[j] -> getName())
                        {
                            cout << "Error: shape " << shapesArray[j] -> getName() << " already exists" << endl;
                            flag = true;
                            break;
                        }
                    }
                    if (flag == true)
                    {
                        break;
                    }
     
                    lineStream >> type;
                    flag = false;
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    for (int j = 0; j < 3; j++)
                    {
                        if (type == shapeTypesList [j])
                        {
                            flag = true;
                        }
                    }
                    if (flag == false)
                    {
                        cout << "Error: invalid shape type" << endl;
                        break;
                    }
                   
                    lineStream >> locx;
                    if (lineStream.fail())
                    {
                        if (lineStream.eof())
                        {
                            cout << "Error: too few arguments" << endl;
                            break;
                        }
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                    if (locx < 0)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }                    
                    lineStream >> locy;
                    if (lineStream.fail())
                    {
                        if (lineStream.eof())
                        {
                            cout << "Error: too few arguments" << endl;
                            break;
                        }
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                    if (locy < 0)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }
                    
                    lineStream >> sizex;
                    if (lineStream.fail())
                    {
                        if (lineStream.eof())
                        {
                            cout << "Error: too few arguments" << endl;
                            break;
                        }
                        cout << "Error: invalid argument" << endl;
                        break;
                    }                    
                    if (sizex < 1)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }
                    lineStream >> sizey;
                    
                    if (lineStream.fail())
                    {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                    if (sizey < 1)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }
                    lineStream >> skipws;
                    if (!lineStream.eof())
                    {
                        cout << "Error: too many arguments" << endl;
                        break;
                    }
                    legit = true;
                    break;
                }
                else if (i==3)
                {
                    bool flag = false;
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    lineStream >> name;
                    for (int j = 0; j < maxShape; j++)
                    {
                        if (shapesArray[j] != NULL && name == shapesArray[j] -> getName())
                            {
                                flag = true;
                                break;
                            }
                    }
                    if (flag == false)
                    {
                        cout << "Error: shape " << name << " not found" << endl;
                        break;
                    }
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    lineStream >> locx;
                    if (lineStream.fail())
                    {
                        if (lineStream.eof())
                        {
                            cout << "Error: too few arguments" << endl;
                            break;
                        }
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                    if (locx < 0)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }
                    lineStream >> locy;
                    if (lineStream.fail())
                    {
                        cout << "Error: invalid argument" << endl;;
                        break;
                    }
                    if (locy < 0)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }
                    lineStream >> skipws;
                    if (!lineStream.eof())
                    {
                        cout << "Error: too many arguments" << endl;
                        break;
                    }
                    legit = true;
                    break;
                }
                else if (i==4)
                {
                    bool flag = false;
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    lineStream >> name;
                    for (int j = 0; j < maxShape; j++)
                    {
                        if (shapesArray[j] != NULL && name == shapesArray[j] -> getName())
                            {
                                flag = true;
                                break;
                            }
                    }
                    if (flag == false)
                    {
                        cout << "Error: shape " << name << " not found" << endl;
                        break;
                    }
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    lineStream >> angle;
                    if (lineStream.fail())
                    {
                        cout << "Error: invalid argument" <<  endl;
                        break;
                    }
                    if (angle < 0 || angle > 360)
                    {
                        cout << "Error: invalid value" << endl;
                        break;
                    }
                    lineStream >> skipws;
                    if (!lineStream.eof())
                    {
                        cout << "Error: too many arguments" <<  endl;
                        break;
                    }
                    legit = true;
                    break;
                }
                else if (i==5)
                {
                    bool flag = false;
                    bool flag1 = false;
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    lineStream >> temp;
                    if (temp == keyWordsList[0])
                    {
                        lineStream >> skipws;
                        if (!lineStream.eof())
                        {
                            cout << "Error: too many arguments" << endl;
                            break;
                        }
                        legit = true;
                        break;
                    }
                    for (int j = 0; j < maxShape; j++)
                    { // for some reason, cant find previous shapes
                        if (shapesArray[j] != NULL && temp == shapesArray[j] -> getName())
                            {
                                lineStream >> skipws;
                                if (!lineStream.eof())
                                {
                                    cout << "Error: too many arguments" << endl;
                                    flag1 = true;
                                    break;
                                }
                                flag = true;
                                break;
                            }
                    }
                    if (flag1 == true)
                    {
                        break;
                    }
                    if (flag == false)
                    {
                        cout << "Error: shape " << temp << " not found" << endl;
                        break;
                    }
                    legit = true;
                    break;
                }
                else if (i==6)
                {
                    bool flag = false;
                    bool flag1 = false;
                    if (lineStream.eof())
                    {
                        cout << "Error: too few arguments" << endl;
                        break;
                    }
                    lineStream >> temp;
                    if (temp == keyWordsList[0])
                    {
                    lineStream >> skipws;
                        if (!lineStream.eof())
                        {
                            cout << "Error: too many arguments" << endl;
                            break;
                        }
                        legit = true;
                        break;
                    }
                    for (int j = 0; j < maxShape; j++)
                    {
                        if (shapesArray[j] != NULL && temp == shapesArray[j] -> getName())
                            {
                                lineStream >> skipws;
                                if (!lineStream.eof())
                                {
                                    cout << "Error: too many arguments" << endl;
                                    flag1 = true;
                                    break;
                                }
                                flag = true;
                                break;
                            }
                    }
                    if (flag1 == true)
                    {
                        break;
                    }
                    if (flag == false)
                    {
                        cout << "Error: shape " << temp << " not found" << endl;
                        break;
                    }
                    legit = true;
                    break;
                }
            }
            if (i==6)
            {
                cout << "Error: invalid command" << endl;
            }
           
        }
        
        if (legit)
        {
            for (int i=1; i < 7; i++)
            {
                if (command == keyWordsList[i])
                {
                    if (i == 1)
                    {
                        if (cnt == 1)
                        {
                            max_shapes = maxShape;
                            shapesArray = new shape *[max_shapes];
                            for (int j = 0; j < maxShape; j++)
                            {
                                shapesArray[j] = NULL;
                            }
                        }
                    }
                    if (i == 2)
                    {
                        bool full = false;
                        for(int j = 0; j < max_shapes; j++)
                        {
                            if (shapesArray[j] == NULL)
                            {
                                shapesArray[j] = new shape(name, type, locx, locy, sizex, sizey);
                                shapeCount++;
                                cout << "Created " << name << ": " << type << " " << locx << " " << locy<< " " << sizex << " " << sizey << endl;
                                break;
                            }
                            else if (shapesArray[j] != NULL && j == max_shapes -1)
                            {
                                cout << "Error: shape array is full" << endl;
                                full = true;
                                break;
                            }
                        }
                        if (full)
                        {
                            break;
                        }
                    }
                    if (i == 3)
                    {
                        for(int j = 0; j < max_shapes; j++)
                        {
                            if (name == shapesArray[j] -> getName())
                            {
                                shapesArray[j]->setXlocation(locx);
                                shapesArray[j]->setYlocation(locy);
                                cout << "Moved " << shapesArray[j]->getName() << " to " << locx << ' ' << locy << endl;
                                break;
                            }
                        }
                    }
                    if (i == 4)
                    {
                        for(int j = 0; j < max_shapes; j++)
                        {
                            if (name == shapesArray[j] -> getName())
                            {
                                shapesArray[j]->setRotate(angle);
                                cout << "Rotated " << shapesArray[j]->getName() << "by " << angle << " degrees" << endl;
                                break;
                            }
                        }
                    }
                    if (i == 5)
                    {
                        if (temp == keyWordsList[0])
                        {
                            cout << "Drew all shapes" << endl; 
                            for(int j = 0; j < max_shapes; j++)
                            {
                                if(shapesArray[j] != NULL)
                                {
                                    cout << shapesArray[j]->getName() << ": " << shapesArray[j]->getType() << ' ' << shapesArray[j]->getXlocation() << ' ' << shapesArray[j]->getYlocation() << ' ' << shapesArray[j]->getXsize() << ' ' << shapesArray[j]->getYsize() << endl;
                                }
                            }
                        }
                        else
                        {
                            for(int j = 0; j < max_shapes; j++)
                            {
                                if (temp == shapesArray[j] -> getName())
                                {
                                    cout << "Drew " << shapesArray[j]->getName() << endl;
                                    cout << shapesArray[j]->getName() << ": " << shapesArray[j]->getType() << ' ' << shapesArray[j]->getXlocation() << ' ' << shapesArray[j]->getYlocation() << ' ' << shapesArray[j]->getXsize() << ' ' << shapesArray[j]->getYsize() << endl;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    if (i == 6)
                    {
                        if (temp == keyWordsList[0])
                        {
                            cout << "Deleted: all shapes" << endl; 
                            for(int j = 0; j < max_shapes; j++)
                            {
                                delete shapesArray[j];
                                shapesArray[j] = NULL;
                                shapeCount = 0;
                            }
                        }
                        else
                        {
                            for(int j = 0; j < max_shapes; j++)
                            {
                                if (temp == shapesArray[j] -> getName())
                                {
                                    cout << "Deleted shape " << shapesArray[j]->getName() << endl;
                                    delete shapesArray[j];
                                    shapesArray[j] = NULL;
                                    shapeCount--;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    for(int j = 0; j < max_shapes; j++)
    {
        delete shapesArray[j];
        shapesArray[j] = NULL;
    }
    delete [] shapesArray;
    *shapesArray = NULL;
    return 0;
}
