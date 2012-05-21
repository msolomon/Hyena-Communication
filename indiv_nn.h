#ifndef INDIV_NN_H
#define INDIV_NN_H

// include AMD Core Math Library (developer.amd.com/libraries/acml)
#include <acml/acml.h>

#include <QList>

#include "globals.h"

#include "indiv_base.h"
#include "weightset.h"

class indiv_nn: public indiv_base {
public:
    indiv_nn();
    ~indiv_nn();

    void evaluate_ann(double input_vector[NETWORK_NUM_INPUT],
                      double *output_vector);
    vect evaluate(agent_info &the_info);

    QStringList serialize();
    void deserialize(QStringList input);
    vect eval_me();
    QString graphviz();
    void clear();
    void generate();

private:
    QList<weightset> network;
};

#endif // INDIV_NN_H
