using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Meow.FR.TAF.API
{
    static class TAFTools
    {
        public static byte[] ToByteArray(this string str)
        {
            System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();
            return encoding.GetBytes(str);
        }
    }
}
