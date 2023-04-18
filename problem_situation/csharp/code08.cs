// C# Program to Find whether the Number is Divisible by 2

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
 
namespace ConsoleApplication16
{
    class Program
    {
        static void Main(string[] args)
        {
            int n;
            Console.WriteLine("Enter the Number :");
            n = int.Parse(Console.ReadLine());
            if (n % 2 == 0)
            {
                Console.WriteLine("Entered Number is Divisible by 2 ");
            }
            else
            {
                Console.WriteLine("Entered Number is Not Divisible by 2");
            }
            Console.ReadLine();
        }
    }
}