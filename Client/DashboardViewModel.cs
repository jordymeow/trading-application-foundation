using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Meow.FR.TAF.API;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;

namespace Meow.FR.TAF.Client
{
    public class DashboardViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<TAFHistoricalPoint> Data
        {
            get { return _Data; }
        }

        public ObservableCollection<TAFHistoricalPoint> _Data = new ObservableCollection<TAFHistoricalPoint>();

        public TAFConnection Server = new TAFConnection();

        public DashboardViewModel()
        {
            Server.HistoricalDataReceived += HistoricalDataReceived;
        }

        void HistoricalDataReceived(TAFHistoricalData obj)
        {
            _Data.Clear();
            foreach (TAFHistoricalPoint p in obj)
                _Data.Add(p);
            PropertyChanged.Invoke(this, new PropertyChangedEventArgs("Data"));
        }

        public void GetHistoricalData(string ticker)
        {
            Server.GetHistoricalData(ticker, DateTime.Today.Subtract(TimeSpan.FromDays(100)), DateTime.Today, TAFHistoricalPeriod.Day);
        }
    }
}
