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

/**
 * @brief by given string create the matrix
 * 
 * @param str 
 */
Matrix::Matrix(const string& str)
{
    if (!Matrix::isGoodMatrixInput(str))
    {
        throw MessageException("matrix must be with format of [..., ..., ...], [..., ..., ...], ...");
    }
    int cols = getNumberOfColumnFromStr(str);
    
    string workOnStr;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] != '[' && str[i] != ']' && str[i] != ',')
        {
            workOnStr += str[i];
        }
    }
    vector<string> numbersStr = split(workOnStr, ' ');
    vector<double> arr;
    for (unsigned int i = 0; i < numbersStr.size(); i++)
    {
        cout << numbersStr[i] << endl;
        arr.push_back(stod(numbersStr[i]));
    }
    int rows = (int)arr.size() / cols;
    for (unsigned int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << rows << " " << cols << endl;
    try
    {
        *this = Matrix{arr, rows, cols};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    
    

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
    int row = m1._row;
    int col = m1._col;
    for (unsigned int i = 0; i < row; i++)
    {
        for (unsigned int j = 0; j < col; j++)
        {
            if (m1._mat[i][j] != m2._mat[i][j])
                return (false);
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
            if (t == 0)
                output << 0;        // because it has problems with printing
            else
                output << t;
            
            if (j < m._col - 1)     // if not the last number print ", "
            {
                output << ", ";
            }
        }
        output << "]\n";
    }

    return (output);
}

vector<string> Matrix::split(const string& str, char parser)
{
    vector<string> splited;
    stringstream strStream(str);
    string outStr;
    while (getline(strStream, outStr, parser))
    {
        splited.push_back(outStr);
    }
    return (splited);
}

vector<string> Matrix::split(const string& str, string parser)
{
    vector<string> splited;
    string copyStr(str);
    int index = -1;
    while ((index = copyStr.find(parser)) != string::npos)
    {
        splited.push_back(copyStr.substr(0, (unsigned int)index));
        copyStr = copyStr.substr((unsigned int)index + parser.length());
    }
    splited.push_back(copyStr);
    return (splited);
}

/**
 * @brief form string get the number of the columns for the matrix
 * 
 * @param str 
 * @return unsigned int 
 */
int Matrix::getNumberOfColumnFromStr(const string& str)
{
    int end = 0;
    vector<int> rows;
    int col = 0;
    vector<string> splited = split(str, ", ");
    for (unsigned int i = 0; i < splited.size(); i++)
    {
        col = count(splited[i].begin(), splited[i].end(), ' ') + 1;
        rows.push_back(col);
    }

    for (unsigned int i = 0; i < rows.size(); i++)
    {
        if (col != rows[i])
        {
            throw MessageException("the string of matrix must have the number of cols for each row");
        }
    }
    return col;
}

bool Matrix::isGoodMatrixInput(const string& str)
{
    string regexDouble = "((\\d+\\.?\\d*)|(\\.\\d+))";                            // checks if numbers are good
    string regexCheckListNumbers = regexDouble + "( " + regexDouble + ")*";  // chacks if spaces are right
    regexCheckListNumbers = "\\[" + regexCheckListNumbers + "\\]";              // checks if [..., ...] is good
    string regexMatrixStr = regexCheckListNumbers + "(\\, " + regexCheckListNumbers + ")*";    // checks if [], [] is good
    regexMatrixStr = "^" + regexMatrixStr + "$";         // checks that if not substring found - must be the whole string

    regex regExMatrix(regexMatrixStr);
    return (regex_match(str, regExMatrix));
}

istream& zich::operator>> (istream& input , Matrix& m)
{
    string inStr;
    getline(input, inStr);
    //cout << Matrix::getNumberOfColumnFromStr(inStr) << endl;
    m = Matrix{inStr};
    return (input);
}

