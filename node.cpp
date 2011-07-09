#include "node.h"

// do fast string building for graphviz output
#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS
//
#define children data.childs
#define the_const data.the_const

using namespace std;

node::node(){
//	for(int i=0; i < 4; i++){
//		children[i] = NULL;
//	}
	operation = north; // just initializing; will be written over
	the_const = NULL;
}

void node::set_child(int c, node *child) {
	children[c] = child;
}

int node::find_child(node *c) {
	int num = 0;
	switch (operation) {
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
		error << "error in find_child: terminal " << (int)operation << endl;
		error.close();
		return -1;
	}
	for (int i = 0; i < num; i++) {
		if (children[i] == c) {
			return i;
		}
	}
	ofstream error;
	error.open("error.txt", ios_base::app);
	error << "error in find_child: child not found " << (int)operation
			<< endl;
	error.close();
	return -1; // still an error
}

void node::copy(node *p) {
	if (!p)
		return;
	clear();
	operation = p->operation;
//	parent = parn;
	switch (operation) {
	// terminals
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
		return;
	case constant:
		the_const = new vect();
		the_const->direction = p->the_const->direction;
		the_const->magnitude = p->the_const->magnitude;
		return;
	case number_hyenas:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		return;
	// non-terminals
	case sum:
		children = new node*[2];
		children[0] = new node();
		children[0]->copy(p->children[0]);
		children[1] = new node();
		children[1]->copy(p->children[1]);
		return;
	case invert:
		children = new node*[1];
		children[0] = new node();
		children[0]->copy(p->children[0]);
		return;
	case iflteMAG:
	case iflteCLOCKWISE:
		children = new node*[4];
		for (int i = 0; i < 4; i++) {
			children[i] = new node();
			children[i]->copy(p->children[i]);
		}
		return;
	case ifVectorZero:
		children = new node*[3];
		for (int i = 0; i < 3; i++) {
			children[i] = new node();
			children[i]->copy(p->children[i]);
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
		return;
	case constant:
		delete the_const;
		return;
	case number_hyenas:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		return;
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
		error << "error in clear: " << (int)operation << endl;
		error.close();
		return;
	}
	for(int i = 0; i < num; i++){
		children[i]->clear();
		delete children[i];
	}
	delete[] children;
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
	case number_hyenas:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		if (Random::Global.Integer(100) < MUTATION_CHANCE){
			if(operation == constant)
				delete the_const;
			if(DISABLED_OP != none_disabled || DISABLED_OP2 != none_disabled){
				do operation = (ops) (Random::Global.Integer(NUM_TERMS));
				while(operation == DISABLED_OP || operation == DISABLED_OP2);
			} else{
				operation = (ops) (Random::Global.Integer(NUM_TERMS));
			}
			if(operation == constant){
				the_const = new vect();
				the_const->random();
			}
		}
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

vect node::evaluate(agent_info *the_indiv, int depth) {
	vect temp;
	if (this == NULL) {
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in evaluate: evaluating null" << endl;
		error.close();
		return (temp);
	}

	depth++;
	// count the size of the tree that is hit
	the_indiv->hits++;

	switch (operation) {
	// terminals
	case zebra:
		the_indiv->importance[zebra] += BASE_IMPORTANCE / depth;
		return (the_indiv->zebra);
	case nearest_hyena:
		the_indiv->importance[nearest_hyena] += BASE_IMPORTANCE / depth;
		return (the_indiv->nearest_hyena);
	case nearest_lion:
		the_indiv->importance[nearest_lion] += BASE_IMPORTANCE / depth;
		return (the_indiv->nearest_lion);
	case nearest_calling:
		the_indiv->importance[nearest_calling] += BASE_IMPORTANCE / depth;
		return (the_indiv->nearest_calling);
	case north:
		the_indiv->importance[north] += BASE_IMPORTANCE / depth;
		temp.direction = 0;
		temp.magnitude = 1;
		return (temp);
	case randm:
		the_indiv->importance[randm] += BASE_IMPORTANCE / depth;
		temp.random();
		return temp;
	case last_move:
		the_indiv->importance[last_move] += BASE_IMPORTANCE / depth;
		return (the_indiv->last_move);
	case constant:
		the_indiv->importance[constant] += BASE_IMPORTANCE / depth;
		return (*the_const);
	case number_hyenas:
		the_indiv->importance[number_hyenas] += BASE_IMPORTANCE / depth;
		temp.direction = 0;
		temp.magnitude = the_indiv->num_hyenas; // only magnitude matters
		return temp;
	case mirror_nearest:
		the_indiv->importance[mirror_nearest] += BASE_IMPORTANCE / depth;
		return (the_indiv->mirrored);
	case last_pen:
		the_indiv->importance[last_pen] += BASE_IMPORTANCE / depth;
		temp.direction = 0;
		temp.magnitude = the_indiv->last_pen;
		return temp;
	case named:
		the_indiv->importance[named] += BASE_IMPORTANCE / depth;
		return the_indiv->named;
	case landmark:
		the_indiv->importance[landmark] += BASE_IMPORTANCE / depth;
		return the_indiv->landmark;
	// non-terminals
	case sum:
		the_indiv->importance[sum] += BASE_IMPORTANCE / depth;
		return children[0]->evaluate(the_indiv, depth) +
				children[1]->evaluate(the_indiv, depth);
	case invert:
		the_indiv->importance[invert] += BASE_IMPORTANCE / depth;
		temp = children[0]->evaluate(the_indiv, depth);
		temp.direction += PI;
		return (temp);
	case iflteMAG:
		the_indiv->importance[iflteMAG] += BASE_IMPORTANCE / depth;
		if (children[0]->evaluate(the_indiv, depth).magnitude <=
				children[1]->evaluate(the_indiv, depth).magnitude)
			return (children[2]->evaluate(the_indiv, depth));
		else
			return (children[3]->evaluate(the_indiv, depth));
	case iflteCLOCKWISE:
		the_indiv->importance[iflteCLOCKWISE] += BASE_IMPORTANCE / depth;
		if (children[0]->evaluate(the_indiv, depth).direction <=
				children[1]->evaluate(the_indiv, depth).direction)
			return (children[2]->evaluate(the_indiv, depth));
		else
			return (children[3]->evaluate(the_indiv, depth));
	case ifVectorZero:
		the_indiv->importance[ifVectorZero] += BASE_IMPORTANCE / depth;
		temp = children[0]->evaluate(the_indiv, depth);
		if (temp.magnitude == 0)
			return (children[1]->evaluate(the_indiv, depth));
		else
			return (children[2]->evaluate(the_indiv, depth));
	default:
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in evaluate: " << operation << endl;
		error.close();
		return temp;
	}
}

void node::grow(int max_d, int depth){
//    parent = pare;
	if(depth == max_d){ // bottomed out, use terminals
		operation = (ops) (Random::Global.Integer(NUM_TERMS));
		if(DISABLED_OP != none_disabled || DISABLED_OP2 != none_disabled){
			do operation = (ops) (Random::Global.Integer(NUM_TERMS));
			while(operation == DISABLED_OP || operation == DISABLED_OP2);
		} else{
			operation = (ops) (Random::Global.Integer(NUM_TERMS));
		}
		if(operation == constant){
			the_const = new vect();
			the_const->random();
		}
	}
	else{ // haven't reached bottom, use FULL or GROW algo. as appropriate
		if(FULL){
			operation = (ops) (NUM_TERMS + Random::Global.Integer(NUM_NON_TERMS));
		} else{
			if(DISABLED_OP != none_disabled || DISABLED_OP2 != none_disabled){
				do operation = (ops) (Random::Global.Integer(NUM_TERMS + NUM_NON_TERMS));
				while(operation == DISABLED_OP || operation == DISABLED_OP2);
			} else{
				operation = (ops) (Random::Global.Integer(NUM_TERMS + NUM_NON_TERMS));
			}
		}
        switch(operation){
		// terminals
		case zebra:
		case nearest_hyena:
		case nearest_lion:
		case nearest_calling:
		case north:
		case randm:
		case last_move:
			break;
		case constant:
			the_const = new vect();
			the_const->random();
			break;
		case number_hyenas:
		case mirror_nearest:
		case last_pen:
		case named:
		case landmark:
			break;
        case sum:
			children = new node*[2];
			children[0] = new node();
			children[0]->grow(max_d,depth+1);
			children[1] = new node();
			children[1]->grow(max_d,depth+1);
            break;
        case invert:
			children = new node*[1];
			children[0] = new node();
			children[0]->grow(max_d,depth+1);
            break;
        case iflteMAG:
        case iflteCLOCKWISE:
			children = new node*[4];
			children[0] = new node();
			children[0]->grow(max_d,depth+1);
			children[1] = new node();
			children[1]->grow(max_d,depth+1);
			children[2] = new node();
			children[2]->grow(max_d,depth+1);
			children[3] = new node();
			children[3]->grow(max_d,depth+1);
            break;
        case ifVectorZero:
			children = new node*[3];
			children[0] = new node();
			children[0]->grow(max_d,depth+1);
			children[1] = new node();
			children[1]->grow(max_d,depth+1);
			children[2] = new node();
			children[2]->grow(max_d,depth+1);
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

int node::calc_size() {
	if (this == NULL) {
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in calc size: evaluating null" << endl;
		error.close();
	}
	int size = 1;
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
	case number_hyenas:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		return size;
	// non-terminals
	case sum:
		size += children[0]->calc_size();
		size += children[1]->calc_size();
		return size;
	case invert:
		size += children[0]->calc_size();
		return size;
	case iflteMAG:
	case iflteCLOCKWISE:
		size += children[0]->calc_size();
		size += children[1]->calc_size();
		size += children[2]->calc_size();
		size += children[3]->calc_size();
		return size;
	case ifVectorZero:
		size += children[0]->calc_size();
		size += children[1]->calc_size();
		size += children[2]->calc_size();
		return size;
	default:
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in calc size: unknown operator" << endl;
		error.close();
		return size;
	}
}

node *node::get_point(int pn, int &current, node *&parent) {
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
	case number_hyenas:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		return this;
	// non-terminals
	case sum:
		parent = this;
		answer = children[0]->get_point(pn, current, parent);
		if (current >= pn)
			return answer;
		parent = this;
		return children[1]->get_point(pn, current, parent);
	case invert:
		parent = this;
		return children[0]->get_point(pn, current, parent);
	case iflteMAG:
	case iflteCLOCKWISE:
		for (int i = 0; i < 4; i++) {
			parent = this;
			answer = children[i]->get_point(pn, current, parent);
			if (current >= pn)
				return answer;
		}
		return answer;
	case ifVectorZero:
		for (int i = 0; i < 3; i++) {
			parent = this;
			answer = children[i]->get_point(pn, current, parent);
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

QString node::graphviz(node *parent, QString extraLabel){
	QString output;
	if(parent == NULL){
		output = QString("digraph hyena {\n") +
				 "splines=true\nepsilon=0\nmclimit=100.0\n" +
				 output.number((int)NULL) + " [label=root]\n";
	} else if(this == NULL){
		return output;
	}
	output += output.number((long long) this) + " [label=\""; // use address as id
    output += extraLabel + " ";

	switch (operation) {
	// terminals
	case zebra:
        output += "zebra\", shape=plaintext]\n";
		break;
	case nearest_hyena:
        output += "nearest_hyena\", shape=plaintext]\n";
		break;
	case nearest_lion:
        output += "nearest_lion\", shape=plaintext]\n";
		break;
	case nearest_calling:
        output += "nearest_calling\", shape=plaintext]\n";
		break;
	case north:
        output += "north\", shape=plaintext]\n";
		break;
	case randm:
        output += "randm\", shape=plaintext]\n";
		break;
	case last_move:
        output += "last_move\", shape=plaintext]\n";
		break;
	case constant:
        output += QString("constant (mag=%1 dir=%2)\", shape=plaintext]\n")
                .arg(the_const->magnitude).arg(the_const->direction);
		break;
	case number_hyenas:
        output += "num_hyenas\", shape=plaintext]\n";
		break;
	case mirror_nearest:
        output += "mirror_nearest\", shape=plaintext]\n";
		break;
	case last_pen:
		output += "last_pen\", shape=plaintext]\n";
		break;
	case named:
		output += "named\", shape=plaintext]\n";
		break;
	case landmark:
		output += "landmark\", shape=plaintext]\n";
		break;
	// non-terminals
	case sum:
        output += "sum\", shape=plaintext]\n";
		for (int i = 0; i < 2; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	case invert:
        output += "invert\", shape=plaintext]\n";
		for (int i = 0; i < 1; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	case iflteMAG:
        output += "iflteMAG\", shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	case iflteCLOCKWISE:
        output += "iflteCLOCKWISE\", shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	case ifVectorZero:
        output += "ifVectorZero\", shape=plaintext]\n";
		for (int i = 0; i < 3; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	default:
		ofstream error;
		error.open("error.txt");
		error << "error in graphviz" << endl;
		error.close();
	}

    output += output.number((long long) parent) +
              "->" + output.number((long long) this) + " [dir=back]\n";

	if(parent == NULL){
		output += QString("}\n");
	}
	return output;
}
#undef children
#undef the_const
