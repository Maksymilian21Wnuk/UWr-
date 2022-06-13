#include <string>
#include <map>
#include <vector>


typedef double (*UnFoo)(double v);
typedef double (*BinFoo)(double v1, double v2);



BinFoo bf[] = {add, sub, mul, div, mod};            
string bnames[] = {"+", "-", "*", "/", "%"};
UnFoo uf[]  = {abs, floor, cos, sin, atan, exp};    
string unames[] = {"abs", "floor", "cos", "sin", "atan", "exp"};


class Symbol{
    private:
        std::string sym_type;
        double val;
    public:
        Symbol();
        virtual std::string type();
        virtual double get_val();
        virtual std::string get_name();
        virtual bool get_arity();
        virtual int get_index();
};

class Stala : public Symbol{
    private:
        double stala_val;
        std::string sym_type;
    public:
        Stala(std::string s);
        std::string type() override;
        double get_val() override;
};

class Operand : public Symbol{
    private:
        double op_val;
        std::string sym_type;
    public:
        Operand(std::string s);
        std::string type() override;
        double get_val() override;        
};

class Zmienna : public Symbol {
    private:
        static std::map<std::string, double> z_set;
        std::string z_name;
        std::string sym_type;
    public:
        Zmienna(std::string s);
        std::string type() override;

};

class Funkcja : public Symbol{
    private:
        std::string foo_name;
        std::string sym_type;
        bool unary = false;
        int foo_index;
    public:
        Funkcja::Funkcja(std::string);
        std::string type() override;
        std::string get_name() override  {return foo_name;}
        bool get_arity() override {return unary;}
        int get_index() override {return foo_index;}
};



bool is_double(const std::string& s);

class Eval{
    public:
        void run(void);
};