using BizHawk.Client.ApiHawk;
using BizHawk.Emulation.Common;
using System;
using System.Windows.Forms;

[assembly: BizHawkExternalTool("Testing")]
namespace BizHawk.Client.EmuHawk
{
    public partial class CustomMainForm : Form, IExternalToolForm
    {
        [RequiredService]
        private IMemoryDomains MemoryDomains { get; set; }
        [RequiredService]
        private IEmulator Emulator { get; set; }
        private int CurrentFrame { get; set; }
        private bool CurrentlyUpdating { get; set; }

        public CustomMainForm()
        {
            InitializeComponent();
        }

        public bool UpdateBefore => throw new NotImplementedException();

        public bool AskSaveChanges()
        {
            throw new NotImplementedException();
        }

        public void FastUpdate()
        {
            throw new NotImplementedException();
        }

        public void NewUpdate(ToolFormUpdateType type)
        {
            throw new NotImplementedException();
        }

        public void Restart()
        {
            throw new NotImplementedException();
        }

        public void UpdateValues()
        {
            throw new NotImplementedException();
        }

        private void buttonTest_Click(object sender, EventArgs e)
        {

        }
    }
}
