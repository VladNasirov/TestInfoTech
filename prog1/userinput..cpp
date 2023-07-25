#include "userinput.h"
#include "ctype.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>


UserInput::UserInput(std::shared_ptr<Buffer> b)
{
    buf=b;
}

std::string UserInput::getString()
{
    return str;
}

void UserInput::setString(std::string s)
{
    str=s;
}

bool UserInput::isValid()
{
    if (str.empty())
    {
        std::cout << "Input line should not be empty!" << std::endl;
        std::cout << "Try again: " << std::endl;
        return false;
    }
    else if(str.size()>64)
    {
        std::cout<<"Input line should have 64 digits or less!"<<std::endl;
        std::cout << "Try again: " << std::endl;
        return false;
    }
    else
    {
        for(int i=0; i<str.size(); i++)
        {
            if(!(isdigit(str[i])))
            {
                 std::cout<<"Input line should contain only digits!"<<std::endl;
                 std::cout << "Try again: " << std::endl;
                return false;
            }
        }
    }
    return true;

}


void UserInput::sortByDescending()
{
    std::vector<int> vec;
   for (char ch : str) {
        if (std::isdigit(ch)) {
            int intValue = ch - '0';
            vec.push_back(intValue);
        }
    }
    sort(vec.begin(), vec.end(), std::greater<double>());
    std::ostringstream oss;
    for (int num : vec) {
        // Используем манипуляторы форматирования для обрезания лишних нулей
        if(num%2==0)
        {
            oss<<"KB";
        }
        else
        {
            oss << num;
        }
    }
    str = oss.str();
}


void UserInput::input()
{
    str.clear();
    do
    {
        
        std::getline(std::cin, str);
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cin.clear();
        

    }while(!isValid());
}

void UserInput::print()
{
    std::cout<<"Thread №"<<std::this_thread::get_id()<< " have changed string: "<<std::endl;
    std::cout<<str<<std::endl;
}

void UserInput::start()
{
    std::cout<<"Input the string: "<<std::endl;
    do
    {
    input();
    sortByDescending();
    buf->setBuffer(getString());
    print();
    }while(true);
}