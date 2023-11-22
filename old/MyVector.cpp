#include "MyVector.h"

MyVector MyVector::operator-(MyVector const &a){
    MyVector result;
    if(vector_value>a.vector_value){
        result.x = x-a.x;
        result.y = y-a.y;
        result.z = z-a.z;
    }
    else{
        result.x = a.x-x;
        result.y = a.y-y;
        result.z = a.z-z;
    }
    result.calc_vector_value();
    return result;
}
MyVector MyVector::operator=(MyVector const &a){
    MyVector result;
    result.x = a.x;
    result.y = a.y;
    result.z = a.z;
    result.calc_vector_value();
    return result;
}
int MyVector::operator>(MyVector const &a){
    return vector_value > a.vector_value ? 1 : 0;
}

float MyVector::get_x(){
    return x;
}
float MyVector::get_y(){
    return y;
}
float MyVector::get_z(){
    return z;
}
float MyVector::get_vector_value(){
    return vector_value;
}

void MyVector::calc_vector_value(){
    float temp = x*x+y*y+z*z;
    vector_value=sqrt(temp);
}
void MyVector::get_vector_xyz(string x, string y, string z){
    this->x=stof(x);
    this->y=stof(y);
    this->z=stof(z);
    calc_vector_value();
}
void MyVector::printv(){
    cout << x << " " << y << " " << z << endl;
}
// int vector_comparison(MyVector a, MyVector b){//첫번째 요소가 크면 1 리턴
//     return (a.vector_value > b.vector_value);
// }
// int get_abs(int num){
//     if(num<0) return -num;
//     return num;
// }