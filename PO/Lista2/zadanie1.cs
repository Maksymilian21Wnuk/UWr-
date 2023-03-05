
using System.Security.Cryptography.X509Certificates;

class Constants
{
    public static readonly int ERROR = -1;
    public static readonly int INT_SIZE = (int)Math.Pow(2, 31);
}

class Functions
{
    public static bool is_prime(int x)
    {
        for (int i = 2; i < Math.Sqrt(x) + 1; i++) {
            if (x == 2) return true;
            if (x % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}

class IntStream{
    protected int n;
    protected bool EOS;

    public IntStream()
    {
        n = 0;
        EOS = false;
    }

    public int next()
    {
        if (EOS == true)
        {
            Console.WriteLine("ERROR, the stream has finished.\n");
            return Constants.ERROR;
        }
        return n++;
    }
    public void reset()
    {
        n = 0;
    }
    public void eos()
    {
        EOS = true;
    }

}

class PrimeStream : IntStream
{
    // n = 1, first number to return is 2
    public PrimeStream()
    {
        n = 1;
    }

    public int next()
    {
        n += 1;
        while (!Functions.is_prime(n))
        {
            n += 1;
            if (n == Constants.INT_SIZE)
            {
                EOS |= true;
            }
        }
        return n;
    }
}


class RandomStream : IntStream
{
    public RandomStream()
    {
        EOS = false;
    }

    public int next()
    {
        Random r = new Random();
        return r.Next();
    }
}

class RandomWordStream{
    protected PrimeStream prime_n;

    public RandomWordStream()
    {
        prime_n = new PrimeStream();
    }

    public string next()
    {
        string s = "";
        int size = prime_n.next();
        RandomStream random = new RandomStream();
        for (int i = 0; i < size; i++)
        {
            s += (char)(random.next() % 60 + 60); // pseudo random, 120 modulo
        }
        return s;

    }

}


class Program
{
    static void Main()
    {
        IntStream s = new IntStream();
        Console.WriteLine(s.next());
        Console.WriteLine(s.next());
        Console.WriteLine(s.next());
        s.reset();
        Console.WriteLine(s.next());
        Console.WriteLine(s.next());

        Console.WriteLine("***");

        PrimeStream p = new PrimeStream();
        Console.WriteLine(p.next());
        Console.WriteLine(p.next());
        Console.WriteLine(p.next());
        Console.WriteLine(p.next());

        Console.WriteLine("***");

        RandomStream r = new RandomStream();
        Console.WriteLine(r.next());
        Console.WriteLine(r.next());
        Console.WriteLine(r.next());
        Console.WriteLine(r.next());
        Console.WriteLine(r.next());

        RandomWordStream w = new RandomWordStream();
        Console.WriteLine(w.next());
        Console.WriteLine(w.next());
        Console.WriteLine(w.next());
        Console.WriteLine(w.next());
    }
}