using Visualiser.ViewModels.Pages;
using Wpf.Ui.Controls;

namespace Visualiser.Views.Pages
{
    public partial class RunPage : INavigableView<RunViewModel>
    {
        public RunViewModel ViewModel { get; }

        public RunPage(RunViewModel viewModel)
        {
            ViewModel = viewModel;
            DataContext = this;

            InitializeComponent();
        }
    }
}
