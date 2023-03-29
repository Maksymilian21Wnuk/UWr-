import java.util.Hashtable;

/* Maksymilian Wnuk 330572
 * Lista 5 zadanie 2
 * Zadanie kompilowane poleceniem javac zad2.java oraz javac Expression.java,
 * następnie uruchamiane poleceniem java zad2
 */

public interface Expression
{
    int evaluate();
    String toString();
}

class Variable implements Expression
{
    String name;
    static Hashtable<String, Integer> var_map;

    public Variable(String name){
        this.name = name;
    }

    public int evaluate(){
        try {
            return var_map.get(this.name);                 
        } 
        // catch the case when hashtable
        // was not initialized in main program
        catch (NullPointerException e) {
            System.out.print("Hashtable was not initialized\n");
            System.exit(1);
            return 1;
            }

    }

    public String toString(){
        return name;
    }
}

class Const implements Expression
{
    int value;

    public Const(int value){
        this.value = value;
    }

    public int evaluate(){
        return this.value;
    }

    public String toString(){
        return Integer.toString(value);
    }
}

class Add implements Expression
{
    Expression left;
    Expression right;

    public Add(Expression l, Expression r){
        this.left = l;
        this.right = r;
    }

    public int evaluate(){
        return left.evaluate() + right.evaluate();
    }

    public String toString(){
        return "(" + left.toString() + "+" + right.toString() + ")";
    }
}

class Sub implements Expression
{
    Expression left;
    Expression right;

    public Sub(Expression l, Expression r){
        this.left = l;
        this.right = r;
    }

    public int evaluate(){
        return left.evaluate() - right.evaluate();
    }

    public String toString(){
        return "(" + left.toString() + "-" + right.toString() + ")";
    }
}

class Div implements Expression
{
    Expression left;
    Expression right;

    public Div(Expression l, Expression r){
        this.left = l;
        this.right = r;
    }

    public int evaluate() throws ArithmeticException
    {
        // case when dividing by 0
        if (right.evaluate() == 0){
            throw new ArithmeticException("Dividing by 0\n");
        }
        return left.evaluate() / right.evaluate();
    }

    public String toString(){
        return "(" + left.toString() + "/" + right.toString() + ")";
    }
}

class Mul implements Expression
{
    Expression left;
    Expression right;

    public Mul(Expression l, Expression r){
        this.left = l;
        this.right = r;
    }

    public int evaluate(){
        return left.evaluate() * right.evaluate();
    }

    public String toString(){
        return "(" + left.toString() + "*" + right.toString() + ")";
    }
}
