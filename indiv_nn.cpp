#include "indiv_nn.h"

int indiv_nn::num_inputs = -1;

indiv_nn::indiv_nn(){
    last_output = NULL;
    calling = false;

    if(num_inputs == -1){ // only calculate once
        if(USE_ANN && LEARN_CALLING){
            assert(NETWORK_NUM_OUTPUT >= 3 &&
                   "Not enough output nodes to learn calling!");
        }
        int num_ops = NETWORK_NUM_INPUT_RAW;
        if(is_disabled(zebra))           num_ops -= 2;
        if(is_disabled(nearest_hyena))   num_ops -= 2;
        if(is_disabled(nearest_lion))    num_ops -= 2;
        if(is_disabled(nearest_calling)) num_ops -= 2;
        if(is_disabled(north))           num_ops -= 2;
        if(is_disabled(randm))           num_ops -= 2;
        if(is_disabled(last_move))       num_ops -= 2;
        if(is_disabled(number_calling))  num_ops -= 1;
        if(is_disabled(mirror_nearest))  num_ops -= 2;
        if(is_disabled(last_pen))        num_ops -= 1;
        if(is_disabled(named))           num_ops -= 2;
        if(is_disabled(landmark))        num_ops -= 2;
        if(!CALLING_ENABLED)             num_ops -= 1;
        num_inputs = num_ops;
    }
}

indiv_nn::~indiv_nn(){
    clear();
}

indiv_nn::indiv_nn(const indiv_nn &indiv){
    network = indiv.network; // uses copy-on-write
    if(indiv.last_output != NULL){
        last_output = new double[NETWORK_NUM_OUTPUT];
        for(int i = 0; i < NETWORK_NUM_OUTPUT; i++){
            last_output[i] = indiv.last_output[i];
        }
    } else last_output = NULL;
}

indiv_nn& indiv_nn::operator=(const indiv_nn &indiv){
    if(this == &indiv) return *this; // check for self-assignment
    delete[] last_output;
    network = indiv.network; // uses copy-on-write
    if(indiv.last_output != NULL){
        last_output = new double[NETWORK_NUM_OUTPUT];
        for(int i = 0; i < NETWORK_NUM_OUTPUT; i++){
            last_output[i] = indiv.last_output[i];
        }
    } else last_output = NULL;
    return *this;
}

QStringList indiv_nn::serialize(){
    QStringList out;
    double *weights;
    for(int i = 0; i < NETWORK_LAYERS - 1; i++){
        weights = network[i].weights;
        out += (QString("%1 %2\n")
                .arg(network[i].cols)
                .arg(network[i].rows));
        for(int j = 0; j < network[i].cols * network[i].rows; j++){
            out += QString("%1 ").arg(weights[j]);
        }
        out += ("\n");
    }
    return out;
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
    network.clear();
    delete[] last_output;
    last_output = NULL;
}

void indiv_nn::generate(){
    // create a list of matrices representing weights
    network = QList<weightset>();
    const int num_layers = (sizeof(NETWORK) / sizeof(int));
    for(int i = 0; i < num_layers - 1; i++){
        // allocate and initialize weights
        weightset *ws;
        if(i == 0){
            ws = new weightset(num_inputs, NETWORK[i+1]);
        } else {
            ws = new weightset(NETWORK[i], NETWORK[i+1]);
        }
        ws->randomize_weights();
        network.append(*ws);
    }
}

void indiv_nn::xOver(indiv_base *p2){
    if(this == p2) return; // no crossover with self
    // do 2-point crossover on each weight matrix
    for(int i = 0; i < NETWORK_LAYERS - 1; i++){
        int size = network[i].cols * network[i].rows;
        int larger = Random::Global.Integer(size);
        int smaller = Random::Global.Integer(size);
        if(larger < smaller){
            int tmp_swap;
            tmp_swap = smaller;
            smaller = larger;
            larger = tmp_swap;
        }
        int diff = larger - smaller;

        if((smaller == larger) || (diff == size))
            return; // nothing to cross over
        // actually perform the crossover
        double *tmp = new double[diff];
        // copy this individual's weights to be switched to temporary buffer
        memcpy(tmp,
               &(network[i].weights[smaller]),
               diff * sizeof(double));
        // copy applicable p2 weights over this one's
        memcpy(&(network[i].weights[smaller]),
               &(((indiv_nn *) p2)->network[i].weights[smaller]),
               diff * sizeof(double));
        // copy temporary buffer over p2's applicable weights
        memcpy(&(((indiv_nn *) p2)->network[i].weights[smaller]),
               tmp,
               diff * sizeof(double));
        delete[] tmp;
    }
}


static int nn_size = 0;
int indiv_nn::get_size(){
    // size is total number of nodes in all weight matrices
    if(nn_size > 0) return nn_size;
    for(int i = 0; i < NETWORK_LAYERS - 1; i++){
        nn_size += NETWORK[i] * NETWORK[i+1];
    }
    return nn_size;
}

void indiv_nn::mutate(){
    int num_mutes;
    QQueue<int> locations;

    // get the number of weights to be mutated
    if(NUM_OVER_SIZE_MUTATION == 0){ // use flat % chance per weight
        num_mutes = poisson_sample(MUTATION_CHANCE/100.0 * get_size());
    } else { // use X/size mutations
        num_mutes = poisson_sample(NUM_OVER_SIZE_MUTATION);
    }

    // get the locations to be mutated
    for(int i = 0; i < num_mutes; i++){
        // note that the same location can be multiply-mutated -- but unlikely
        locations.enqueue(Random::Global.Integer(num_mutes));
    }

    // mutate each location in the approprate set of weights
    for(int i = 0; i < NETWORK_LAYERS - 1; i++){
        weightset *layer = &network[i];
        int matrix_size = layer->cols * layer->rows;
        int locations_to_try = locations.length();
        for(int j = 0; j < locations_to_try; j++){
            int loc = locations.dequeue();
            assert(loc >= 0 && "Mutation location was negative!");
            if(loc >= matrix_size){ // will be in next set of weights
                loc -= matrix_size;
                locations.enqueue(loc);
            } else { // mutation is in this set of weights
                // mutate. notice the weights are NOT clamped to [-1, 1]
                layer->weights[loc] += normal_sample(0, MUTATION_SIGMA);
            }

        }
    }
}

void indiv_nn::evaluate_ann(double input_vector[]){
    delete[] last_output;
    int in_rows;
    int in_cols;
    double *temp_in = NULL;
    int out_rows = num_inputs;
    const int out_cols = 1;  // could be changed to evaluate multiple cases at once
    double *temp_out = new double[out_rows * out_cols + 1]; // +1 = bias
    for(int i = 0; i < out_rows * out_cols; i++){
        temp_out[i] = activation(input_vector[i]); // apply activation function
    }
    temp_out[out_rows * out_cols] = 1; // set bias node

    // feed-forward through the network
    for(int i = 0; i < network.length(); i++){
        weightset *w = &network[i];
        temp_in = temp_out;
        in_rows = out_rows;
        in_cols = out_cols;
        out_rows = w->cols; // since weight matrix will be transposed
        temp_out = new double[out_rows * out_cols + 1];
        temp_out[out_rows * out_cols] = 1; // set bias for next iteration
        // perform the matrix multiplication
        dgemm('t', // transpose weight matrix
              'n', // don't transpose net (input) matrix
              w->cols, // w->cols == out_rows == # nodes in next layer
              in_cols, // in_cols == out_cols == 1 == # test cases evaluated
              w->rows, // w->rows == in_rows + 1 == # nodes in this layer + 1 bias
              1, // multiply the resulting matrix by the scalar 1
              w->weights, // c = a * b, so a = w->weights
              w->rows, // first dimension of transpose(a), so = w->rows
              temp_in, // c = a * b, so b = temp_in
              in_rows + 1, // first dimension of b, so = in_rows + 1 == w->rows
              0, // multiply c by 0 and add it (so essentially skip this)
              temp_out, // output matrix. note that it doesn't fill the last
                        // slot, which holds the bias value 1
              out_rows); // out_rows == w->cols == # nodes next layer
        // apply the activation function to each element in the output, bar bias
        for(int j = 0; j < out_rows * out_cols; j++){ // skip bias node
            temp_out[j] = activation(temp_out[j]);
        }
        assert(temp_out[out_rows*out_cols] == 1 && "Bias node corrupted!");
        delete[] temp_in;
    }
    // temp_out now holds the output matrix, and an extraneous bias node
    last_output = temp_out;
}

vect indiv_nn::evaluate(agent_info &the_info){
    double input[num_inputs];
    int i = 0;
    for(; i < NUM_HYENA_INPUTS * 2; i += 2){
        input[i] = the_info.hyenas[i / 2].direction;
        input[i + 1] = scale_magnitude(the_info.hyenas[i / 2].magnitude);
    }

    if(!is_disabled(zebra)){
        input[i++] = scale_direction(the_info.zebra.direction);
        input[i++] = scale_magnitude(the_info.zebra.magnitude);
    }
    if(!is_disabled(nearest_hyena)){
        input[i++] = scale_direction(the_info.nearest_hyena.direction);
        input[i++] = scale_magnitude(the_info.nearest_hyena.magnitude);
    }
    if(!is_disabled(nearest_lion)){
        input[i++] = scale_direction(the_info.nearest_lion.direction);
        input[i++] = scale_magnitude(the_info.nearest_lion.magnitude);
    }
    if(!is_disabled(nearest_calling)){
        input[i++] = scale_direction(the_info.nearest_calling.direction);
        input[i++] = scale_magnitude(the_info.nearest_calling.magnitude);
    }
    if(!is_disabled(north)){
        input[i++] = the_info.north_enabled ? 1 : 0; // direction
        input[i++] = the_info.north_enabled ? 1 : 0; // magnitude
    }
    if(!is_disabled(randm)){
        input[i++] = the_info.randm_enabled ? Random::Global.FixedW() : 0;
        input[i++] = the_info.randm_enabled ? Random::Global.FixedW() : 0;
    }
    if(!is_disabled(last_move)){
        input[i++] = scale_direction(the_info.last_move.direction);
        input[i++] = scale_magnitude(the_info.last_move.magnitude);
    }
    if(!is_disabled(mirror_nearest)){
        input[i++] = scale_direction(the_info.mirrored.direction);
        input[i++] = scale_magnitude(the_info.mirrored.magnitude);
    }
    if(!is_disabled(named)){
        input[i++] = scale_direction(the_info.named.direction);
        input[i++] = scale_magnitude(the_info.named.magnitude);
    }
    if(!is_disabled(landmark)){
        input[i++] = scale_direction(the_info.landmark.direction);
        input[i++] = scale_magnitude(the_info.landmark.magnitude);
    }
    // input[i++] = activation(the_info.num_lions / 2.0);
    if(!is_disabled(number_calling)){
        input[i++] = activation(the_info.num_hyenas / 15.0);
    }
    if(!is_disabled(last_pen)){
        input[i++] = activation(the_info.last_pen);
    }
    if(CALLING_ENABLED){
        input[i++] = calling ? 1 : -1;
    }
    assert(i == num_inputs && "# ANN inputs not as expected!");

    evaluate_ann(input); // feed forward through network

    assert(NETWORK_NUM_OUTPUT >= 2 && "Require 2+ output nodes in ANN.");
    // rescale outputs
    last_output[0] = inverse_scale_direction(last_output[0]);
    assert(last_output[0] <= PI &&
           last_output[0] >= -PI &&
           "Got direction outside of valid range!");
    last_output[1] = inverse_scale_magnitude(last_output[1]);
    if(LEARN_CALLING){
        set_calling(inverse_scale_calling(last_output[2]));
    }
    vect v;
    v.direction = last_output[0];
    v.magnitude = last_output[1];
    return v;
}

