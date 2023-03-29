import java.util.Hashtable;

/* Maksymilian Wnuk 330572
 * Lista 5 zadanie 2
 * Zadanie kompilowane poleceniem javac zad2.java oraz javac Expression.java,
 * następnie uruchamiane poleceniem java zad2
 */


public class zad2{
    public static void main(String[] s){        
        Hashtable<String, Integer> var_map = new Hashtable<String, Integer>();
        var_map.put("x", 10);
        var_map.put("y", 100);
        var_map.put("z", -1);

        System.out.println("x = 10");
        System.out.println("y = 100");   
        System.out.println("z = -1");   
        System.out.println("***"); 

        Variable.var_map = var_map;
        
        System.out.println("\nNormal tests with variables and constants: \n");

        Expression e1 = new Add(new Const(20), new Variable("x"));
        System.out.println(e1.toString());
        System.out.println(e1.evaluate());

        Expression e2 = new Div(new Variable("y"), 
                                new Add(new Const(99), 
                                    new Variable("z")));

        System.out.println(e2.toString());
        System.out.println(e2.evaluate());

        Expression e3 = new Add(e2, e1);

        System.out.println(e3.toString());
        System.out.println(e3.evaluate());

        System.out.println("\n div by 0 test with try catch: \n");
        Expression zero_div = new Div(new Const(42), 
                                new Sub(new Const(42), new Const(42)));
        
        System.out.println(zero_div.toString());
        try {
            System.out.println(zero_div.evaluate());
        } catch (Exception arithmException) {
            System.out.println("Handled it...");
        }
        

        }

}
