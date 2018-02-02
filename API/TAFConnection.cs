using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.ComponentModel;
using System.Threading;
using System.IO;
using System.Globalization;
using System.Windows.Threading;

namespace Meow.FR.TAF.API
{
    public enum TAFHistoricalPeriod : int
    {
        Minute = 1,
        Hour = 60,
        Day = 1440,
        Week = 10080,
        Month = 43800,
        Year = 525600
    }

    public class TAFConnection : DispatcherObject
    {
        public bool IsConnected { private get; set; }

        public event Action<TAFRealtimeData> RealtimeDataReceived = delegate { };
        public event Action<TAFHistoricalData> HistoricalDataReceived = delegate { };

        BackgroundWorker worker = new BackgroundWorker();
        TcpClient client;
        NetworkStream netStream;
        StreamReader reader;
        StreamWriter writer;

        public bool Connect(string server, int port)
        {
            try
            {
                client = new TcpClient(server, port);
                netStream = client.GetStream();
                writer = new StreamWriter(netStream);
                worker.DoWork += DataReader;
                worker.RunWorkerAsync();
                IsConnected = true;
                return true;
            }
            catch (SocketException)
            {
                return false;
            }
        }

        private void DataReceived(string buffer)
        {
            if (buffer[0] == 'F')
            {

            }
            else if (buffer[0] == 'S')
            {
                string[] sBuffer = buffer.Split('!');
                // Connection of a new IP
                if (sBuffer[1] == "C")
                {
                }
            }
            else if (buffer[0] == 'D')
            {
                string[] sBuffer = buffer.Split('&');
                string[] sMarketData = sBuffer[0].Split('!');
                TAFMarketData data = null;
                if (sBuffer.Length > 1)
                {
                    if (sBuffer[1][0] == 'R')
                    {
                        // REALTIME DATA
                        string[] sRealtimeData = sBuffer[1].Split('!');
                        DateTime time = DateTime.Parse(sMarketData[2]);
                        data = new TAFRealtimeData(sMarketData[1], time,
                            sRealtimeData[1] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[1]),
                            sRealtimeData[2] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[2]),
                            sRealtimeData[3] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[3]),
                            sRealtimeData[4] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[4]),
                            sRealtimeData[5] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[5]),
                            sRealtimeData[6] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[6]),
                            sRealtimeData[7] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[7]),
                            sRealtimeData[8] == "" ? null : (Nullable<double>)Convert.ToDouble(sRealtimeData[8]));
                    }
                    else if (sBuffer[1][0] == 'H')
                    {
                        // HISTORICAL DATA
                        data = new TAFHistoricalData(sMarketData[1], DateTime.Parse(sMarketData[2]));
                        for (int c = 1; c < sBuffer.Length; c++)
                        {
                            string[] sHistoricalData = sBuffer[c].Split('!');
                            TAFHistoricalPoint p = new TAFHistoricalPoint(DateTime.Parse(sHistoricalData[2]),
                                sHistoricalData[3] == "" ? null : (Nullable<double>)Convert.ToDouble(sHistoricalData[3]),
                                sHistoricalData[4] == "" ? null : (Nullable<double>)Convert.ToDouble(sHistoricalData[4]),
                                sHistoricalData[5] == "" ? null : (Nullable<double>)Convert.ToDouble(sHistoricalData[5]),
                                sHistoricalData[6] == "" ? null : (Nullable<double>)Convert.ToDouble(sHistoricalData[6]),
                                sHistoricalData[7] == "" ? null : (Nullable<double>)Convert.ToDouble(sHistoricalData[7]));
                            ((TAFHistoricalData)data).Add(p);
                            if (c == 1)
                            {
                                ((TAFHistoricalData)data).Period = (TAFHistoricalPeriod)int.Parse(sHistoricalData[1]);
                                ((TAFHistoricalData)data).To = p.Time;
                                ((TAFHistoricalData)data).From = p.Time;
                            }
                            else
                            {
                                if (p.Time > ((TAFHistoricalData)data).To)
                                    ((TAFHistoricalData)data).To = p.Time;
                                else if (p.Time < ((TAFHistoricalData)data).From)
                                    ((TAFHistoricalData)data).From = p.Time;
                            }
                        }

                    }
                }

                if (data != null && data is TAFRealtimeData)
                    Dispatcher.Invoke(DispatcherPriority.Normal, new Action<TAFRealtimeData>(RealtimeDataReceived), data);
                else if (data != null && data is TAFHistoricalData)
                    Dispatcher.Invoke(DispatcherPriority.Normal, new Action<TAFHistoricalData>(HistoricalDataReceived), data);
            }
        }

        private void DataReader(object sender, DoWorkEventArgs e)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.CreateSpecificCulture("en-US");
            reader = new StreamReader(netStream);
            while (true)
            {
                string buffer = reader.ReadLine();
                DataReceived(buffer);
            }
        }

        private string PeriodToString(TAFHistoricalPeriod p)
        {
            switch (p)
            {
                case TAFHistoricalPeriod.Minute:
                    return "MM";
                case TAFHistoricalPeriod.Hour:
                    return "HH";
                case TAFHistoricalPeriod.Day:
                    return "D";
                case TAFHistoricalPeriod.Month:
                    return "M";
                case TAFHistoricalPeriod.Week:
                    return "W";
                case TAFHistoricalPeriod.Year:
                    return "Y";
                default:
                    throw new Exception(p.ToString() + " is not known yet.");
            }
        }

        public void GetHistoricalData(string ticker, DateTime from, DateTime to, TAFHistoricalPeriod p)
        {
            writer.WriteLine("%" + ticker + "!" +
                from.Year.ToString() + (from.Month < 10 ? "0" : "") + from.Month.ToString() + (from.Day < 10 ? "0" : "") + from.Day.ToString() + "!" +
                to.Year.ToString() + (to.Month < 10 ? "0" : "") + to.Month.ToString() + (to.Day < 10 ? "0" : "") + to.Day.ToString() + "!" +
                PeriodToString(p));
            writer.Flush();
        }

        public void Subscribe(string ticker)
        {
            writer.WriteLine("+" + ticker);
            writer.Flush();
        }

        public void Unsubscribe(string ticker)
        {
            writer.WriteLine("-" + ticker);
            writer.Flush();
        }
    }
}
