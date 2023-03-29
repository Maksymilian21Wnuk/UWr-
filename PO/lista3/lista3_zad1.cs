
namespace Zadanie1
{
    public class MyList<T>
    {
        class Item
        {
            public T val;
            public Item next;
            public Item prev;
            public Item(T el)
            {
                next = null;
                prev = null;
                val = el;
            }
        }

        Item start;
        Item end;

        public MyList()
        {
            start = null;
        }

        public bool is_empty()
        {
            return start == null;
        }

        public void add_first(T val)
        {
            if (start == null)
            {
                start = new Item(val);
                end = new Item(val);
                start.next = end;
                end.prev = start;
            }
            else
            {
                start.prev = new Item(val);
                start.prev.next = start;
                start = start.prev;
            }


        }

        public T pop_front()
        {
            if (this.is_empty())
            {
                throw new Exception("empty list\n");
            }
            else
            {
                T val = start.val;
                start = start.next;
                start.prev = null;
                if (start.next == null)
                {
                    start = null;
                    end = null;
                }
                return val;
            }
        }

        public void push_back(T val)
        {
            if (start == null)
            {
                start = new Item(val);
                end = new Item(val);
                start.next = end;
                end.prev = start;
            }
            else
            {
                end.next = new Item(val);
                end.next.prev = end;
                end = end.next;
            }


        }

        public T pop_back()
        {
            if (this.is_empty())
            {
                throw new Exception("Empty\n");
            }
            else
            {
                T val = end.val;
                end = end.prev;
                end.next = null;
                if (end.prev == null)
                {
                    end = null;
                    start = null;
                }
                return val;
            }
        }


    }

    class Program
    {
        public static void Main()
        {
            MyList<int> l = new MyList<int>();

            // test if order is still correct
            l.push_back(1);
            l.add_first(2);
            l.add_first(3);
            Console.WriteLine(l.pop_front());
            Console.WriteLine(l.pop_back());
            Console.WriteLine(l.pop_front());
            // test if returns true on empty
            Console.WriteLine(l.is_empty());

            l.push_back(1);
            l.pop_front();
            Console.WriteLine(l.is_empty());
            l.add_first(2);
            l.pop_back();
            Console.WriteLine(l.is_empty());

            // various tests

            l.add_first(1);
            l.add_first(3);
            l.push_back(5);
            l.push_back(10);
            Console.WriteLine(l.pop_front());
            Console.WriteLine(l.pop_back());
            Console.WriteLine(l.pop_front());
            Console.WriteLine(l.pop_front());
        }

    }

}