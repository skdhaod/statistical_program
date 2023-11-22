#include <iostream>
#include <windows.h> //ȭ�� clear, �ܼ� Ŀ�� ��ġ ����
#include <iomanip>//cout ������ ���.. 
#include <fstream>//txt ���� ����
using namespace std;
//�浹 ���� ���ó�� �ý���
/////////���� �б�� ���� // �������̽� Ŭ������ ����������¡.....

//Ŭ���� ����
class blackbox{
    protected:
    int smash_direction;//�浹 ����
    enum direction{FRONT=1, BACK, LEFT, RIGHT};
    float smash_speed;//�浹 �ӷ�
    bool detection_status;//���� ����

    public:
    static float cycle_num;//���ݱ��� �ݺ��� Ƚ��
    blackbox(){}
    
};

class bb_test: public blackbox{ // �ۺ��� is-a�����϶� ���°��� �ٲ���
    bb_test* next;
    public:
    bb_test():blackbox(){cycle_num++;next=NULL;}

    void get_node();//�� ������ �߰�

    void title();//Ÿ��Ʋ ȭ��
    
    void add_data();//������ �߰� ȭ��
    
    void view();//��ȸ
    void view_data_list();//������ ��� ��ȸ
    void view_stats();//��� ��ȸ

    void save();//txt�� ����
    void exit();
    public:
};
float blackbox::cycle_num=-1; //����� ����� 0�� �Ǿ����


//main �Լ�
int main(){
    bb_test* b=new bb_test;
    int select=0;
    // cout << bb_test::cycle_num;
    
    while(select!=4){
        b->title();
        cin>>select;
        switch(select){
            case 1: b->get_node();
            break;

            case 2: b->view();
            break;

            case 3: b->save();
            break;

            case 4: b->exit();
            delete b;
            return 0;
            break;
        }
    }
    return 0;
}

//�Լ� ����
void bb_test::get_node(){
    //��� �߰�
    bb_test* ptr=this;
    bb_test* newnode=new bb_test;
        newnode->add_data();
    if(this->next==NULL){
        this->next = newnode;
    }else{
        while(ptr->next) // tail ��� ã��
            ptr=ptr->next;
        ptr->next=newnode;
    }
}

void bb_test::title(){
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      ��� ó�� ���α׷�      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      1. �� ������ �߰�       ��" << endl;
    cout << "    ��      2. ��ȸ                 ��" << endl;
    cout << "    ��      3. ����                 ��" << endl;
    cout << "    ��      4. ����                 ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      >>                      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
}
void bb_test::add_data(){
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��         ������ �߰�          ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��     1-�� 2-�� 3-�� 4-��      ��" << endl;
    cout << "    ��     �浹 ���� >>             ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��     �浹 �ӷ� >>             ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��     ���� ����(0, 1) >>       ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {23, 6});
    cin >> this->smash_direction;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {23, 8});
    cin >> this->smash_speed;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {29, 10});
    cin >> this->detection_status;
}
void bb_test::view(){
    int select;
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��             ��ȸ             ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      1. ������ ���          ��" << endl;
    cout << "    ��      2. ���                 ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      >>                      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
    cin >> select;
    switch (select)
    {
    case 1: this->view_data_list();
        break;
    case 2: this->view_stats();
        break;
    default:
        break;
    }

}
void bb_test::view_data_list(){
    string temp;
    bb_test *ptr=this;
    for(int i=0; i<cycle_num; i++){
        ptr=ptr->next;
        switch (ptr->smash_direction)
        {
            case FRONT: temp="��";
                break;
            case BACK: temp="��";
                break;
            case LEFT: temp="��";
                break;
            case RIGHT: temp="��";
                break;
            default: temp="??";
                break;
        }
        system("cls");
        cout << endl << "    ����������������������������������������������������������������" << endl;
        cout << "    ��                              ��" << endl;
        cout << "    ��     ������ ��� ��ȸ         ��" << endl;
        cout << "    ��                              ��" << endl;
        cout << "    ��      �浹 ����: " << setw(2) <<right <<  temp << "           ��" << endl;
        cout << "    ��      �浹 �ӷ�: " << setw(4) <<left <<  ptr->smash_speed << "         ��" << endl;
        cout << "    ��      ���� ����: " <<  ptr->detection_status << "            ��" << endl;
        cout << "    ��                              ��" << endl;
        cout << "    ��     1-���� ������ 2-Ȩ ȭ��  ��" << endl;
        cout << "    ��      >>                      ��" << endl;
        cout << "    ��                              ��" << endl;
        cout << "    ����������������������������������������������������������������" << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
        cin>>temp;
        if(temp=="2") break;

    }
    
}
void bb_test::view_stats(){///////////////���ó���� ��� �и��ϱ� // ���ó���κ��� �߻�ȭ�ϱ�?
    bb_test *ptr=this->next;
    string temp;
    float avg=0.00;
    float percent=0.00;
	cout << fixed;
	cout.precision(2);

    system("cls");
    for(int i=0; i<cycle_num; i++){
        avg+=ptr->smash_speed;
        
        if(ptr->detection_status) percent++;
        ptr=ptr->next;
    }

    avg/=cycle_num;
    percent=percent*100/cycle_num;

    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��          ��� ��ȸ           ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      ��� �ӷ� : "<< setw(4) <<right << avg<<"        ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      ���� Ȯ�� : "<< setw(6) <<right << percent <<"%     ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      �ƹ� ���ڳ� �Է��ϼ���  ��" << endl;
    cout << "    ��      >>                      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
    cin>>temp;
}
void bb_test::save(){
    bb_test *ptr=this->next;
    string temp;
    ofstream file;
    int i=0;
    float avg=0.00;
    float percent=0.00;
	cout << fixed;
	cout.precision(2);

    file.open("result.txt");
    for(;i<cycle_num; i++){
        switch (ptr->smash_direction)
        {
            case FRONT: temp="��";
                break;
            case BACK: temp="��";
                break;
            case LEFT: temp="��";
                break;
            case RIGHT: temp="��";
                break;
            default: temp="??";
                break;
        }
        file << "��������" << i+1 << "�� �����ͦ�������" << endl;
        file << "�浹 ����: " <<  temp << endl;
        file << "�浹 �ӷ�: " <<  ptr->smash_speed << endl;
        file << "���� ����: " <<  ptr->detection_status << endl << endl;

        //��� ���
        avg+=ptr->smash_speed;

        
        if(ptr->detection_status) percent++;
        ptr=ptr->next;
        file.close();
    }
    avg/=cycle_num;
    percent=percent*100/cycle_num;
    file << "��������������覡����������" << endl;
    file << "��� �ӷ� : "<< avg<<"" << endl;
    file << "���� Ȯ�� : "<< percent <<"%" << endl;

    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��          txt���Ϸ�           ��" << endl;
    cout << "    ��       ����Ǿ����ϴ�.        ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      �ƹ� ���ڳ� �Է��ϼ���  ��" << endl;
    cout << "    ��      >>                      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
    cin>>temp;
}
void bb_test::exit(){
    system("cls");
    cout << endl << "    ����������������������������������������������������������������" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      ��� ó�� ���α׷�      ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      1. �� ������ �߰�       ��" << endl;
    cout << "    ��      2. ��ȸ                 ��" << endl;
    cout << "    ��      3. ����                 ��" << endl;
    cout << "    ��      4. ����                 ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ��      >> �����մϴ�.          ��" << endl;
    cout << "    ��                              ��" << endl;
    cout << "    ����������������������������������������������������������������" << endl << endl;
    bb_test *temp=this->next;
    bb_test *nexttemp=temp->next;
    for(int i=0; i<cycle_num; i++){
        delete temp;
        temp=nexttemp;
        nexttemp=temp->next;
    }
}
