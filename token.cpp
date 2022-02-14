//对输入的算式进行处理使其转换为字符串进行运算
#include <iostream>
#include "token.h"
#include <stdexcept>
#include <string>
#include <tuple>
//处理第一个字符
static std::tuple<double, std::string> parseNumber(std::string input)
{
    std::string numstr;
    bool firstDot = true;
    while (1)
    {
        //若第一个字符为空格
        if (input.empty())
        {
            break;
        }
        //若第一个字符为数字
        char ch = input.front();
        if ((ch >= '0' && ch <= '9') || (ch == '.'))
        {
            numstr.push_back(ch);
            input.erase(input.begin());
            //若第一个字符为标点
            if (ch == '.')
            {
                firstDot = false;
            }
        }
        else
        {
            break;
        }
    };
    return {std::stod(numstr), input};
}
//逐个依次解析算式中的数字和运算符号并转换为字符串
std::tuple<Token, std::string> tokenize(std::string input)
{
    char ch;
    Token tk;
    do
    {
        //若字符为空格
        if (input.empty())
        {
            tk.type = TokenType::End;
            return {tk, ""};
        }
        //移动到下一个字符进行转换
        else
        {
            ch = input.front();
            input.erase(input.begin());
        }
    } while (ch == ' ');
    //逐个转换过程
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        tk.type = TokenType(ch);
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        tk.type = TokenType::Number;
        input.insert(input.begin(), ch);
        std::tie(tk.value, input) = parseNumber(input);
        break;
    //输入其他非法字符时的报错处理
    default:
        throw std::runtime_error("Error\n");
        break;
    }
    return {tk, input};
}
