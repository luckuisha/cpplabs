/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

    #include <iostream>
    #include <string>
    using namespace std;
    #include "TreeDB.h"

       // You will need to add additional private functions
    bool TreeDB::helpInsert(DBentry* newEntry, TreeNode * parent, string key)
    {
//        TreeNode* childLeft = parent ->getLeft();
//        TreeNode * childRight = parent ->getRight();
        string parentKey = parent->getEntry()->getName();
        //unsigned int leftKey = childLeft->getEntry()->getName();
        //unsigned int rightKey = childRight->getEntry()->getName();

        if( parentKey.compare(key) > 0 ) //go left
        {
            if (parent->getLeft() == NULL)
            {
                parent->setLeft(new TreeNode(newEntry)); //insertion
                return true;
            }
            return helpInsert (newEntry, parent->getLeft(), key);
        }
        else if( parentKey.compare(key) < 0 ) //go right 
        {
            if (parent->getRight() == NULL)
            {
                parent->setRight(new TreeNode(newEntry)); // insertion
                return true;
            }
            return helpInsert (newEntry, parent->getRight(), key); //recursive
        }
        return false;
    };

    DBentry* TreeDB::helpFind(TreeNode * ptr, string key)
    {
        if (ptr == NULL)
            return NULL;
        if (ptr->getEntry()->getName() == key){
            probesCount++;//add
            return ptr->getEntry();
        }
        else if (ptr->getEntry()->getName().compare(key) < 0) //left
        {
            probesCount++;
            return helpFind (ptr->getRight(), key);
        }
        else //right
        {
            probesCount++;
            return helpFind (ptr->getLeft(), key);
        }
    };

    void TreeDB::helpClear(TreeNode * parent)
    {
        if (parent->getLeft() != NULL)
        {
            helpClear(parent->getLeft()); //recursion go to end and delete backwards
        }
        if (parent->getRight() != NULL)
        {
            helpClear(parent->getRight());
        }
        delete parent;
        return;
    };


    int TreeDB::helpCount(TreeNode * parent, int & cnt) const
    {
        if (parent == NULL)
            return 0;
        if (parent->getLeft() != NULL)
        {
            helpCount(parent->getLeft(), cnt);
        }
        if (parent->getRight() != NULL)
        {
            helpCount(parent->getRight(), cnt);
        }
        if (parent->getEntry()->getActive() == true)
            cnt++; // only increment when true
        return cnt; //returns value in order to cout this number

    };

    bool TreeDB::helpDelete(TreeNode * parent, string key)
    {
        TreeNode * tempL = parent; //points to left child of killed parent
        TreeNode * tempR = parent; //points to right child of killed parent
        TreeNode * tempReplace; // replacement parent, up for adoption, this is the right parent of left child
        TreeNode * tempReplaceLeft; // if replacement parent has kids to the left of her, this is the node
        if (parent->getEntry()->getName().compare(key) > 0) //parent > key (go left)
        {
            if (parent->getLeft()->getEntry()->getName().compare(key) == 0)
            {
                if (parent->getLeft()->getLeft() == NULL && parent->getLeft()->getRight() == NULL ) // left and right child are dead
                {
                    delete parent->getLeft();
                    parent->setLeft(NULL);
                    return true;
                }
                else if (parent->getLeft()->getLeft() != NULL && parent->getLeft()->getRight() == NULL )  // only child
                {
                    tempL = parent->getLeft()->getLeft();
                    delete parent->getLeft();
                    parent->setLeft(tempL);
                    return true;
                }
                else if (parent->getLeft()->getLeft() == NULL && parent->getLeft()->getRight() != NULL )
                {
                    tempR = parent->getLeft()->getRight();
                    delete parent->getLeft();
                    parent->setLeft(tempR);
                    return true;
                }
                else // when 2 children are alive
                {
                    tempR = parent->getLeft()->getRight();
                    tempL = parent->getLeft()->getLeft();
                    if (parent->getLeft()->getLeft()->getRight() != NULL) // checker for null
                    {
                        tempReplace = findRight(parent->getLeft()->getLeft());
                        if (tempReplace->getRight()->getLeft() != NULL)
                        {
                            tempReplaceLeft = tempReplace->getRight()->getLeft();
                        }
                        delete parent->getLeft();
                        parent->setLeft(tempReplace->getRight());
                        parent->getLeft()->setLeft(tempL);
                        parent->getLeft()->setRight(tempR);
                        if (tempReplace->getRight()->getLeft() != NULL)
                        {
                            tempReplace->setRight(tempReplaceLeft);
                        }
                        else tempReplace->setRight(NULL);
                        return true;
                    }
                    else
                    {
                        delete parent->getLeft(); // actual deletion
                        parent->setLeft(tempL);
                        tempL->setRight(tempR);
                        return true;
                    }
                }
            }
            else helpDelete (parent->getLeft(), key);
        }
        else if (parent->getEntry()->getName().compare(key) < 0) // go right, same functionality as top but different direciton
        {
            if (parent->getRight()->getEntry()->getName().compare(key) == 0)
            {
                if (parent->getRight()->getLeft() == NULL && parent->getRight()->getRight() == NULL )
                {
                    delete parent->getRight();
                    parent->setRight(NULL);
                    return true;
                }
                else if (parent->getRight()->getLeft() != NULL && parent->getRight()->getRight() == NULL )
                {
                    tempL = parent->getRight()->getLeft();
                    delete parent->getRight();
                    parent->setRight(tempL);
                    return true;
                }
                else if (parent->getRight()->getLeft() == NULL && parent->getRight()->getRight() != NULL )
                {
                    tempR = parent->getRight()->getRight();
                    delete parent->getRight();
                    parent->setRight(tempR);
                    return true;
                }
                else
                {
                    tempR = parent->getRight()->getRight();
                    tempL = parent->getRight()->getLeft();
                    tempReplace = findRight(parent->getRight()->getLeft());
                    if(parent->getRight()->getLeft()->getRight() != NULL)
                    {
                        if (tempReplace->getRight()->getLeft() != NULL)
                        {
                            tempReplaceLeft = tempReplace->getRight()->getLeft();
                        }
                        delete parent->getRight();
                        parent->setRight(tempReplace->getRight());
                        parent->getRight()->setLeft(tempL);
                        parent->getRight()->setRight(tempR);
                        if (tempReplace->getRight()->getLeft() != NULL)
                        {
                            tempReplace->setRight(tempReplaceLeft);
                        }
                        else tempReplace->setRight(NULL);
                        return true;
                    }
                    else
                    {
                        delete parent->getRight();
                        parent->setRight(tempL);
                        tempL->setRight(tempR);
                        return true;
                    }
                }
            }
            else helpDelete(parent->getLeft(), key); // recursion to execute this again
        }
        else return false;
    };
    
    TreeNode * TreeDB::findRight (TreeNode *parent) // finds the right most parent of left child of dead parent
    {
        if (parent->getRight()->getRight() == NULL)
            return parent;
        else return (findRight(parent->getRight()));
    };

    
    
    
    
    
   // the default constructor, creates an empty database.
   TreeDB::TreeDB()
   {
       root=NULL;
       probesCount = 0;
   };

   // the destructor, deletes all the entries in the database.
   TreeDB::~TreeDB()
   {
       clear(); //calls clear
   };

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool TreeDB::insert(DBentry* newEntry)
   {
       if (find (newEntry -> getName ()) != NULL)
            return false;
       if (root == NULL)
       {
            root=new TreeNode(newEntry);
            return true;
       }
       
       return helpInsert(newEntry, root, newEntry->getName()); //calls helper
       
   }; 

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* TreeDB::find(string name)
   {
       probesCount = 0;
       if (root == NULL)
           return NULL;
       return helpFind (root, name);       //calls helper
   };

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   // See section 6 of the lab handout for the *required* removal method.
   // If you do not use that removal method (replace deleted node by
   // maximum node in the left subtree when the deleted node has two children)
   // you will not match exercise's output.
   bool TreeDB::remove(string name)
   {
        TreeNode * tempL = root;
        TreeNode * tempR = root;
        TreeNode * tempReplace;
        TreeNode * tempReplaceLeft;
       if (root == NULL)
           return false;
       else if ( root->getEntry()->getName().compare(name) == 0) // this checks if root is to be deleted, same functionality of helper delete
       {
           if (root->getLeft()==NULL && root->getRight()==NULL )
           {
                delete root;
                root = NULL;
                return true;
           }
           else if (root->getLeft()==NULL && root->getRight()!=NULL )
           {
                tempR = root->getRight();
                delete root;
                root = tempR;
                return true;
           }
           else if (root->getLeft()!=NULL && root->getRight()==NULL )
           {
                tempL = root->getLeft();
                delete root;
                root = tempL;
                return true;
           }
           else 
           {
                tempR = root->getRight();
                tempL = root->getLeft();
                if (root->getLeft()->getRight()!=NULL)
                {
                    tempReplace = findRight(root->getLeft());
                    if (tempReplace->getRight()->getLeft() != NULL)
                    {
                        tempReplaceLeft = tempReplace->getRight()->getLeft();
                    }
                    delete root;
                    root->setRight(tempReplace->getRight());
                    root->getRight()->setLeft(tempL);
                    root->getRight()->setRight(tempR);
                    if (tempReplace->getRight()->getLeft() != NULL)
                    {
                        tempReplace->setRight(tempReplaceLeft);
                    }
                    else tempReplace->setRight(NULL);
                    return true;
                }
                else
                {
                    delete root;
                    root = tempL;
                    root->setRight(tempR);
                    return true;
                }
           }
       }
       else return helpDelete ( root, name ); // calls helper if root is not being deleted
   };
	
   // deletes all the entries in the database.
   void TreeDB::clear()
   { 
       if (root == NULL)
           return;
       helpClear(root); // helper function
       root = NULL;
       probesCount = 0;
       return;
   };
    
   // prints the number of probes stored in probesCount
   void TreeDB::printProbes() const
   {
       cout << probesCount << endl;
       return;
   };
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void TreeDB::countActive () const{
       int count = 0;
       cout << helpCount (root, count) << endl;
       return;
   };
   
    void TreeDB::helpPrint(ostream& out,TreeNode * printed) const
   {
       if(printed == NULL)
            return;
       if (printed ->getLeft() != NULL)
           helpPrint (out, printed->getLeft());
       out<<*printed->getEntry(); //prints, uses operator << to print
       if (printed->getRight()!=NULL)
           helpPrint (out, printed->getRight()); //recursion
       return;
   }
   
   ostream& operator<< (ostream& out, const TreeDB& rhs)
   {
       rhs.helpPrint(out , rhs.root); //calls help, helper outputs out
       return out;
   };
   
   ostream& operator<< (ostream& out, TreeNode* rhs)
   {
       return out << rhs->getEntry(); // used by help print helper function
   }; 
   
   
 