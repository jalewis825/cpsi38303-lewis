#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_set>

void tokenType (std::string code) {

    //Check that the string is not empty
    //Check that the string starts with a non-digit
    if (code.empty() || !std::isdigit(code[0])) {
        std::cout << "NEITHER" << std::endl;
        return;
    }
    
    size_t cursor = 0;
    bool hasDecimal = false;
    const std::unordered_set <char> OPERATORS = {'+', '-', '*', '/'};

    //Scan for digits and decimal points
    //If a decimal has already been found, prints error
    //Otherwise the cursor continues on through the string
    //While noting that there is a decimal so we can use float later
    while (cursor < code.size()) {
        if (std::isdigit(code[cursor])){
            cursor++;
        } else if (code[cursor] == '.') {
            if (hasDecimal) {
                std::cout << "ERROR" << std::endl;
                return;
            }
            hasDecimal = true;
            cursor++;
            
        } else {
            break;
        }
    }
    
    //Checking if that character right after the digits is a valid boundary such as the end of the string, a space, or one of the 4 defined operators
    if (cursor == code.size() || std::isspace(code[cursor]) || OPERATORS.count(code[cursor]) > 0) {
        std::string type;
        std::string valueString = code.substr(0, cursor);

        //Setting up for printing off results by defining float (from above) or int
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
    //Check if a letter comes immediatley after the number and prints error if so
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

