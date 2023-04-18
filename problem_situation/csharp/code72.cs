// C# Program to Print Binary Equivalent of an Integer using Recursion

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
class Program
{
    public static void Main(string[] args)
    {
        int num;
        prog pg = new prog();
        Console.WriteLine("Enter a decimal number: ");
        num = int.Parse(Console.ReadLine());
        Console.WriteLine("The binary equivalent of num is :");
        pg.binaryconversion(num);
        Console.ReadLine();
    }
}
public class prog
{
    public int binaryconversion(int num)
    {
        int bin;
        if (num != 0)
        {
            bin = (num % 2) + 10 * binaryconversion(num / 2);
            Console.Write(bin);
            return 0;
        }
        else
        {
            return 0;
        }
 
    }
}