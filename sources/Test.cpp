/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Gilad Livshitz
 * 
 * Date: 2022-04-06
 */

#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
using namespace std;

#include "Matrix.hpp"
using namespace zich;

string gl_nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

TEST_CASE("Bad c'tor")
{
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    
    CHECK_THROWS(Matrix(arr, -1, -1));
    CHECK_THROWS(Matrix(arr, 5, -1));
    CHECK_THROWS(Matrix(arr, -5, 2));
    
    // invalid size
    CHECK_THROWS(Matrix(arr, 5, 2));
}

TEST_CASE("Bad operators' sizes")
{
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    std::vector<double> arr2 = {3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 3, 0};
    Matrix a{arr, 3, 3};
    Matrix b{arr2, 3, 4};

    CHECK_THROWS(a+b);
    CHECK_THROWS(a-b);
    CHECK_THROWS(b*a);

    CHECK_THROWS(b += a);
    CHECK_THROWS(b -= a);
    CHECK_THROWS(b *= a);
    CHECK_THROWS(b *= b);

    CHECK_THROWS(cout << (a == b));
    CHECK_THROWS(cout << (a <= b));
    CHECK_THROWS(cout << (a >= b));
    CHECK_THROWS(cout << (a < b));
    CHECK_THROWS(cout << (a > b));

    std::vector<double> arr3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Matrix c{arr3, 2, 5};
    CHECK_THROWS(a+c);
    CHECK_THROWS(c+a);
    CHECK_THROWS(c-a);
    CHECK_THROWS(a-c);
    CHECK_THROWS(a*c);
    CHECK_THROWS(c*a);
    CHECK_THROWS(c += a);
    CHECK_THROWS(c -= a);
    CHECK_THROWS(c *= a);
    CHECK_THROWS(a += c);
    CHECK_THROWS(a -= c);
    CHECK_THROWS(a *= c);
}

TEST_CASE("Good comperators")
{
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    std::vector<double> arr2 = {3, 0, 0, 0, 3, 0, 0, 0, 4};
    std::vector<double> arr3 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<double> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Matrix m1{arr, 3, 3};
    Matrix m2{arr, 3, 3};
    Matrix m3{arr2, 3, 3};
    Matrix m4{arr3, 3, 3};
    Matrix O{zero, 3, 3};
    Matrix I{identity, 3, 3};

    CHECK((m1 == m1) == true);
    CHECK((m1 != m1) == false);
    CHECK((m2 == m2) == true);
    CHECK((m1 == m2) == true);
    CHECK((m1 == m3) == false);
    CHECK((m1 < m3) == true);
    CHECK((m1 <= m3) == true);
    CHECK((m1 > m3) == false);
    CHECK((m1 >= m3) == false);

    CHECK((m1 < O) == false);
    CHECK((m1 > O) == true);

    CHECK(((m1 > m4) || (m1 == m4) || (m1 < m4)) == false);     // all of them are false, not eqaul but the sum is equal
    CHECK(((m4 > I) && !(m4 < I) && (m4 >= I) && !(m4 <= I)) == true);
}

TEST_CASE("Good +-*")
{
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr1 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<double> arr2 = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    std::vector<double> arr3 = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    std::vector<double> arr4 = {3, 3, 3, 3, 3, 3, 3, 3, 4};
    std::vector<double> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Matrix m1{arr1, 3, 3};
    Matrix m2{arr2, 3, 3};
    Matrix m3{arr3, 3, 3};
    Matrix m4{arr4, 3, 3};
    Matrix O{zero, 3, 3};
    
    CHECK((m1 + m2) == m3); // 1 + 2 = 3
    CHECK((m1 + m2) != m4);

    CHECK((m3 - m2) == m1); // 3 - 2 = 1
    CHECK((m4 - m2) != m1);

    CHECK(m3 == 3*m1);  // 3 = 3 * 1
    CHECK(m3 == m1*3);  // 3 = 1 * 3
    CHECK(m4 != 3*m1);
    CHECK(m4 != m1*3);

    CHECK(O == (O *= m1));  // 0 = 0*a 
    CHECK((O *= m2) == O);
    m1 *= 3;
    CHECK(m1 == m3);

    CHECK((--m1) == m2);    // (--3)  -->  2 == 2 
    CHECK((m1--) == m2);    // (2--)  --> 2 == 2  --> 1 != 2
    CHECK((m1--) != O);
    CHECK((m1++) == O);
    
    CHECK((+m1) == m1);
    m4 = m1 - m2;

    CHECK((-m1) == m4);

}

TEST_CASE("Good mult")
{
    std::vector<double> origins = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector<double> ansArr = {70, 80, 90, 158, 184, 210, 246, 288, 330};
    Matrix a{origins, 3, 4};        // creating a 3x4 (n x k)
    Matrix b{origins, 4, 3};        // on the same create 4x3 (k x m)
    Matrix ans{ansArr, 3, 3};       // the result must be nxm --> 3x3
    CHECK(a * b == ans);
    b *= a;
    CHECK_THROWS(cout << (b == ans));

    std::vector<double> arrVect = {1, 2, 3, 8, 9, 4, 7, 6, 5};
    ansArr = std::vector<double>({38, 38, 26, 108, 121, 80, 90, 98, 70});
    a = Matrix{arrVect, 3, 3};      // a has size 3x3
    ans = Matrix{ansArr, 3, 3};     // me can make a^2 ==> a*a
    CHECK(ans == a * a);
    a *= a;
    CHECK(a == ans);
}

TEST_CASE("GOOD OUTPUT")
{
    std::stringstream strStream;
    std::vector<double> arr = {1, 2, 3, 8, 9, 4, 7, 6, 5};
    Matrix a{arr, 3, 3};      // a has size 3x3
    strStream << a;     // use the operator<< to save the data
    string output = strStream.str();    // get the output outcome
    CHECK(gl_nospaces(output) == gl_nospaces("[1 2 3]\n"
                                       "[8 9 4]\n"
                                       "[7 6 5]\n"));

}
