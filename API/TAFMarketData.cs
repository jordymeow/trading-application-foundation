using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Meow.FR.TAF.API
{
    public class TAFMarketData
    {
        public string Ticker;
        public DateTime UpdateDate;

        public TAFMarketData(string ticker, DateTime updateDate)
        {
            Ticker = ticker;
            UpdateDate = updateDate;
        }
    }
}
