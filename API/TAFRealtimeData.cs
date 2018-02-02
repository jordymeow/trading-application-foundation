using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Meow.FR.TAF.API
{
    public class TAFRealtimeData : TAFMarketData
    {
        public Nullable<double> Open;
        public Nullable<double> High;
        public Nullable<double> Low;
        public Nullable<double> Volume;
        public Nullable<double> Last;
        public Nullable<double> Bid;
        public Nullable<double> Ask;
        public Nullable<double> Change;

        public TAFRealtimeData(string ticker, DateTime updateDate, Nullable<double> last, Nullable<double> high,
            Nullable<double> low, Nullable<double> volume, Nullable<double> open, Nullable<double> change, 
            Nullable<double> bid, Nullable<double> ask)
            : base(ticker, updateDate)
        {
            Last = last;
            High = high;
            Low = low;
            Volume = volume;
            Open = open;
            Change = change;
            Bid = bid;
            Ask = ask;
        }

        public override string ToString()
        {
            return Ticker + " (" + UpdateDate.ToShortDateString() + "): " + Last.ToString();
        }
    }
}
