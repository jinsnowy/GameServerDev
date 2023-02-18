using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            var LeEncoding = new UnicodeEncoding(false, true);
            var BeEncoding = new UnicodeEncoding(true, true);
            string message = "안녕하세요";

            var bytesCount1 = LeEncoding.GetByteCount(message.ToCharArray(), 0, message.Length);
            var bytesCount2 = BeEncoding.GetByteCount(message.ToCharArray(), 0, message.Length);
            var bytes1 = LeEncoding.GetBytes(message.ToCharArray());
            var bytes2 = BeEncoding.GetBytes(message.ToCharArray());
            var bom1 = LeEncoding.GetPreamble();
            var bom2 = BeEncoding.GetPreamble();

            using (var ms = new MemoryStream())
            {
                using (var sw = new StreamWriter(ms, LeEncoding))
                {
                    sw.Write(message);
                    sw.Flush();

                    var data = ms.ToArray();
                    var size = ms.Length;

                    Console.WriteLine($"LittleEndian Write {size} bytes");
                    PrintBuffer(data, size);
                }
            
            }

            using (var ms = new MemoryStream())
            {
                using (var sw = new StreamWriter(ms, BeEncoding))
                {
                    sw.Write(message);
                    sw.Flush();

                    var data = ms.ToArray();
                    var size = ms.Length;

                    Console.WriteLine($"BigEndian Write {size} bytes");
                    PrintBuffer(data, size);
                }
            }

            Console.ReadLine();
        }

        static void PrintBuffer(byte[] data, long length)
        {
            for (long i = 0; i < length; ++i) {
                Console.Write($"{data[i]} ");
            }
            Console.WriteLine();
        }
    }
}
