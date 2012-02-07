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
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <fstream>
#include <string>
#include "BinaryHeap.h"
#include "HelperFunctions.h"
using namespace std;

const int ALPHA_SIZE = 27;

class Huffman{
public:
	//constructor
	//Fills the Letter vector with the characters.
	Huffman(): Codes(ALPHA_SIZE), Freqs(ALPHA_SIZE), Letters(ALPHA_SIZE){
		root = NULL;		
		char s = 'a';
		for(int i=0; i<ALPHA_SIZE; i++){
			if(i == 26){
				Letters[i] = '*';
			}
			else{
				Letters[i] = s;
				s++;				
			}			
		}
	}
	//vector freq of ALPHA_SIZE has the frequency of
	//occurrence for each symbol. freq[0] corresponds to
	//frequency of 'a', freq[1] ro the frequency of 'b'
	//and so on. freq[ALPHA_SIZE - 1] corresponds to the
	//frequency of '*'.
	//1) Build Huffman Tree
	//2) Generate the code word for each symbol and record it
	//At th end it builds all the codes and the Huffman tree.
	void BuildCodes(const vector<int> &freq){
		Freqs = freq;
		for(int i=0; i<ALPHA_SIZE; i++){
			HuffNode* t = new HuffNode(NULL,NULL,i);
			HeapNode a;
			a.rt = t;
			a.freq = freq[i];
			Bheap.insert(a);			
		}
		combine();
		HeapNode temp;
		Bheap.deleteMin(temp);
		root = temp.rt;		
		for(int i=0; i<ALPHA_SIZE;i++){
			string c;
			findcode(root,i,c);
			reverseString(c);			
			Codes[i] = c;		
		}
	}
	//Prints the table of Freq, Symbol, and Codes.
	void PrintFreqAndCodeWords(ostream &outs){
		outs << "\tFreq\tSymbol\tCode" << endl;
		outs << "\t----\t------\t----" << endl;
		for(int i = 0; i<ALPHA_SIZE; i++){
			outs<< "\t" << Freqs[i] << "\t" << Letters[i] 
				<< "\t" << Codes[i] << endl;
		}	
	}
	//Prints the Huffman tree in an inorder traversal.
	void PrintHuffmanTree(ostream &outs){
		if(root != NULL){
			printTree(root, outs);
		}
	}
	//Computes the Wepl of the Huffman tree.
	int Wepl(){
		int wepl = 0;
		for(int i=0; i<ALPHA_SIZE; i++){
			int temp;
			temp = Freqs[i] * static_cast<int>(Codes[i].size());
			wepl = wepl + temp;
		}
		return(wepl);
	}
	//Encodes the decoded string and places it in the
	//encoded string paramater.
	void Encode(const string &decStr, string &encStr){
		for(int i = 0; i < static_cast<int>(decStr.size()); i++){
			for(int k = 0; k<ALPHA_SIZE; k++){
				if(decStr[i] == Letters[k]){
					encStr = encStr + Codes[k];
				}
			}
		}
	}
	//Decodes the string by traversing the huffman tree by '0' being
	//left and '1' being right and when it hits a huffman node with
	//an actual character number it is appended on to the decoded string.
	void Decode(const string &endStr, string &decStr){
		HuffNode* t = root;
		for(int i = 0; i<static_cast<int>(endStr.size()); i++){
			if(endStr[i] == '0'){
				if(t->left->charNum != -1){
					decStr = decStr + Letters[t->left->charNum];
					t = root;
				}
				else{
					t = t->left;
				}
			}
			else if(endStr[i] == '1'){
				if(t->right->charNum != -1){
					decStr = decStr + Letters[t->right->charNum];
					t = root;
				}
				else{
					t = t->right;
				}
			}
		}
	}
private:
	//This is the Huffman node for the huffman tree.
	//holds the char number and the combination number
	//if there is one.
	struct HuffNode
	{
		HuffNode *left;
		HuffNode *right;
		int charNum;
		int combnum;		

		HuffNode(HuffNode* lt, HuffNode* rt, int c = -1, int s=0)
			: left(lt), right(rt), charNum(c), combnum(s) {}
	};

	//This is the Node for the heap that connects the frequency of
	//each letter and the pointer to the node of a Huffman Node.
	//Also all of the comparisons were overloaded for use with the heap.
	struct HeapNode
	{
		HuffNode *rt;
		int freq;

		bool operator<(const HeapNode &x) const{
			return(this->freq < x.freq);
		}
		bool operator>(const HeapNode &x) const{
			return(this->freq > x.freq);
		}
		bool operator==(const HeapNode &x) const{
			return(this->freq == x.freq);
		}
		bool operator>=(const HeapNode &x) const{
			return(this->freq >= x.freq);
		}
		bool operator<=(const HeapNode &x) const{
			return(this->freq <= x.freq);	
		}
		bool operator!=(const HeapNode &x) const{
			return(this->freq != x.freq);			
		}
	};
	//The Binary Heap
	BinaryHeap<HeapNode> Bheap;
	//Main root of the Huffman Tree
	HuffNode *root;
	//The Vectors the Hold the information.
	vector<string> Codes;
	vector<int> Freqs;
	vector<char> Letters;
	
	//This function completes the Huffman combine method and uses the
	//binary heap to combine the frequencies and the Huffman pointers
	//to create the final Huffman Tree.
	void combine(){
		int count = 0;
		while(Bheap.size()!= 1){
			count++;
			HeapNode temp, temp2, newHN;
			Bheap.deleteMin(temp);
			Bheap.deleteMin(temp2);
			if(temp <= temp2){
				HuffNode* t = new HuffNode(temp.rt,temp2.rt,-1,count);
				int newFreq = (temp.freq + temp2.freq);
				newHN.freq = newFreq;
				newHN.rt = t;
				Bheap.insert(newHN);
			}
		}
	}
	//This creates the codes for the characters recursivley.
	//The only problem is the codes come out backwards so the
	//function reversestring takes care of that.
	bool findcode(HuffNode *& t, int charval, string& code){		
		if(t != NULL){
			if(t->charNum == charval){
				return(true);
			}
			else if(t->left && findcode(t->left,charval,code)){
				code = code + "0";
				return true;
			}
			else if(t->right && findcode(t->right,charval,code)){
				code = code + "1";
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}		
	}
	//The Recursive call for the inorder traversal print.
	void printTree( HuffNode *t, ostream & out ) const
    {
        if( t != NULL ){
			if(t->left){
				if(t->left->combnum != 0){
					out << "(";
				}
				printTree( t->left, out );
				if(t->left->combnum != 0){
					out << ")";
				}
			}
			if(t->left && t->left->charNum != -1){
				out << Letters[t->left->charNum];
			}
			if(t->combnum != 0){
				out << " " << t->combnum << " ";
			}
			if(t->right && t->right->charNum != -1){
				out << Letters[t->right->charNum];
			}
			if(t->right){
				if(t->right->combnum != 0){
					out << "(";
				}
				printTree( t->right, out );
				if(t->right->combnum != 0){
					out << ")";
				}				
			}
        }
    }
	//reverses the string so the codes come out the right way.
	void reverseString(string& t){
		int size = static_cast<int>(t.size());
		string temp;
		for(int i = size; i>0; i--){
			temp = temp + t[i-1];			
		}
		t = temp;
	}	
};
#endif




