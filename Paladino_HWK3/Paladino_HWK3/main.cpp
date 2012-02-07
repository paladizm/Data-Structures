/**********************************************************
* Author: Zac Paladino
* Date: Oct/08/2008
* Purpose: The Purpose of the program was to make a 
*          functioning Ternary Tree and to do multitude of
*		   operations with these trees.
* Input:  input.txt
* Output: paladino3.txt
* Login-id: cps350-n1.16
**********************************************************/
#include "TernaryTree.h"
#include "HelperFunctions.h"
#include "DriverFunctions.h"
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
using namespace std; 

int main(){
	TernaryTree<int> treeAr[10];
	TernaryTree<int> t1;	
	ifstream myfile;
	ofstream out;
	myfile.open("input.txt");
	out.open("paladino3.txt");
	if (myfile.is_open()){
		OperationHandle(myfile,out,treeAr);
	    myfile.close();		
	}
	else out << "Unable to open file";
	out.close();
	return 0;
}