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
    size = 0;
}

void node::set_child(int c, node *child) {
	children[c] = child;
}

int node::find_child(node *c) {
    int num = 0; // arity of operator
	switch (operation) {
	// non-terminals
	case sum:
	case subtract:
    case compare:
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
    size = p->size;
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
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		return;
	// non-terminals
	case sum:
	case subtract:
	case compare:
		children[0] = new node();
		children[0]->copy(p->children[0]);
		children[1] = new node();
		children[1]->copy(p->children[1]);
		return;
	case invert:
		children[0] = new node();
		children[0]->copy(p->children[0]);
		return;
	case iflteMAG:
	case iflteCLOCKWISE:
		for (int i = 0; i < 4; i++) {
			children[i] = new node();
			children[i]->copy(p->children[i]);
		}
		return;
	case ifVectorZero:
		for (int i = 0; i < 3; i++) {
			children[i] = new node();
			children[i]->copy(p->children[i]);
		}
		return;
	default:
		// handle hyena input case
		if(operation < NUM_OPS){
			return; // don't need to do anything
		}
		ofstream error;
		error.open("error.txt");
		error << "error in copy" << endl;
		error.close();
	}
}

void node::clear(void) {
	if(this == NULL)
		return;
    int num = 0; // arity of operator
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
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		return;
	// non-terminals
	case sum:
    case subtract:
    case compare:
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
		// handle hyena input case
		if(operation < NUM_OPS){
			return; // don't need to do anything
		}
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
}

static double spare;
static bool spare_ready = false;
double normal_sample(double mu, double sigma){
	/* Generate random samples using the Marsaglia polar method */
	if(spare_ready){
		spare_ready = false;
		return mu + (spare * sigma);
	}

	double u, v, s;
	do{
		u = Random::Global.FixedW();
		v = Random::Global.FixedW();
		s = (u * u) + (v * v);
	} while(s >= 1 || s == 0);

	spare = v * sqrt(-2.0 * (log(s) / s));
	spare_ready = true;

	return mu + sigma * u * sqrt(-2.0 * (log(s) / s));
}

ops mutate_internal(const ops choices[], ops except=(ops)255){
	ops choice;
	do
		choice = choices[Random::Global.Integer(sizeof(choices)/sizeof(ops))];
	while(choice == except);
	return choice;
}

/* chance of mutation on [0, 1] per node*/
void node::mutate(double chance) {
	bool mut_this = (Random::Global.FixedN() < chance);
	switch (operation) {
	// non-terminals
	case sum:
    case subtract:
    case compare:
		if(mut_this && ALLOW_INTERNAL_MUTATION){
			const ops same_arity[] = {sum, subtract, compare};
			operation = mutate_internal(same_arity, operation);
		}
		children[0]->mutate(chance);
		children[1]->mutate(chance);
		break;
	case invert:
		// can't mutate: no other nodes of same arity
		children[0]->mutate(chance);
		break;
	case iflteMAG:
	case iflteCLOCKWISE:
		if(mut_this && ALLOW_INTERNAL_MUTATION){
			const ops same_arity[] = {iflteMAG, iflteCLOCKWISE};
			operation = mutate_internal(same_arity, operation);
		}
		children[0]->mutate(chance);
		children[1]->mutate(chance);
		children[2]->mutate(chance);
		children[3]->mutate(chance);
		break;
	case ifVectorZero:
		// can't mutate: no other nodes of same arity
		children[0]->mutate(chance);
		children[1]->mutate(chance);
		children[2]->mutate(chance);
		break;

	// terminals
	case constant:
		// specialized "gaussian shift" constant mutation
		if(mut_this){
			the_const->magnitude += normal_sample(0.0, CONST_MUT_MAG_SIGMA);
			if(the_const->magnitude < 0.0) the_const->magnitude = 0.0;

			the_const->direction += normal_sample(0.0, CONST_MUT_DIR_SIGMA);
			if(the_const->direction > PI) the_const->direction -= 2*PI;
			else if(the_const->direction < -PI) the_const->direction += 2*PI;
		}
		break;
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
	default:
		// handle hyena input case as well as terminals
		if(operation < NUM_OPS){
			if (mut_this){
				operation = get_rand_terminal(operation);
				if(operation == constant){
					the_const = new vect();
					the_const->random();
				}
			}
		} else {
			ofstream error;
			error.open("error.txt", ios_base::app);
			error << "error in mutate: " << operation << endl;
			error.close();
			return;
		}
	}
}

vect node::evaluate(agent_info *the_indiv, int depth) {
/*
	if (this == NULL) {
		vect temp;
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in evaluate: evaluating null" << endl;
		error.close();
		return (temp);
	}
*/

	depth++;
	// count the size of the tree that is hit
	the_indiv->hits++;

	the_indiv->importance[operation] += BASE_IMPORTANCE / depth;

	switch (operation) {
	// terminals
	case zebra:
		return (the_indiv->zebra);
	case nearest_hyena:
		return (the_indiv->nearest_hyena);
	case nearest_lion:
		return (the_indiv->nearest_lion);
	case nearest_calling:

		return (the_indiv->nearest_calling);
	case north: {
		vect temp;
        temp.direction = 0;
		temp.magnitude = the_indiv->north_enabled ? 1 : 0;
		return (temp);
	}
	case randm: {
		vect temp;
        if(the_indiv->randm_enabled)
			temp.random();
		else
			temp.reset();
		return temp;
	}
	case last_move:
		return (the_indiv->last_move);
	case constant:
		if(the_indiv->constant_enabled)
			return (*the_const);
		else{
			vect temp;
			temp.reset();
			return temp;
		}
	case number_calling: {
		vect temp;
		temp.direction = 0;
		temp.magnitude = the_indiv->num_hyenas; // only magnitude matters
		return temp;
	}
	case mirror_nearest:
		return (the_indiv->mirrored);
	case last_pen: {
		vect temp;
		temp.direction = 0;
		temp.magnitude = the_indiv->last_pen;
		return temp;
	}
	case named:
		return the_indiv->named;
	case landmark:
		return the_indiv->landmark;
	// non-terminals
	case sum:
		return children[0]->evaluate(the_indiv, depth) +
				children[1]->evaluate(the_indiv, depth);
	case subtract: {
		vect temp;
		// get second input and invert it
		temp = children[1]->evaluate(the_indiv, depth);
		temp.invert();
		// add it to the first input
		return (temp + children[0]->evaluate(the_indiv, depth));
	}
    case compare:
		return compare_vectors(children[0]->evaluate(the_indiv, depth),
							   children[1]->evaluate(the_indiv, depth));
	case invert: {
		vect temp;
        temp = children[0]->evaluate(the_indiv, depth);
		temp.invert();
		return (temp);
	}
	case iflteMAG:
		if (children[0]->evaluate(the_indiv, depth).magnitude <=
				children[1]->evaluate(the_indiv, depth).magnitude)
			return (children[2]->evaluate(the_indiv, depth));
		else
			return (children[3]->evaluate(the_indiv, depth));
	case iflteCLOCKWISE:
		if (children[0]->evaluate(the_indiv, depth).direction <=
				children[1]->evaluate(the_indiv, depth).direction)
			return (children[2]->evaluate(the_indiv, depth));
		else
			return (children[3]->evaluate(the_indiv, depth));
	case ifVectorZero: {
		vect temp;
		temp = children[0]->evaluate(the_indiv, depth);
		if (temp.magnitude == 0)
			return (children[1]->evaluate(the_indiv, depth));
		else
			return (children[2]->evaluate(the_indiv, depth));
	}
	default: {
		// handle hyena input case
		if(operation < NUM_OPS){
			return the_indiv->hyenas[operation - NUM_UNIQUE_OPS];
		}
		vect temp;
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in evaluate: " << operation << endl;
		error.close();
		return temp;
	}
	}
}

vect node::compare_vectors(vect a, vect b){
    vect temp;
	double ax, ay, bx, by;
    ax = sin(a.direction) * a.magnitude;
    ay = cos(a.direction) * a.magnitude;

	bx = sin(b.direction) * b.magnitude;
	by = cos(b.direction) * b.magnitude;

    // distance between the two points
	temp.magnitude = dist(bx - ax, by - ay);
	// angle between (0, 0) and the end points
	temp.direction = atan2(bx, by) - atan2(ax, ay);
	if(temp.direction > PI) temp.direction -= 2*PI;
	else if(temp.direction < -PI) temp.direction += 2*PI;
	temp.direction = fabs(temp.direction);
    return temp;
}

void node::grow(int max_d, int depth){
//    parent = pare;
	if(depth == max_d){ // bottomed out, use terminals
		operation = get_rand_terminal();

		if(operation == constant){
			the_const = new vect();
			the_const->random();
		}
	}
	else{ // haven't reached bottom, use FULL or GROW algo. as appropriate
		if(FULL)
			operation = get_rand_nonterminal();
		else // grow
			operation = get_rand_op();

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
		case number_calling:
		case mirror_nearest:
		case last_pen:
		case named:
		case landmark:
			break;
        case sum:
		case subtract:
		case compare:
			children[0] = new node();
			children[0]->grow(max_d,depth+1);
			children[1] = new node();
			children[1]->grow(max_d,depth+1);
            break;
        case invert:
			children[0] = new node();
			children[0]->grow(max_d,depth+1);
            break;
        case iflteMAG:
        case iflteCLOCKWISE:
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
			children[0] = new node();
			children[0]->grow(max_d,depth+1);
			children[1] = new node();
			children[1]->grow(max_d,depth+1);
			children[2] = new node();
			children[2]->grow(max_d,depth+1);
            break;
        default:
			// handle hyena input case
			if(operation < NUM_OPS){
				break;
			}
            ofstream error;
            error.open("error.txt", ios_base::app);
            error << "error in grow: " << operation << endl;
            error.close();
            break;
        }
    }

//    get_size(); // this will be done on first usage anyway. lazy evaluate
}

int node::get_size() {
/*
	if (this == NULL) {
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in calc size: evaluating null" << endl;
		error.close();
	}
*/
    if(size > 0){
        return size;
    }

    size = 1;

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
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
        break;
	// non-terminals
	case sum:
	case subtract:
	case compare:
        size += children[0]->get_size();
        size += children[1]->get_size();
        break;
	case invert:
        size += children[0]->get_size();
        break;
	case iflteMAG:
	case iflteCLOCKWISE:
        size += children[0]->get_size();
        size += children[1]->get_size();
        size += children[2]->get_size();
        size += children[3]->get_size();
        break;
	case ifVectorZero:
        size += children[0]->get_size();
        size += children[1]->get_size();
        size += children[2]->get_size();
        break;
	default:
		// handle hyena input case
		if(operation < NUM_OPS){
			break;
		}
		ofstream error;
		error.open("error.txt", ios_base::app);
		error << "error in calc size: unknown operator" << endl;
		error.close();
        break;
	}
    return size;
}

// count internal and leaf nodes seperately (for 90/10 crossover)
void node::count_nodes(int &internal, int &leaf) {

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
    case number_calling:
    case mirror_nearest:
    case last_pen:
    case named:
    case landmark:
        leaf += 1;
        return;
    // non-terminals
    case sum:
    case subtract:
    case compare:
        children[0]->count_nodes(internal, leaf);
        children[1]->count_nodes(internal, leaf);
        break;
    case invert:
        children[0]->count_nodes(internal, leaf);
        break;
    case iflteMAG:
    case iflteCLOCKWISE:
        children[0]->count_nodes(internal, leaf);
        children[1]->count_nodes(internal, leaf);
        children[2]->count_nodes(internal, leaf);
        children[3]->count_nodes(internal, leaf);
        break;
    case ifVectorZero:
        children[0]->count_nodes(internal, leaf);
        children[1]->count_nodes(internal, leaf);
        children[2]->count_nodes(internal, leaf);
        break;
    default:
        // handle hyena input case
        if(operation < NUM_OPS){
            leaf += 1;
            return;
        }
        ofstream error;
        error.open("error.txt", ios_base::app);
        error << "error in count_nodes: unknown operator" << endl;
        error.close();
        break;
    }
    internal += 1;
    return;
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
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		return this;
	// non-terminals
	case sum:
	case subtract:
	case compare:
        size = 0;
		parent = this;
		answer = children[0]->get_point(pn, current, parent);
		if (current >= pn)
			return answer;
		parent = this;
		return children[1]->get_point(pn, current, parent);
	case invert:
        size = 0;
		parent = this;
		return children[0]->get_point(pn, current, parent);
	case iflteMAG:
	case iflteCLOCKWISE:
        size = 0;
		for (int i = 0; i < 4; i++) {
			parent = this;
			answer = children[i]->get_point(pn, current, parent);
			if (current >= pn)
				return answer;
		}
		return answer;
	case ifVectorZero:
        size = 0;
		for (int i = 0; i < 3; i++) {
			parent = this;
			answer = children[i]->get_point(pn, current, parent);
			if (current >= pn)
				return answer;
		}
		return answer;
	default:
		// handle hyena input case
		if(operation < NUM_OPS){
			return this;
		}
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
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
		output += ops_names[operation];
		output += "\", shape=plaintext]\n";
		break;
	case constant:
        output += QString("constant (mag=%1 dir=%2)\", shape=plaintext]\n")
                .arg(the_const->magnitude).arg(the_const->direction);
		break;
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		output += ops_names[operation];
		output += "\", shape=plaintext]\n";
		break;
	// non-terminals
	case sum:
	case subtract:
	case compare:
		output += ops_names[operation];
		output += "\", shape=plaintext]\n";
		for (int i = 0; i < 2; i++) {
			output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	case invert:
		output += ops_names[operation];
		output += "\", shape=plaintext]\n";
		for (int i = 0; i < 1; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	case iflteMAG:
	case iflteCLOCKWISE:
		output += ops_names[operation];
		output += "\", shape=plaintext]\n";
		for (int i = 0; i < 4; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	case ifVectorZero:
		output += ops_names[operation];
		output += "\", shape=plaintext]\n";
		for (int i = 0; i < 3; i++) {
            output += children[i]->graphviz(this, QString::number(i));
		}
		break;
	default:
		// handle hyena input case
		if(operation < NUM_OPS){
			output += QString("hyena_%1").arg(operation - NUM_OPS);
			output += "\", shape=plaintext]\n";
			break;
		}
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

QStringList node::serialize(){
	QStringList output;
	if(this == NULL)
		return output;

	switch (operation) {
	// terminals
	case zebra:
	case nearest_hyena:
	case nearest_lion:
	case nearest_calling:
	case north:
	case randm:
	case last_move:
		output += QString("%1 ").arg(operation);
		break;
	case constant:
		output += QString("%1 %2 %3 ").arg(constant).arg(the_const->magnitude).
				arg(the_const->direction);
		break;
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		output += QString("%1 ").arg(operation);
		break;
	// non-terminals
	case sum:
	case subtract:
	case compare:
		output += QString("%1 ").arg(operation);
		for (int i = 0; i < 2; i++) {
			output += children[i]->serialize();
		}
		break;
	case invert:
		output += QString("%1 ").arg(invert);
		for (int i = 0; i < 1; i++) {
			output += children[i]->serialize();
		}
		break;
	case iflteMAG:
	case iflteCLOCKWISE:
		output += QString("%1 ").arg(operation);
		for (int i = 0; i < 4; i++) {
			output += children[i]->serialize();
		}
		break;
	case ifVectorZero:
		output += QString("%1 ").arg(ifVectorZero);
		for (int i = 0; i < 3; i++) {
			output += children[i]->serialize();
		}
		break;
	default:
		// handle hyena input case
		if(operation < NUM_OPS){
			output += QString("%1 ").arg(operation);
			break;
		}
		ofstream error;
		error.open("error.txt");
		error << "error in serialize" << endl;
		error.close();
	}
	return output;
}

node* node::deserialize(QStringList &input){
	if(input.isEmpty())
		return NULL;

	ops op = (ops) input.takeFirst().toInt();
	operation = op;

	switch (op) {
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
		the_const->magnitude = input.takeFirst().toDouble();
		the_const->direction = input.takeFirst().toDouble();
		break;
	case number_calling:
	case mirror_nearest:
	case last_pen:
	case named:
	case landmark:
		break;
	// non-terminals
	case sum:
	case subtract:
	case compare:
		for (int i = 0; i < 2; i++) {
			node* child = new node();
			children[i] = child->deserialize(input);
		}
		break;
	case invert:
		for (int i = 0; i < 1; i++) {
			node* child = new node();
			children[i] = child->deserialize(input);
		}
		break;
	case iflteMAG:
	case iflteCLOCKWISE:
		for (int i = 0; i < 4; i++) {
			node* child = new node();
			children[i] = child->deserialize(input);
		}
		break;
	case ifVectorZero:
		for (int i = 0; i < 3; i++) {
			node* child = new node();
			children[i] = child->deserialize(input);
		}
		break;
	default:
		// handle hyena input case
		if(operation < NUM_OPS){
			break; // don't need to do anything else
		}
		ofstream error;
		error.open("error.txt");
		error << "error in deserialize" << endl;
		error.close();
	}
	return this;
}

#undef children
#undef the_const
