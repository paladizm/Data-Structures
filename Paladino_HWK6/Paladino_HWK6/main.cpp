/**********************************************************
* Author: Zac Paladino
* Date: Dec/10/2008
* Purpose: The Purpose of the program was to make a 
*          functioning Graph class that can identify
*		   cycles, cut edges, connection, and if
*		   it is Bipartite.
*
* Input:  User Driven
* Output: paladino5.txt
* Login-id: cps350-n1.16
**********************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include "Driver.h"
#include "graph.h"

int main(){
	ifstream myfile;
	ofstream out;
	string in;
	vector<Graph *> graphs(11);
	cout << "Please Enter Input File: ";
	cin >> in;
	myfile.open(in.c_str());
	out.open("paladino6.txt");
	if (myfile.is_open()){
		Driver(myfile,out,graphs);
	    myfile.close();		
	}
	else out << "Unable to open file";
	out.close();
	return 0;
}