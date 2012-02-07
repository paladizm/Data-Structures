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
#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
#include "DriverFunctions.h"
using namespace std;
int main(){
	BinarySearchTree<int> treeAr[10];		
	ifstream myfile;
	ofstream out;
	myfile.open("input.txt");
	out.open("paladino4.txt");
	if (myfile.is_open()){
		OperationHandle(myfile,out,treeAr);
	    myfile.close();		
	}
	else out << "Unable to open file";
	out.close();
	return 0;

	return 0;
}