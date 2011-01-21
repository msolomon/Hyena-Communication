#ifndef NODE_H
#define NODE_H

#include "globals.h"

enum ops {num_scouts,zebra, nearest_scout, nearest_invest, 
	north, randm, last_move, constant, sum, invert, iflteMAG, iflteCLOCKWISE, ifVectorZero};
const int num_terms = 8;
const int num_non_terms = 4;//5;

class node{
  public:
    node(void);
    void grow(int,int,node *);
    vect evaluate(agent_info *);
    void mutate(void);
    void clear(void);
    void copy(node *,node *);
    int calc_size(int &);
    node *get_parent(void){return parent;}
    void set_parent(node *p){parent = p;}
    int find_child(node *);
    void set_child(int c2,node *);
    node *get_point(int,int &);
  private:
    node *children[4];
    ops operation;
    vect the_const;
    node *parent;
    void replace(node*[], int index);
};

#endif
