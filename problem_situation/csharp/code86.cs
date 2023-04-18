// C# Program to Check Whether the Given Number is a Prime number if so then Display its Largest Factor

using System;
namespace example
{
    class prime
    {
        public static void Main()
        {
            Console.Write("Enter a Number : ");
            int num;
            num = Convert.ToInt32(Console.ReadLine());
            int k;
            k = 0;
            for (int i = 1; i <= num; i++)
            {
                if (num % i == 0)
                {
                    k++;
                }
            }
            if (k == 2)
            {
                Console.WriteLine("Entered Number is a Prime Number and " + 
                                  "the Largest Factor is {0}",num);
            }
            else
            {
                Console.WriteLine("Not a Prime Number");
            }
            Console.ReadLine();
        }
    }
}