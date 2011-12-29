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

void indiv::lion_move(void) {
	if (the_info.num_hyenas > (the_info.num_lions * HYENA_LION_FEAR_RATIO)) {
		float mag = MAX_HYENA_MOVE -
				(the_info.num_hyenas /
				 (the_info.num_lions * HYENA_LION_FEAR_RATIO));
		if(mag < -MAX_HYENA_MOVE)
			mag = -MAX_HYENA_MOVE;
		x += mag * sin(the_info.nearest_hyena.direction);
		y += mag * cos(the_info.nearest_hyena.direction);
	}
	else if(LIONS_RETURN &&
			the_info.zebra.magnitude < LION_SEES_ZEBRA &&
			the_info.zebra.magnitude > LION_NEAR_ZEBRA){
		float mag = MAX_HYENA_MOVE -
				(the_info.num_hyenas /
				 (the_info.num_lions * HYENA_LION_FEAR_RATIO));
		if(mag < -MAX_HYENA_MOVE)
			mag = -MAX_HYENA_MOVE;
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
	if (v.magnitude > MAX_HYENA_MOVE){ // trying to move too far
		v.magnitude = MAX_HYENA_MOVE;

		the_info.last_move.direction = v.direction;
		the_info.last_move.magnitude = v.magnitude;

		if(v.magnitude != 0) // if moving
			the_info.moved_yet = true;

		x += v.magnitude * sin(v.direction);
		y += v.magnitude * cos(v.direction);
	}
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

