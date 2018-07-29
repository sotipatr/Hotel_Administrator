#include "string.h"
#include <string>
#include "classfile.h"
#include "stdlib.h"

Reservation::Reservation( char *name, char *ciDate, int sDD ){ strcpy(res_name, name); strcpy(checkinDate, ciDate); stayDurationDays = sDD; }
Reservation::~Reservation(){}

Hotel::Hotel(int num_id, char *name,  int h_stars, int nOR){ id = num_id; strcpy(h_name, name); stars = h_stars; numberOfRooms = nOR;}
Hotel::~Hotel(){}

/* red-black tree functions */
    void RBtree::insert(Hotel* z)
{
     int i=0;
     RBnode *p,*q;
     RBnode *t=new RBnode;
     t->data = z;
     t->key=z->id;
     t->left=NULL;
     t->right=NULL;
     t->color='r';
     p=root;
     q=NULL;
     if(root==NULL)	{
           root=t;
           t->parent=NULL;
     }
     else {
         while(p!=NULL)	{
              q=p;
              if(p->key<t->key)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=q;
         if(q->key<t->key)
              q->right=t;
         else
              q->left=t;
     }
     insertfix(t);
}

	void RBtree::insertfix(RBnode *z)
{
	if (z->parent != NULL && z->parent->parent != NULL)
	{
		while (z != NULL && z->parent != NULL &&
		z->parent->parent != NULL && !z->parent->color == 'b')
		// ass long as color is not black, thus red
		{
			if (z->parent == z->parent->parent->left)
			{
				RBnode *y = z->parent->parent->right;
				if (y != NULL && y->color == 'r')
				{
					z->parent->color = 'b';
					y->color = 'b';
					z->parent->parent->color = 'r';
					z = z->parent->parent;
				}
				else if (z == z->parent->right)
				{
					z = z->parent;
					leftrotate(z);
				}
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rightrotate(z->parent->parent);
			}
			else
			{	
				RBnode *y = z->parent->parent->left; // left instead of right
				if (y != NULL && y->color == 'r') // is red?
				{
					z->parent->color = 'b'; // color = black
					y->color = 'b'; // color = black
					z->parent->parent->color = 'r'; // color = red
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left) // left instead of right
					{
						z = z->parent;
						rightrotate(z);
					}
					z->parent->color = 'b'; // color is black
					z->parent->parent->color = 'r'; // color is red
					leftrotate(z->parent->parent);
				}
			}
		}
	}
}


void RBtree::leftrotate(RBnode *p)
{
     if(p->right==NULL)
           return ;
     else {
           RBnode *y=p->right;
           if(y->left!=NULL) {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}

void RBtree::rightrotate(RBnode *p)
{
     if(p->left==NULL)
          return ;
     else {
         RBnode *y=p->left;
         if(y->right!=NULL) {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

int RBtree::search(int x)
{
     if(root==NULL) {
           cout<<"\nEmpty Tree\n" ;
           return  -2;
     }
     RBnode *p=root;
     int found=0;
     while(p!=NULL&& found==0) {
        if(p->key==x)
            found=1;
        if(found==0) {
            if(p->key<x)
                p=p->right;
            else
                p=p->left;
        }
     }
     if(found==0) {
	           cout<<"\nElement Not Found.";
	           return -1;
	 }
     else
     {
        cout<<"\n\t FOUND NODE: ";
        cout<<"\n Key: "<<p->key;
        cout<<"\n ID: "<<p->data->id;
        cout<<"\n Name: "<<p->data->h_name;
        cout<<"\n Stars: "<<p->data->stars;
        cout<<"\n Number of rooms: "<<p->data->numberOfRooms;
        cout<<"\n Colour: ";
    	if(p->color=='b')
     		cout<<"Black";
    	else
     		cout<<"Red";
        if(p->parent!=NULL)
            cout<<"\n Parent: "<<p->parent->key;
        else
            cout<<"\n There is no parent of the node.  ";
        if(p->right!=NULL)
            cout<<"\n Right Child: "<<p->right->key;
        else
            cout<<"\n There is no right child of the node.  ";
        if(p->left!=NULL)
            cout<<"\n Left Child: "<<p->left->key;
        else
            cout<<"\n There is no left child of the node.  ";
        cout<<endl;
        cout << "\n---- Reservations of hotel " << p->data->h_name << "----" << endl;
		    for(int j=0; j<p->data->reservations.size(); j++){
		        cout << "Name of reservation: " << p->data->reservations[j].res_name << endl;
		        cout << "Check in date: " << p->data->reservations[j].checkinDate << endl;
		        cout << "Stay duration days: " << p->data->reservations[j].stayDurationDays << endl;
		        cout << endl;
		    }
		    cout << endl;
        return x;
     }
}

int RBtree::search2(int x)
{
     if(root==NULL) {
           return  -2;
     }
     RBnode *p=root;
     int found=0;
     while(p!=NULL&& found==0) {
        if(p->key==x)
            found=1;
        if(found==0) {
            if(p->key<x)
                p=p->right;
            else
                p=p->left;
        }
     }
     if(found==0) {
	           return -1;
	 }
     else
     {
        return x;
     }
}

void RBtree::clear(RBnode* &p)
{
	RBnode* temp;
	if (p != NULL)
	{
		clear(p->left);
		clear(p->right);
		temp=p;
		free(temp);
		p=NULL;
	}
}

	/* tries functions */
bool digital_trie::searchTrie(string key)
{
	int level;
	int length = key.size();
	int index;
	bool found = true;
	int i;
	trie_node* searchterm = this->root;
	for (level = 0; level < length; level++)
	{
		if (level == 0)
			index = cap_to_index(key[level]);
		else
			index = char_to_index(key[level]);
		if (!searchterm->children[index])
		{
			found = false;
			break;
		}
		searchterm = searchterm->children[index];
	}
	if (found == true)
	{
		for (i = 0; i < searchterm->TrieVector.size(); i++)
		{
			cout << key + " has made a reservation to  " + searchterm->TrieVector[i]->h_name + " hotel." << endl;
		}
		cout << "\nTotal reservations found with this name:" << i << endl <<endl;
	}
	return found;
}
 
 void digital_trie::insertTrie(Hotel* hotel, string key)
	{
		int level;
		int length = key.size();
		int index;
		trie_node *inserted = this->root;
		for (level = 0; level < length; level++)
		{
			if (level == 0)
				index = cap_to_index(key[level]);
			else
				index = char_to_index(key[level]);
			if (!inserted->children[index])
			{
				trie_node *temp = new trie_node();
				inserted->children[index] = temp;
			}
			inserted = inserted->children[index];
		}
		inserted->TrieVector.push_back(new Hotel(hotel->id, hotel->h_name, hotel->stars, hotel->numberOfRooms));
		inserted->TrieVector[inserted->TrieVector.size() - 1] = hotel;
	}

bool digital_trie::searchTrie2(string key)
{
	int level;
	int length = key.size();
	int index;
	bool found = true;
	int i;
	trie_node* searchterm = this->root;
	for (level = 0; level < length; level++)
	{
		if (level == 0)
			index = cap_to_index(key[level]);
		else
			index = char_to_index(key[level]);
		if (!searchterm->children[index])
		{
			found = false;
			break;
		}
		searchterm = searchterm->children[index];
	}
	return found;
}
