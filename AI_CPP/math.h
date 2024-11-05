#ifndef math_h
#define math_h

#include <iostream>
#include <vector>
using namespace std;

class numc {
    
private:
    
public:
    vector<double> Y;
    vector<vector<double>> x;
    
    void make_array(const int& size, const int& parameter_n);
    void print();
    
    void gradient_descent(vector<double>& weight, double b, int epoch);
    // vector<double> mean(const vector<vector <double>>& vec);
    
};

#endif /* math_h */
