using System;
using System.Collections;
using System.Collections.Generic;

/*
* Maksymilian Wnuk 330572
*
* Zadanie kompilowane komendą mcs na systemie Linuxowym, w folderze
* zamieszczam plik Makefile, który komendą make 
* stworzy wykonywalny plik, jednak wymaga uprawnien 
* administratora, który nada uprawniena na wykonywanie pliku 
*
* Zadanie 2 Lista 4
*/


namespace Exercise2
{
    public class FibWords : IEnumerable<string>{
        // how many items in iterator we want
        private int count;

        // if our iterator is negative, throw an error
        public FibWords(int count){
            if (count < 1){
                throw new ArgumentException("Argument should be positive number.\n");
            }
            this.count = count;
        }

        // function that returns item of enumerator
        public IEnumerator<string> GetEnumerator(){
            string prev = "";
            string prev_prev = "";
            int position = 1;
            string cur;

            while (position <= this.count){
                if (position == 1){
                    cur = "b";
                }
                else if(position == 2){
                    cur = "a";
                }
                else{
                    cur = prev + prev_prev;
                }
                yield return cur;
                prev_prev = prev;
                prev = cur;
                position++;
            }


        }
        IEnumerator IEnumerable.GetEnumerator(){
            return GetEnumerator();
        }


    }



    // small tests for program
    public class Program{
        static void Main(){
            FibWords f = new FibWords(10);
            foreach (string s in f){
                Console.WriteLine(s);
            }
            Console.WriteLine("***");
            foreach(string s in new FibWords(1)){
                Console.WriteLine(s);
            }
            Console.WriteLine("***");
            
            foreach(string s in new FibWords(15)){
                Console.WriteLine(s);
            }

            Console.WriteLine("***");
            
            // should throw an error
            try{
                foreach(string s in new FibWords(-1)){
                    Console.WriteLine(s);
                }
            }
            catch (ArgumentException){
                Console.WriteLine("Caught an error\n");
            }
            
            
        }

    }
    
}