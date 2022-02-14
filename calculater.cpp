//算式输入与主程序执行页面
#include "parser.h"
#include <string>
#include "parser.cpp"
#include <stdio.h>
using namespace std;
int main (int argc, char * argv[])
{
    //在此处输入算式进行运算
    std::string input = "1 + 2 * 3";
    double result;
    std::string res;
    try
    {
        auto re = parseExpress(input);
        result = get<0>(re);
        res = get<1>(re);
        printf ("%.31f\n", result);
    }
    //对输入的算式进行输出
    catch (std::exception& e)
    {
        printf("%s", e.what());
    }
    return 0;
}
