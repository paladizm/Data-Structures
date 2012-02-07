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
#include "DriverFunctions.h"
#include "HelperFunctions.h"
#include "BinarySearchTree.h"
//OperationHandle takes care of all of the I/O for the program. It is the 
//driver function.
//Pre: The BinarySearchTree Must be int;
//Post: Outputs the commands to a file.
void OperationHandle(ifstream& in, ofstream& out, BinarySearchTree<int> treeA[]){
	while(!in.eof()){
			vector<string> tokens;
			string lin, delim = " ";
			getline(in,lin);
			tokens = MakeTokens(lin, delim);
			if(tokens[0] == "print"){
				out << "Input Command: ";
				int arnum = 0;
				arnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tTree " << arnum << " inorder: ";	
				treeA[arnum].printTree(out);
				out << endl;
			}
			else if(tokens[0] == "width"){
				out << "Input Command: ";
				int arnum = 0;
				arnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tTree " << arnum << " Width: ";
				out << treeA[arnum].Width() << endl;
			}
			else if(tokens[0] == "avl"){
				out << "Input Command: ";
				int arnum = 0;
				arnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tTree " << arnum << " AVL?: ";
				if(treeA[arnum].AVL()){
					out << "Yes";
				}
				else{
					out << "No";
				}
				out << endl;			
			}
			else if(tokens[0] == "insert"){
				out << "Input Command: ";
				int arnum = 0, element = 0, parent = 0, child = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);				
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;				
				treeA[arnum].insert(element);				
			}
			else if(tokens[0] == "delete"){
				out << "Input Command: ";				
				int arnum = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);				
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;							
				treeA[arnum].remove(element);				
			}
			else if(tokens[0] == "ll"){
				out << "Input Command: ";				
				int arnum = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);				
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;							
				if(treeA[arnum].LLat(element));				
				else out << "-- Failed " << endl;			
			}
			else if(tokens[0] == "rr"){
				out << "Input Command: ";				
				int arnum = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);				
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;								
				if(treeA[arnum].RRat(element));
				else out << "-- Failed " << endl;
			}
			else if(tokens[0] == "onell"){
				out << "Input Command: ";
				int arnum = 0;
				arnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tTree " << arnum << " onell?: ";
				int val;
				if(treeA[arnum].OneLLDoesIt(val)){
					out << "Yes at " << val;
				}
				else{
					out << "No";
				}
				out << endl;	
			}
			else if(tokens[0] == "=="){
				out << "Input Command: ";													
				int arnum = 0, arnum2 = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				arnum2 = StringToInt(tokens[2]);
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tTree " << arnum << " and Tree " << arnum2;
				if(treeA[arnum] == treeA[arnum2]){
					out << " Are Equal" << endl;
				}
				else{
					out << " Are Not Equal" << endl;
				}
			}
			else if(tokens[0] == "="){
				out << "Input Command: ";								
				int arnum = 0, arnum2 = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				arnum2 = StringToInt(tokens[2]);
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				treeA[arnum] = treeA[arnum2];

			}
			else{
				out << "not a valid command!" << endl;
			}			
	}
}