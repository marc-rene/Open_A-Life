using Visualiser.ViewModels.Pages;
using Wpf.Ui.Controls;

namespace Visualiser.Views.Pages
{
    public partial class HelpPage : INavigableView<HelpViewModel>
    {
        public HelpViewModel ViewModel { get; }

        public HelpPage(HelpViewModel viewModel)
        {
            ViewModel = viewModel;
            DataContext = this;

            InitializeComponent();
        }
    }
}
