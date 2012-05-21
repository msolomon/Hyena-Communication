#ifndef WEIGHTSET_H
#define WEIGHTSET_H

class weightset{
public:
    double *weights;
    int cols;
    int rows;

    weightset(int rows, int cols){
        // the weights matrix is stored in row-major form
        weights = new double[(rows + 1) * cols]; // +1 for bias accommodation
        this->cols = cols;
        this->rows = rows + 1;
    }

    ~weightset(){
        delete[] weights;
    }

    void randomize_weights(){
        for(int i = 0; i < rows * cols; i++){
            // use initialization adapted from Kim and Ra 1991
            weights[i] = Random::Global.FixedW() * sqrt(0.5 / rows);
        }
    }
};

#endif // WEIGHTSET_H
