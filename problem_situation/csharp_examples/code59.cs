//C# Program to Print the Sum of all the Multiples of 3 and 5

using System;
class program
{
    public static void Main()
    {
        int a, b, i, Sum = 0;
        for (i = 1; i < 100; i++)
        {
            a = i % 3;
            b = i % 5;
            if (a == 0 || b == 0)
            {
                Console.Write("{0}\t", i);
                Sum = Sum + i;
            }
        }
        Console.WriteLine("\nThe Sum of all the Multiples of 3 or 5 Below 100 : {0}", 
                          Sum);
        Console.Read();
    }
}