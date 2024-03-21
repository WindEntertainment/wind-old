using System;
using System.Runtime.InteropServices;

namespace Scripts
{
  public static class Lib2
  {
    private static int s_CallCount = 1;

    [StructLayout(LayoutKind.Sequential)]
    public struct LibArgs
    {
      public IntPtr Message;
      public int Number;
    }

    public static int Hello(IntPtr arg, int argLength)
    {
      if (argLength < System.Runtime.InteropServices.Marshal.SizeOf(typeof(LibArgs)))
      {
        return 1;
      }

      LibArgs libArgs = Marshal.PtrToStructure<LibArgs>(arg);
      Console.WriteLine($"Hello, world! from {nameof(Lib2)} [count: {s_CallCount++}]");
      PrintLibArgs(libArgs);
      return 0;
    }

    public static int HelloAgain(IntPtr arg, int argLength)
    {
      if (argLength < System.Runtime.InteropServices.Marshal.SizeOf(typeof(LibArgs)))
      {
        return 1;
      }

      LibArgs libArgs = Marshal.PtrToStructure<LibArgs>(arg);
      Console.WriteLine($"Hello again, world! from {nameof(Lib2)} [count: {s_CallCount++}]");
      PrintLibArgs(libArgs);
      return 0;
    }

    public delegate void CustomEntryPointDelegate(LibArgs libArgs);
    public static void CustomEntryPoint(LibArgs libArgs)
    {
      Console.WriteLine($"Hello, world! from {nameof(CustomEntryPoint)} in {nameof(Lib2)}");
      PrintLibArgs(libArgs);
    }

    [UnmanagedCallersOnly]
    public static void CustomEntryPointUnmanagedCallersOnly(LibArgs libArgs)
    {
      Console.WriteLine($"Hello, world! from {nameof(CustomEntryPointUnmanagedCallersOnly)} in {nameof(Lib2)}");
      PrintLibArgs(libArgs);
    }

    private static void PrintLibArgs(LibArgs libArgs)
    {
      string message = RuntimeInformation.IsOSPlatform(OSPlatform.Windows)
          ? Marshal.PtrToStringUni(libArgs.Message)
          : Marshal.PtrToStringUTF8(libArgs.Message);

      Console.WriteLine($"-- message: {message}");
      Console.WriteLine($"-- number: {libArgs.Number}");
    }
  }
}
