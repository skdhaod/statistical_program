#include "CollisionVectorStats.h"
using namespace std;

int Data::operator>(Data const &a){
    if(v.magnitude>a.v.magnitude){
        return 1;
    }
    return 0;
}

// 
int CollisionVectorStats::load_file_name(string s){
    data_file_name=s;
    this->data_file.open(s);
    if(this->data_file.is_open()) return 0;
    else return 1;
}
string CollisionVectorStats::get_filename(){
    return data_file_name;
}

string CollisionVectorStats::get_file_create_time(){
    string result="";
    int first=-1;//���ڰ� ó�� ������ �ε���
    int last; //���ڰ� ���������� ������ �ε���
    for(int i=0; i<data_file_name.length(); i++){
        if(first==-1 && data_file_name[i]>=48 && data_file_name[i]<=57)
            first=i;
        if(data_file_name[i]>=48 && data_file_name[i]<=57)
            last=i;
    }
    for(int i=first; i<=last; i++){
        result+=data_file_name[i];
    }
    return result;
}

//Tick[ms],Height[g],Horizontal[g],Vertical[g],Magnitude[g],Temperature[C],Date,Time ���߿� ���� ���� ���� ���� ��¥�ð��� ó��
int CollisionVectorStats::load_field_name(){
    string character;
    string temp="";//�ܾ� �ӽ������� ����
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
                    record_lists[j].v.height=stof(temp);
                if(comma_index==f_i.vertical_index)
                    record_lists[j].v.vertical=stof(temp);
                if(comma_index==f_i.vector_index)
                    record_lists[j].v.magnitude=stof(temp);
                if(comma_index==f_i.horizontal_index)
                    record_lists[j].v.horizontal=stof(temp);
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

    if(!record_lists[total_line_num-1].v.height) return 1;
    return 0;
}

int CollisionVectorStats::stats_processing(){
    int i;
    max_differene_index=0;
    Data temp;
    for(i=1;i<total_line_num;i++){ // ù��° ���� �� ���Ͱ��� ����
        if(get_vector_sub(record_lists[i], record_lists[i-1]) > temp){
            max_differene_index=i;
            temp=get_vector_sub(record_lists[i], record_lists[i-1]);
        }
    }
    if(i==total_line_num) return 0;
    return 1;
}

Data CollisionVectorStats::get_vector_sub(Data vec1, Data vec2){
    Data result;
    result.date=vec1.date;
    result.time=vec1.time;
    if(vec1.v.magnitude>vec2.v.magnitude){
        result.v.height=vec1.v.height-vec2.v.height;
        result.v.horizontal=vec1.v.horizontal-vec2.v.horizontal;
        result.v.vertical=vec1.v.vertical-vec2.v.vertical;
    }
    else{
        result.v.height=vec2.v.height-vec1.v.height;
        result.v.horizontal=vec2.v.horizontal-vec1.v.horizontal;
        result.v.vertical=vec2.v.vertical-vec1.v.vertical;
    }
    result.v.magnitude=sqrt(result.v.height*result.v.height + result.v.horizontal*result.v.horizontal + result.v.vertical*result.v.vertical);
    return result;
}

int CollisionVectorStats::save(){
    ofstream file;
    Data temp;
    temp=get_vector_sub(record_lists[max_differene_index], record_lists[max_differene_index-1]);
    file.open(get_file_create_time()+"_result.txt");
    file << "flie name: " << data_file_name << endl << endl;
    file << "���� ū ���� ��" << endl << endl;

    file << " index["<< max_differene_index-1 <<"] ("<< record_lists[max_differene_index-1].v.height << ", " << record_lists[max_differene_index-1].v.horizontal
        <<", "<< record_lists[max_differene_index-1].v.vertical << ") -> "<< record_lists[max_differene_index-1].v.magnitude << endl;

    file << " index["<< max_differene_index <<"] ("<< record_lists[max_differene_index].v.height << ", " << record_lists[max_differene_index].v.horizontal
        <<", "<< record_lists[max_differene_index].v.vertical<< ") -> "<< record_lists[max_differene_index].v.magnitude << endl;
    
	file << fixed;
	file.precision(5);
    file << " ���� ��(" << temp.v.height << ", " << temp.v.horizontal << ", " << temp.v.vertical << ") -> " << temp.v.magnitude << left << endl << endl;
    
}

//void CollisionVectorStats::view_title(){
//     system("cls");
//     cout << " ��� ó�� ���α׷�" << endl << endl;
//     cout << " 1. ������ ��ȸ" << endl;
//     cout << " 2. ��� ��ȸ" << endl;
//     cout << " 3. ����" << endl;
//     cout << " 4. ����" << endl << endl;
//     cout << " >> ";
// }
// void CollisionVectorStats::view_save(){
//     string temp;
//     system("cls");
//     cout << "txt���Ϸ� ����Ǿ����ϴ�. " << endl << endl;
//     cout << " �ƹ� ���ڳ� �Է��ϼ���" << endl;
//     cout << " >> ";
//     cin>>temp;
// }
// void CollisionVectorStats::exit(){
//     system("cls");
//     cout << endl <<  " �����մϴ�." << endl;
// }
// void CollisionVectorStats::view_data_list(){
//     int temp;
//     int i=0;
//     for(;;){
//         system("cls");
//         cout << "������ ��� ��ȸ: "<<setw(2) << left << i+1 << "��" << endl << endl;
//         cout << " " << record_lists[i].date << " " << record_lists[i].time << endl;
//         cout << " height: " << setw(8) << left << record_lists[i].height << endl;
//         cout << " Horizontal: " << setw(8) << left << record_lists[i].horizontal << endl;
//         cout << " vertical: " << setw(8) << left << record_lists[i].vertical << endl << endl;
//         cout << "  ����-n�� ������" << endl;
//         cout << "  >> ";
//         cin >> temp;
//         if (cin.fail()) { // ����ó��
//             cin.clear(); // ���� �÷��׸� �ʱ�ȭ
//             cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // �߸��� �Է��� ����
//             return; // ���� �޽��� ��� �Ǵ� �ٸ� ó��
//         }
//         if(temp>total_line_num || temp<1) return;
//         i=temp-1;
//     }
// }
// void CollisionVectorStats::view_stats(){
//     string temp;
//     system("cls");
//     cout << "���� ū ���Ͱ� ����" << endl << endl;
//     cout << " index["<< max_differene_index-1 <<"] x: "<< record_lists[max_differene_index-1].height << ", y: " << record_lists[max_differene_index-1].horizontal <<", z: "<< record_lists[max_differene_index-1].vertical << ", v: "<< record_lists[max_differene_index-1].vector << endl;
//     cout << " index["<< max_differene_index <<"] x: "<< record_lists[max_differene_index].height << ", y: " << record_lists[max_differene_index].horizontal <<", z: "<< record_lists[max_differene_index].vertical<< ", v: "<< record_lists[max_differene_index].vector << endl;
//     cout << " �� ���Ͱ� ����: " << setw(7) << left << get_vector_sub(record_lists[max_differene_index].vector, record_lists[max_differene_index-1].vector) << endl << endl;
//     cout << "  �ƹ� ���ڳ� �Է��ϼ���" << endl;
//     cout << "   >> ";
//     cin>>temp;
// }
