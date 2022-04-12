#include "Menu.hpp"
using zich::Menu;



Menu::Menu(/* args */)
{
}

Menu::~Menu()
{
}

/**
 * @brief the function returns whether the naming of variable is good or bad.
 * the var name can only have underscore, letters and numbers (the)
 * 
 * @param str 
 * @return true
 * @return false
 */
bool Menu::isGoodVarName(const string& str)
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

void Menu::addVarMatrix()
{
    string name;
    bool isNotGoodMat = true;
    cout << "enter here the variable name: ";
    cin >> name;
    do
    {
        try
        {
            cin >> _variables[name];
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

Matrix Menu::getMatFromInput()
{
    Matrix m;
    bool isNotGoodMat = true;
    do
    {
        cout << "enter here your matrix: ";
        try
        {
            cin >> m;
            isNotGoodMat = false;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << endl;
            cout << "please try again" << endl;
            isNotGoodMat = true;
        }
        
    } while (isNotGoodMat);

    return (m);
}

string Menu::getVarName()
{
    bool isNotValidVar = true;
    string varName;
    do
    {
        cout << "enter here the your variable name: ";
        cin >> varName;
        isNotValidVar = !isGoodVarName(varName);
        
        if (isNotValidVar)
        {
            cout << "the name of the var is not valid" << endl;
            cout << "please try again" << endl;
        }

    } while (isNotValidVar);

    return (varName);
}

bool Menu::isVarExist(const string& var)
{
    return (_variables.count(var) > 0);
}