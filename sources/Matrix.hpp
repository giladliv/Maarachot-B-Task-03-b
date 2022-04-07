#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

namespace zich
{
    class Matrix
    {
        public:
            // c'tor
            Matrix(vector<double>& mat, int row, int col);
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


            
            

        private:
            /* data */
            vector<vector<double>> _mat; 
            int _row;
            int _col;

            void arrToMat(vector<double>& matArr, int row, int col);

            friend void throwIfNotSameSize(const Matrix& a, const Matrix& b);
            friend void throwIfMulWrong(const Matrix& a, const Matrix& b);
            
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