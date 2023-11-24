#include "CollisionVectorStats.h"
//충돌 실험 통계처리 시스템

using namespace std;
int main(int argc, char** argv){
    int num;
    if(argc<2){
        cout << "파일 이름을 인수로 넣어주세요." << endl;
        return 0;
    }

    for(int i=1; i<argc; i++){
        CollisionVectorStats *p = new CollisionVectorStats;

        if(p->load_file_name(argv[i])){
            cout << "failed to open file" << endl;
            return 0;
        }
        
        if(p->load_field_name()){
            cout << "field name load error" << endl;
            return 0;
        }
        if(p->load_record()){
            cout << "record load error" << endl;
        }
        p->stats_processing();

        p->stats_processing();
        p->save();

        cout << "Processing of "<< p->get_filename() << " file completed" << endl;
        cout << "Check the "<< p->get_file_create_time() << "_result.txt file" << endl << endl;

        delete p;
    }
    return 0;
}