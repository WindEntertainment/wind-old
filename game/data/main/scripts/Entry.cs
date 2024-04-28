using System;
using System.Runtime.InteropServices;

namespace Wind {
    public static class Game {
        [DllImport("libwind-core.so")]
        public static extern void wind_Window_init();

        public static int Entry(IntPtr arg, int argLength) {
            Console.WriteLine("Hello, World!");
            wind_Window_init();
            Console.WriteLine("WOW");
            return 0;
        }
    }
}
