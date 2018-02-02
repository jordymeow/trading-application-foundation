using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace Meow.FR.TAF.API
{
    public class TAFHistoricalData : TAFMarketData, IEnumerable<TAFHistoricalPoint>
    {
        public TAFHistoricalPeriod Period;
        public DateTime From;
        public DateTime To;
        private List<TAFHistoricalPoint> _points = new List<TAFHistoricalPoint>();

        public TAFHistoricalData(string ticker, DateTime updateDate)
            : base(ticker, updateDate)
        {
        }

        public void Add(TAFHistoricalPoint p)
        {
            _points.Add(p);
        }

        public int Count
        {
            get { return _points.Count; }
        }

        public TAFHistoricalPoint this[int c]
        {
            get { return _points[c]; }
        }

        public override string ToString()
        {
            return Ticker + " (" + From.ToShortDateString() + " to " + To.ToShortDateString() + "): " + _points.Count + " data";
        }

        public IEnumerator<TAFHistoricalPoint> GetEnumerator()
        {
            foreach (TAFHistoricalPoint p in _points)
                yield return p;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            foreach (TAFHistoricalPoint p in _points)
                yield return p;
        }
    }
}
