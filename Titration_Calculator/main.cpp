#include<vector> 
#include<string> 
#include<iostream>
#include <math.h> 
#include "titration_Calculator.h"


int main()
{
    Calculator current;
 
    current.push_file(); 
    current.print();
    current.prompt(); 

    return 0; 
}
