#ifndef INDIV_H
#define INDIV_H

#include "indiv_base.h"

class indiv: public indiv_base {
public:


	void rand_move(void);
	void lion_move(void);
	void move(void);
	indiv &operator=(const indiv &);

	void mutate(void);
	void clear(void);
	void grow(void);
	void reset(void);
	void reset_fitness(void);

	int get_size(void) {
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

};

#endif
