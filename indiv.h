#ifndef INDIV_H
#define INDIV_H

#include "indiv_base.h"

class indiv: public indiv_base {
public:
    indiv();
    void rand_move();
    void move();
    indiv &operator=(const indiv &);

    void mutate();
    void clear();
    void grow();
    void reset();
    void reset_fitness();
    void generate();

    int get_size() {
        return tree->get_size();
	}
    void count_nodes(int &internal, int &leaf){
        tree->count_nodes(internal, leaf);
    }

    void xOver(indiv*);
    void xOver_90_10(indiv *p2);

	node *tree;

	QStringList serialize();
	void deserialize(QStringList input);
    vect eval_me();
    QString graphviz();
};

#endif
