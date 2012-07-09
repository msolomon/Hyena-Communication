#ifndef INDIV_HYBRID_H
#define INDIV_HYBRID_H

#include "indiv.h"
#include "indiv_nn.h"

class indiv_hybrid : public indiv_base {
public:
    indiv_hybrid();
    ~indiv_hybrid();
    indiv_hybrid &operator=(const indiv_hybrid &other);
    QStringList serialize();
    void deserialize(QStringList input);
    vect eval_me();
    QString graphviz();
    void clear();
    void generate();
    void xOver(indiv_base *p2);
    int get_size();
    void mutate();
    void set_type(agent_type t);

private:
    indiv vet;
    indiv_nn ann;
};

#endif // INDIV_HYBRID_H
