#include <iostream>
#include <type_traits>
#include "math.h"
using namespace std;

void numc::make_array(const int& size,const int& parameter_n) {
    srand((unsigned int)time(NULL));
    this->Y.resize(size);
    for (int i = 0; i < size; i++) {
        this->Y[i] = double(rand()%10+1)/10;
    }
    for (int i = 0; i < size; i++) {
        this->x.push_back(vector<double> (parameter_n));
        for (int j = 0; j < parameter_n; j++) {
            this->x[i][j] = double(rand()%10+1)/10;
        }
    }
}

/*
vector<double> numc::mean(const vector<vector<double>>& vec) {
    vector<double> data_sum;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[0].size(); j++) {
            data_sum[i] += vec[i][j];
        }
    }
    
    for (int i = 0; i < data_sum.size(); i++) {
        data_sum[i] /= vec.size();
    }
    
    return data_sum;
}
*/
void numc::print() {
    /*
     print all the 2D-vector elements
     */
    cout << "Y | ";
    for (int i = 1; i <= this->x[0].size(); i++) {
        cout << "x" << i << ", ";
    }
    cout << '\n' << "---------------------------------" << '\n';
    
    for (int i = 0; i < Y.size(); i++) {
        cout << Y[i] << " | ";
        for (int j = 0; j < x[i].size(); j++) {
            cout << x[i][j] << " ";
        }
        cout << '\n';
    }
}

void numc::gradient_descent(vector<double>& weight, double b, int epoch) {
    const double learning_rate = 0.15;
    vector<double> y_hat (this->Y.size());
    
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[i].size(); j++) {
            for (int k = 0; k < x[i].size(); k++) {
                y_hat[j] += weight[k] * x[i][k];
            }
            y_hat[j] += b;
        }
    }
    
    double error = 0;
    for (int i = 1; i < y_hat.size(); i++) {
        error += pow(y_hat[i]-Y[i],2);
    }
    error /= Y.size();
    
    if (epoch % 5==0) {
        cout << "epoch : " << epoch << ", ";
        for (int i = 0; i < weight.size(); i++) {
            cout << "w" << i+1 << " = " << weight[i] << ", ";
        }
        cout << "b = " << b << " error = " << error << '\n';
    }
    
    if (error < 0.00001 || epoch > 10000) {
        return;
    }
    else {
        for (int i = 0; i < weight.size(); i++) {
            double weight_sum = 0;
            for (int j = 0; j < x[i].size(); j++) {
                weight_sum += x[j][i] * (y_hat[j]-Y[j]);
            }
            weight[i] = weight[i] - learning_rate * weight_sum/y_hat.size();
        }
        
        double b_sum = 0;
        for (int i = 0; i < y_hat.size(); i++) {
            b_sum += y_hat[i]-Y[i];
        }
        b -= learning_rate * b_sum/y_hat.size();
        gradient_descent(weight,b,epoch+1);
    }
}
