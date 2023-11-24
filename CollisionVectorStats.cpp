#include "CollisionVectorStats.h"
using namespace std;

void CollisionVectorStats::view_title(){
    system("cls");
    cout << " 통계 처리 프로그램" << endl << endl;
    cout << " 1. 데이터 조회" << endl;
    cout << " 2. 통계 조회" << endl;
    cout << " 3. 저장" << endl;
    cout << " 4. 종료" << endl << endl;
    cout << " >> ";
}
int CollisionVectorStats::load_file_name(string s){
    data_file_name=s;
    this->data_file.open(s);
    if(this->data_file.is_open()) return 0;
    else return 1;
}

//Tick[ms],Height[g],Horizontal[g],Vertical[g],Magnitude[g],Temperature[C],Date,Time 이중에 높이 가로 세로 벡터 날짜시간만 처리
int CollisionVectorStats::load_field_name(){
    string character; //한 글자씩 받을거임
    string temp="";//단어 임시저장할 공간
    int comma_index=0;
    getline(data_file, character);
    for(int i=0;character[i];i++){
        if(character[i]==','){
            comma_index++;
            temp="";
            continue;
        }
        temp+=character[i];

        if(temp=="Height")
            f_i.height_index=comma_index;
        if(temp=="Horizontal")
            f_i.horizontal_index=comma_index;
        if(temp=="Vertical")
            f_i.vertical_index=comma_index;
        if(temp=="Date")
            f_i.date_index=comma_index;
        if(temp=="Time")
            f_i.time_index=comma_index;
        if(temp=="Magnitude")
            f_i.vector_index=comma_index;
    }
    cout << f_i.height_index << " " << f_i.horizontal_index << " " << f_i.date_index << " " << f_i.vertical_index << " " <<  f_i.time_index << " " << endl; 
    if(f_i.height_index==-1 || f_i.horizontal_index==-1 || f_i.vertical_index==-1 || f_i.date_index==-1 || f_i.time_index==-1 || f_i.vector_index==-1){
        return 1;
    }
    return 0;
}
int CollisionVectorStats::load_record(){
    string temp;
    string str;
    int a;
    total_line_num=0;
    for(int j=0;; j++){
        int comma_index=0;
        getline(data_file, str);
        if(str=="") break;
        for(int i=0;str[i];i++){
            if(str[i]==',') {

                if(comma_index==f_i.height_index)
                    record_lists[j].height=stof(temp);
                if(comma_index==f_i.vertical_index)
                    record_lists[j].vertical=stof(temp);
                if(comma_index==f_i.horizontal_index)
                    record_lists[j].horizontal=stof(temp);
                if(comma_index==f_i.date_index)
                    record_lists[j].date=temp;
                if(comma_index==f_i.time_index)
                    record_lists[j].time=temp;

                temp="";
                comma_index++; continue;
            }
            temp+=str[i];
        }
        total_line_num++;
        //v[j].get_vector_xyz(record_lists[j].height, record_lists[j].horizontal, record_lists[j].vertical);
        // cout << record_lists[j].height << endl;
        // v[j].printv();
        // cout << total_line_num << endl;
        // cin>>a;
    }

    if(!record_lists[total_line_num-1].height) return 1;
}

void CollisionVectorStats::view_data_list(){
    int temp;
    int i=0;
    for(;;){
        system("cls");
        cout << "데이터 목록 조회: "<<setw(2) << left << i+1 << "번" << endl << endl;
        cout << " " << record_lists[i].date << " " << record_lists[i].time << endl;
        cout << " height: " << setw(8) << left << record_lists[i].height << endl;
        cout << " Horizontal: " << setw(8) << left << record_lists[i].horizontal << endl;
        cout << " vertical: " << setw(8) << left << record_lists[i].vertical << endl << endl;
        cout << "  숫자-n번 데이터" << endl;
        cout << "  >> ";

        cin >> temp;
        if (cin.fail()) { // 예외처리
            cin.clear(); // 에러 플래그를 초기화
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // 잘못된 입력을 무시
            return; // 에러 메시지 출력 또는 다른 처리
        }
        if(temp>total_line_num || temp<1) return;
        i=temp-1;
    }
}
void CollisionVectorStats::view_stats(){
    string temp;
    system("cls");
    cout << "가장 큰 벡터값 차이" << endl << endl;
    cout << " index["<< max_differene_index-1 <<"] x: "<< record_lists[max_differene_index-1].height << ", y: " << record_lists[max_differene_index-1].horizontal <<", z: "<< record_lists[max_differene_index-1].vertical << ", v: "<< record_lists[max_differene_index-1].vector << endl;
    cout << " index["<< max_differene_index <<"] x: "<< record_lists[max_differene_index].height << ", y: " << record_lists[max_differene_index].horizontal <<", z: "<< record_lists[max_differene_index].vertical<< ", v: "<< record_lists[max_differene_index].vector << endl;
    cout << " 총 벡터값 차이: " << setw(7) << left << get_vector_sub(record_lists[max_differene_index].vector, record_lists[max_differene_index-1].vector) << endl << endl;
    cout << "  아무 글자나 입력하세요" << endl;
    cout << "   >> ";

    cin>>temp;
}
void CollisionVectorStats::stats_processing(){
    int i;
    max_differene_index=0;
    float temp=0.00000;
    for(i=1;i<total_line_num;i++){ // 첫번째 값은 전 벡터값이 없음
        if(get_vector_sub(record_lists[i].vector, record_lists[i-1].vector) > temp){
            max_differene_index=i;
            temp=get_vector_sub(record_lists[i].vector, record_lists[i-1].vector);
        }
    }
}

float CollisionVectorStats::get_vector_sub(float num1, float num2){
    float result;
    if(num1>num2){
        return num1-num2;
    }
    else{
        return num2-num1;
    }
     
}

void CollisionVectorStats::save(){
    ofstream file;
	cout << fixed;
	cout.precision(2);

    file.open(data_file_name+"_result.txt");
    file << "flie name: " << data_file_name << endl << endl;
    file << "가장 큰 벡터값 차이" << endl << endl;
    file << " index["<< max_differene_index-1 <<"] x: "<< record_lists[max_differene_index-1].height << ", y: " << record_lists[max_differene_index-1].horizontal <<", z: "<< record_lists[max_differene_index-1].vertical << ", v: "<< record_lists[max_differene_index-1].vector << endl;
    file << " index["<< max_differene_index <<"] x: "<< record_lists[max_differene_index].height << ", y: " << record_lists[max_differene_index].horizontal <<", z: "<< record_lists[max_differene_index].vertical<< ", v: "<< record_lists[max_differene_index].vector << endl;
    file << " 총 벡터값 차이: " << setw(7) << left << get_vector_sub(record_lists[max_differene_index].vector, record_lists[max_differene_index-1].vector)<< endl << endl;

    view_save();
}
void CollisionVectorStats::view_save(){
    string temp;
    system("cls");
    cout << "txt파일로 저장되었습니다. " << endl << endl;
    cout << " 아무 글자나 입력하세요" << endl;
    cout << " >> ";
    cin>>temp;
}
void CollisionVectorStats::exit(){
    system("cls");
    cout << endl <<  " 감사합니다." << endl;
}
