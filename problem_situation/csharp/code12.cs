// C# Program to Find Sum of Digits of a Number using Recursion

using System;
class program
{
    public static void Main()
{
    int num, result;
    pro pg = new pro();
    Console.WriteLine("Enter the Number : ");
    num=int.Parse(Console.ReadLine());
    result =pg.sum(num);
    Console.WriteLine("Sum of Digits in {0} is {1}", num, result);
    Console.ReadLine();
}
}
class pro
{
    public int sum(int num)
    {
        if (num != 0)
        {
            return (num % 10 + sum(num / 10));
        }
        else
        {
            return 0;
        }
    }
}