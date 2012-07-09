#include "indiv_hybrid.h"

indiv_hybrid::indiv_hybrid(){
}

indiv_hybrid::~indiv_hybrid(){
}

indiv_hybrid &indiv_hybrid::operator =(const indiv_hybrid &other){
    x = other.x;
    y = other.y;
    type = other.type;
    the_info = other.the_info;
    vet = other.vet;
    ann = other.ann;
    return *this;
}

QStringList indiv_hybrid::serialize(){
    QStringList both;
    both += vet.serialize();
    both += ann.serialize();
    return both;
}

void indiv_hybrid::deserialize(QStringList input){
    // TODO: fill in
}

vect indiv_hybrid::eval_me(){
    // VET controls movement
    vet.set_info(the_info);
    // ANN controls calling
    if(CALLING_ENABLED)
        ann.evaluate(the_info);
    return vet.eval_me();
}

QString indiv_hybrid::graphviz(){
    // just graphviz the VET
    return vet.graphviz();
}

void indiv_hybrid::clear(){
    vet.clear();
    ann.clear();
}

void indiv_hybrid::generate(){
    vet.generate();
    ann.generate();
}

void indiv_hybrid::xOver(indiv_base *p2){
    vet.xOver((indiv_base *) &((indiv_hybrid *) p2)->vet);
    ann.xOver((indiv_base *) &((indiv_hybrid *) p2)->ann);
}

int indiv_hybrid::get_size(){
    return vet.get_size(); // ignore ANN size (since used for parsimony pressure)
}

void indiv_hybrid::mutate(){
    vet.mutate();
    ann.mutate();
}

void indiv_hybrid::set_type(agent_type t){
    type = t;
    vet.set_type(t);
    ann.set_type(t);
}
