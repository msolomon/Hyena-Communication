#ifndef INDIV_NN_H
#define INDIV_NN_H

// include AMD Core Math Library (developer.amd.com/libraries/acml)
#include <acml/acml.h>

#include <QList>

#include "globals.h"

#include "indiv_base.h"
#include "weightset.h"

class indiv_nn: indiv_base {
public:
    indiv_nn();
    ~indiv_nn();

    void evaluate(double input_vector[NETWORK_NUM_INPUT],
                  double output_vector[NETWORK_NUM_OUTPUT]);

    QStringList serialize();
    void deserialize(QStringList input);

private:
    QList<weightset> network;
};

#endif // INDIV_NN_H
