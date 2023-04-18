// C# Program to Perform Unboxing Operation

using System;
class sample
{
    int data;
    void insert(object x)
    {
        data = (int)x * 5;
    }
    object delete()
    {
        data=0;
        return (object)data;
    }
    public static void Main()
    {
        sample s = new sample();
        s.insert(10);
        Console.WriteLine("Data : {0}", s.data);
        Console.WriteLine("Data : {0}", s.delete());
        Console.ReadLine();
    }
}