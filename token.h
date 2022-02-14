#pragma once
//定义并转换输入数据
enum class TokenType
{
    Number,
    End,
    Error,
    Plus='+',
    Minus='-',
    Mul='*',
    Div='/',
    Lp='(',
    Rp=')'
};
//定义数据成员Token
struct Token
{
    TokenType type;
    double value;
};

std::tuple<Token,std::string> tokenize(std::string input);