// C# Program to Find the Sum of first 50 Natural Numbers using For Loop

using System;
class program
{
    public static void Main()
    {
        int num, sum = 0;
        for (num = 1; num <= 50; num++)
        {
            sum = sum + num;
        }
        Console.WriteLine("Sum = {0}", sum);
       Console.ReadLine();
    }
}