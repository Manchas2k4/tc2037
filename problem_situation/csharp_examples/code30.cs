// C# Program to Illustrate the use of Conditional Logical Operator

using System;
public class Program
{
    static void Main()
    {
        int age;
        Console.WriteLine("Enter the Age :");
        age=int.Parse(Console.ReadLine());
        bool adult = age >= 18 ? true : false;
        Console.WriteLine("Adult : {0}", adult);
        Console.Read();
    }
}