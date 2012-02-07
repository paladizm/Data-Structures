/**********************************************************
* Author: Zac Paladino
* Date: Oct/08/2008
* Purpose: The Purpose of the program was to make a 
*          functioning Binary Search Tree with some AVL tree
*		   functions.		  
*
* Input:  input.txt
* Output: paladino4.txt
* Login-id: cps350-n1.16
**********************************************************/
#ifndef DRIVERFUNCTIONS_H
#define DRIVERFUNCTIONS_H
#include <string>
#include <stdlib.h> 
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "BinarySearchTree.h"
using namespace std;
//OperationHandle takes care of all of the I/O for the program. It is the 
//driver function.
//Pre: The BinarySearchTree Must be int;
//Post: Outputs the commands to a file.
void OperationHandle(ifstream& in, ofstream& out, BinarySearchTree<int> treeA[]);
#endif