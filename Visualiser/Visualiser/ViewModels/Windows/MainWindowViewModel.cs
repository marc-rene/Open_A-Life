using System.Collections.ObjectModel;
using Wpf.Ui.Controls;

namespace Visualiser.ViewModels.Windows
{
    public partial class MainWindowViewModel : ObservableObject
    {
        [ObservableProperty]
        private string _applicationTitle = "WPF UI - Visualiser";

        [ObservableProperty]
        private ObservableCollection<object> _menuItems = new()
        {
            // Home
            new NavigationViewItem()
            {
                Content = "Dashboard",
                Icon = new SymbolIcon { Symbol = SymbolRegular.Home32},
                TargetPageType = typeof(Views.Pages.DashboardPage)
            },

            // Run
            new NavigationViewItem()
            {
                Content = "Run",
                Icon = new SymbolIcon { Symbol = SymbolRegular.Play32 },
                FontSize = 55,
                TargetPageType = typeof(Views.Pages.RunPage)
            },

            // Settings
            new NavigationViewItem()
            {
                Content = "Settings",
                Icon = new SymbolIcon { Symbol = SymbolRegular.Settings32 },
                TargetPageType = typeof(Views.Pages.SettingsPage)
            },

            // Data
            new NavigationViewItem()
            {
                Content = "Database",
                Icon = new SymbolIcon { Symbol = SymbolRegular.Database32 },
                TargetPageType = typeof(Views.Pages.DataPage)
            }
        };

        [ObservableProperty]
        private ObservableCollection<object> _footerMenuItems = new()
        {
            new NavigationViewItem()
            {
                Content = "Help",
                Icon = new SymbolIcon { Symbol = SymbolRegular.BookQuestionMark24 },
                TargetPageType = typeof(Views.Pages.HelpPage)
            }
        };

        [ObservableProperty]
        private ObservableCollection<MenuItem> _trayMenuItems = new()
        {
            new MenuItem { Header = "Dashboard", Tag = "tray_home" }
        };
    }
}
