#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "globals.h"

enum ops {
	zebra,
	nearest_scout,
	nearest_invest,
	nearest_calling,
	north,
	randm,
	last_move,
	constant,
	num_scouts,
	//mirror_nearest, // repeat the previous action of the nearest hyena
	sum,
	invert,
	iflteMAG,
	iflteCLOCKWISE,
	ifVectorZero
};

const int num_terms = 9;//10;
const int num_non_terms = 5;

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
private:
	node *children[4];
	ops operation;
	vect the_const;
	node *parent;
	void replace(node*[], int index);
};

#endif
