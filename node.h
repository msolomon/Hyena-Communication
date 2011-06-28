#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <QString>

#include "globals.h"

class node;

typedef union{
	node **childs;
	vect *the_const;
} datastore;

class node {
public:
	node(void);
	void grow(int, int);
	vect evaluate(agent_info *, int);
	void mutate(void);
	void clear(void);
	void copy(node *);
	int calc_size();
	int find_child(node *);
	void set_child(int c2, node *);
	node *get_point(int, int &, node *&);
	QString graphviz(node *, QString);
private:
	datastore data;
	ops operation;
//#define children data.childs[0]
//#define the_const data.the_const
//#undef children
//#undef the_const
//	node *children = data.childs;
//	vect *the_const = data.the_const;
//	node *(*children[]);
//	node **children;
//	vect *the_const;
//	node *parent;
	void replace(node*[], int index);
};



#endif
