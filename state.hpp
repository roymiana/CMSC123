#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int state[3][4][6] = 
 { 
   { {0,13,1,13,2,13}, {12,12,12,12,12,12}, {3,13,4,13,5,13}, {12,12,12,12,12,12} },
   { {6,13,7,13,8,13}, {12,12,12,12,12,12}, {9,13,10,13,11,13}, {12,12,12,12,12,12} },
	 { {12,12,12,12,12,12}, {13,6,13,7,13,8}, {12,12,12,12,12,12}, {13,9,13,10,13,11} }
 };

const string equation[16] = 
	{
		"x(b-(a-2))+2", "x(b/c-(a-2))+2", "x(log(c)b-(a-2))+2",
		"x(b-(a-1))+2", "x(b/c-(a-1))+2", "x(log(c)b-(a-1))+2",
		"x(n-(a-2))+2", "x(n/c-(a-2))+2", "x(log(c)n-(a-2))+2",
		"x(n-(a-1))+2", "x(n/c-(a-1))+2", "x(log(c)n-(a-1))+2",
		"2", "infinite",
        "x sqrt(n) + y", "x cubert(n) + y"
	};

int check_firstState(string init_value, string cond_value){
    if(init_value == "n")
        return 2;

    if(cond_value == "n")
        return 1;

    return 0;
}

int check_secondState(string cond_operation){
    if(cond_operation == "<=")
        return 2;
    if(cond_operation == ">=")
        return 3;
    if(cond_operation == "<")
        return 0;
    if(cond_operation == ">")
        return 1;
    
    return -1;
}

int check_thirdState(string iterate_operation){
    if(iterate_operation == "++")
        return 0;
    if(iterate_operation == "--")
        return 1;
    if(iterate_operation == "+=")
        return 2;
    if(iterate_operation == "-=")
        return 3;
    if(iterate_operation == "*=")
        return 4;
    if(iterate_operation == "/=")
        return 5;

    return -1;
}

