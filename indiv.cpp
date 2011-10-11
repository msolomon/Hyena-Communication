#include "indiv.h"

void indiv::xOver(indiv *p2) {
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
            short c1 = tempP1->find_child(xOver1);
            short c2 = tempP2->find_child(xOver2);
			tempP2->set_child(c2, xOver1);
			tempP1->set_child(c1, xOver2);
		}
	}
}

void indiv::reset_fitness() {
    for(int i = 0; i < NUM_TESTS; i++){
        fitnesses[i] = 0;
    }
	reward = 0;
	lion_attacks = 0;
    attack_pen = 0;
	avg_dist_to_zebra = 0;
	the_info.hits = 0;
	for(int i = 0; i < NUM_OPS; i++){
		the_info.importance[i] = 0;
	}
}

void indiv::reset(void) {
	calling = false;
	if (type == lion) {
		// place lions within 1 unit of zebra
		x = ZEBRAX + Random::Global.FloatW();
		y = ZEBRAY + Random::Global.FloatW();
	} else {
		x = y = 0;
		while (distance_sq(x, y) < (
				   (LION_ATTACK_RADIUS + 1) * (LION_ATTACK_RADIUS + 1)
				   )){
			x = Random::Global() / ((float)Random::max / (float)X);
			y = Random::Global() / ((float)Random::max / (float)Y);
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
	tree->mutate();
}

void indiv::rand_move() {
	//   x+=((rand()%3-1)/50.0);
	//   y+=((rand()%3-1)/50.0);
}

void indiv::lion_move(void) {
	if (the_info.num_hyenas > (the_info.num_lions * HYENA_LION_FEAR_RATIO)) {
		float mag = tanh((the_info.num_hyenas /
						  (the_info.num_lions * HYENA_LION_FEAR_RATIO)));
		x += mag * sin(the_info.nearest_hyena.direction);
		y += mag * cos(the_info.nearest_hyena.direction);
	}
	else if(LIONS_RETURN &&
			the_info.zebra.magnitude < LION_SEES_ZEBRA &&
			the_info.zebra.magnitude > LION_NEAR_ZEBRA){
		float mag = 1.0 - (the_info.num_hyenas /
				(the_info.num_lions * HYENA_LION_FEAR_RATIO));
	 x -= mag * sin(the_info.zebra.direction);
	 y -= mag * cos(the_info.zebra.direction);
	 }
}

void indiv::move(void) {
	vect v;
	if (type == lion) {
		lion_move();
		return;
	}
	v = tree->evaluate(&the_info, 0);
	if (v.magnitude > 1){ // trying to move too far
		v.magnitude = 1;

		the_info.last_move.direction = v.direction;
		the_info.last_move.magnitude = v.magnitude;

		x += v.magnitude * sin(v.direction);
		y += v.magnitude * cos(v.direction);
	}
}

indiv::indiv(void) {
}

