#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_set>

void tokenType (std::string code) {

    //Check if the input is empty or starts with a non-digit character
    if (code.empty() || !std::isdigit(code[0])) {
        std::cout << "NEITHER" << std::endl;
        return;
    }
    
    size_t cursor = 0;
    bool hasDecimal = false;
    const std::unordered_set <char> OPERATORS = {'+', '-', '*', '/'};

    //Scan through digits and allow at most one decimal point;
    //Stop scanning as soon as a non-digit/non-dot boundary is reached
    while (cursor < code.size()) {
        if (std::isdigit(code[cursor])){
            cursor++;
        } else if (code[cursor] == '.') {
            if (hasDecimal) {
                std::cout << "ERROR" << std::endl; //Flag second decimal point as an error
                return;
            }
            hasDecimal = true;
            cursor++;
            
        } else {
            break;
        }
    }
    
    //Checking if that character right after the digits is a valid boundary
    //(end of string, whitespace, or one of the 4 valid operators)
    if (cursor == code.size() || std::isspace(code[cursor]) || OPERATORS.count(code[cursor]) > 0) {
        std::string type;
        std::string valueString = code.substr(0, cursor);

        //Determine token type based on whether a decimal point was encountered
        if (hasDecimal) {
            type = "FLOAT";
        } else {
                type = "INT";
            }
        
        size_t remainderPos = cursor;
        
        //Advances remainderPos past any spaces/tabs so the leftover string doesn't start with whitespace
        while (remainderPos < code.size() && std::isspace(code[remainderPos])) {
            remainderPos++;
        }

        std::string remainder = code.substr(remainderPos);

        std::cout << "(\"" << type << "\", " << valueString << ")" << std::endl;
        std::cout << "Remaining: \"" << remainder << "\"" << std::endl;
        return;
    
    //Check if a letter comes immediatley after the number
    } else if (std::isalpha(code[cursor])) {
        std::cout << "ERROR" << std::endl;
        return;
        }
}

int main() {
    std::vector <std::string> testCases = {
        "1231234asdf",      //Expected: ERROR
        "1231234 asdf",     //Expected: ("INT", 1231234) Remaining: "asdf"
        "123.1234asdf",     //Expected: ERROR
        "123.123.123",      //Expected: ERROR
        "123.1234+asdf",    //Expected: ("FLOAT, 123.1234") Remaining: "+asdf"
        "+234",             //Expected: NEITHER
        "asdf+asdf",        //Expected: NEITHER
    };

    std::cout << "==============================================" << std::endl;
    std::cout << "       RUNNING NUMERIC LEXER TEST SUITE       " << std::endl;
    std::cout << "==============================================" << std::endl;

    for (size_t i = 0; i < testCases.size(); ++i) {
        std::cout << "Test " << (i + 1) << ":" << std::endl;
        std::cout << "Input: \"" << testCases[i] << "\"" << std::endl;
        std::cout << "Output: ";
        tokenType (testCases[i]);
        std::cout << "----------------------------------------------" << std::endl;
    }

    return 0;
}

