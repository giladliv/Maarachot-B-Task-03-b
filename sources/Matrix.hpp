#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <regex>

using namespace std;

//#define EPS 1e-50
#define EPS 0

namespace zich
{
    class Matrix
    {
        public:
            // c'tor
            Matrix(vector<double>& mat, int row, int col);
            Matrix(const string& str);
            Matrix(const Matrix& other);
            
            // d'tor
            ~Matrix();

            // operator =
            Matrix& operator=(const Matrix& other);

            // math operators
            // + operators
            Matrix operator+() const;
            Matrix operator+(const Matrix& other) const;
            // - operator
            Matrix operator-() const;
            Matrix operator-(const Matrix& other) const;
            // * operator
            Matrix operator*(const Matrix& other) const;
            Matrix operator*(double skalar) const;
            friend Matrix operator*(double skalar, const Matrix& m);


            // assignment operators
            Matrix& operator+=(const Matrix& other);
            Matrix& operator-=(const Matrix& other);
            Matrix& operator*=(const Matrix& other);
            Matrix& operator*=(double skalar);
            
            // prefix
            Matrix& operator++();
            Matrix& operator--();

            // postfix
            Matrix operator++(int dummy_flag_for_postfix_increment);
            Matrix operator--(int dummy_flag_for_postfix_increment);            

            // compare operators
            friend bool operator==(const Matrix& m1, const Matrix& m2);
            friend bool operator!=(const Matrix& m1, const Matrix& m2);
            friend bool operator<(const Matrix& m1, const Matrix& m2);
            friend bool operator>(const Matrix& m1, const Matrix& m2);
            friend bool operator<=(const Matrix& m1, const Matrix& m2);
            friend bool operator>=(const Matrix& m1, const Matrix& m2);
            
            // io operators
            friend std::ostream& operator<< (ostream& output, const Matrix& m);
            friend std::istream& operator>> (istream& input , Matrix& m);
            string toString() const;
            vector<string> split(const string& str, char parser);
            static int getNumberOfColumnFromStr(const string& str);

        private:
            /* data */
            vector<vector<double>> _mat; 
            int _row;
            int _col;

            void arrToMat(vector<double>& matArr, int row, int col);
            friend void throwIfNotSameSize(const Matrix& a, const Matrix& b);
            friend void throwIfMulWrong(const Matrix& a, const Matrix& b);
            static int compareSumMatrix(const Matrix& a, const Matrix& b);
            long double sumMatrix() const;
            static bool isGoodMatrixInput(const string& str);
            
    };
    
    
    
}

class MessageException : public exception
{
    // this class is for throwing exceptions by given string
    // the what method will return the given string
    // altough the best solution is to create for each case its own exception'
    // in this task it would be easier and more efficient
    // to just make an exception that returns its given string

    public:
        MessageException(string str) : _msg(str) {}     // using init line (for c'tor)
        const char* what() const noexcept {return _msg.c_str();}    // return the saved string as const char *
    private:
        string _msg;

};