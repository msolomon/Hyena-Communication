#include "indiv_hybrid.h"

indiv_hybrid::indiv_hybrid(){

}

indiv_hybrid &indiv_hybrid::operator =(const indiv_hybrid &other){
    x = other.x;
    y = other.y;
    type = other.type;
    the_info = other.the_info;
    vep = other.vep;
    ann = other.ann;
    return *this;
}

QStringList indiv_hybrid::serialize(){
    QStringList both;
    both += vep.serialize();
    both += ann.serialize();
    return both;
}

void indiv_hybrid::deserialize(QStringList input){
    // TODO: fill in
}

vect indiv_hybrid::eval_me(){
    // VEP controls movement
    vep.set_info(the_info);
    // ANN controls calling
    if(CALLING_ENABLED)
        ann.evaluate(the_info);
    return vep.eval_me();
}

QString indiv_hybrid::graphviz(){
    // just graphviz the VEP
    return vep.graphviz();
}

void indiv_hybrid::clear(){
    vep.clear();
    ann.clear();
}

void indiv_hybrid::generate(){
    vep.generate();
    ann.generate();
}

void indiv_hybrid::xOver(indiv_base *p2){
    vep.xOver((indiv_base *) &((indiv_hybrid *) p2)->vep);
    ann.xOver((indiv_base *) &((indiv_hybrid *) p2)->ann);
}

int indiv_hybrid::get_size(){
    return vep.get_size(); // ignore ANN size (since used for parsimony pressure)
}

void indiv_hybrid::mutate(){
    vep.mutate();
    ann.mutate();
}

void indiv_hybrid::set_type(agent_type t){
    type = t;
    vep.set_type(t);
    ann.set_type(t);
}
