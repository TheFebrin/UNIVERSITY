/*
Dawid
Dieu
302052
*/
#include "functions.hpp"

bool check_if_good_ip(char *ip)
{
    /*
    Check if every char is a digit or a dot.
    Check if every number is between [0, 255].
    Check if there are 3 dots in between the numbers.
    */
    string ip_string(ip);
    int dots = 0;

    string tmp;
    ip_string += '.';
    for(auto a: ip_string)
    {
        if(a == '.')
        {
            dots ++;
            if(tmp == "")
                return false;
            int act_num = stoi(tmp);
            if(act_num > 255)
                return false;
            tmp = "";
        }
        else if (a >= '0' and a <= '9')
            tmp += a;
        else
            return false;
    }
    return dots == 4;
}
