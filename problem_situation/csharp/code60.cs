// C# Program to Print all the Multiples of 17 which are Less than 100

using System;
class program
{
    public static void Main()
    {
        int a,i;
        Console.WriteLine("Multiples of 17 are : ");
        for (i = 1; i < 100; i++)
        {
            a = i % 17;
            if (a == 0)
            {
                Console.WriteLine(i);
            }
        }
        Console.Read();
    }
}