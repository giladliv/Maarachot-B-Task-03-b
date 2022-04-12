#pragma once

#include "Matrix.hpp"
#include <unordered_map>

using zich::Matrix;

namespace zich
{
    class Menu
    {
        public:
        Menu(/* args */);
        void addVarMatrix();
        static string getVarName();
        static Matrix getMatFromInput();
        ~Menu();
        

        private:
           unordered_map<string, Matrix> _variables;
           static bool isGoodVarName(const string& str);
           bool isVarExist(const string& var);
           
    
    };
    
    
    
}