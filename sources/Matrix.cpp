#include "Matrix.hpp"
using zich::Matrix;

/**
 * @brief Construct a new Matrix:: Matrix object
 * 
 * @param mat 
 * @param row 
 * @param col 
 */
Matrix::Matrix(const vector<double>& mat, int row, int col)
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


void Matrix::arrToMat(const vector<double>& matArr, int row, int col)
{
    _mat.clear();
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
Matrix::Matrix(const Matrix& other) : _row(other._row), _col(other._col)
{
    (*this) = other;
}

Matrix::Matrix() : Matrix({0}, 1, 1)
{

}

/**
 * @brief by given string create the matrix
 * 
 * @param str 
 */
Matrix::Matrix(const string& str)
{
    // if the regex check found that the matrix input is not suitable throw a message exception
    if (!Matrix::isGoodMatrixInput(str))
    {
        throw MessageException("matrix must be with format of [.. .. ..], [.. .. ..], [.. .. ..]\n"
                                "each row must be inside of squared brackets\n"
                                "each row must contain valid numbers, which will be saperated by only one space\n"
                                "each row  will be saperated by \", \"");
    }

    string line;
    vector<string> matRows = split(str, ", ");
    
    _row = matRows.size();

    _mat.clear();
    vector<string> numbersStr;

    for (unsigned int i = 0; i < _row; i++)
    {
        _mat.push_back(vector<double>());
        line = matRows[i];
        line.pop_back();    // remove the last char ']' from the line - thats because the input is ok
        line = line.erase(0, 1);   // remove the first char '[' from the line - thats because the input is ok
        
        numbersStr = split(line, " "); // split the string to the
        
        // if the number of colums is difrrent from the previous then the input is invalid
        if (i > 0 && _col != numbersStr.size())
        {
            throw MessageException("invalid column number - each row must have the same amount of numbers");
        }

        // set now the columns number - the first time will make the change the others won't
        _col = numbersStr.size();

        for (unsigned int j = 0; j < _col; j++)
        {
            _mat[i].push_back(stod(numbersStr[j]));     // for each row push the number as double to the matrix line
        }
        
    }
    
}

Matrix::~Matrix()
{
    
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
    return (this->operator*(-1));
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
    int n = this->_row;
    int k = this->_col;
    int m = other._col;

    vector<double> zero((unsigned int)n*(unsigned int)m, 0);
    Matrix ret{zero, n, m};

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            for (unsigned int t = 0; t < k; t++)
            {
                ret._mat[i][j] += this->_mat[i][t] * other._mat[t][j];
            }
            // zero mul neg causes troubles
            ret._mat[i][j] = (ret._mat[i][j] == 0) ? 0 : ret._mat[i][j];
        }
    }

    return (ret);
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
    (*this) = (*this) * other;
    return (*this);
}

Matrix& Matrix::operator*=(double skalar)
{
    for(unsigned int i = 0; i < _row; i++)
    {
        for (unsigned int j = 0; j < _col; j++)
        {
            _mat[i][j] *= skalar;

            // zero mul neg causes troubles
            _mat[i][j] = (_mat[i][j] == 0) ? 0 : _mat[i][j];
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
 * @return int: (-1) if sum(a) < sum(b),
 *               (0) if sum(a) = sum(b)
 *               (1) if sum(a) > sum(b)
 */
int Matrix::compareSumMatrix(const Matrix& a, const Matrix& b)
{
    long double diff = a.sumMatrix() - b.sumMatrix();
    if (diff < 0)        // if the comparison is lower than the -EPS then (a > b)
    {
        return (-1);
    }
    if (diff > 0)        // if the comparison is higher than the EPS then (a < b)
    {
        return (1);
    }
    return 0;
}

bool zich::operator==(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    int row = m1._row;
    int col = m1._col;
    for (unsigned int i = 0; i < row; i++)
    {
        for (unsigned int j = 0; j < col; j++)
        {
            if (m1._mat[i][j] != m2._mat[i][j])
            {
                return (false);
            }
                
        }
    }
    
    return (true);
}

bool zich::operator!=(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (!(m1 == m2));
}

bool zich::operator<(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (Matrix::compareSumMatrix(m1, m2) < 0);
}

bool zich::operator>(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (Matrix::compareSumMatrix(m1, m2) > 0);
}

bool zich::operator<=(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (m1 == m2 || m1 < m2);
}

bool zich::operator>=(const Matrix& m1, const Matrix& m2)
{
    throwIfNotSameSize(m1, m2);   // throw if illegal
    return (m1 == m2 || m1 > m2);
}

string Matrix::toString() const
{
    stringstream strm;
    strm << (*this);

    return strm.str();
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
            output << t;
            
            if (j < m._col - 1)     // if not the last number print " "
            {
                output << " ";
            }
        }
        output << "]";
        if (i < m._row - 1)     // if not the last line then print \n
        {
            output << "\n";
        }
    }

    return (output);
}

vector<string> Matrix::split(const string& str, const string& parser)
{
    vector<string> splited;
    string copyStr(str);
    int index = -1;
    // check the first apperance of the str
    while ((index = copyStr.find(parser)) != string::npos)
    {
        splited.push_back(copyStr.substr(0, (unsigned int)index));          // push it to the vector
        copyStr = copyStr.substr((unsigned int)index + parser.length());    // remove the substring from start
    }
    splited.push_back(copyStr);     // push the remain to the vector
    return (splited);
}

/**
 * @brief using regex to check if string is matching to the format of input matrix
 * 
 * @param str 
 * @return true 
 * @return false 
 */
bool Matrix::isGoodMatrixInput(const string& str)
{
    string regexDouble = "([-+]?((\\d+\\.?\\d*)|(\\.\\d+)))";                                     // checks if numbers are good
    string regexCheckListNumbers = regexDouble + "( " + regexDouble + ")*";                     // chacks if spaces are right
    regexCheckListNumbers = "\\[" + regexCheckListNumbers + "\\]";                              // checks if [..., ...] is good
    string regexMatrixStr = regexCheckListNumbers + "(\\, " + regexCheckListNumbers + ")*";     // checks if [], [] is good
    regexMatrixStr = "^" + regexMatrixStr + "$";                                                // checks that if not substring found - must be the whole string

    regex regExMatrix(regexMatrixStr);
    return (regex_match(str, regExMatrix));
}

istream& zich::operator>>(istream& input , Matrix& m)
{
    string inStr;
    getline(input, inStr);
    //cout << Matrix::getNumberOfColumnFromStr(inStr) << endl;
    m = Matrix{inStr};
    return (input);
}

