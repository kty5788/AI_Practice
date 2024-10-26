#include <iostream>
#include <vector>
using namespace std;
using Matrix = vector<vector <double>>;

void fill_data(Matrix& data) {
    
    /*
     fill the data(vector)
     number is random real number (0.1 ~ 1)
     */
    
    srand((unsigned int)time(NULL));
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < 2; j++) {
            data[i][j] = double(rand()%10+1)/10;
        }
    }
}

void print(const Matrix& data) {
    
    /*
     print the all elements of vector
     */
    
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < 2; j++) {
            cout << data[i][j] << '\t';
        }
        cout << '\n';
    }
}

int gradient_descent(const Matrix& data, double w, double b, int epoch=1) {
    /*
     Do gradient descent
     
     this function is **only** work in monomial (y = w*x + b)
     */
    
    const double learning_rate = 0.5;
    double sum = 0;
    for (int i = 0; i < data.size(); i++) {
        int x = data[i][0];
        int y = data[i][1];
        double y_hat = w*x + b;
        sum += pow((y_hat-y),2);
    }
    double error = sum/data.size();
    
    if (error < 0.0005 || epoch > 100) {
        cout << "------------------------------------------------------" << endl;
        cout <<"Final | epoch : " << epoch << " | error : " << error << " w = " << w << " b = " << b << endl;
        return 0;
    }
    else {
        double w_sum = 0;
        double b_sum = 0;
        for (int i = 0; i < data.size(); i++) {
            int x = data[i][0];
            int y = data[i][1];
            
            w_sum += (w*x+b-y)*x;
            b_sum += (w*x+b-y);
        }
        w -= learning_rate * (w_sum)/data.size();
        b -= learning_rate * (b_sum)/data.size();
        
        cout <<"epoch : " << epoch << " | error : " << error << " w = " << w << " b = " << b << endl;
    }
    return gradient_descent(data,w,b,epoch+1);
}

int main() {
    int data_number;
    cout << "Enter the number of data : ";
    cin >> data_number;
    
    if (cin.fail() || data_number <= 0) {
        cout << "Type Error!!, You have to enter (int > 0)" << endl;
    }
    else {
        Matrix data(data_number, vector <double>(2));
        fill_data(data);
        print(data);
        cout << '\n';
        gradient_descent(data,0.5,0.3);
    }
    
    
    
    return 0;
}

