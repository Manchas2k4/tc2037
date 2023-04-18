// C# Program to Display Absolute value of a Number

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
 
namespace example
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            int num;
            Console.Write("Enter a number:");
            num = Convert.ToInt32(Console.ReadLine());
            if (num < 0)
            {
                num = num * -1;
            }
 
            Console.WriteLine("Absolute value : " + num);
            Console.ReadLine();
        }
    }
}