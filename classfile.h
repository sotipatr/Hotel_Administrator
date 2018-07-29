#ifndef CLASSFILE_H
#define CLASSFILE_H

#include <iostream>
#include <vector>
#include <string>
#include "string.h"
using namespace std;

/* main classes */
class Reservation{
      public:
      char res_name[56];
      char checkinDate[256];
      int stayDurationDays;      
      Reservation(char *name, char *ciDate, int sDD); 
      ~Reservation();
      };
      
class Hotel{
      public:
		int id;
		char h_name[256];
		int stars;
		int numberOfRooms;
		vector<Reservation> reservations;
		Hotel( int num_id, char *name,  int h_stars, int nOR);
        ~Hotel();
      };

/* red-black tree structure and class */
struct RBnode
{
       int key;
       RBnode *parent;
       char color;
       RBnode *left;
       RBnode *right;
       Hotel *data;
};

class RBtree
{
      RBnode *root;
      RBnode *q;
   public :
      RBtree()
      {
              q=NULL;
              root=NULL;
      }
      void clear(RBnode* &);
      void insert(Hotel* z);
      void insertfix(RBnode *);
      void leftrotate(RBnode *);
      void rightrotate(RBnode *);
      void display(RBnode *);
      void disp();
      int search(int x);
      int search2(int x);
};

/* digital trie structure and class */
#define char_to_index(c) ((int)c-(int)'a')
#define cap_to_index(c) ((int)c-(int)'A')

class trie_node {
public:
	trie_node* children[26];
	vector<Hotel*> TrieVector;
	trie_node()
	{
		for (int i = 0; i < 26; i++)	children[i] = 0;
	}
};

class digital_trie {
public:
	trie_node *root;
	digital_trie()
	{
		root = new trie_node();
	}
	~digital_trie() {}
	void insertTrie(Hotel* hotel, string key);
	bool searchTrie(string key);
	bool searchTrie2(string key);
};     
#endif
