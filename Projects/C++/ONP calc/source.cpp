#include "headers.hpp"
#include "sourcefoos.cpp"
#include <string>
#include <iostream>
#include <math.h>


using namespace std;




Stala::Stala(string s){
    sym_type = "Stala";
    double values[] = {2,718281828, 3,141592653589, 1,618033988750};
    string value_names[] = {"e", "pi", "fi"};

    for (int i = 0; i < 3; i++){
        if (s == value_names[i]){
            stala_val = values[i];
            return;
        }
    }
    cerr << "Wrong argument" << endl;
}

Operand::Operand(string s){
    sym_type = "Operand";
    op_val = stod(s);
}

Zmienna::Zmienna(string s){
    sym_type = "Zmienna";
    z_name = s;
}

Funkcja::Funkcja(string s){
    sym_type = "Funkcja";

    for (int i = 0; i < 5; i++){
        if (bnames[i] == s){ // array with binary foos
            unary = false;
            foo_name = bnames[i];
            foo_index = i;
            return;
        }
    }
    for (int i = 0; i < 6; i++){ // array with unary foos
        if (unames[i] == s){
            unary = true;
            foo_name = unames[i];
            foo_index = i;
            return;
        }
    }
    cerr << "Wrong input" << endl;
}




string Funkcja::type(){
    return sym_type;
}

string Stala::type(){
    return sym_type;
}

string Zmienna::type(){
    return sym_type;
}

string Operand::type(){
    return sym_type;
}



string Symbol::type(){
    return sym_type;
}

Symbol::Symbol(){
    sym_type = "Symbol";
    val = 42;
}

double Symbol::get_val(){
    return val;
}

double Stala::get_val(){
    return stala_val;
}

double Operand::get_val(){
    return op_val;
}
