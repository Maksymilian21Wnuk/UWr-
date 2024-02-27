#include "util.hpp"


using namespace std;


int main(int argc, char *argv[]){

    Program *p = new Program(argv, argc);
    p->run();

    return 0;
}