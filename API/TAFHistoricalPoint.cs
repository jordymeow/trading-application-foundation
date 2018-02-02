using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Meow.FR.TAF.API
{
    public class TAFHistoricalPoint
    {
        public DateTime Time { get; set; }
        public Nullable<double> Open { get; set; }
        public Nullable<double> High { get; set; }
        public Nullable<double> Low { get; set; }
        public Nullable<double> Close { get; set; }
        public Nullable<double> Volume { get; set; }

        public TAFHistoricalPoint(DateTime time, Nullable<double> open, Nullable<double> high, Nullable<double> low,
            Nullable<double> close, Nullable<double> volume)
        {
            Time = time;
            Open = open;
            High = high;
            Low = low;
            Close = close;
            Volume = volume;
        }

        public override string ToString()
        {
            return "[" + Time.ToShortDateString() + "|" + Time.ToLongTimeString() + "] " + Close.ToString();
        }
    }
}
