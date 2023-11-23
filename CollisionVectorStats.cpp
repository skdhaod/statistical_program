#include "CollisionVectorStats.h"
using namespace std; // ���� ������ ���������� �ٲ� �� �ְ� �ϱ� //1123

void CollisionVectorStats::view_title(){
    system("cls");
    cout << " ��� ó�� ���α׷�" << endl << endl;
    cout << " 1. ������ ��ȸ" << endl;
    cout << " 2. ��� ��ȸ" << endl;
    cout << " 3. ����" << endl;
    cout << " 4. ����" << endl << endl;
    cout << " >> ";
}
int CollisionVectorStats::load_file_name(string s){
    data_file_name=s;
    this->data_file.open(s);
    if(this->data_file.is_open()) return 0;
    else return 1;
}

//Tick[ms],Height[g],Horizontal[g],Vertical[g],Magnitude[g],Temperature[C],Date,Time ���߿� ���� ���� ���� ���� ��¥�ð��� ó��
int CollisionVectorStats::load_field_name(){
    string character; //�� ���ھ� ��������
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
                comma_index++; continue;
            }
            if(comma_index==f_i.height_index)
                record_lists[j].height+=str[i];

            if(comma_index==f_i.horizontal_index)
                record_lists[j].horizontal+=str[i];

            if(comma_index==f_i.vertical_index)
                record_lists[j].vertical+=str[i];

            if(comma_index==f_i.date_index)
                record_lists[j].date+=str[i];

            if(comma_index==f_i.time_index)
                record_lists[j].time+=str[i];
            if(comma_index==f_i.vector_index)
                record_lists[j].vector+=str[i];
        }
        total_line_num++;
        //v[j].get_vector_xyz(record_lists[j].height, record_lists[j].horizontal, record_lists[j].vertical);
        // cout << record_lists[j].height << endl;
        // v[j].printv();
        // cout << total_line_num << endl;
        // cin>>a;
    }

    if(record_lists[total_line_num-1].height!="") return 0;
}

void CollisionVectorStats::view_data_list(){
    int temp;
    int i=0;
    for(;;){
        system("cls");
        cout << "������ ��� ��ȸ: "<<setw(2) << left << i+1 << "��" << endl << endl;
        cout << " " << record_lists[i].date << " " << record_lists[i].time << endl;
        cout << " height: " << setw(8) << left << record_lists[i].height << endl;
        cout << " Horizontal: " << setw(8) << left << record_lists[i].horizontal << endl;
        cout << " vertical: " << setw(8) << left << record_lists[i].vertical << endl << endl;
        cout << "  ����-n�� ������" << endl;
        cout << "  >> ";

        cin >> temp;
        if (cin.fail()) { // ����ó��
            cin.clear(); // ���� �÷��׸� �ʱ�ȭ
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // �߸��� �Է��� ����
            return; // ���� �޽��� ��� �Ǵ� �ٸ� ó��
        }
        else{
            break;
        }

        if(temp>total_line_num || temp<1) return;
        i=temp-1;
    }
}
void CollisionVectorStats::view_stats(){
    string temp;
    system("cls");
    cout << "���� ū ���Ͱ� ����" << endl << endl;
    cout << " index["<< max_differene_index-1 <<"] x: "<< record_lists[max_differene_index-1].height << ", y: " << record_lists[max_differene_index-1].horizontal <<", z: "<< record_lists[max_differene_index-1].vertical << ", v: "<< record_lists[max_differene_index-1].vector << endl;
    cout << " index["<< max_differene_index <<"] x: "<< record_lists[max_differene_index].height << ", y: " << record_lists[max_differene_index].horizontal <<", z: "<< record_lists[max_differene_index].vertical<< ", v: "<< record_lists[max_differene_index].vector << endl;
    cout << " �� ���Ͱ� ����: " << setw(7) << left << get_vector_sub(record_lists[max_differene_index].vector, record_lists[max_differene_index-1].vector) << endl << endl;
    cout << "  �ƹ� ���ڳ� �Է��ϼ���" << endl;
    cout << "   >> ";

    cin>>temp;
}
void CollisionVectorStats::stats_processing(){
    int i;
    max_differene_index=0;
    float temp=0.00000;
    for(i=1;i<total_line_num;i++){ // ù��° ���� �� ���Ͱ��� ����
        if(get_vector_sub(record_lists[i].vector, record_lists[i-1].vector) > temp){
            max_differene_index=i;
            temp=get_vector_sub(record_lists[i].vector, record_lists[i-1].vector);
        }
    }
}

float CollisionVectorStats::get_vector_sub(string s1, string s2){
    float result;
    if(s1>s2){
        result=stof(s1)-stof(s2);
    }
    else{
        result=stof(s2)-stof(s1);
    }
    return result;
}

void CollisionVectorStats::save(){
    ofstream file;
	cout << fixed;
	cout.precision(2);

    file.open(data_file_name+"_result.txt");
    file << "flie name: " << data_file_name << endl << endl;
    file << "���� ū ���Ͱ� ����" << endl << endl;
    file << " index["<< max_differene_index-1 <<"] x: "<< record_lists[max_differene_index-1].height << ", y: " << record_lists[max_differene_index-1].horizontal <<", z: "<< record_lists[max_differene_index-1].vertical << ", v: "<< record_lists[max_differene_index-1].vector << endl;
    file << " index["<< max_differene_index <<"] x: "<< record_lists[max_differene_index].height << ", y: " << record_lists[max_differene_index].horizontal <<", z: "<< record_lists[max_differene_index].vertical<< ", v: "<< record_lists[max_differene_index].vector << endl;
    file << " �� ���Ͱ� ����: " << setw(7) << left << get_vector_sub(record_lists[max_differene_index].vector, record_lists[max_differene_index-1].vector)<< endl << endl;

    view_save();
}
void CollisionVectorStats::view_save(){
    string temp;
    system("cls");
    cout << "txt���Ϸ� ����Ǿ����ϴ�. " << endl << endl;
    cout << " �ƹ� ���ڳ� �Է��ϼ���" << endl;
    cout << " >> ";
    cin>>temp;
}
void CollisionVectorStats::exit(){
    system("cls");
    cout << endl <<  " �����մϴ�." << endl;
}
