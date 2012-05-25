#include "indiv.h"

indiv::indiv(){
    tree = NULL;
}

void indiv::xOver_regular(indiv *p2) {
	int temp = 0;
    int point1, point2, tmp1, tmp2, size1, size2;
	point1 = point2 = 0;
	node *tempP1 = NULL;
	node *xOver1;
	node *tempP2 = NULL;
	node *xOver2;
    size1 = get_size();
    size2 = p2->get_size();
	do{
        point1 += Random::Global.Integer(size1 + 1 - point1);
        point2 += Random::Global.Integer(size2 + 1 - point2);
		temp = 0;
		xOver1 = tree->get_point(point1, temp, tempP1);
        tmp1 = xOver1->get_size();
		temp = 0;
		xOver2 = p2->tree->get_point(point2, temp, tempP2);
        tmp2 = xOver2->get_size();
	} while (TREE_MAX_SIZE != INT_MAX && // INT_MAX means unbounded trees
			 (size1 + tmp2 - tmp1 > TREE_MAX_SIZE ||
			  size2 + tmp1 - tmp2 > TREE_MAX_SIZE));
	if (tempP1 != NULL) { // not root
		if (tempP2 != NULL) { // not root
            int c1 = tempP1->find_child(xOver1);
            int c2 = tempP2->find_child(xOver2);
			tempP2->set_child(c2, xOver1);
			tempP1->set_child(c1, xOver2);
		}
	}
}

void indiv::xOver_90_10(indiv *p2) {
    int temp = 0;
    int point1, point2, tmp1, tmp2, internal1, internal2, leaf1, leaf2;
    node *tempP1 = NULL;
    node *xOver1;
    node *tempP2 = NULL;
    node *xOver2;
    internal1 = internal2 = leaf1 = leaf2 = tmp1 = tmp2 = 0;
    count_nodes(internal1, leaf1);
    p2->count_nodes(internal2, leaf2);

    do{
        // pick an internal node 90% of the time and leaf node 10% of the time
        if (Random::Global.Integer(100) < 90){ // then pick internal
            point1 = Random::Global.Integer(internal1 + 1);
        } else{
            point1 = internal1 + Random::Global.Integer(leaf1 + 1);
        }
        // repeat independently for point on second parent
        if (Random::Global.Integer(100) < 90){ // then pick internal
            point2 = Random::Global.Integer(internal2 + 1);
        } else{
            point2 = internal2 + Random::Global.Integer(leaf2 + 1);
        }

        temp = 0;
        xOver1 = tree->get_point(point1, temp, tempP1);
        tmp1 = xOver1->get_size();
        temp = 0;
        xOver2 = p2->tree->get_point(point2, temp, tempP2);
        tmp2 = xOver2->get_size();
    } while (TREE_MAX_SIZE != INT_MAX && // INT_MAX means unbounded trees
             (internal1 + leaf1 + tmp2 - tmp1 > TREE_MAX_SIZE ||
              internal2 + leaf2 + tmp1 - tmp2 > TREE_MAX_SIZE));
    if (tempP1 != NULL) { // not root
        if (tempP2 != NULL) { // not root
            int c1 = tempP1->find_child(xOver1);
            int c2 = tempP2->find_child(xOver2);
            tempP2->set_child(c2, xOver1);
            tempP1->set_child(c1, xOver2);
        }
    }
}



indiv &indiv::operator=(const indiv &source) {
	x=source.x;
	y=source.y;
	the_info = source.the_info;
    clear(); // this deletes tree
	if(source.type == hyena){
		tree = new node();
		tree->copy(source.tree);
	}
	return *this;
}

void indiv::grow(void) {
	x = ZEBRAX;
	y = ZEBRAY;
	tree = new node();
	tree->grow(GROW_DEPTH, 0);
}

void indiv::clear(void) {
	tree->clear();
	delete tree;
	tree = NULL;
}

void indiv::mutate(void) {
	double chance;
	if(NUM_OVER_SIZE_MUTATION > 0){
		chance = NUM_OVER_SIZE_MUTATION / tree->get_size();
	} else{
		chance = MUTATION_CHANCE / 100.0;
	}
	tree->mutate(chance);
}

void indiv::rand_move() {
	//   x+=((rand()%3-1)/50.0);
	//   y+=((rand()%3-1)/50.0);
}



vect indiv::eval_me(){
    return tree->evaluate(&the_info, 0);
}

QString indiv::graphviz(){
    return tree->graphviz(NULL, "");
}

QStringList indiv::serialize(){
    return tree->serialize();
}

void indiv::deserialize(QStringList input){
	tree->clear();
	tree = NULL;
	node* child = new node();
	tree = child->deserialize(input);
}



void indiv::generate(){
    grow();
}

void indiv::xOver(indiv_base *p2)
{
    if(USE_90_10_XOVER)
        xOver_90_10((indiv *) p2);
    else
        xOver_regular((indiv *) p2);
}
