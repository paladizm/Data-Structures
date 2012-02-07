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
#ifndef TERNARYTREE_H
#define TERNARYTREE_H

#include <iostream>
#include <queue>
using namespace std;       

template <class ItemType>
class TernaryTree{
   public:
	   //constructor
	   TernaryTree(){
		   levelque = new queue<int>;
		   root = NULL;
	   }
	   //destructor
	   ~TernaryTree(){
		   MakeEmpty();
	   }
	   //copy constructor
	   TernaryTree(const TernaryTree<ItemType> & rhs){
		   levelque = new queue<int>;
		   root = NULL;
		   *this = rhs;
	   }
	   //Prints the contence in a Pre order traversal 
	   void printTreePre(ostream &out) const{
		   if(root == NULL){
			   out << "Tree Empty";
		   }
		   else{
			   printTreePreR(out, root);			   
		   }
	   }
	   //Prints the contence in a level order traversal 
	   void printTreeLevel(ostream &out) const{	   
		   if(root == NULL){
			   out << "Tree Empty";
		   }
		   else{
			   levelque->push(root->element);
			   printTreeLevelR(out, root);			   
		   }
	   }
	   //overloads the operator = so that trees can be copied
	   const TernaryTree& operator=(const TernaryTree<ItemType> & rhs){
			if( this != &rhs ){
				MakeEmpty();
				root = clone( rhs.root );
			 }
			return *this;
		}
	   //overloads the == operator to see if 2 trees are equal.
	   bool operator==(const TernaryTree<ItemType> & rhs){		   
		   if(this->root == NULL && rhs.root == NULL){
			   return true;
		   }
		   else if(compare(this->root, rhs.root)){
			   return true;
		   }
		   else{
			   return false;
		   }
	   }
	   //Creates a tree with the given item as the root with
	   //its subtrees being empty.
	   //Post: Previouse value of the tree is lost.
	   void InsertRoot(const ItemType &item){
			MakeEmpty();
			root = new TernaryNode(item, NULL, NULL, NULL);
		}
	   //If the node containing the parent exists, and if the specified child
	   //is absent then this returns true and inserts the item in that place.
	   //Pre: The data in the tree must be distinct.
	   //Post: If successful the item is now in the tree.
	   //Params: item to be inserted, parent value, and the child (1,2,3)
	   //(Left,Middle,Right).
	   bool InsertItem(const ItemType &item, const ItemType &parent, int child){
			if (root == NULL)
				return (false);
			else
				return (InsertItemR(item, parent, child, root));	
		}
	   //Delete the subtree rooted at the item that is give. if
	   // it succeeds it will return true.
	   bool DeleteSubTree(const ItemType &item){
		   if(root == NULL){
			   return false;
		   }
		   else{
			   if(DeleteSubTreeR(root, item)){
				   return true;
			   }
			   else{
				   return false;
			   }
		   }			   
	   }
	   //Creates a copy of the given tree as the specified subtree of parent,
	   //this is provided that the parent is present and the specified subtree is empty.
	   //Pre: data in the tree is distinct.
	   //Post: if the operation is successful the specified subtree was created and 
	   // giventree remains the same.
	   //Params: giventree who you are copying from, the parent node you are looking to add the
	   // subtree to, and the child (1,2,3) (LST,MST,RST).
	   bool CreateSubTree(const TernaryTree<ItemType> &GivenTree, const ItemType &parent, int child){
		   if(root==NULL){
			   return(false);
		   }
		   else{
			   if(CreateSubTreeR(root, GivenTree.root, parent, child)){
				   return true;
			   }
			   else{return false;}
		   }
	   }
	   //Transplants a subtree rooted at item, if it is present, to be the new
	   //value of othertree. 
	   //Pre: Values in the tree are distinct.
	   //Post: The Subtree has been removed from the parent tree and given to the 
	   //othertree.
	   //returns true if it was successful
	   bool TransplantSubTree(const ItemType &item, TernaryTree<ItemType> &OtherTree){
		   if(root==NULL){
			   return false;
		   }
		   else if(root->element == item){
			   OtherTree = *this;
			   MakeEmpty();
			   return true;
		   }
		   else{
			   if(TransplantSubTreeR(root, OtherTree.root, item)){
				   return(true);
			   }
			   else{
				   return(false);
			   }
		   }
	   }
	   //Returns true if both values are present in the tree and are siblings.
	   bool AreSiblings(const ItemType& val1, const ItemType& val2){
		   if(root==NULL){
			   return(false);
		   }
		   else{
			   if(AreSiblingsR(root, val1, val2)){
				   return(true);
			   }
			   else{
				   return(false);
			   }
		   }
	   }

   private:
	   struct TernaryNode{
		   ItemType element;
		   TernaryNode *left;
		   TernaryNode *middle;
		   TernaryNode *right;		
		   TernaryNode(const ItemType &theElement, TernaryNode *lt, TernaryNode *mt, TernaryNode *rt)
			   : element(theElement), left(lt), middle(mt), right(rt) { }
	   };
	   TernaryNode *root;
	   queue<int> *levelque;  
	   //MakeEmpty Destroys the tree; 
	   void MakeEmpty(){
		   MakeEmpty(root);
	   }
	   //Recursive path for MakeEmpty.
	   void MakeEmpty(TernaryNode* &t){
			if( t != NULL ){
			   MakeEmpty( t->left );
			   MakeEmpty( t->middle);
			   MakeEmpty( t->right );
			   delete t;
			}
			t = NULL;
	   }
	   //Compare compares two Ternary nodes to see if they are equal
	   //Used by operation ==.
	   bool compare(const TernaryNode * t, const TernaryNode * t2){
		   bool temp = false;
		   if(t == NULL && t2 == NULL){
			   return(true);
		   }
		   else if(t && t2 && t->element == t2->element){
			   temp = true;
			   return(temp && compare(t->left,t2->left) && compare(t2->middle, t->middle)
					&& compare(t2->right, t->right));
		   }
		   else{
			   return(false);
		   }
	   }
	   //Recersive call for Print Pre Order Tree.
	   void printTreePreR(ostream& out, const TernaryNode* t) const{
		   if(t != NULL){
			   out << t->element << " ";
			   printTreePreR(out, t->left);
			   printTreePreR(out, t->middle);
			   printTreePreR(out, t->right);
		   }
	   }
	   //Recersive call for Delete Sub Tree.
	   bool DeleteSubTreeR(TernaryNode*& t, const ItemType &item){
		   TernaryNode *p;
		   if(t->left && t->left->element == item){
			   MakeEmpty(t->left);
			   t->left = NULL;
			   return(true);
		   }
		   if(t->middle && t->middle->element == item){
			   MakeEmpty(t->middle);
			   t->middle = NULL;
			   return(true);
		   }
		   if(t->right && t->right->element == item){
			   MakeEmpty(t->right);
			   t->right = NULL;
			   return(true);
		   }
		   else{
				p = t->left;
				if (p && DeleteSubTreeR(p, item))
					return (true);				
				else{
					p = t->middle;
					if(p && DeleteSubTreeR(p, item)){
						return (true);
					}
					else{
						p = t->right;
						return (p && DeleteSubTreeR(p, item));
					}
				}
		   }
	   }
	   //Recursive Call for print level trav. for tree.
	   void printTreeLevelR(ostream& out, const TernaryNode* t) const{	   
		   int k = 0;		   
		   if(t != NULL){	
			   while(!levelque->empty()){				   
				   out << levelque->front() << " ";
				   levelque->pop();
			   }
			   if(t->left !=NULL){
				   k = t->left->element;
				   levelque->push(k);
			   }	
			   if(t->middle !=NULL){	
				   k = t->middle->element;
				   levelque->push(k);
			   }
			   if(t->right !=NULL){	
				   k = t->right->element;
				   levelque->push(k);
			   }
			printTreeLevelR(out, t->left);			   
			printTreeLevelR(out, t->middle);		   
			printTreeLevelR(out, t->right);
		   }		    	
	   }
	   //Recursive call for insert.
	   bool InsertItemR (const ItemType &item, const ItemType &parent, int child, TernaryNode *p){
		   	const int LCHILD = 1;
			const int MCHILD = 2;
			const int RCHILD = 3;
			TernaryNode *t;
			if (p->element == parent){
				if (child == LCHILD){
					if (p->left != NULL)	// if there already is a LCHILD
						return false;
					else{
						p->left = new TernaryNode (item, NULL, NULL, NULL);
						return true;
					}
				}
				else if (child == MCHILD){
					if (p->middle != NULL)	// if there already is a LCHILD
						return false;
					else{
						p->middle = new TernaryNode (item, NULL, NULL, NULL);
						return true;
					}
				}
				else{// to be inserted as RCHILD 
					if (p->right != NULL)	// if there already is a RCHILD
						return false;
					else{
						p->right = new TernaryNode (item, NULL, NULL, NULL);
						return true;
					}
				}
			} // if node containing parent found
			else{ // try inserting into the LST, followed by into the RST	
				t = p->left;
				if (t && InsertItemR (item, parent, child, t))
					return (true);				
				else{
					t = p->middle;
					if(t && InsertItemR (item, parent, child, t)){
						return (true);
					}
					else{
						t = p->right;
						return (t && InsertItemR(item, parent, child, t));
					}
				}
			}
	   }
	   //Recersive call for create subtree.
	   bool CreateSubTreeR(TernaryNode* p1, TernaryNode* p2, const ItemType &parent, int child){
		   	const int LCHILD = 1;
			const int MCHILD = 2;
			const int RCHILD = 3;
			TernaryNode *t;
			if (p1->element == parent){
				if (child == LCHILD){
					if (p1->left != NULL)	// if there already is a LCHILD
						return false;
					else{
						p1->left = clone(p2);
						return true;
					}
				}
				else if (child == MCHILD){
					if (p1->middle != NULL)	// if there already is a LCHILD
						return false;
					else{
						p1->middle = clone(p2);
						return true;
					}
				}
				else{// to be inserted as RCHILD 
					if (p1->right != NULL)	// if there already is a RCHILD
						return false;
					else{
						p1->right = clone(p2);
						return true;
					}
				}
			} // if node containing parent found
			else{ // try inserting into the LST, followed by into the RST	
				t = p1->left;
				if (t && CreateSubTreeR (t, p2, parent, child))
					return (true);				
				else{
					t = p1->middle;
					if(t && CreateSubTreeR (t, p2, parent, child)){
						return (true);
					}
					else{
						t = p1->right;
						return (t && CreateSubTreeR(t, p2, parent, child));
					}
				}
			}
	   }
	   //Recursive call for transplant Subtree.
	   bool TransplantSubTreeR(TernaryNode*& t, TernaryNode*& t2, const ItemType &item){
		   TernaryNode *p;
		   if(t->left && t->left->element == item){
			   t2 = clone(t->left);
			   MakeEmpty(t->left);
			   t->left = NULL;
			   return(true);
		   }
		   if(t->middle && t->middle->element == item){
			   t2 = clone(t->middle);
			   MakeEmpty(t->middle);
			   t->middle = NULL;
			   return(true);
		   }
		   if(t->right && t->right->element == item){
			   t2 = clone(t->right);
			   MakeEmpty(t->right);
			   t->right = NULL;
			   return(true);
		   }
		   else{
				p = t->left;
				if (p && TransplantSubTreeR(p,t2,item))
					return (true);				
				else{
					p = t->middle;
					if(p && TransplantSubTreeR(p,t2,item)){
						return (true);
					}
					else{
						p = t->right;
						return (p && TransplantSubTreeR(p,t2,item));
					}
				}
		   }
	   }
	   //Recursive call for AreSiblings.
	   bool AreSiblingsR(TernaryNode*& t, const ItemType& val1, const ItemType& val2){
		   TernaryNode *p;
		   if(((t->left && t->right) && (((t->left->element == val1)&&(t->right->element==val2))
			   || ((t->right->element == val1)&&(t->left->element==val2))))){
				   return true;
		   }
		   else if(((t->left && t->middle) && (((t->left->element == val1)&&(t->middle->element==val2))
			   || ((t->middle->element == val1)&&(t->left->element==val2))))){
				   return true;
		   }
		   else if(((t->right && t->middle) && (((t->right->element == val1)&&(t->middle->element==val2))
			   || ((t->middle->element == val1)&&(t->right->element==val2))))){
				   return true;
		   }
		   else{
				p = t->left;
				if (p && AreSiblingsR(p,val1,val2))
					return (true);				
				else{
					p = t->middle;
					if(p && AreSiblingsR(p,val1,val2)){
						return (true);
					}
					else{
						p = t->right;
						return (p && AreSiblingsR(p,val1,val2));
					}
				}
		   }
	   }
	   //Clone copies returns a copy of the entire TernaryNode that it is copying.
	   TernaryNode* clone(TernaryNode *t) const{		   
			if( t == NULL )
				return NULL;
			else
				return new TernaryNode(t->element, clone(t->left), clone(t->middle), clone(t->right));
		}
	   
};
#endif

