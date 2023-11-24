#pragma once
#include <iostream>
//#include "MyVector.h"
#include <windows.h> //ȭ�� clear, �ܼ� Ŀ�� ��ġ ����
#include <iomanip>//cout ������ ���..
#include <fstream>//txt ���� ����
#include <string>
#include <limits>
using namespace std;

class Record{
    public:
    float height;
    float horizontal;
    float vertical;
    float vector; //���� ���Ͱ��� �־���...
    string date;
    string time;
};
class FieldIndex{
    public:
    int height_index;
    int horizontal_index;
    int vertical_index;
    int vector_index;
    int date_index;
    int time_index;
};

class CollisionVectorStats{
    FieldIndex f_i={-1,-1,-1,-1,-1,-1};
    Record record_lists[80];
    int max_differene_index; //���̰� ���� ū �ε���
    int total_line_num; //���� ����
    ifstream data_file;
    string data_file_name;
    // MyVector v[80];
    // MyVector v_sub; //���� ��
    
    public:
    CollisionVectorStats(){}

    string get_file_create_time();
    string get_filename();

    int load_file_name(string s);
    int load_field_name();
    int load_record();

    void stats_processing();
    float get_vector_sub(float, float);

    void view_title();//Ÿ��Ʋ ȭ��


    void save();//��� ���� txt�� ����
    
    // void view_data_list();//������ ��� ��ȸ
    // void view_stats();//��� ��ȸ
    // void view_save();

    // void exit();
};