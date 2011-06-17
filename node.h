#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <QString>

#include "globals.h"

typedef char ops;
const ops zebra = 0;
const ops nearest_hyena = 1;
const ops nearest_lion = 2;
const ops nearest_calling = 3;
const ops north = 4;
const ops randm = 5;
const ops last_move = 6;
const ops constant = 7;
const ops num_hyenas = 8;
const ops mirror_nearest = 9; // repeat the previous action of the nearest hyena
const ops delta_fitness = 10;
const ops sum = 11;
const ops invert = 12;
const ops iflteMAG = 13;
const ops iflteCLOCKWISE = 14;
const ops ifVectorZero = 15;

//enum ops {
//	zebra,
//	nearest_hyena,
//	nearest_lion,
//	nearest_calling,
//	north,
//	randm,
//	last_move,
//	constant,
//	num_hyenas,
//	mirror_nearest, // repeat the previous action of the nearest hyena
//	sum,
//	invert,
//	iflteMAG,
//	iflteCLOCKWISE,
//	ifVectorZero
//};

const int num_terms = 11;
const int num_non_terms = 5;

class node;

typedef union{
	node **childs;
	vect *the_const;
} datastore;

class node {
public:
	node(void);
	void grow(int, int, node *);
	vect evaluate(agent_info *);
	void mutate(void);
	void clear(void);
	void copy(node *, node *);
	int calc_size(int &);
	node *get_parent(void) {
		return parent;
	}
	void set_parent(node *p) {
		parent = p;
	}
	int find_child(node *);
	void set_child(int c2, node *);
	node *get_point(int, int &);
	QString graphviz(node *);
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
	node *parent;
	void replace(node*[], int index);
};



#endif
