// C# Program to Find Square Root of a Given Number

using System;
using System.Text;
using System.Collections;
using System.Data;
namespace Cons
{
    public class squareroot
    {
        public static void Main()
        {
                Console.WriteLine("Enter a Number : ");
                int Number = Convert.ToInt16(Console.ReadLine());
                double SqrtNumber = Math.Sqrt(Number);
                Console.WriteLine("Square root of {0} is: {1}", Number, SqrtNumber);
                Console.ReadLine();
        }
    }
}