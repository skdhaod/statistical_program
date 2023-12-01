#include "CollisionVectorStats.h"
//�浹 ���� ���ó�� �ý���

using namespace std;
int main(int argc, char** argv){
    int num;
    if(argc<2){
        cout << "���� �̸��� �μ��� �־��ּ���." << endl;
        return 0;
    }

    for(int i=1; i<argc; i++){
        CollisionVectorStats *p = new CollisionVectorStats();

        if(p->load_file_name(argv[i])){
            cout << "failed to open file" << endl << endl;
            continue;
        }
        
        if(p->load_field_name()){
            cout << "field name load error" << endl << endl;
            continue;
        }
        if(p->load_record()){
            cout << "record load error" << endl << endl;
            continue;
        }

        if(p->stats_processing()){
            cout << "stats processing error" << endl << endl;
            continue;
        }
        p->save();

        cout << "Processing of "<< p->get_filename() << " file completed" << endl;
        cout << "Check the "<< p->get_file_create_time() << "_result.txt file" << endl << endl;

        delete p;
    }
    return 0;
}