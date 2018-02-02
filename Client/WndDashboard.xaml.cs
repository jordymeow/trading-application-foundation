using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Meow.FR.TAF.Client
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class WndMain : Window
    {
        DashboardViewModel dashboardVM = new DashboardViewModel();

        public WndMain()
        {
            this.DataContext = dashboardVM;
            dashboardVM.Server.RealtimeDataReceived += new Action<Meow.FR.TAF.API.TAFRealtimeData>(Server_RealtimeDataReceived);
            if (!dashboardVM.Server.Connect("localhost", 1982))
            {
                MessageBox.Show("Can't connect on the TAF server. Start the server first on localhost and try again.", "TAF Client", MessageBoxButton.OK, MessageBoxImage.Error);
                Close();
            }
            InitializeComponent();
            dashboardVM.Server.Subscribe("EURJPY CURNCY");
            dashboardVM.Server.Subscribe("MSFT US EQUITY");
            dashboardVM.Server.Subscribe("6758 JP EQUITY");
            dashboardVM.Server.Subscribe("ACA FP EQUITY");
        }

        void Server_RealtimeDataReceived(Meow.FR.TAF.API.TAFRealtimeData obj)
        {
            if (obj.Last == null)
                return;
            string newValue = obj.Last.Value.ToString();
            if (obj.Ticker == "EURJPY CURNCY" && txtEURJPY.Text != newValue)
                txtEURJPY.Text = newValue;
            else if (obj.Ticker == "MSFT US EQUITY" && txtMicrosoft.Text != newValue)
                txtEURJPY.Text = newValue;
            else if (obj.Ticker == "6758 JP EQUITY" && txtSony.Text != newValue)
                txtSony.Text = newValue;
            else if (obj.Ticker == "ACA FP EQUITY" && txtCreditAgricole.Text != newValue)
                txtCreditAgricole.Text = newValue;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            dashboardVM.GetHistoricalData(txtTicker.Text);
        }
    }
}
