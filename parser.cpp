//利用递归的方法解决四则运算的算法问题
#include <iostream>
#include "parser.h"
#include "token.h"
#include <tuple>

//处理输入的括号
static std::tuple<double, std::string> parseFactor(std::string input)
{
    double result;
    Token tk;
    std::tie (tk, input) =  tokenize(input);

    switch (tk.type)
    {
        case TokenType::Number:
        result = tk.value;
        break;
        case TokenType::Lp:
        std::tie (result, input) = parseExpress(input);
        std::tie (tk, input) = tokenize(input);
        //缺少半边括号的错误算式处理
        if (tk.type != TokenType::Rp)
        {
            throw std::runtime_error("bad syntax: need a )\n");
        }
        break;
        default:
        throw std::runtime_error("bad syntax: need a number or a (\n");
        break;
    }
    return {result,input};
}
//处理乘除运算的先后顺序
static std::tuple <double, std::string> parseTerm(std::string input)
{
    double result;
    std::tie(result, input) = parseFactor(input);
    bool loop = true;
    while(loop)
    {
        Token op;
        std::string res;
        double term;
        std::tie(op, res) = tokenize(input);
        switch (op.type)
        {
            case TokenType::Mul:
            std::tie (term, input) = parseFactor(res);
            result *= term;
            break;
            case TokenType::Div:
            std::tie (term, input) = parseFactor(res);
            //输入分母为0时的错误算式处理
            if (term == 0.0)
            {
                throw std::runtime_error("ERROR");
            }
                result /= term;
            break;
            default:
                loop = false;
            break;
        }
    }
    return {result, input};
}
//处理加减运算的先后顺序
std::tuple <double, std::string> parseExpress(std::string input)
{
    double result;
    std::tie(result, input) = parseTerm(input);
    bool loop = true;
    while(loop)
    {
        Token op;
        std::string res;
        double term;
        std::tie(op, res) = tokenize(input);
        switch (op.type)
        {
            case TokenType::Plus:
            std::tie (term, input) = parseTerm(res);
            result += term;
            break;
            case TokenType::Minus:
            std::tie (term, input) = parseTerm(res);
            result -= term;
            break;
            default:
                loop = false;
            break;
        }
    }
    return {result, input};
}
