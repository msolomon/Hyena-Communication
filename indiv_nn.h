#ifndef INDIV_NN_H
#define INDIV_NN_H

#include <cstring> // for memcpy
#include <QList>
#include <QQueue>

#include "globals.h"

#include "indiv_base.h"
#include "weightset.h"

class indiv_nn: public indiv_base {
public:
    indiv_nn();
    ~indiv_nn();
    indiv_nn(const indiv_nn &indiv);
    indiv_nn &operator=(const indiv_nn &other);
    void evaluate_ann(double input_vector[NETWORK_NUM_INPUT]);
    vect evaluate(agent_info &the_info);

    QStringList serialize();
    void deserialize(QStringList input);
    vect eval_me();
    QString graphviz();
    void clear();
    void generate();
    void xOver(indiv_base *p2);
    int get_size();
    void mutate();

private:
    QList<weightset> network;
    double *last_output;
    inline double activation(double input){
        return tanh(input / 2.0);
    }
    inline double scale_magnitude(double input){
        return (input / (double) X);
    }
    inline double scale_direction(double input){
        return input / PI;
    }

    inline double inverse_scale_magnitude(double input){
        return fabs(input) * X; // on [0, X]
    }
    inline double inverse_scale_direction(double input){
        return input * PI;
    }
    inline bool inverse_scale_calling(double input){
        return input > 0; // > 0 calling; <= 0 not calling
    }
};

#endif // INDIV_NN_H
