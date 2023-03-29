using System;

namespace Zadanie4
{
    class MyVector
    {
        private float[] values;
        private int size;

        public MyVector(int size)
        {
            values = new float[size];
            this.size = size;
        }

        public MyVector(float[] values)
        {
            this.values = values;
            this.size = values.Length;
        }

        // method for printing values of vector
        public void Print()
        {
            for (int i = 0; i < size; i++)
            {
                Console.WriteLine(values[i]);
            }
            Console.WriteLine("***");
        }


        // getter of size
        public int Get_size()
        {
            return size;
        }

        // function to set idx of vector to value
        public void Set_idx(int idx, float val)
        {
            values[idx] = val;
        }

        // getter for idx of value
        public float Get_idx(int idx)
        {
            return values[idx];
        }

        public static MyVector operator +(MyVector v1, MyVector v2)
        {
            if (v1.Get_size() != v2.Get_size())
            {
                throw new ArgumentException("different sizes\n");
            }

            MyVector new_vec = new MyVector(v1.Get_size());
            float temp_val;

            for (int i = 0; i < v1.Get_size(); i++)
            {
                temp_val = v1.Get_idx(i) + v2.Get_idx(i);
                new_vec.Set_idx(i, temp_val);
            }

            return new_vec;
        }

        // dot product of two given vectors
        public static float operator *(MyVector v1, MyVector v2)
        {
            float dot_product = 0;
            if (v1.Get_size() != v2.Get_size())
            {
                throw new ArgumentException("different sizes\n");
            }

            for (int i = 0; i < v1.Get_size(); i++)
            {
                dot_product += v1.Get_idx(i) + v2.Get_idx(i);
            }

            return dot_product;
        }

        // scalar multiplication *
        public static MyVector operator *(MyVector v, float scalar)
        {
            MyVector v_new = new MyVector(v.Get_size());
            for (int i = 0; i < v.Get_size(); i++)
            {
                v_new.Set_idx(i, v.Get_idx(i) * scalar);
            }

            return v_new;
        }

        // method for calculating vector norm
        // using overloaded operator * between
        // classes vector, * is used to
        // acquire the square of vector
        public float norm()
        {
            float res = this * this;
            return (float)Math.Sqrt((double)res);
        }

    }

    class Program
    {
        static void Main()
        {
            float[] vals1 = { 1, 2, 3, 4 };
            MyVector v1 = new MyVector(vals1);
            v1.Print();

            float[] vals2 = { 3, 3, 2, 2 };
            MyVector v2 = new MyVector(vals2);
            v2.Print();



            MyVector v3 = v1 + v2;
            v3.Print();

            float dot_prod = v1 * v2;
            Console.WriteLine(dot_prod);
            Console.WriteLine("***");

            MyVector v4 = v3 * 1000;
            v4.Print();

            float[] ones = { 1, 1, 1, 1, 1 };
            MyVector v_one = new MyVector(ones);
            Console.WriteLine(v_one.norm());

        }

    }


}
