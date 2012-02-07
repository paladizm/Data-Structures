/**********************************************************
* Author: Zac Paladino
* Date: Nov/11/2008
* Purpose: The Purpose of the program was to make a 
*          functioning Huffman Tree and to be able to
*		   encode and decode strings.
*
* Input:  input.txt
* Output: paladino5.txt
* Login-id: cps350-n1.16
**********************************************************/
#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <fstream>
#include <string>
#include "HelperFunctions.h"
#include "Huffman.h"

//This is the Driver function that takes care of all I/O from
//the tree and the files.
//Pre: The files are inputed as paramaters.
//Post: The output file is written with the tree info and Encoding
//		and decoding information.
void Driver(ifstream& in, ofstream& out){
	while(!in.eof()){
		out << "The Huffman Tree" << endl;
		out << "----------------" << endl;
		out << endl;
		vector<int> Freq;
		string t;
		int temp;
		for(int i=0; i<ALPHA_SIZE; i++){			
			getline(in,t);
			temp = StringToInt(t);
			Freq.push_back(temp);
		}
		Huffman tree;
		tree.BuildCodes(Freq);
		tree.PrintHuffmanTree(out);
		out << endl;
		out << endl;
		tree.PrintFreqAndCodeWords(out);
		out << endl;
		out << "Weighted external path length of tree: " << tree.Wepl() << endl;
		out << endl;
		out << "Encoding" << endl;
		out << "--------" << endl;
		out << endl;
		t = "";
		while(t == ""){
			getline(in,t);
		}		
		temp = StringToInt(t);
		for(int i = 0; i<temp; i++){
			getline(in,t);
			out << t << endl;			
			string enc;
			tree.Encode(t, enc);
			out << " ---> " << enc << endl;
		}
		out << endl;
		out << "Decoding" << endl;
		out << "--------" << endl;
		out << endl;
		t = "";
		while(t == ""){
			getline(in,t);
		}
		temp = StringToInt(t);
		for(int i = 0; i<temp; i++){
			getline(in,t);
			out << t << endl;			
			string dec;
			tree.Decode(t, dec);
			out << " ---> " << dec << endl;
		}
	}
}
#endif