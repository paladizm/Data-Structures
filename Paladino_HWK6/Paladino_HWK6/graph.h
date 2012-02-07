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
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

class Graph {
public:
	// n is the number of vertices. Vertices are labeled 1 through n.
	// Hence, vectors have a size of (n+1).
	explicit Graph (int n): 
		nVertices(n), Adj(n+1), dfsNumber(n+1), 
		Visited(n+1), Parent(n+1), InStack(n+1)
	{
	}

	~Graph ()
	{
	}

	// Print the adjacency lists to stream outs
	void PrintAdjacencies (ostream &outs)
	{
		list<int>::iterator p;
		int v;

		for (v=1; v <= nVertices; v++)
		{
			outs << setw(2) << v << ": ";
			for (p = Adj[v].begin(); p != Adj[v].end(); p++)
				outs << setw(2) << *p << " ";
			outs << endl;
		}
	}

	// Print the dfsNumber of vertices to stream outs
	void PrintDfsNumbers (ostream &outs)
	{
		int v;

		outs << setw(12) << "Vertex: ";
		for (v=1; v <= nVertices; v++)
			outs << setw(2) << v << " ";
		outs << endl;

		outs << setw(12) << "dfsNumber: ";
		for (v=1; v <= nVertices; v++)
			outs << setw(2) << dfsNumber[v] << " ";
		outs << endl;
	}
	
	// Print the parents of vertices (in DFS forest) to stream outs
	void PrintParents (ostream &outs)
	{
		int v;

		outs << setw(8) << "Vertex: ";
		for (v=1; v <= nVertices; v++)
			outs << setw(2) << v << " ";
		outs << endl;

		outs << setw(8) << "Parent: ";
		for (v=1; v <= nVertices; v++)
			outs << setw(2) << Parent[v] << " ";
		outs << endl;
	}

	// Perform a DFS of graph. Record the DFS forest and the
	// dfsNumber for each vertex
	void Dfs (){
		int v;
		int dfsNum;

		for (v=1; v <= nVertices; v++)
		{
			Visited[v] = false;
			Parent[v] = -1;
		}

		dfsNum = 0;
		for (v=1; v <= nVertices; v++)
			if (!Visited[v])
				dfs(v, dfsNum);
	}

	// perform depth first search from vertex v
	void dfs (int v, int &dfsNum)
	{
		list<int>::iterator	p;
		int					w;

		Visited[v]= true;
		dfsNum++;
		dfsNumber[v] = dfsNum;
		
		for (p = Adj[v].begin(); p != Adj[v].end(); p++){
			w = *p;
			if (!Visited[w])
			{
				Parent[w] = v;
				dfs(w, dfsNum);
			}
		}
	}
		
	// Add the adjacency between vertices x and y
	void AddEdge (int x, int y)
	{
		Adj[x].push_back(y);
		Adj[y].push_back(x);
	}

	//This function checks to see if the graph is connected or not.
	//Pre: empty compList;
	//Post: full compList and returns if the graph is connected or not.
	bool Connected (list<int> &compList){	
		int v;
		int dfsNum;

		for (v=1; v <= nVertices; v++)
		{
			Visited[v] = false;			
			Parent[v] = -1;
		}

		dfsNum = 0;		
		for (v=1; v <= nVertices; v++){
			if (!Visited[v]){
				if(v == 1){
					compList.push_back(v);
				}
				else{
					compList.push_back(-1);
					compList.push_back(v);
				}
				ConnectDfs(v, dfsNum, compList);				
			}
		}
		list<int>::iterator k;
		int t;
		bool z=true;
		for(k = compList.begin(); k != compList.end() && z; k++){
			t = *k;
			if(t == -1){
				z = false;
				break;
			}
		}
		return(z);
	}
	//This function checks the graph for any cycle;
	//Pre: empty cycleList
	//Post: cycle list is eaither full or empty and it returns
	//		true if there is a cycle and false otherwise.
	bool Cycle (list<int> &cycleList){
		list<int> comp;
		if(Connected(comp)){
			stack<int> cycleStack;
			int v;
			int dfsNum;

			for (v=1; v <= nVertices; v++){
				Visited[v] = false;
				InStack[v] = false;
				Parent[v] = -1;
			}
			dfsNum = 0;
			bool cycleFound = false;
			for (v=1; v <= nVertices && !cycleFound; v++){
				if (!Visited[v]){
					cycleStack.push(v);
					InStack[v] = true;
					CycleDfs(v,dfsNum,cycleStack,cycleList,cycleFound);
				}
			}
			if(!cycleList.empty()){
				return(true);
			}
			else{
				return(false);
			}
		}
		else{
			return(false);
		}
	}
	//This function checks to see if the graph is Bipartite.
	//Pre: empty color lists.
	//Post: Full color lists and returns true if the graph is bipartite
	//		and false otherwise.
	bool Bipartite (list<int> &colorX, list<int> &colorY){
		list<int> con;
		queue<int> Bque;
		vector<bool> InQue(nVertices+1);
		vector<char> colors(nVertices+1);
		int count = 0;
		if(Connected(con)){	
			bool foundbi = false;
			for(int k=1; k<=nVertices && !foundbi; k++){
				for (int v=1; v <= nVertices; v++){
					Visited[v] = false;
					InQue[v] = false;
					Parent[v] = -1;
				}
				int v = k;
				Bque.push(v);
				colors[v] = 'x';
				InQue[v] = true;
				while(InQue[v]){
					Bfs(v, Bque, InQue);	
					if(!Bque.empty()){
						v = Bque.front();
					}
					InQue[v] = false;
					if(count == 0 || colors[Parent[v]] == 'y'){
						colorX.push_back(v);
						colors[v] = 'x';
					}
					else{
						colorY.push_back(v);
						colors[v] = 'y';
					}
					count++;
					Bque.pop();
					if(!Bque.empty()){
						v = Bque.front();
					}
				}
				bool b = true;
				for(int z=1; z<=nVertices && b; z++){
					checkColor(z,colorX, colorY, b, colors);
				}
				if(b){
					foundbi = true;
				}
				else{
					colorX.clear();
					colorY.clear();
					count = 0;
				}
			}
			return(foundbi);
		}
		else{
			return false;
		}
	}
	//This function checks the entire graph for cut edges and
	//puts them out into standard out.
	//Pre: Need to specify a standard out.
	//Post: Will find all the cut edges and display them in
	//      standard out.
	void CutEdges (ostream &outs){
		vector<string> edges;
		for(int v=1; v <= nVertices; v++){
			list<int>::iterator p;
			for (p = Adj[v].begin(); p != Adj[v].end();p++){
				int w = *p;
				vector<list<int>> Temp = Adj;
				DelEdge(Temp,v, w);
				list<int> con;
				string z = v + " " + w;
				bool i=false;				
				for(int k = 0; k<static_cast<int>(edges.size()); k++){
					if(edges[k] == z){
						i = true;
					}
				}
				if(!cutConnected(Temp, con) && !i){
					string o = v + " " + w;
					string k = w + " " + v;
					edges.push_back(o);
					edges.push_back(k);

					outs << "There is a cut edge at " << v << "--" << w 
						<< " and makes:" << endl;
					list<int>::iterator z;	
					outs << "Component 1: ";
					int i = 1;
					for(z=con.begin(); z!=con.end(); z++){
						if(*z != -1){
							outs << *z << " ";							
						}
						else{
							i++;
							outs << endl;
							outs << "Component " << i << ": ";
						}							
					}
					outs << endl;
				}
				AddcutEdge(Temp,v,w);			
			}
		}
	}




private:
	// Vertices are assumed to be 1 through nVertices. Therefore,
	// all relevant vectors are of the size (nVertices+1). Consult
	// the constructor Graph() on how the vectors are constructed.

	int					nVertices;	// number of vertices
	vector<list<int>>	Adj;		// adjacency lists of vertices		
	vector<int>			dfsNumber;	// dfsNumber of each vertex
	vector<bool>		Visited;	// visited or not, during dfs
	vector<int>			Parent;		// parent in dfs forest
	vector<bool>		InStack;	// checks if the vector is in the stack.

	//This function deals with the Dfs search of the graph and
	//works with finding if the graph is connected or not.
	void ConnectDfs (int v, int &dfsNum, list<int> &compList){
		list<int>::iterator	p;
		int					w;

		Visited[v]= true;		
		dfsNum++;
		dfsNumber[v] = dfsNum;
		
		for (p = Adj[v].begin(); p != Adj[v].end(); p++){
			w = *p;
			if (!Visited[w]){
				Parent[w] = v;	
				compList.push_back(w);
				ConnectDfs(w, dfsNum, compList);
			}
		}
	}

	//This is the Dfs search for finding a cycle;
	void CycleDfs(int v, int &dfsNum, stack<int> &cycleStack, list<int> &cycleList, bool &cycleFound){
		list<int>::iterator	p;
		int					w;

		Visited[v]= true;
		dfsNum++;
		dfsNumber[v] = dfsNum;
		
		for (p = Adj[v].begin(); p != Adj[v].end(); p++){
			w = *p;
			if (!Visited[w]){
				Parent[w] = v;
				cycleStack.push(w);
				InStack[w] = true;
				CycleDfs(w, dfsNum,cycleStack,cycleList,cycleFound);
			}
			else{
				if(Parent[v] != w && w != v){
					int t;
					if(InStack[v] && !cycleStack.empty()){
						t = cycleStack.top();
						cycleStack.pop();
						while(t != w){
							cycleList.push_back(t);
							InStack[t] = false;
							t = cycleStack.top();
							cycleStack.pop();
						}
						cycleList.push_back(t);
						InStack[t] = false;
						cycleFound = true;
						break;
					}
				}
			}
		}
	}
	//This function is used to del cut edges.
	void DelEdge (vector<list<int>> &Temp, int x, int y){
		Temp[x].remove(y);
		Temp[y].remove(x);
	}
	//This functon is used to add the cut edges back in after
	//they are found to preserve the graph.
	void AddcutEdge (vector<list<int>> &Temp, int x, int y){
		Temp[x].push_back(y);
		Temp[y].push_back(x);
	}

	//This is the BFS search that is used with the bipartite
	//function. 
	void Bfs (int v, queue<int> &Bque, vector<bool> &InQue)
	{
		list<int>::iterator	p;
		int					w;
		Visited[v]= true;
		
		for (p = Adj[v].begin(); p != Adj[v].end(); p++){
			w = *p;
			if (!Visited[w]){				
				Bque.push(w);				
				Visited[w] = true;
				Parent[w] = v;
				InQue[w] = true;
			}
		}
	}

	//This function checks to see if two verts have 
	//the same color and have an edge connecting them.
	void checkColor (int v, list<int> colorX, list<int> colorY, bool &foundbi, vector<char> colors){
		list<int>::iterator	p, a, z;
		int					w;			
		for (p = Adj[v].begin(); p != Adj[v].end() && foundbi; p++){
			w = *p;
			if(colors[w] == colors[v]){
				foundbi = false;
			}			
		}
	}
	//This is to check to see if the graph is still connected after the
	//deletion of a cut edge.
	bool cutConnected (vector<list<int>> &Temp, list<int> &compList){	
		int v;
		int dfsNum;

		for (v=1; v <= nVertices; v++)
		{
			Visited[v] = false;			
			Parent[v] = -1;
		}

		dfsNum = 0;		
		for (v=1; v <= nVertices; v++){
			if (!Visited[v]){
				if(v == 1){
					compList.push_back(v);
				}
				else{
					compList.push_back(-1);
					compList.push_back(v);
				}
				cutConnectDfs(Temp, v, dfsNum, compList);				
			}
		}
		list<int>::iterator k;
		int t;
		bool z=true;
		for(k = compList.begin(); k != compList.end() && z; k++){
			t = *k;
			if(t == -1){
				z = false;
				break;
			}
		}
		return(z);
	}
	
	//This is the Dfs search for the CutEdges function.
	void cutConnectDfs (vector<list<int>> &Temp, int v, int &dfsNum, list<int> &compList){
		list<int>::iterator	p;
		int					w;

		Visited[v]= true;		
		dfsNum++;
		dfsNumber[v] = dfsNum;
		
		for (p = Temp[v].begin(); p != Temp[v].end(); p++){
			w = *p;
			if (!Visited[w]){
				Parent[w] = v;	
				compList.push_back(w);
				cutConnectDfs(Temp, w, dfsNum, compList);
			}
		}
	}

};
#endif