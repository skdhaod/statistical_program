#include <iostream>
#include <windows.h> //화면 clear, 콘솔 커서 위치 변경
#include <iomanip>//cout 조작자 사용.. 
#include <fstream>//txt 파일 접근
using namespace std;
//충돌 실험 통계처리 시스템
/////////파일 읽기로 변경 // 인터페이스 클래스도 만들어버려야징.....

//클래스 정의
class blackbox{
    protected:
    int smash_direction;//충돌 방향
    enum direction{FRONT=1, BACK, LEFT, RIGHT};
    float smash_speed;//충돌 속력
    bool detection_status;//감지 여부

    public:
    static float cycle_num;//지금까지 반복한 횟수
    blackbox(){}
    
};

class bb_test: public blackbox{ // 퍼블릭은 is-a관계일때 쓰는거임 바꾸자
    bb_test* next;
    public:
    bb_test():blackbox(){cycle_num++;next=NULL;}

    void get_node();//새 테이터 추가

    void title();//타이틀 화면
    
    void add_data();//데이터 추가 화면
    
    void view();//조회
    void view_data_list();//데이터 목록 조회
    void view_stats();//통계 조회

    void save();//txt로 저장
    void exit();
    public:
};
float blackbox::cycle_num=-1; //헤드노드 만들면 0이 되어야함


//main 함수
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

//함수 구현
void bb_test::get_node(){
    //노드 추가
    bb_test* ptr=this;
    bb_test* newnode=new bb_test;
        newnode->add_data();
    if(this->next==NULL){
        this->next = newnode;
    }else{
        while(ptr->next) // tail 노드 찾기
            ptr=ptr->next;
        ptr->next=newnode;
    }
}

void bb_test::title(){
    system("cls");
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      통계 처리 프로그램      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      1. 새 데이터 추가       │" << endl;
    cout << "    │      2. 조회                 │" << endl;
    cout << "    │      3. 저장                 │" << endl;
    cout << "    │      4. 종료                 │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      >>                      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
}
void bb_test::add_data(){
    system("cls");
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │         데이터 추가          │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │     1-앞 2-뒤 3-좌 4-우      │" << endl;
    cout << "    │     충돌 방향 >>             │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │     충돌 속력 >>             │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │     감지 여부(0, 1) >>       │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl;
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
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │             조회             │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      1. 데이터 목록          │" << endl;
    cout << "    │      2. 통계                 │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      >>                      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl;
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
            case FRONT: temp="앞";
                break;
            case BACK: temp="뒤";
                break;
            case LEFT: temp="좌";
                break;
            case RIGHT: temp="우";
                break;
            default: temp="??";
                break;
        }
        system("cls");
        cout << endl << "    ┌──────────────────────────────┐" << endl;
        cout << "    │                              │" << endl;
        cout << "    │     데이터 목록 조회         │" << endl;
        cout << "    │                              │" << endl;
        cout << "    │      충돌 방향: " << setw(2) <<right <<  temp << "           │" << endl;
        cout << "    │      충돌 속력: " << setw(4) <<left <<  ptr->smash_speed << "         │" << endl;
        cout << "    │      감지 여부: " <<  ptr->detection_status << "            │" << endl;
        cout << "    │                              │" << endl;
        cout << "    │     1-다음 데이터 2-홈 화면  │" << endl;
        cout << "    │      >>                      │" << endl;
        cout << "    │                              │" << endl;
        cout << "    └──────────────────────────────┘" << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
        cin>>temp;
        if(temp=="2") break;

    }
    
}
void bb_test::view_stats(){///////////////통계처리랑 출력 분리하기 // 통계처리부분을 추상화하기?
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

    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │          통계 조회           │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      평균 속력 : "<< setw(4) <<right << avg<<"        │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      감지 확률 : "<< setw(6) <<right << percent <<"%     │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      아무 글자나 입력하세요  │" << endl;
    cout << "    │      >>                      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl;
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
            case FRONT: temp="앞";
                break;
            case BACK: temp="뒤";
                break;
            case LEFT: temp="좌";
                break;
            case RIGHT: temp="우";
                break;
            default: temp="??";
                break;
        }
        file << "────" << i+1 << "번 데이터────" << endl;
        file << "충돌 방향: " <<  temp << endl;
        file << "충돌 속력: " <<  ptr->smash_speed << endl;
        file << "감지 여부: " <<  ptr->detection_status << endl << endl;

        //통계 계산
        avg+=ptr->smash_speed;

        
        if(ptr->detection_status) percent++;
        ptr=ptr->next;
        file.close();
    }
    avg/=cycle_num;
    percent=percent*100/cycle_num;
    file << "──────통계──────" << endl;
    file << "평균 속력 : "<< avg<<"" << endl;
    file << "감지 확률 : "<< percent <<"%" << endl;

    system("cls");
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │          txt파일로           │" << endl;
    cout << "    │       저장되었습니다.        │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      아무 글자나 입력하세요  │" << endl;
    cout << "    │      >>                      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {14, 10});
    cin>>temp;
}
void bb_test::exit(){
    system("cls");
    cout << endl << "    ┌──────────────────────────────┐" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      통계 처리 프로그램      │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      1. 새 데이터 추가       │" << endl;
    cout << "    │      2. 조회                 │" << endl;
    cout << "    │      3. 저장                 │" << endl;
    cout << "    │      4. 종료                 │" << endl;
    cout << "    │                              │" << endl;
    cout << "    │      >> 감사합니다.          │" << endl;
    cout << "    │                              │" << endl;
    cout << "    └──────────────────────────────┘" << endl << endl;
    bb_test *temp=this->next;
    bb_test *nexttemp=temp->next;
    for(int i=0; i<cycle_num; i++){
        delete temp;
        temp=nexttemp;
        nexttemp=temp->next;
    }
}
