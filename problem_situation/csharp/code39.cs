// C# Program to Print all the Armstrong Numbers from 1 to 1000

using System;
class Program
{
    static void Main()
    {
        int a, b, c, d;
        for (int i = 1; i <= 1000; i++)
        {
            a = i / 100;
            b = (i - a * 100) / 10;
            c = (i - a * 100 - b * 10);
            d = a * a * a + b * b * b + c * c * c;
            if (i == d)
            {
                System.Console.WriteLine("{0}", i);
            }
        } 
        Console.Read();
    }
}