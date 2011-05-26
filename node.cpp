#include "node.h"

// do fast string building for graphviz output
#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

using namespace std;

node::node(){
	operation = ops(rand() % num_terms);
	for(int i=0; i < 4; i++){
		children[i] = NULL;
	}
}

void node::set_child(int c, node *child) {
	children[c] = child;
}

int node::find_child(node *c) {
	ofstream error;
	if (operation < num_terms) {
		error.open("error.txt", ios_base::app);
		error << "error in find_child: terminal" << endl;
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
	error.open("error.txt", ios_base::app);
	error << "error in find_child: child not found " << int(operation)
			<< endl;
	error.close();
	return -1; // still an error
}

void node::copy(node *p, node * parn) {
	if (!p)
		return;
	operation = p->operation;
	parent = parn;
	clear();
	the_const.magnitude = p->the_const.magnitude;
	the_const.direction = p->the_const.direction;
	switch (operation) {
	// terminals
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
	case constant:
	case num_hyenas:
	case mirror_nearest:
		return;
	// non-terminals
	case sum:
		children[0] = new node();
		children[0]->copy(p->children[0], this);
		children[1] = new node();
		children[1]->copy(p->children[1], this);
		return;
	case invert:
		children[0] = new node();
		children[0]->copy(p->children[0], this);
		return;
	case iflteMAG:
	case iflteCLOCKWISE:
		for (int i = 0; i < 4; i++) {
			children[i] = new node();
			children[i]->copy(p->children[i], this);
		}
		return;
	case ifVectorZero:
		for (int i = 0; i < 3; i++) {
			children[i] = new node();
			children[i]->copy(p->children[i], this);
		}
		return;
	default:
		ofstream error;
		error.open("error.txt");
		error << "error in copy" << endl;
		error.close();
	}
}

void node::clear(void) {
	if(this == NULL)
		return;
	int num = 0;
	switch (operation) {
	// terminals
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
	case constant:
	case num_hyenas:
	case mirror_nearest:
		break;
	// non-terminals
	case sum:
		num = 2;
		break;
	case invert:
		num = 1;
		break;
	case iflteMAG:
	case iflteCLOCKWISE:
		num = 4;
		break;
	case ifVectorZero:
		num = 3;
		break;
	default:
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in clear: " << operation << endl;
		error.close();
		return;
	}
	for(int i = 0; i < num; i++){
		children[i]->clear();
		delete children[i];
	}
}

void node::mutate(void) {
	switch (operation) {
	// terminals
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
	case constant:
	case num_hyenas:
	case mirror_nearest:
		if (rand() % 100 < 10)
			operation = ops(rand() % num_terms);
		break;
	// non-terminals
	case sum:
		children[0]->mutate();
		children[1]->mutate();
		break;
	case invert:
		children[0]->mutate();
		break;
	case iflteMAG:
	case iflteCLOCKWISE:
		children[0]->mutate();
		children[1]->mutate();
		children[2]->mutate();
		children[3]->mutate();
		break;
	case ifVectorZero:
		children[0]->mutate();
		children[1]->mutate();
		children[2]->mutate();
		break;
	default:
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in mutate: " << operation << endl;
		error.close();
		return;
	}
}

vect node::evaluate(agent_info *the_indiv) {
	vect temp, temp1;
	if (this == NULL) {
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in evaluate: evaluating null" << endl;
		error.close();
		return (temp);
	}

	switch (operation) {
	// terminals
	case zebra:
		return (the_indiv-> zebra);
	case nearest_hyena:
		return (the_indiv->nearest_hyena);
	case nearest_lion:
		return (the_indiv->nearest_lion);
	case nearest_calling:
		return (the_indiv->nearest_calling);
	case north:
		temp.direction = PI;
		temp.magnitude = 1;
		return (temp);
	case randm:
		temp.random();
		return temp;
	case last_move:
		return (the_indiv->last_move);
	case constant:
		return (the_const);
	case num_hyenas:
		temp.direction = PI;
		temp.magnitude = the_indiv->num_hyenas; // only magnitude matters
		return temp;
	case mirror_nearest:
		return (the_indiv->mirrored);
	// non-terminals
	case sum:
		temp = children[0]->evaluate(the_indiv);
		temp1 = children[1]->evaluate(the_indiv);
		return ((temp) + (temp1));
	case invert:
		temp = children[0]->evaluate(the_indiv);
		temp.direction += 3.1417;
		return (temp);
	case iflteMAG:
		temp = children[0]->evaluate(the_indiv);
		temp1 = children[1]->evaluate(the_indiv);
		if (temp.magnitude <= temp1.magnitude)
			return (children[2]->evaluate(the_indiv));
		else
			return (children[3]->evaluate(the_indiv));
	case iflteCLOCKWISE:
		temp = children[0]->evaluate(the_indiv);
		temp1 = children[1]->evaluate(the_indiv);
		if (temp.direction <= temp1.direction)
			return (children[2]->evaluate(the_indiv));
		else
			return (children[3]->evaluate(the_indiv));
	case ifVectorZero:
		temp = children[0]->evaluate(the_indiv);
		if (temp.direction == 0 && temp.magnitude == 0)
			return (children[1]->evaluate(the_indiv));
		else
			return (children[2]->evaluate(the_indiv));
	default:
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in evaluate: " << operation << endl;
		error.close();
		return temp;
	}
}

void node::grow(int max_d,int depth,node *pare){
    the_const.random();
    parent = pare;
    if(depth == max_d) // bottomed out, use terminals
        operation = ops(rand()%num_terms);
    else{ // haven't reached bottom, use non-terminals
        operation = ops(num_terms + rand()%num_non_terms);
        switch(operation){
        case sum:
			children[0] = new node();
            children[0]->grow(max_d,depth+1,this);
			children[1] = new node();
            children[1]->grow(max_d,depth+1,this);
			children[2] = NULL;
			children[3] = NULL;
            break;
        case invert:
			children[0] = new node();
            children[0]->grow(max_d,depth+1,this);
			children[1] = NULL;
			children[2] = NULL;
			children[3] = NULL;
            break;
        case iflteMAG:
        case iflteCLOCKWISE:
			children[0] = new node();
            children[0]->grow(max_d,depth+1,this);
			children[1] = new node();
            children[1]->grow(max_d,depth+1,this);
			children[2] = new node();
            children[2]->grow(max_d,depth+1,this);
			children[3] = new node();
            children[3]->grow(max_d,depth+1,this);
            break;
        case ifVectorZero:
			children[0] = new node();
            children[0]->grow(max_d,depth+1,this);
			children[1] = new node();
            children[1]->grow(max_d,depth+1,this);
			children[2] = new node();
            children[2]->grow(max_d,depth+1,this);
			children[3] = NULL;
            break;
        default:
            ofstream error;
            error.open("error.txt", ios_base::app);
            error << "error in grow: " << operation << endl;
            error.close();
            return;
        }
    }
}

int node::calc_size(int &size) {
	if (this == NULL) {
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in calc size: evaluating null" << endl;
		error.close();
	}
	size++;
	switch (operation) {
	// terminals
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
	case constant:
	case num_hyenas:
	case mirror_nearest:
		return size;
	// non-terminals
	case sum:
		children[0]->calc_size(size);
		children[1]->calc_size(size);
		return size;
	case invert:
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
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in calc size: unknown operator" << endl;
		error.close();
		return size;
	}
}

node *node::get_point(int pn, int &current) {
	current++;
	node *answer;
	if (pn == current)
		return this;
	switch (operation) {
	// terminals
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
	case constant:
	case num_hyenas:
	case mirror_nearest:
		return this;
	// non-terminals
	case sum:
		answer = children[0]->get_point(pn, current);
		if (current >= pn)
			return answer;
		return children[1]->get_point(pn, current);
	case invert:
		return children[0]->get_point(pn, current);
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
		ofstream error;
		error.open("error.txt");
		error << "error in get point" << endl;
		error.close();
	}
	return this; // error
}

QString node::graphviz(node *parent){
	QString output;
	if(parent == NULL){
		output = QString("digraph hyena {\n") +
				 "splines=true\nepsilon=0\nmclimit=100.0\n" +
				 output.number((int)NULL) + " [label=root]\n";
	} else if(this == NULL){
		return output;
	}
	output += output.number((long) this) + " [label="; // use address as id

	switch (operation) {
	// terminals
	case zebra:
		output += "zebra, shape=plaintext]\n";
		break;
	case nearest_hyena:
		output += "nearest_hyena, shape=plaintext]\n";
		break;
	case nearest_lion:
		output += "nearest_lion, shape=plaintext]\n";
		break;
	case nearest_calling:
		output += "nearest_calling, shape=plaintext]\n";
		break;
	case north:
		output += "north, shape=plaintext]\n";
		break;
	case randm:
		output += "randm, shape=plaintext]\n";
		break;
	case last_move:
		output += "last_move, shape=plaintext]\n";
		break;
	case constant:
		output += "constant, shape=plaintext]\n";
		break;
	case num_hyenas:
		output += "num_hyenas, shape=plaintext]\n";
		break;
	case mirror_nearest:
		output += "mirror_nearest, shape=plaintext]\n";
		break;

	// non-terminals
	case sum:
		output += "sum, shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
			output += children[i]->graphviz(this);
		}
		break;
	case invert:
		output += "invert, shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
			output += children[i]->graphviz(this);
		}
		break;
	case iflteMAG:
		output += "iflteMAG, shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
			output += children[i]->graphviz(this);
		}
		break;
	case iflteCLOCKWISE:
		output += "iflteCLOCKWISE, shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
			output += children[i]->graphviz(this);
		}
		break;
	case ifVectorZero:
		output += "ifVectorZero, shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
			output += children[i]->graphviz(this);
		}
		break;
	default:
		ofstream error;
		error.open("error.txt");
		error << "error in graphviz" << endl;
		error.close();
	}

	//		cout << "--" << output.toStdString()  << "--" << endl;
	QString label;
	switch(operation){
	case constant:
//		label += ", label=\"(" + label.number(the_const.direction)
//				 + ", " + label.number(the_const.magnitude) + ")\"";
		break;
	default:
		break;
	}

	output += output.number((long) parent) +
			  "->" + output.number((long) this) + " [dir=back"
			  + label + "]\n";


	if(parent == NULL){
		output += QString("}\n");
	}
	return output;
}
