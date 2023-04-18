// C# Program to Accept the Height of a Person & Categorize as  Tall, Dwarf or Average

using System;
class program
{
    public static void Main()
    {
        float height;
        Console.WriteLine("Enter  the Height (in centimeters) \n");
        height = int.Parse(Console.ReadLine());
        if (height < 150.0)
            Console.WriteLine("Dwarf \n");
        else if ((height >= 150.0) && (height <= 165.0))
            Console.WriteLine(" Average Height \n");
        else if ((height >= 165.0) && (height <= 195.0))
            Console.WriteLine("Taller \n");
        else
            Console.WriteLine("Abnormal height \n");
    }
}