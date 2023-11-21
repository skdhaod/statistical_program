#include "CollisionVectorStats.h"
using namespace std;

void CollisionVectorStats::view_title(){
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      ��� ó�� ���α׷�      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      1. ������ ��ȸ          ��" << endl;
    cout << "    ��      2. ��� ��ȸ            ��" << endl;
    cout << "    ��      3. ����                 ��" << endl;
    cout << "    ��      4. ����                 ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      >>                      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
}
int CollisionVectorStats::load_file_name(string s){
    data_file_name=s;
    this->data_file.open(s);
    if(this->data_file.is_open()) return 0;
    else return 1;
}

//Tick[ms],Height[g],Horizontal[g],Vertical[g],Magnitude[g],Temperature[C],Date,Time ���߿� ���� ���μ��� ��¥�� ó��
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
    }
}
int CollisionVectorStats::load_record(){
    string temp;
    string str;
    for(int j=0; j<80; j++){
        int comma_index=0;
        getline(data_file, str);
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
        }
        v[j].get_vector_xyz(record_lists[j].height, record_lists[j].horizontal, record_lists[j].vertical);
        // cout << record_lists[j].height << endl;
        // v[j].printv();
        
    }

    if(record_lists[79].height!="") return 0;
}

void CollisionVectorStats::view_data_list(){
    int temp;
    int i=0;
    for(;;){
        system("cls");
        cout << endl << "    ����������������������������������������������������������������" << endl;
        cout << "    ��                              ��" << endl;
        cout << "    ��    ������ ��� ��ȸ: "<<setw(2) << left << i+1 << "��    ��" << endl;
        cout << "    ��     " << record_lists[i].date << " " << record_lists[i].time << "      ��" << endl;
        cout << "    ��     height: " << setw(8) << left << record_lists[i].height << "         ��" << endl;
        cout << "    ��     Horizontal: " << setw(8) << left << record_lists[i].horizontal << "     ��" << endl;
        cout << "    ��     vertical: " << setw(8) << left << record_lists[i].vertical << "       ��" << endl;
        cout << "    ��                              ��" << endl;
        cout << "    ��      ����-n�� ������         ��" << endl;
        cout << "    ��      >>                      ��" << endl;
        cout << "    ��                              ��" << endl;
        cout << "    ����������������������������������������������������������������" << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});

        do{
            std::cin >> temp;
            if (cin.fail()) { // ����ó��
                cin.clear(); // ���� �÷��׸� �ʱ�ȭ
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �߸��� �Է��� ����
                return; // ���� �޽��� ��� �Ǵ� �ٸ� ó��
            }
            else{
                break;
            }
        }while(1);

        if(temp>80 || temp<1) return;
        i=temp-1;
    }
}
void CollisionVectorStats::view_stats(){
    string temp;
    //this->stats_processing();
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      ���� ū ���Ͱ� ����     ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��    index["<<"i-1"<<"] x: "<< v[max_differene_index-1].get_x() << ", y: " << v[max_differene_index-1].get_y() <<", z: "<< v[max_differene_index-1].get_z() << endl;
    cout << "    ��    index["<<"i"<<"] x: "<< v[max_differene_index].get_x() << ", y: " << v[max_differene_index].get_y() <<", z: "<< v[max_differene_index].get_z() << endl;
    cout << "    ��    �� ���Ͱ� ����: "<< v_sub.get_vector_value() <<"   ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��     �ƹ� ���ڳ� �Է��ϼ���   ��" << endl;
    cout << "    ��      >>                      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
    cin>>temp;
}
void CollisionVectorStats::stats_processing(){
    int i;
    MyVector temp;
    for(i=1;i<80;i++){ // ù��° ���� �� ���Ͱ��� ����
        cout << v[i-1].get_vector_value() << " " << v[i].get_vector_value() << endl;
        temp=v[i]-v[i-1];
        if(temp.get_vector_value()>v_sub.get_vector_value()){//���ݲ� �� ũ��
            max_differene_index=i;
        }
        cout << temp.get_vector_value() << endl;
        cout << max_differene_index<< endl;
    }
    // cin>>i;
}
void CollisionVectorStats::save(){
    ofstream file;
	cout << fixed;
	cout.precision(2);

    file.open("result.txt");
    file << "flie name: " << data_file_name << endl << endl;
    // file << " height �ִ�: " << record_lists[s_i.height_max_index].height << ", index: " << s_i.height_max_index << endl;
    // file << " height �ּڰ�: " << record_lists[s_i.height_min_index].height << ", index: " << s_i.height_min_index << endl;
    // file << " horizontal �ִ�: " << record_lists[s_i.horizontal_max_index].horizontal << ", index: " << s_i.horizontal_max_index << endl;
    // file << " horizontal �ּڰ�: " << record_lists[s_i.horizontal_min_index].horizontal << ", index: " << s_i.horizontal_min_index << endl;
    // file << " vertical �ִ�: " << record_lists[s_i.vertical_max_index].height << ", index: " << s_i.vertical_max_index << endl;
    // file << " vertical �ּڰ�: " << record_lists[s_i.vertical_min_index].height << ", index: " << s_i.vertical_min_index << endl;

    view_save();
}
void CollisionVectorStats::view_save(){
    string temp;
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��          txt���Ϸ�           ��" << endl;
    cout << "    ��       ����Ǿ����ϴ�.        ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��     �ƹ� ���ڳ� �Է��ϼ���   ��" << endl;
    cout << "    ��      >>                      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
    cin>>temp;
}
void CollisionVectorStats::exit(){
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      ��� ó�� ���α׷�      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      1. ������ ��ȸ          ��" << endl;
    cout << "    ��      2. ��� ��ȸ            ��" << endl;
    cout << "    ��      3. ����                 ��" << endl;
    cout << "    ��      4. ����                 ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      >> �����մϴ�.          ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl << endl;
}
