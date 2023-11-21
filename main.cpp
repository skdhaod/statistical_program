#include "CollisionVectorStats.h"
//충돌 실험 통계처리 시스템
/////////파일 읽기로 변경
//Tick[ms],Height[g],Horizontal[g],Vertical[g],Magnitude[g],Temperature[C],Date,Time 이중에 높이 가로세로 날짜만 처리

using namespace std;
int main(int argc, char** argv){
    int num;
    int exception_handling;
    CollisionVectorStats p1;
    ifstream file; 
    if(argc<2){
        cout << "파일 이름을 인수로 넣어주세요." << endl;
        return 0;
    }

    if(p1.load_file_name(argv[1])){
        cout << "failed to open file" << endl;
        return 0;
    }
    
    p1.load_field_name();
    p1.load_record();
    p1.stats_processing();
    // cout<< argv[1] << argc << endl;
    // while(1){
    //     system("cls");
    //     p1.view_title();
    //     cin>>num;
    //     switch (num){
    //     case 1: p1.view_data_list();
    //         break;
    //     case 2: p1.view_stats();
    //         break;
    //     case 3: p1.save();
    //         break;
    //     case 4: p1.exit(); return 0;
    //         break;
    //     default:
    //         break;
    //     }
    // }
    // return 0;
}