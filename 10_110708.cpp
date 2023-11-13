#include <iostream>
#include <windows.h> //화면 clear, 콘솔 커서 위치 변경
#include <iomanip>//cout 조작자 사용.. 
#include <fstream>//txt 파일 접근
#include <string>
using namespace std;
//충돌 실험 통계처리 시스템
/////////파일 읽기로 변경
//Tick[ms],Height[g],Horizontal[g],Vertical[g],Magnitude[g],Temperature[C],Date,Time 이중에 높이 가로세로 날짜만 처리

//클래스 정의
struct Record{
    string height;
    string horizontal;
    string vertical;
    string date;
    string time;
};
struct field_index{
    int height_index;
    int horizontal_index;
    int vertical_index;
    int date_index;
    int time_index;
};
struct stats_index{
    int height_max_index;
    int horizontal_max_index;
    int vertical_max_index;
    int height_min_index;
    int horizontal_min_index;
    int vertical_min_index;
};

class Program{
    struct field_index f_i;
    struct stats_index s_i={0,0,0,0,0,0};
    struct Record record_list[80];
    int record_list_index;
    ifstream data_file;
    string data_file_name;
    
    public:
    Program(){record_list_index=0;}
    void load_file_name(string s);
    void load_field_name();
    void load_record();

    void stats_processing();

    void title();//타이틀 화면

    void view_data_list();//데이터 목록 조회
    void view_stats();//통계 조회

    void save();//통계 내용 txt로 저장
    void save_interface();

    void exit();
};
int main(int argc, char** argv){
    int swch;
    Program p1;
    ifstream file; 
    if(argc<2){
        cout << "파일 이름을 인수로 넣어주세요." << endl;
        return 0;
    }
    p1.load_file_name(argv[1]);
    p1.load_field_name();
    p1.load_record();
    p1.stats_processing();
    //cout<< argv[1] << argc << endl;
    while(1){
        system("cls");
        p1.title();
        cin>>swch;
        switch (swch){
        case 1: p1.view_data_list();
            break;
        case 2: p1.view_stats();
            break;
        case 3: p1.save();
            break;
        case 4: p1.exit(); return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}


void Program::title(){
    system("cls");
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      통계 처리 프로그램      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      1. 데이터 조회          │" << endl;
    cout << "    │      2. 통계 조회            │" << endl;
    cout << "    │      3. 저장                 │" << endl;
    cout << "    │      4. 종료                 │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      >>                      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
}
void Program::load_file_name(string s){
    data_file_name=s;
    this->data_file.open(s);
}
void Program::load_field_name(){
    string str;
    int comma_index=0;
    getline(data_file, str);
    for(int i=0;str[i];i++){
        if(str[i]==','){comma_index++; continue;}
        if(comma_index==1)f_i.height_index=comma_index;
        if(comma_index==2)f_i.horizontal_index=comma_index;
        if(comma_index==3)f_i.vertical_index=comma_index;
        if(comma_index==6)f_i.date_index=comma_index;
        if(comma_index==7)f_i.time_index=comma_index;
    }
}
void Program::load_record(){
    string str;
    for(int j=0; j<80; j++){
        int comma_index=0;
        getline(data_file, str);
        for(int i=0;str[i];i++){
            if(str[i]==','){comma_index++; continue;}
            if(comma_index==f_i.height_index)record_list[record_list_index].height+=str[i];
            if(comma_index==f_i.horizontal_index)record_list[record_list_index].horizontal+=str[i];
            if(comma_index==f_i.vertical_index)record_list[record_list_index].vertical+=str[i];
            if(comma_index==f_i.date_index)record_list[record_list_index].date+=str[i];
            if(comma_index==f_i.time_index)record_list[record_list_index].time+=str[i];
        }
        record_list_index++;
    }
    
}

void Program::view_data_list(){
    string temp;
    int i=0;
    for(;;){
        system("cls");
        cout << endl << "    ┌──────────────────────────────┐" << endl;
        cout << "    │                              │" << endl;
        cout << "    │    데이터 목록 조회: "<<setw(2) << left << i+1 << "번    │" << endl;
        cout << "    │     " << record_list[i].date << " " << record_list[i].time << "      │" << endl;
        cout << "    │     height: " << setw(8) << left << record_list[i].height << "         │" << endl;
        cout << "    │     Horizontal: " << setw(8) << left << record_list[i].horizontal << "     │" << endl;
        cout << "    │     vertical: " << setw(8) << left << record_list[i].vertical << "       │" << endl;
        cout << "    │                              │" << endl;
        cout << "    │      숫자-n번 데이터         │" << endl;
        cout << "    │      >>                      │" << endl;
        cout << "    │                              │" << endl;
        cout << "    └──────────────────────────────┘" << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
        cin>>temp;
        if(temp>"80" || temp<"1") break;//이거 고치기
        i=stoi(temp)-1;
    }
}
void Program::view_stats(){
    string temp="m";

    while(1){
        system("cls");
        cout << endl << "    ┌──────────────────────────────┐" << endl;
        cout << "    │                              │" << endl;
        cout << "    │        최소 통계 조회        │" << endl;
        cout << "    │                              │" << endl;
        cout << "    │    height 최소 index: "<< setw(2) << right << s_i.height_min_index <<"     │" << endl;
        cout << "    │    horizontal 최소 index: "<< setw(2) << right << s_i.horizontal_min_index <<" │" << endl;
        cout << "    │    vertical 최소 index: "<< setw(2) << right << s_i.vertical_min_index <<"   │" << endl;
        cout << "    │                              │" << endl;
        cout << "    │      m-최대 통계 조회        │" << endl;
        cout << "    │      >>                      │" << endl;
        cout << "    │                              │" << endl;
        cout << "    └──────────────────────────────┘" << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
        cin>>temp;
        if(temp!="m") break;
        system("cls");
        cout << endl << "    ┌──────────────────────────────┐" << endl;
        cout << "    │                              │" << endl;
        cout << "    │        최대 통계 조회        │" << endl;
        cout << "    │                              │" << endl;
        cout << "    │    height 최대 index: "<< setw(2) << right << s_i.height_max_index <<"     │" << endl;
        cout << "    │    horizontal 최대 index: "<< setw(2) << right << s_i.horizontal_max_index <<" │" << endl;
        cout << "    │    vertical 최대 index: "<< setw(2) << right << s_i.vertical_max_index <<"   │" << endl;
        cout << "    │                              │" << endl;
        cout << "    │      m-최소 통계 조회        │" << endl;
        cout << "    │      >>                      │" << endl;
        cout << "    │                              │" << endl;
        cout << "    └──────────────────────────────┘" << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
        cin>>temp;
        if(temp!="m") break;
    }
}
void Program::stats_processing(){
    int i;
    float temp1, temp2;
    for(i=1; i<80; i++){
        temp1=stof(record_list[i].height);
        temp2=stof(record_list[s_i.height_max_index].height);
        if(temp1 > temp2) s_i.height_max_index=i;

        temp2=stof(record_list[s_i.height_min_index].height);
        if(temp1 < temp2) s_i.height_min_index=i;

        temp1=stof(record_list[i].horizontal);
        temp2=stof(record_list[s_i.horizontal_max_index].horizontal);
        if(temp1 > temp2) s_i.horizontal_max_index=i;

        temp2=stof(record_list[s_i.horizontal_min_index].horizontal);
        if(temp1 < temp2) s_i.horizontal_min_index=i;

        temp1=stof(record_list[i].vertical);
        temp2=stof(record_list[s_i.vertical_max_index].vertical);
        if(temp1 > temp2) s_i.vertical_max_index=i;

        temp2=stof(record_list[s_i.vertical_min_index].vertical);
        if(temp1 < temp2) s_i.vertical_min_index=i;
    }
}
void Program::save(){
    ofstream file;
	cout << fixed;
	cout.precision(2);

    file.open("result.txt");
    file << "flie name: " << data_file_name << endl << endl;
    file << " height 최댓값: " << record_list[s_i.height_max_index].height << ", index: " << s_i.height_max_index << endl;
    file << " height 최솟값: " << record_list[s_i.height_min_index].height << ", index: " << s_i.height_min_index << endl;
    file << " horizontal 최댓값: " << record_list[s_i.horizontal_max_index].horizontal << ", index: " << s_i.horizontal_max_index << endl;
    file << " horizontal 최솟값: " << record_list[s_i.horizontal_min_index].horizontal << ", index: " << s_i.horizontal_min_index << endl;
    file << " vertical 최댓값: " << record_list[s_i.vertical_max_index].height << ", index: " << s_i.vertical_max_index << endl;
    file << " vertical 최솟값: " << record_list[s_i.vertical_min_index].height << ", index: " << s_i.vertical_min_index << endl;

    save_interface();
}
void Program::save_interface(){
    string temp;
    system("cls");
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │          txt파일로           │" << endl;
    cout << "    │       저장되었습니다.        │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │     아무 글자나 입력하세요   │" << endl;
    cout << "    │      >>                      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
    cin>>temp;
}
void Program::exit(){
    system("cls");
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      통계 처리 프로그램      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      1. 데이터 조회          │" << endl;
    cout << "    │      2. 통계 조회            │" << endl;
    cout << "    │      3. 저장                 │" << endl;
    cout << "    │      4. 종료                 │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      >> 감사합니다.          │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl << endl;
}
