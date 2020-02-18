#include <iostream>
#include <string>

using std::string;

class CBaseConverter
{
    const static char digArray[];
    unsigned int length = 64;
    //****************************************************************************//
public:
    CBaseConverter() {}

    //----------------------------------------------------------------------------//

    unsigned int GetValOfDigit(char* character)
    {
        for(unsigned int i = 0; i < length; ++i)
        {
            if(digArray[i] == *character)
            {
                return i;
            }
        }
        return 0;
    }

    //----------------------------------------------------------------------------//

    /*
    Gets value of number in any base as an unsigned integer in base 10
    */
    unsigned int ValOfBase(string num, unsigned int base)
    {
        unsigned int total = 0;
        unsigned int len = num.length();
        for(unsigned int i = 0; i < len; ++i)
        {
            unsigned int val = GetValOfDigit(&num.at(i));
            if(val >= base)
            {
                std::cout << "\n" << "INVALID DIGIT\n";
                return -1;
            }
            total += val * pow(base, len - i - 1);
        }
        return total;
    }

    //----------------------------------------------------------------------------//
    
    /*
    Returns value of digit from table
    */
    char GetDigOfVal(unsigned int val)
    {
        return digArray[val];
    }

    //----------------------------------------------------------------------------//

    /*
    Recurvise method for converting from one base to another. Modifies string by reference
    */
    unsigned int ConvertRec(unsigned int val, string &outputString, unsigned int base = 2, unsigned int fact = 1)
    {
        if(fact * base <= val) //START HERE
        {
            val = ConvertRec(val, outputString, base, fact * base);
        }
        outputString += GetDigOfVal(val / fact);
        return val - fact * (val / fact);
    }

    //----------------------------------------------------------------------------//

    /*
    Shell function for converting bases
    */
    string ConvertBase(string num, unsigned int fromBase, unsigned int toBase)
    {
        string convertedNum = "";
        ConvertRec(ValOfBase(num, fromBase), convertedNum, toBase);
        return convertedNum;
    }
};

const char CBaseConverter::digArray[] = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
            'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
            'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
            'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
            'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
            'Y', 'Z', '+', '/'
            };

unsigned int main(unsigned int argc, char* argv[])
{
    CBaseConverter basec;
    string num = "";
    string input = "";
    unsigned int debugMode = 0;
    unsigned int base = 2;
    unsigned int toBase = 2;
    unsigned int inNum = 0;
    std::cout << "Debug Mode: ";
    std::cin >> debugMode;
    switch(debugMode)
    {
        case 0:
            
            while(base > 0)
            {
                std::cout << "Base: ";
                std::cin >> base;
                std::cout << "Number: ";
                std::cin >> num;
                string num10 = basec.ConvertBase(num, base, 10);
                std::cout << num10 << "\n\n";
            }
            break;
        case 1:
            
            while(inNum >= 0)
            {
                std::cout << "Number to convert: ";
                std::cin >> inNum;
                //basec.ConvertBase(inNum, num);
                std::cout << num << "\n\n";
                num = "";
            }
            
            break;
        case 2:
            while(input != "exit")
            {
                std::cout << "Number to convert: ";
                std::cin >> input;
                if(input == "exit")
                {
                    return 0;
                }
                std::cout << "From base: ";
                std::cin >> base;
                std::cout << "To base: ";
                std::cin >> toBase;
                basec.ConvertRec(basec.ValOfBase(input, base), num, toBase);
                std::cout << num << "\n\n";
                num = "";
            }
            break;
    }

    
    
    return 0;
}

//#include limits
//numeric_limits<streamsize>::max() //Max stream size