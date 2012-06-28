#ifndef WEIGHTSET_H
#define WEIGHTSET_H

class weightset{
public:
    double *weights;
    int cols;
    int rows;

    weightset(const weightset &other){
        this->rows = other.rows;
        this->cols = other.cols;
        weights = new double[rows * cols];
        for(int i = 0; i < rows * cols; i++){
            weights[i] = other.weights[i];
        }
    }

    weightset &operator=(const weightset &other){
        if(this == &other) return *this; // check for self-assignment
        this->rows = other.rows;
        this->cols = other.cols;
        delete[] weights;
        weights = new double[rows * cols];
        for(int i = 0; i < rows * cols; i++){
            weights[i] = other.weights[i];
        }
        return *this;
    }

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
            weights[i] = Random::Global.FixedW();
        }
    }
};

#endif // WEIGHTSET_H
