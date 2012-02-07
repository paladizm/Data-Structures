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
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "dsexceptions.h"
#include <iostream>    
#include <queue>
#include "HelperFunctions.h"
using namespace std;    
template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) :root( NULL ){}

    BinarySearchTree( const BinarySearchTree & rhs ) : root( NULL ){
        *this = rhs;
    }

    /**
	 * Destructor for the tree
	 */
    ~BinarySearchTree( ){
        makeEmpty( );
    }
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const{
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const{
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order with parens seperating
	 * the children and parent.
     */
    void printTree( ostream & out = cout ) const{
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( ){
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x ){
        insert( x, root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
	
	//Preforms an LL rotation on that node
	//if it is possible. 
	//return true on success false otherwise.
	bool LLat (const Comparable &x){
		if(root == NULL){
			return false;
		}
		else{
			return(LLat(x, root));
		}
	}		
	//Preforms an RR rotation on that node
	//if it is possible. 
	//return true on success false otherwise.
	bool RRat (const Comparable &x){
		if(root == NULL){
			return false;
		}
		else{
			return(RRat(x, root));
		}
	}
	//Returns true if the tree is an AVL tree false
	//if otherwise.
	bool AVL(){
		if(root == NULL){
			return true;
		}
		else{
			return(AVL(root));
		}
	}
	//Checks to see if the tree can be turned into an AVL tree
	//upon one LL rotation if it cannot the function will return false
	//if it can it will preform the rotation and return the value it rotated on.
	bool OneLLDoesIt(Comparable &Value){
		if(root == NULL){
			return false;
		}
		else if(AVL()){
			return false;
		}
		else{
			return(OneLLDoesIt(Value, root));
		}
	}
	//Calculates the width of the tree and returns it.
	int Width(){
		if(root == NULL){
			return(0);
		}
		else{
			return(Width(root));
		}
	}

	//overloads the == operator to see if 2 trees are equal.
	bool operator==(const BinarySearchTree<Comparable> & rhs){		   
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
    /**
     * Deep copy.
     */
    const BinarySearchTree & operator=( const BinarySearchTree & rhs ){
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
		int height;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, int h = 0 )
            : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };

    BinaryNode *root;
	//Calculates the hieght of the tree
	int height(BinaryNode* p){		
		int lh, rh;
		if (p==NULL)
			return(-1);
		else{
			lh = height (p->left);
			rh = height (p->right);
			if(lh > rh)
				return(1 + lh);
			else
				return(1 + rh);
		}
	}
	//Compare compares two Binary nodes to see if they are equal
	//Used by operation ==.
	bool compare(const BinaryNode * t, const BinaryNode * t2){
		   bool temp = false;
		   if(t == NULL && t2 == NULL){
			   return(true);
		   }
		   else if(t && t2 && t->element == t2->element){
			   temp = true;
			   return(temp && compare(t->left,t2->left) && compare(t2->right, t->right));
		   }
		   else{
			   return(false);
		   }
	   }
	//Recursive algorithm for LLat
	bool LLat (const Comparable &x, BinaryNode*& t){
		if(t!=NULL){
			if(t->element == x){				
				if(t->left && t->left->element < x){
						rotateLeft(t);
						return true;			
				}
				else{
					return false;
				}
			}		
			else if( x < t->element){
				return(LLat(x, t->left));
			}
			else if( x > t->element){
				return(LLat(x, t->right));
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	//The left rotation	
	void rotateLeft(BinaryNode*& t){
		BinaryNode *t2 = t->left;
		t->left = t2->right;
		t2->right = t;
		t->height = max(height(t->left), height(t->right))+1;
		t2->height = max(height(t2->left), height(t2->right))+1;
		t = t2;
	}
	//Recursive algorithm for RRat
	bool RRat (const Comparable &x, BinaryNode*& t){
		if(t!=NULL){
			if(t->element == x){				
				if(t->right && t->right->element > x){
						rotateRight(t);
						return true;
					}
				else{
					return false;
					}
			}		
			else if( x < t->element){
				return(RRat(x, t->left));
			}
			else if( x > t->element){
				return(RRat(x, t->right));
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	//rotation right
	void rotateRight(BinaryNode*& t){
		BinaryNode *t2 = t->right;
		t->right = t2->left;
		t2->left = t;
		t->height = max(height(t->left), height(t->right))+1;
		t2->height = max(height(t2->left), height(t2->right))+1;
		t = t2;
	}
	//recursive algorithm for AVL
	bool AVL(BinaryNode*& t){
		if(t!=NULL){
			int p = (height(t->left) - height(t->right));
			if((p <= 1) && (p >= -1)){
				return(AVL(t->left)&& AVL(t->right));
			}
			else{
				return false;
			}
		}
		else{
			return true;
		}
	}
	//recersive algorithm for OneLLDoesIt.
	bool OneLLDoesIt(Comparable &Value, BinaryNode*& t){
		if(t!=NULL){
			bool h;
			h = LLat(t->element, t);
			if(h){
				if(AVL()){
					Value = t->element;
					return true;
				}
				else{
					RRat(t->element, t);
					bool a,k;
					a = OneLLDoesIt(Value, t->left);					
					if(a){
						return a;
					}
					k = OneLLDoesIt(Value, t->right);
					if(k){
						return k;
					}
					else{
						return false;
					}
				}

			}
			else{
				bool a,k;
					a = OneLLDoesIt(Value, t->left);					
					if(a){
						return a;
					}
					k = OneLLDoesIt(Value, t->right);
					if(k){
						return k;
					}
					else{
						return false;
					}
			}
		}
		else{
			return false;
		}
	}
	//Non-Recursive width of a tree.
	int Width(BinaryNode *& t){                
	   queue<BinaryNode*> q1, q2;    
	   BinaryNode* temp = t;    
	   int width, maxwidth;                  
	   bool emptyrow; 
	   if( temp == NULL )             
		  emptyrow = true;            
	   else                             
		  emptyrow = false;           
	   width = maxwidth = 0;           
	   q1.push(temp);     
	   while( emptyrow == false ){
		  emptyrow = true;         
		  while(!q1.empty()){
			 temp = q1.front();
			 q1.pop();
			 if(temp != NULL){
				width++;                 
				q2.push(temp->left);  
				q2.push(temp->right);             
				if( temp->left != NULL || temp->right != NULL ){
					emptyrow = false;}
			 }
		  }
		  while(!q2.empty()) {        
			q1.push(q2.front());
			q2.pop();
		  }
			if( width > maxwidth ){       
				maxwidth = width; } 
			width = 0;     
	   }	
		return maxwidth; 
	}
	   
		  
			
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            t = new BinaryNode( x, NULL, NULL );
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
		t->height = max( height(t->left), height(t->right)) + 1;
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != NULL && t->right != NULL ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            delete oldNode;
        }
		if(t){
			t->height = max( height(t->left), height(t->right)) + 1;
		}
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != NULL ){
            out << "(";
			printTree( t->left, out );
			out << ")";
            out << t->element << " ";
			out << "(";
            printTree( t->right, out );
			out << ")";
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new BinaryNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }

};

#endif
