#ifndef WEIGHTSET_H
#define WEIGHTSET_H

class weightset{
public:
    double *weights;
    int cols;
    int rows;

    weightset(int rows, int cols){
        weights = new double[rows * cols];
        this->cols = cols;
        this->rows = rows;
    }

    ~weightset(){
        delete[] weights;
    }

    void randomize_weights(){
        for(int i = 0; i < (rows * cols); i++){
            weights[i] = Random::Global.FixedW(); // [-1, 1]
        }
    }
};

#endif // WEIGHTSET_H
