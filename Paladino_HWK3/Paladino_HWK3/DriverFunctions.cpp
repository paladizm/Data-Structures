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
#include "DriverFunctions.h"
#include "HelperFunctions.h"
#include "TernaryTree.h"
//OperationHandle takes care of all of the I/O for the program. It is the 
//driver function.
//Pre: The TernaryTree Must be int;
//Post: Outputs the commands to a file.
void OperationHandle(ifstream& in, ofstream& out, TernaryTree<int> treeA[]){
	while(!in.eof()){
			vector<string> tokens;
			string lin, delim = " ";
			getline(in,lin);
			tokens = MakeTokens(lin, delim);
			if(tokens[0] == "printpre"){
				out << "Input Command: ";
				int arnum = 0;
				arnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tTree " << arnum << " Pre: ";				
				treeA[arnum].printTreePre(out);
				out << endl;
			}
			else if(tokens[0] == "printlevel"){
				out << "Input Command: ";
				int arnum = 0;
				arnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tTree " << arnum << " Level: ";
				treeA[arnum].printTreeLevel(out);
				out << endl;
			}
			else if(tokens[0] == "insertroot"){
				out << "Input Command: ";
				TernaryTree<int> temp;
				int arnum = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				temp.InsertRoot(element);
				treeA[arnum] = temp;
			}
			else if(tokens[0] == "insert"){
				out << "Input Command: ";
				int arnum = 0, element = 0, parent = 0, child = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);
				parent = StringToInt(tokens[3]);
				child = StringToInt(tokens[4]);
				for(int i=0; i<5;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				if(treeA[arnum].InsertItem(element, parent, child));
				else out << "-- Failed " << endl;
			}
			else if(tokens[0] == "createsubtree"){
				out << "Input Command: ";				
				int arnum = 0, arnum2 = 0, parent = 0, child = 0;
				arnum = StringToInt(tokens[1]);
				arnum2 = StringToInt(tokens[2]);				
				parent = StringToInt(tokens[3]);
				child = StringToInt(tokens[4]);
				for(int i=0; i<5;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				if(treeA[arnum].CreateSubTree(treeA[arnum2],parent,child));
				else out << "-- Failed " << endl;
			}
			else if(tokens[0] == "transplantsubtree"){
				out << "Input Command: ";
				int arnum = 0, arnum2 = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);
				arnum2 = StringToInt(tokens[3]);
				for(int i=0; i<4;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				if(treeA[arnum].TransplantSubTree(element,treeA[arnum2]));
				else{
					out << "-- Failed" << endl;
				}
			}
			else if(tokens[0] == "deletesubtree"){
				out << "Input Command: ";
				int arnum = 0, element = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);	
				for(int i=0; i<3;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				if(treeA[arnum].DeleteSubTree(element));
				else{
					out << "-- Failed" << endl;
				}
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
			else if(tokens[0] == "siblings"){
				out << "Input Command: ";	
				int arnum = 0, element = 0, element2 = 0;
				arnum = StringToInt(tokens[1]);
				element = StringToInt(tokens[2]);
				element2 = StringToInt(tokens[3]);
				for(int i=0; i<4;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "\tIn Tree " << arnum << " ";				
				if(treeA[arnum].AreSiblings(element,element2)){
					out << element << " and " << element2 << " are siblings." << endl;}

				else out << element << " and " << element2 << " are NOT siblings." << endl;
			}
			else{
				out << "not a valid command!" << endl;
			}			
	}
}