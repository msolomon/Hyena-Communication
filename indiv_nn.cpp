#include "indiv_nn.h"

indiv_nn::indiv_nn(){
    network = NULL;
}

indiv_nn::~indiv_nn(){
}

QStringList indiv_nn::serialize(){
    // TODO: fill in stub
    return QStringList();
}

void indiv_nn::deserialize(QStringList input){
    // TODO: fill in stub
}

vect indiv_nn::eval_me(){
    return evaluate(the_info);
}

QString indiv_nn::graphviz(){
    return QString();
}

void indiv_nn::clear(){
    // TODO: fill in stub
}

void indiv_nn::generate(){
    // create a list of matrices representing weights
    network = QList<weightset>();
    const int num_layers = (sizeof(NETWORK) / sizeof(int));
    network.reserve(num_layers);
    for(int i = 0; i < num_layers - 1; i++){
        // allocate and initialize weights
        weightset *ws = new weightset(NETWORK[i], NETWORK[i+1]);
        ws->randomize_weights();
        network.append(*ws);
    }
}

void indiv_nn::evaluate_ann(double input_vector[],
                        double *output_vector){

    // TODO: bugcheck all of this!

    // initialize temporory vectors
    int in_rows;
    int in_cols;
    double *temp_in = NULL;
    int out_rows = NETWORK_NUM_INPUT;
    int out_cols = 1;  // could be changed to evaluate multiple cases at once
    double *temp_out = new double[out_rows + 1]; // +1 = bias
    for(int i = 0; i < out_rows; i++){
        temp_out[i] = input_vector[i];
    }
    temp_out[out_rows] = 1; // set bias node

    // feed-forward through the network
    foreach(weightset w, network){
        delete[] temp_in;
        temp_in = temp_out;
        in_rows = out_rows;
        in_cols = out_cols;
        out_rows = w.cols; // since weight matrix will be transposed
        temp_out = new double[out_rows * out_cols];
        temp_out[out_rows * out_cols - 1] = 1; // set bias for next iteration
        // preform the matrix multiplication
        dgemm('t', // transpose weight matrix
              'n', // don't transpose net (input) matrix
              w.cols - 1, // w.cols - 1 == out_rows == # nodes in next layer
              in_cols, // in_cols == out_cols == 1 == # test cases evaluated
              w.rows, // w.rows == in_rows + 1 == # nodes in this layer + 1 bias
              1, // multiply the resulting matrix by the scalar 1
              w.weights, // c = a * b, so a = w.weights
              w.rows, // first dimension of transpose(a), so = w.rows
              temp_in, // c = a * b, so b = temp_in
              w.rows, // first dimension of b, so = w.rows == in_rows + 1
              0, // multiply c by 0 and add it (so essentially skip this)
              temp_out, // output matrix. note that it doesn't fill the last
                        // slot, which holds the bias value 1
              out_rows); // out_rows == w.cols - 1 == # nonbias nodes next layer
    }
    // temp_out now holds the output matrix, and an extraneous bias node
    delete[] temp_in;
    output_vector = temp_out;
}

vect indiv_nn::evaluate(agent_info &the_info){
    double input[NETWORK_NUM_INPUT];
    int i = 0;
    for(; i < NUM_HYENAS * 2; i += 2){
        input[i] = the_info.hyenas[i / 2].direction;
        input[i + 1] = the_info.hyenas[i / 2].magnitude;
    }

    input[i++] = the_info.zebra.direction;
    input[i++] = the_info.zebra.magnitude;
    input[i++] = the_info.nearest_hyena.direction;
    input[i++] = the_info.nearest_hyena.magnitude;
    input[i++] = the_info.nearest_lion.direction;
    input[i++] = the_info.nearest_lion.magnitude;
    input[i++] = the_info.last_move.direction;
    input[i++] = the_info.last_move.magnitude;
    input[i++] = the_info.mirrored.direction;
    input[i++] = the_info.mirrored.magnitude;
    input[i++] = the_info.nearest_calling.direction;
    input[i++] = the_info.nearest_calling.magnitude;
    input[i++] = the_info.named.direction;
    input[i++] = the_info.named.magnitude;
    input[i++] = the_info.landmark.direction;
    input[i++] = the_info.landmark.magnitude;

    assert(i == NETWORK_NUM_INPUT && "# ANN inputs not as expected!");

}
