/**********************************************************
* Author: Zac Paladino
* Date: Dec/10/2008
* Purpose: The Purpose of the program was to make a 
*          functioning Graph class that can identify
*		   cycles, cut edges, connection, and if
*		   it is Bipartite.
*
* Input:  User Driven
* Output: paladino6.txt
* Login-id: cps350-n1.16
**********************************************************/
#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "HelperFunctions.h"
#include "graph.h"

//This is the Driver function that takes care of all I/O from
//the graphs and the files.
//Pre: The files and graphs are inputed as paramaters.
//Post: The output file is written with the graphs info and
//		commands are completed.
void Driver(ifstream& in, ofstream& out, vector<Graph *> graphs){
	while(!in.eof()){
			vector<string> tokens;			
			string lin, delim = " ";
			getline(in,lin);
			tokens = MakeTokens(lin, delim);
			if(tokens[0] == "graph"){
				out << "Input Command: ";
				int graphnum = 0, verts = 0, edges = 0;
				graphnum  = StringToInt(tokens[1]);				
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				getline(in,lin);
				tokens = MakeTokens(lin, delim);
				verts = StringToInt(tokens[0]);
				edges = StringToInt(tokens[1]);				
				graphs[graphnum] = new Graph(verts);
				for(int i=0; i<edges; i++){
					int temp, temp2;
					getline(in,lin);
					tokens = MakeTokens(lin, delim);
					temp = StringToInt(tokens[0]);	
					temp2 = StringToInt(tokens[1]);	
					graphs[graphnum]->AddEdge(temp, temp2);
				}				
				out << endl;				
			}
			else if(tokens[0] == "alists"){
				out << "Input Command: ";
				int graphnum = 0;
				graphnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "Adjacency lists of graph ";	
				out << tokens[1] << ":";
				out << endl;
				graphs[graphnum]->PrintAdjacencies(out);
				out << endl;
			}
			else if(tokens[0] == "connected"){
				list<int> compList;
				out << "Input Command: ";
				int graphnum = 0;
				bool t=false;
				graphnum = StringToInt(tokens[1]);
				t = graphs[graphnum]->Connected(compList);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "Graph " << tokens[1] << " is ";
				if(t){
					out << "CONNECTED and has the following components:" << endl;
					out << "Component 1: ";
					list<int>::iterator p;
					for(p=compList.begin(); p!=compList.end(); p++){
						out << *p << " ";
					}
					out << endl;
				}
				else{
					int count = 1, count2 = 0;
					out << "DISCONNECTED and has the following components:" << endl;
					int temp = static_cast<int>(compList.size());
					list<int>::iterator p;	
					out << "Component 1: ";
					int i = 1;
					for(p=compList.begin(); p!=compList.end(); p++){
						if(*p != -1){
							out << *p << " ";							
						}
						else{
							i++;
							out << endl;
							out << "Component " << i << ": ";
						}							
					}
					out << endl;
				}
			}			
			else if(tokens[0] == "cycle"){
				out << "Input Command: ";
				list<int> cycleList;
				int graphnum = 0;
				bool t=false;
				graphnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "Graph " << tokens[1] << " ";
				t = graphs[graphnum]->Cycle(cycleList);
				if(t){
					list<int>::iterator p;
					out << "has cycle: ";
					for(p=cycleList.begin(); p!=cycleList.end(); p++){
						out << *p << " ";
					}
				}
				else{
					out << " has NO cycles.";
				}				
				out << endl;
			}
			else if(tokens[0] == "bipartite"){
				out << "Input Command: ";
				int graphnum = 0;
				bool t=false;
				graphnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				out << "Graph " << tokens[1] << " ";
				list<int> colorX, colorY;
				t = graphs[graphnum]->Bipartite(colorX, colorY);
				if(t){
					out << "is bipartite with the following bipartation:";
					out << endl;
					out << "ColorX: ";
					list<int>::iterator p;
					for(p=colorX.begin(); p!=colorX.end(); p++){
						out << *p << " ";
					}
					out << endl;
					out << "ColorY: ";
					for(p=colorY.begin(); p!=colorY.end(); p++){
						out << *p << " ";
					}
				}
				else{
					out << " is NOT bipartite";
				}				
				out << endl;
			}
			else if(tokens[0] == "cutedges"){
				out << "Input Command: ";
				int graphnum = 0;				
				graphnum = StringToInt(tokens[1]);
				for(int i=0; i<2;i++){
					out << tokens[i] << " ";
				}
				out << endl;
				graphs[graphnum]->CutEdges(out);
				out << endl;
			}
			else{
				out << "not a valid command!" << endl;
			}			
	}
} 
#endif