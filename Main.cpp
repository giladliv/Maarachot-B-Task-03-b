/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 * 
 * Edited by Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
using namespace std;


#include "sources/Matrix.hpp"
#include <unordered_map>

using zich::Matrix;

namespace zich
{
    class MatCalc
    {
        public:
        MatCalc(/* args */);
        void addVarMatrix();
        static void removeSpacesFromStart(string& str);
        static void removeSpacesFromEnd(string& str);
        vector<string> separate(const string& str);
        void parser(const string& str);
        static vector<string> splitOneTime(const string& str, const string& pars);
        bool actionForTwo(const string& a, const string& b, const string& calcSign);
        void minusOperation(const string& a, const string& b);
        void regMulOperation(const string& a, const string& b);
        void mulAsgnOperation(const string& a, const string& b);
        ~MatCalc();
        

        private:
           unordered_map<string, Matrix> _variables;
           static bool isGoodVarName(const string& str);
           bool isVarExist(const string& var);
           static bool isDouble(const string& str);
           vector<string> _signes;
           
    
    };
    
    
    
}

using zich::MatCalc;


MatCalc::MatCalc()
{
    _signes = {"+=", "-=", "*=", "++", "--", "+", "-", "*", "==", "!=", "<=", ">=", "<", ">"};
}

MatCalc::~MatCalc()
{

}

void MatCalc::parser(const string& str)
{
    string temp(str);
    removeSpacesFromStart(temp);
    removeSpacesFromEnd(temp);
    if (isVarExist(temp))
    {
        cout << temp << endl;
        return;
    }
    
    vector<string> calcParts = separate(str);
    if (calcParts.size() == 1)
    {
        return;
    }
    if (calcParts.size() > 3)
    {
        return;
    }
    string calcSign = calcParts[2];
    string a = calcParts[0];
    string b = calcParts[1];
    removeSpacesFromEnd(a);
    removeSpacesFromStart(b);

    if (actionForTwo(a, b, calcSign))
    {
        return;
    }

    if (calcSign == "-")
    {
        minusOperation(a, b);
    }
    else if (calcSign == "*")
    {
        regMulOperation(a, b);
    }
    else if (calcSign == "*=")
    {
        mulAsgnOperation(a, b);
    }
    else if (calcSign == "++")
    {
        if (a == "" && isVarExist(b))
        {
            cout << (++_variables[b]) << endl;
        }
        else if (b == "" && isVarExist(a))
        {
            cout << (_variables[b]++) << endl;
        }
        else
        {
            throw MessageException("invalid calculation for++");
        }
    }
    else if (calcSign == "--")
    {
        if (a == "" && isVarExist(b))
        {
            cout << (--_variables[b]) << endl;
        }
        else if (b == "" && isVarExist(a))
        {
            cout << (_variables[b]--) << endl;
        }
        else
        {
            throw MessageException("invalid calculation for--");
        }
    }

}



/**
 * @brief the function returns whether the naming of variable is good or bad.
 * the var name can only have underscore, letters and numbers (the)
 * 
 * @param str 
 * @return true
 * @return false
 */
bool MatCalc::isGoodVarName(const string& str)
{   
    unsigned int digitCount = 0;
    if (str.length() == 0)
    {
        return (false);
    }
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (isalpha(str[i]) != 0 || str[i] == '_')   // if the ch is letter or _ then its ok
        {
            continue;
        }
        if (isdigit(str[i]) != 0)    // if the letter is digit then set to the counter and continue
        {
            digitCount++;
            continue;
        }
        return (false);         // if not none of the above then thats not a legal name
    }

    return (digitCount != str.length());        // if the whole string is not a number
    
}

bool MatCalc::actionForTwo(const string& a, const string& b, const string& calcSign)
{
    
    if (calcSign != "+=" && calcSign != "-="  && calcSign != "+" 
        && calcSign != "==" && calcSign != "!=" && calcSign != "<=" && calcSign != ">="
         && calcSign != "<" && calcSign != ">")
    {
        return false;
    }
    if (!isVarExist(a))
        {
            throw MessageException("the variable \'" + a + "\' is not recognized");
        }
        if (!isVarExist(a))
        {
            throw MessageException("the variable " + b + " is not recognized");
        }
    
    if (calcSign == "+=")
    {
        _variables[a] += _variables[b];
        cout << _variables[a] << endl << endl;
    }
    else if (calcSign == "-=")
    {
        _variables[a] -= _variables[b];
        cout << _variables[a] << endl << endl;
    }
    else if (calcSign == "+")
    {
        cout << _variables[a] + _variables[b] << endl << endl;
    }
    else if (calcSign == "==")
    {
        cout << ((_variables[a] == _variables[b]) ? "true" : "false") << endl << endl;
    }
    else if (calcSign == "!=")
    {
        cout << ((_variables[a] != _variables[b]) ? "true" : "false") << endl << endl;
    }
    else if (calcSign == "<=")
    {
        cout << ((_variables[a] <= _variables[b]) ? "true" : "false") << endl << endl;
    }
    else if (calcSign == ">=")
    {
        cout << ((_variables[a] >= _variables[b]) ? "true" : "false") << endl << endl;
    }
    else if (calcSign == "<")
    {
        cout << ((_variables[a] < _variables[b]) ? "true" : "false") << endl << endl;
    }
    else if (calcSign == ">")
    {
        cout << ((_variables[a] > _variables[b]) ? "true" : "false") << endl << endl;
    }
    return (true);
}

void MatCalc::minusOperation(const string& a, const string& b)
{
    if (a == "" && isVarExist(b))
    {
        cout << -_variables[b] << endl << endl;
    }
    else if (isVarExist(a) && isVarExist(b))
    {
        cout << _variables[a] - _variables[b] << endl << endl;
    }
    else
    {
        throw MessageException("invalid claculation for -");
    }
}

void MatCalc::mulAsgnOperation(const string& a, const string& b)
{
    if (isVarExist(a) && isDouble(b))
    {
        _variables[a] *= stod(b);
        cout << _variables[a] << endl << endl;
    }
    else if (isVarExist(a) && isVarExist(b))
    {
        _variables[a] *= _variables[b];
        cout << _variables[a] << endl << endl;
    }
    else
    {
        throw MessageException("invalid claculation for *=");
    }
}

void MatCalc::regMulOperation(const string& a, const string& b)
{
    if (isVarExist(a) && isDouble(b))
    {
        cout << _variables[a] * stod(b) << endl << endl;
    }
    else if (isDouble(a) && isVarExist(b))
    {
        cout << stod(a) * _variables[b] << endl << endl;
    }
    else if (isVarExist(a) && isVarExist(b))
    {
        cout << _variables[a] * _variables[b] << endl << endl;
    }
    else
    {
        throw MessageException("invalid claculation for *");
    }
}

void MatCalc::addVarMatrix()
{
    bool isNotValidVar = true;
    bool isNotGoodMat = true;
    string varName;
    Matrix m;
    do
    {
        cout << "enter here the your variable name: ";
        getline(cin, varName);
        isNotValidVar = !isGoodVarName(varName);
        
        if (isNotValidVar)
        {
            cout << "the name of the var is not valid" << endl;
            cout << "please try again" << endl;
        }

    } while (isNotValidVar);
    do
    {
        cout << "enter here your matrix: ";
        try
        {
            cin >> m;
            _variables[varName] = m;
            isNotGoodMat = false;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << endl;
            cout << "please try again" << endl;
            isNotGoodMat = true;
        }
        
    } while (isNotGoodMat);
    
}

bool MatCalc::isVarExist(const string& var)
{
    return (_variables.count(var) > 0);
}

bool MatCalc::isDouble(const string& str)
{
    try
    {
        stod(str);
    }
    catch(const std::exception& e)
    {
        return (false);
    }
    return (true);
    
}

vector<string> MatCalc::splitOneTime(const string& str, const string& pars)
{
    vector<string> splited = Matrix::split(str, pars);
    while (splited.size() > 2)
    {
        splited[1] += pars + splited[2];
        splited.erase(splited.begin() + 2);
    }
    return (splited);
}

/**
 * @brief finding the operator and return its sign number
 * 
 * @param str 
 */
vector<string> MatCalc::separate(const string& str)
{
    vector<string> retVect{str};

    for (unsigned int i = 0; i < _signes.size(); i++)
    {
        if (str.find(_signes[i]) != string::npos)
        {
            retVect = splitOneTime(str, _signes[i]);
            retVect.push_back(_signes[i]);
            return (retVect);
        }
    }

    return retVect;
}

void MatCalc::removeSpacesFromStart(string& str)
{
    while (str.length() > 0 && str[0] == ' ')
    {
        str.erase(0, 1);
    }
}

void MatCalc::removeSpacesFromEnd(string& str)
{
    while (str.length() > 0 && str.back() == ' ')
    {
        str.pop_back();
    }
}



int main()
{
  MatCalc calc;
  cout << "Welcome to our matrix calculator" << endl;
  
  string op;

  do
  {
    cout << "\nfor entering new variable please enter 1" << endl;
    cout << "for performing calculations please enter 2" << endl;
    cout << "for performing calculations please enter q" << endl;
    cout << "please enter your choice: ";
    getline(cin, op);
    if (op == "1")
    {
      
      calc.addVarMatrix();
    }
    else if (op == "2")
    {
      string calcLine;
      cout << "enter here your calculations, for ending please enter \"q!\"" << endl;
      while (calcLine != "q!")
      {
        try
        {
          cout << ">>>>  ";
          getline(cin, calcLine);
          if (calcLine == "q!")
          {
            break;
          }
          calc.parser(calcLine);
        }
        catch(const std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }
        
      }
      
    }
    else 
    {
      cout << "invalid choice" << endl;
    }
  } while (op != "q");
  cout << "Goodbye" << endl;

}
