#include "Matrix.hpp"
using zich::Matrix;

/**
 * @brief Construct a new Matrix:: Matrix object
 * 
 * @param mat 
 * @param row 
 * @param col 
 */
Matrix::Matrix(vector<double>& mat, int row, int col)
{
    if (row <= 0 || col <= 0)   // the row and col must be positive
    {
        throw MessageException("rows and columns must be positive numbers");
    }
    if ((row * col) != mat.size())  // the size that given must be the same as size of thevector
    {
        throw MessageException("the matrix must be at the same size of: row * col");
    }
    _row = row;
    _col = col;
    arrToMat(mat, row, col);        // copy the vector to the matrix
    
}

void Matrix::arrToMat(vector<double>& matArr, int row, int col)
{
    _mat = vector<vector<double>>();
    unsigned int ind = 0;
    int len = matArr.size();
    for (unsigned int i = 0; i < row && ind < len; i++)
    {
        auto startSub = matArr.begin() + ind;           // set the start index (iterator) of sub vector
        auto endSub = matArr.begin() + ind + col;       // set the end index (iterator) of sub vector

        _mat.push_back(vector<double>(startSub, endSub));   // get the sub vector by start iterator and end
        ind += (unsigned int)col;   // add the number that jumped over
        
    }
}

/**
 * @brief Construct a new Matrix:: Matrix object - deep copy
 * 
 * @param other 
 */
Matrix::Matrix(const Matrix& other)
{
    (*this) = other;
}

Matrix::~Matrix()
{
    for(unsigned int i = 0; i < _mat.size(); i++)
    {
        _mat[i].clear();
    }
}

/**
 * @brief *deep* copy of other matrix
 * 
 * @param other 
 * @return Matrix& 
 */
Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)
    {
        return (*this);
    }
    
    for(unsigned int i = 0; i < _mat.size(); i++)
    {
        _mat[i].clear();
    }
    
    _mat = vector<vector<double>>();
    
    for (unsigned int i = 0; i < other._mat.size(); i++)
    {
        this->_mat.push_back(vector<double>(other._mat[i]));
    }
    
    this->_row = other._row;
    this->_col = other._col;

    return (*this);
}



/**
 * @brief the function throws exception if the 2 matrixes doesn't have the same row and colomns
 * it must be same size - (nxm) for both of the sides
 * 
 * @param a 
 * @param b 
 */
void zich::throwIfNotSameSize(const Matrix& a, const Matrix& b)
{
    if (a._row != b._row || a._col != b._col)
    {
        throw MessageException("the matrixes must have same number of row and same number column");
    }
}

/**
 * @brief the function throws exception if the law of matrix mulitplication has been broken:
 * according to the below --> must be: m = k
 * 
 * @param a (nxm) sized matrix 
 * @param b (kxl) sized matrix
 */
void zich::throwIfMulWrong(const Matrix& a, const Matrix& b)
{
    if (a._col != b._row)
    {
        throw MessageException("the number of column of the left matrix must be equal to the number of rows of the right matrix");
    }
}

/**
 * @brief pre+
 * 
 * @return Matrix 
 */
Matrix Matrix::operator+() const
{
    return (*this);
}

/**
 * @brief adding to other matrix
 * 
 * @param other 
 * @return Matrix 
 */
Matrix Matrix::operator+(const Matrix& other) const
{
    throwIfNotSameSize(*this, other);   // throw if illegal
    Matrix temp = (*this);
    temp += other;
    return (temp);
}

/**
 * @brief pre minus -> matrix m --> -m = -1*m
 * 
 * @return Matrix 
 */
Matrix Matrix::operator-() const
{
    return ((*this)*(-1));
}

/**
 * @brief matrix (a - b)
 * 
 * @param other the b matrix
 * @return Matrix 
 */
Matrix Matrix::operator-(const Matrix& other) const
{
    throwIfNotSameSize(*this, other);   // throw if illegal

    return ((*this) + (-other));
}

// * operator
/**
 * @brief operator * between 2 matrixes
 * 
 * @param other 
 * @return Matrix 
 */
Matrix Matrix::operator*(const Matrix& other) const
{
    throwIfMulWrong(*this, other);   // throw if illegal
    return (*this);
}

Matrix Matrix::operator*(double skalar) const
{
    Matrix temp{*this};
    temp *= skalar;
    return (temp);
}

Matrix zich::operator*(double skalar, const Matrix& m)
{
    return (m * skalar);
}



Matrix& Matrix::operator+=(const Matrix& other)
{
    throwIfNotSameSize(*this, other);   // throw if illegal
    for(unsigned int i = 0; i < _row; i++)
    {
        for (unsigned int j = 0; j < _col; j++)
        {
            _mat[i][j] += other._mat[i][j];
        }
    }

    return (*this);
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    throwIfNotSameSize(*this, other);   // throw if illegal
    (*this) += (-other);
    return (*this);
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    throwIfMulWrong(*this, other);   // throw if illegal
    return (*this);
}

Matrix& Matrix::operator*=(double skalar)
{
    for(unsigned int i = 0; i < _row; i++)
    {
        for (unsigned int j = 0; j < _col; j++)
        {
            _mat[i][j] *= skalar;
        }
    }
    return (*this);
}

Matrix& Matrix::operator++()
{
    for(unsigned int i = 0; i < _row; i++)
    {
        for (unsigned int j = 0; j < _col; j++)
        {
            _mat[i][j] += 1;
        }
    }
    return (*this);
}

Matrix& Matrix::operator--()
{
    for(unsigned int i = 0; i < _row; i++)
    {
        for (unsigned int j = 0; j < _col; j++)
        {
            _mat[i][j] -= 1;
        }
    }
    return (*this);
}

Matrix Matrix::operator++(int dummy_flag_for_postfix_increment)
{
    Matrix temp{*this};
    ++(*this);
    return temp;
}

Matrix Matrix::operator--(int dummy_flag_for_postfix_increment)
{
    Matrix temp{*this};
    --(*this);
    return temp;
}

long double Matrix::sumMatrix() const
{
    long double sum = 0;
    for (unsigned int i = 0; i < _row; i++)
    {
        for (unsigned int j = 0; j < _col; j++)
        {
            sum += (long double)_mat[i][j];
        }
        
    }
    return (sum);
}

/**
 * @brief comapres the matrixes sum, for a,b matrixes
 * 
 * @param a the left matrix
 * @param b the right matrix
 * @return int: (-1) if sum(a) > sum(b),
 *               (0) if sum(b) < sum(b)
 */
int Matrix::compareSumMatrix(const Matrix& a, const Matrix& b)
{
    long double diff = b.sumMatrix() - a.sumMatrix();
    if (diff < -EPS)        // if the comparison is lower than the -EPS then (a > b)
    {
        return (-1);
    }
    if (diff > EPS)        // if the comparison is higher than the EPS then (a < b)
    {
        return (1);
    }
    return 0;
}

bool zich::operator==(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (false);
}

bool zich::operator!=(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (false);
}

bool zich::operator<(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (false);
}

bool zich::operator>(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (false);
}

bool zich::operator<=(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (false);
}

bool zich::operator>=(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (false);
}

string Matrix::toString() const
{
    string s;
    for (unsigned int i = 0; i < _row; i++)
    {
        s += "[";
        for (unsigned int j = 0; j < _col; j++)
        {
            s += to_string(_mat[i][j]);
            if (j < _col - 1)
            {
                s += ", ";
            }
        }
        s += "]\n";
    }

    return s;
}

ostream& zich::operator<< (ostream& output, const Matrix& m)
{
    double t = 0.0;
    for (unsigned int i = 0; i < m._row; i++)
    {
        output << "[";
        for (unsigned int j = 0; j < m._col; j++)
        {
            t = m._mat[i][j];
            if (t == 0)
                output << 0;
            else
                output << t;
            
            if (j < m._col - 1)
            {
                output << ", ";
            }
        }
        output << "]\n";
    }

    return (output);
}

istream& zich::operator>> (istream& input , Matrix& m)
{
    //for the regex:
    //\[\d+(\, \d+)*\](\, \[\d+(\, \d+)*\])*$
    
    return (input);
}

