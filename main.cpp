#include "CollisionVectorStats.h"
//충돌 실험 통계처리 시스템
/////////파일 읽기로 변경

using namespace std;
int main(int argc, char** argv){
    int num;
    CollisionVectorStats p1;
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
    cout<< argv[1] << argc << endl;
    while(1){
        system("cls");
        p1.view_title();

        do{
            cin>>num;
            if (cin.fail()) { // 예외처리
                cin.clear(); // 에러 플래그를 초기화
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // 잘못된 입력을 무시
                continue;
            }
            else{
                break;
            }
        }while(1);

        switch (num){
        case 1: p1.view_data_list();
            break;
        case 2: p1.view_stats();
            break;
        case 3: p1.save();
            break;
        case 4: p1.exit();
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}