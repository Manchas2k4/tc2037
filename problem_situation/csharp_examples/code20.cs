// C# Program to Perform Multiplication of Exponents of Same Base

using System;
class Program
{
    static void Main()
    {
        Console.WriteLine("Enter the Base : ");
        double num = double.Parse(Console.ReadLine());
        Console.WriteLine("Enter the First Exponent :");
        double exp1 = double.Parse(Console.ReadLine());
        Console.WriteLine("Enter the Second Exponent :");
        double exp2 = double.Parse(Console.ReadLine());
        double mul;
        mul = exp1 + exp2;
        Console.WriteLine("Result is : {0}^{1} : {2}", num, mul, Math.Pow(num, mul));
        Console.ReadLine();
    }
}