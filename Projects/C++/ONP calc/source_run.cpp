#include "headers.hpp"
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
#include <algorithm>
#include <typeinfo>
#include <queue>
#include <stack>



using namespace std;

queue<string> rozdziel(string s){
    queue<string> res;
    stringstream ss(s);
    string word;
    while (ss >> word) {
        res.push(word);
    }
    return res;
}

bool is_double(const string& s)
{
    try
    {
        stod(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}


bool in_vector(vector<string> vec, string comp_s){
    for (string vec_s : vec){
        if(vec_s == comp_s){
            return true;
        }
    }
    return false;
}




int evaluate(queue<Symbol> unev_vals){
    stack<Symbol> elem_stack;
    string var_type, foo_name;
    Symbol value, right, left;

    while (unev_vals.size() != 1){
        value = unev_vals.front();
        var_type = value.type();

        if (var_type == "Operand" or var_type == "Stala"){
            elem_stack.push(value);
            continue;
        }
        else{
            left = elem_stack.top();
            right = elem_stack.top();
            elem_stack.pop();
            elem_stack.pop();
            foo_name = value.get_name();
            if (value.get_arity() == true){
                elem_stack.push(Operand(uf[value.get_index()](left))); // push to stack evaluated function with left argument
                continue;
            } 
            elem_stack.push(Operand(bf[value.get_index()](left, right))); // push to stack bin foo
        }
    }
    
    return elem_stack.top().get_val();
}



queue<Symbol> parse_onp(queue<string> unparsed){
    vector<string> Stale = {"e", "fi", "pi"};
    vector<string> Funkcje = {"+", "-", "*", "/", "%", "abs", "floor", "cos", "sin", "atan", "exp"};
    queue<Symbol> result;

    while (!unparsed.empty()){
        string s = unparsed.front();
        unparsed.pop();

        if (in_vector(Stale, s)){
            result.push(Stala(s));
            continue;
        }
        else if (in_vector(Funkcje, s)){
            result.push(Funkcja(s));
            continue;
        }
        else if (is_double(s)){
            result.push(Operand(s));
            continue;
        }
        else if (s == "print"){
            continue;
        }

        cerr << "Wrong input" << endl;
    }

    return result;
}


void Eval::run(void){
    string user_inp;
    queue<string> actions;
    queue<Symbol> parsed_actions;

    cout << "Program begins: " << endl;
    getline(cin, user_inp);

    actions = rozdziel(user_inp);
    
    if (actions.front() == "print"){
        parsed_actions = parse_onp(actions);
    }

    evaluate(parsed_actions);

    return;

}