#include "node.h"
void node::set_child(int c, node *child) {
	children[c] = child;
}

int node::find_child(node *c) {
	std::ofstream error;
	if (operation < num_terms) {
		error.open("error.txt", std::ios_base::app);
		error << "error in find_child: terminal" << std::endl;
		error.close();
	}
	int count; // number of children
	if (operation == ifVectorZero)
		count = 3;
	else
		count = 4;
	for (int i = 0; i < count; i++) {
		if (children[i] == c) {
			return i;
		}
	}
	error.open("error.txt", std::ios_base::app);
	error << "error in find_child: child not found " << int(operation)
			<< std::endl;
	error.close();
}

void node::copy(node *p, node * parn) {
	if (!p)
		return;
	operation = p->operation;
	parent = parn;
	for (int i = 0; i < 4; i++) {
		children[i] = NULL;
	}
	the_const.magnitude = p->the_const.magnitude;
	the_const.direction = p->the_const.direction;
	switch (operation) {
	case nearest_scout:
	case zebra:
	case nearest_invest:
	case randm:
	case north:
	case last_move:
	case num_scouts:
	case constant:
		return;
	case invert:
		children[0] = new node;
		children[0]->copy(p->children[0], this);
		return;
	case sum:
		children[0] = new node;
		children[0]->copy(p->children[0], this);
		children[1] = new node;
		children[1]->copy(p->children[1], this);
		return;
	case iflteMAG:
	case iflteCLOCKWISE:
		for (int i = 0; i < 4; i++) {
			children[i] = new node;
			children[i]->copy(p->children[i], this);
		}
		return;
	case ifVectorZero:
		for (int i = 0; i < 3; i++) {
			children[i] = new node;
			children[i]->copy(p->children[i], this);
		}
		return;
	default:
		std::ofstream error;
		error.open("error.txt");
		error << "error in copy" << std::endl;
		error.close();
	}
}

void node::clear(void) {
	int count = 4;
	if (operation && operation == ifVectorZero)
		count = 3;
	for (int i = 0; i < count; i++)
		if (children[i] != NULL) {
			children[i]->clear();
			delete children[i];
		}
}

void node::mutate(void) {
	switch (operation) {
	case nearest_scout:
	case nearest_invest:
	case zebra:
	case randm:
	case north:
	case last_move:
	case num_scouts:
	case constant:
		if (rand() % 100 < 10)
			operation = ops(rand() % num_terms);
		break;
	case invert:
		children[0]->mutate();
		break;
	case sum:
		children[0]->mutate();
		children[1]->mutate();
		break;
	case iflteMAG:
	case iflteCLOCKWISE:
		children[0]->mutate();
		children[1]->mutate();
		children[2]->mutate();
		children[3]->mutate();
		break;
	}
}

vect node::evaluate(agent_info *the_indiv) {
	vect temp, temp1, temp2, temp3;
	temp.magnitude = 0;
	temp.direction = 0;
	if (this == NULL) {
		std::ofstream error;
		error.open("error.txt", std::ios_base::app);
		error << "error in evaluate: evaluating null" << std::endl;
		error.close();
		return (temp);
	}
	switch (operation) {
	case num_scouts:
		temp.direction = PI;
		temp.magnitude = the_indiv->num_scouts; // only magnitude matters
		return temp;
	case zebra:
		return (the_indiv-> zebra);
	case nearest_scout:
		return (the_indiv->nearest_scout);
	case nearest_invest:
		return (the_indiv->nearest_invest);
	case randm:
		temp.random();
		return temp;
	case north:
		temp.direction = PI;
		temp.magnitude = 1;
		return (temp);
	case last_move:
		return (the_indiv->last_move);
	case constant:
		return (the_const);
	case invert:
		temp = children[0]->evaluate(the_indiv);
		temp.direction += 3.1417;
		return (temp);
	case sum:
		temp1 = children[0]->evaluate(the_indiv);
		temp2 = children[1]->evaluate(the_indiv);
		temp3 = temp1 + temp2;
		return temp3;
	case iflteMAG:
		temp1 = children[0]->evaluate(the_indiv);
		temp2 = children[1]->evaluate(the_indiv);
		if (temp1.magnitude <= temp2.magnitude)
			return (children[2]->evaluate(the_indiv));
		else
			return (children[3]->evaluate(the_indiv));
	case iflteCLOCKWISE:
		temp1 = children[0]->evaluate(the_indiv);
		temp2 = children[1]->evaluate(the_indiv);
		if (temp1.direction <= temp2.direction)
			return (children[2]->evaluate(the_indiv));
		else
			return (children[3]->evaluate(the_indiv));
	case ifVectorZero:
//		std::cout << children[0];
//		std::cout << the_indiv;
		temp1 = children[0]->evaluate(the_indiv);
		if (temp1.direction == 0 && temp1.magnitude == 0)
			return (children[1]->evaluate(the_indiv));
		else
			return (children[2]->evaluate(the_indiv));
	default:
		std::ofstream error;
		error.open("error.txt", std::ios_base::app);
		error << "error in evaluate: " << operation << std::endl;
		error.close();
	}
}
;

void node::grow(int max_d, int depth, node *pare) {
	the_const.random();
	parent = pare;
	for (int i = 0; i < 4; i++)
		children[i] = NULL;
	if (depth == max_d)
		operation = ops(rand() % num_terms);
	else {
		operation = ops(num_terms + rand() % num_non_terms);
		switch (operation) {
		case invert:
			children[0] = new node;
			//replace(children, 0);
			children[0]->grow(max_d, depth + 1, this);
			break;
		case sum:
			children[0] = new node;
			//  replace(children, 0);
			children[0]->grow(max_d, depth + 1, this);
			children[1] = new node;
			//replace(children, 1);
			children[1]->grow(max_d, depth + 1, this);
			break;
		case iflteMAG:
		case iflteCLOCKWISE:
			children[0] = new node;
			//  replace(children, 0);
			children[0]->grow(max_d, depth + 1, this);
			children[1] = new node;
			//replace(children, 1);
			children[1]->grow(max_d, depth + 1, this);
			children[2] = new node;
			//replace(children, 2);
			children[2]->grow(max_d, depth + 1, this);
			children[3] = new node;
			//replace(children, 3);
			children[3]->grow(max_d, depth + 1, this);
			break;
		case ifVectorZero:
			children[0] = new node;
			//  replace(children, 0);
			children[0]->grow(max_d, depth + 1, this);
			children[1] = new node;
			//replace(children, 1);
			children[1]->grow(max_d, depth + 1, this);
			children[2] = new node;
			//replace(children, 2);
			children[2]->grow(max_d, depth + 1, this);
		}
	}
}

void node::replace(node *arr[], int idx) {
	if (arr[idx] != NULL)
		delete arr[idx];
	arr[idx] = new node;
}

int node::calc_size(int &size) {
	if (this == NULL) {
		std::ofstream error;
		error.open("error.txt", std::ios_base::app);
		error << "error in calc size: evaluating null" << std::endl;
		error.close();
	}
	size++;
	switch (operation) {
	case zebra:
	case nearest_scout:
	case nearest_invest:
	case randm:
	case north:
	case last_move:
	case constant:
	case num_scouts:
	case invert:
		return (size);
	case sum:
		children[0]->calc_size(size);
		children[1]->calc_size(size);
		return size;
	case iflteMAG:
	case iflteCLOCKWISE:
		children[0]->calc_size(size);
		children[1]->calc_size(size);
		children[2]->calc_size(size);
		children[3]->calc_size(size);
		return size;
	case ifVectorZero:
		children[0]->calc_size(size);
		children[1]->calc_size(size);
		children[2]->calc_size(size);
		return size;
	default:
		std::ofstream error;
		error.open("error.txt", std::ios_base::app);
		error << "error in calc size: unknown operator" << std::endl;
		error.close();
	}
}
;

node::node(void) {
	operation = ops(rand() % num_terms);
}

node *node::get_point(int pn, int &current) {
	current++;
	node *answer;
	if (pn == current)
		return this;
	switch (operation) {
	case zebra:
	case nearest_scout:
	case nearest_invest:
	case randm:
	case north:
	case last_move:
	case constant:
	case num_scouts:
		return this;
	case invert:
		return children[0]->get_point(pn, current);
	case sum:
		answer = children[0]->get_point(pn, current);
		if (current >= pn)
			return answer;
		return children[1]->get_point(pn, current);
	case iflteMAG:
	case iflteCLOCKWISE:
		for (int i = 0; i < 4; i++) {
			answer = children[i]->get_point(pn, current);
			if (current >= pn)
				return answer;
		}
		return answer;
	case ifVectorZero:
		for (int i = 0; i < 3; i++) {
			answer = children[i]->get_point(pn, current);
			if (current >= pn)
				return answer;
		}
		return answer;
	default:
		std::ofstream error;
		error.open("error.txt");
		error << "error in get point" << std::endl;
		error.close();
	}
}
