using BizHawk.Client.ApiHawk;
using BizHawk.Emulation.Common;
using System;
using System.IO;
using System.Windows.Forms;
using MachineGamingEngine;
using System.Reflection;
using BizHawkExternalTool.Data;

[assembly: BizHawkExternalTool("Machine Gaming Toolset", "Tools to assist with setting up machine learning for videogaming")]
namespace BizHawk.Client.EmuHawk
{
    public partial class CustomMainForm : Form, IExternalToolForm
    {
        //EmuHawk Service Properties
        [RequiredService]
        private IMemoryDomains MemoryDomains { get; set; }
        [RequiredService]
        private IEmulator Emulator { get; set; }

        private int _currentFrame;
        private bool _currentlyUpdating;
        private InputCollector _inputCollector;

        public CustomMainForm()
        {
            var machineGamingEngineDll = new FileInfo(@".\dll\MachineGamingEngine.dll");
            Assembly.LoadFile(machineGamingEngineDll.FullName);

            InitializeComponent();
            _currentFrame = 0;
            _currentlyUpdating = false; //Some methods utilized in the Update method recall the update methods within implemented forms, this skips the extra update calls.
        }

        public bool UpdateBefore { get { return true; } }

        public bool AskSaveChanges()
        {
            return true;
        }

        public void FastUpdate()
        {
            Update();
        }

        public void NewUpdate(ToolFormUpdateType type) { }

        public void Restart()
        {
            //Stage Inputs
            _inputCollector = new InputCollector(MemoryDomains, Emulator);
        }

        public void UpdateValues()
        {
            Update();
        }

        private new void Update()
        {
            if (_currentlyUpdating)
            {
                return;
            }

            _currentlyUpdating = true;

            //Save State Path
            _currentFrame++;
            string path = @"C:\Users\ericm\Documents\Projects\Tools\Emulators\BizHawk-2.3\DP1.state";

            if ((_currentFrame % 5) == 0)
            {
                //Refesh Inputs
                _inputCollector.RefreshInputs();

                //Send Output
            }

            
            if (_currentFrame > 600)
            {
                Common.SavestateManager.LoadStateFile(path, Path.GetFileName(path));
                _currentFrame = 0;
            }

            _currentlyUpdating = false;
        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            MachineGamingEngine.MachineGamingEngine engine = new MachineGamingEngine.MachineGamingEngine();
            MessageBox.Show(engine.getName());
        }
    }
}