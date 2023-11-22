#pragma once
#include <cmath>
#include <string>
#include <iostream>
using namespace std;
class MyVector{
    float x; //height
    float y; //horizontal
    float z; //vertical
    float vector_value;
    float vector_difference;
    
    friend int vector_comparison(MyVector a, MyVector b);
    friend int get_abs(int);

    public:
    
    MyVector():x(0), y(0), z(0), vector_value(0){}
    void get_vector_xyz(string, string, string);
    void calc_vector_value();

    float get_x();
    float get_y();
    float get_z();
    float get_vector_value();
    
    MyVector operator-(MyVector const &a);
    int operator>(MyVector const &a);
    MyVector operator=(MyVector const &a);
    void printv();

};
// int vector_comparison(MyVector a, MyVector b);//첫번째 요소가 크면 1 리턴
// int get_abs(int);