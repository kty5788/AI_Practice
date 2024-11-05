#include <iostream>
#include <vector>
#include "math.h"
using namespace std;

int main() {
    int x_num;
    cout << "Enter the number of x(independent value) : ";
    cin >> x_num;
    
    if (cin.fail() || x_num <= 0) {
        cout << "Type Error!!, You have to enter (int > 0)" << endl;
    }
    else {
        numc data;
        data.make_array(50, x_num);
        data.print();
        vector<double> weight (x_num);
        for (int i = 0; i < weight.size(); i++) {
            weight[i] = 0.2;
        }
        data.gradient_descent(weight,0.2,0);
    }
    
    
    
    return 0;
}

