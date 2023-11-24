#pragma once
#include <iostream>
//#include "MyVector.h"
#include <windows.h> //화면 clear, 콘솔 커서 위치 변경
#include <iomanip>//cout 조작자 사용..
#include <fstream>//txt 파일 접근
#include <string>
#include <limits>
using namespace std;

class Record{
    public:
    float height;
    float horizontal;
    float vertical;
    float vector; //계산된 벡터값이 있었다...
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
    int max_differene_index; //차이가 가장 큰 인덱스
    int total_line_num; //라인 개수
    ifstream data_file;
    string data_file_name;
    // MyVector v[80];
    // MyVector v_sub; //벡터 차
    
    public:
    CollisionVectorStats(){}

    string get_file_create_time();
    string get_filename();

    int load_file_name(string s);
    int load_field_name();
    int load_record();

    void stats_processing();
    float get_vector_sub(float, float);

    void view_title();//타이틀 화면


    void save();//통계 내용 txt로 저장
    
    // void view_data_list();//데이터 목록 조회
    // void view_stats();//통계 조회
    // void view_save();

    // void exit();
};