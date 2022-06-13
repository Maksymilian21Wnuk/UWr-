#include <string>
#include <map>
#include <vector>



class Symbol{
    private:
        std::string sym_type;
        double val;
    public:
        Symbol();
        virtual std::string type();
        virtual double get_val();
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
        bool unary = false;
        std::string sym_type;
    public:
        Funkcja(std::string s);
        std::string type() override;

};

class Binarna : public Funkcja{
    private:
        double (*bin_name)(double, double);
    public:
        auto get_foo();
};

class Unarna : public Funkcja{
    private:
        double (*un_name)(double);
    public:
         auto get_foo();
};




bool is_double(const std::string& s);

class Eval{
    public:
        void run(void);
};