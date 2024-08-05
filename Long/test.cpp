#include "calc.cpp"
#include <iostream>



int main(){
    //Long y=Long("11011000011011000000000000011011000011011");
    Long y=Long(1073741824);//2**30
    //y*b;
    y*y;y*y;y*y;y*y;y*y;//2**11*30
    y*1024;y*1024;
    std::cout<<y.toString()<<std::endl;
    return 0;
}