#include "indiv_nn.h"

indiv_nn::indiv_nn(){
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

indiv_nn::~indiv_nn(){
}

QStringList indiv_nn::serialize(){
    // TODO: fill in stub
    return QStringList();
}

void indiv_nn::deserialize(QStringList input){
    // TODO: fill in stub
}
