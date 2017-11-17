//
// Created by kapildd on 9/29/17.
//

#include <bits/stdc++.h>
using namespace std;

class Matrix{
public:
    vector< vector<int> > data;
    int rows, cols;
    Matrix() {rows = 0; cols = 0;}
    Matrix(int n) {//Identity matrix
        rows = n;
        cols = n;
        data = vector< vector<int> >(n, vector<int>(n, 0));
        for(int i=0; i<n; i++) {
            data[i][i] = 1;
        }
    }
    Matrix(int n, int m) {
        rows = n;
        cols = m;
        data = vector< vector<int> >(n, vector<int>(m, 0));
    }
    Matrix(int n, int m, vector< vector<int> > values) {
        rows = n;
        cols = m;
        data = values;
    }
    Matrix operator*(Matrix& b) {
        Matrix res;
        if(cols == b.rows) {
            res = Matrix(rows, b.cols);
            for(int i=0; i<rows; i++) {
                for(int j=0; j<b.cols; j++) {
                    for(int k=0; k<cols; k++) {
                        res.data[i][j] += data[i][k] * b.data[k][j];
                    }
                }
            }
        }
        return res;
    }
    Matrix operator*(int b) {
        Matrix res = Matrix(rows, cols, data);
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                res.data[i][j] *= b;
            }
        }
        return res;
    }
    Matrix operator^(long long p) {
        Matrix res, base = *this;
        if(rows == cols) {
            res = Matrix(rows);
            while (p) {
                if (p & 1) {
                    res = res * base;
                }
                base = base * base;
                p /= 2;
            }
        }
        return res;
    }
    Matrix operator+(Matrix& b) {
        Matrix res;
        if(rows == b.rows && cols == b.cols) {
            res = Matrix(rows, cols);
            for(int i=0; i<rows; i++) {
                for(int j=0; j<cols; j++) {
                    res.data[i][j] = data[i][j] + b.data[i][j];
                }
            }
        }
        return res;
    }
    void print() {
        cout << "Rows " << rows << ", Columns " << cols << endl;
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Matrix a(2, 3), b(3, 2);
    for(int i=0; i<2; i++) {
        for(int j=0; j<3; j++) {
            a.data[i][j] = i+j;
            b.data[j][i] = i+j;
        }
    }
    cout << "Matrix a" << endl;
    a.print();
    cout << "Matrix b" << endl;
    b.print();
    Matrix c = a*b;
    cout << "Matrix c" << endl;
    c.print();
    cout << "Matrix c^2" << endl;
    c = c^2;
    c.print();
    return 0;
}