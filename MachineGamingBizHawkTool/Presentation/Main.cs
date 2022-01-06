using MachineGamingEngine;
using BizHawk.Client.Common;
using BizHawk.Client.EmuHawk;
using BizHawk.Emulation.Common;
using System.Windows.Forms;
using MachineGamingBizHawkTool.Data;
using System.Diagnostics;

namespace MachineGamingBizHawkTool.Presentation
{
    [ExternalTool("Machine Gaming", Description = "Machine Gaming")]
    public partial class Main : ToolFormBase, IExternalToolForm
    {
        //EmuHawk Service Properties
        [RequiredService]
        private IMemoryDomains MemoryDomains { get; set; }
        [RequiredService]
        private IEmulator Emulator { get; set; }

        [RequiredApi]
        private IJoypadApi Joypad { get; set; }

        [RequiredApi]
        private ISaveStateApi SaveStateApi { get; set; }

        public ApiContainer _apiContainer { get; set; }

        private const int TIMEOUT = 300;
        private int _currentFrame;
        private bool _currentlyUpdating;
        private int _timeout;
        private int _maxX = 0;
        private InputCollector _inputCollector;
        ManagedMachineGamingEngine.ManagedMachineGamingEngine _engine;
        private float[] _inputs;
        private float[] _outputs;

        public Main()
        {
            InitializeComponent();
            _currentFrame = 0;
            _currentlyUpdating = false; //Some methods utilized in the Update method recall the update methods within implemented forms, this skips the extra update calls.
        }

        protected override string WindowTitleStatic => "Machine Gaming";

        public override void Restart()
        {
            //Stage Inputs
            _inputCollector = new InputCollector(MemoryDomains, Emulator);

            int inputs = _inputCollector.NeuronInputs.Count;
            int outputs = 8;

            _inputs = new float[inputs];
            _outputs = new float[outputs];

            _engine = new ManagedMachineGamingEngine.ManagedMachineGamingEngine(inputs, outputs);
        }

        protected override void FastUpdateAfter() => Update();
        protected override void UpdateAfter() => Update();

        private new void Update()
        {
            if (_currentlyUpdating)
            {
                return;
            }

            _currentlyUpdating = true;

            //Save State Path
            _currentFrame++;
            string path = @"C:\Users\ericm\source\repos\MachineGaming\BizHawk\SNES\State\YoshisIsland1.State";

            if ((_currentFrame % 5) == 0)
            {
                //Refesh Inputs
                _inputCollector.RefreshInputs(_inputs);
                _engine.populateInputs(_inputs);

                _engine.activateCurrent();

                //Collect Output
                _engine.retrieveOutputs(_outputs);

            }

            //Update Controller
            ClearController();
            Joypad.Set("P1 Right", true);

            //Update Game Run Tracking
            if (_inputCollector.CharX > _maxX)
            {
                _maxX = _inputCollector.CharX;
                _timeout = TIMEOUT;
            }
            _timeout--;

            if (_timeout <= 0 || _inputCollector.LevelStatus == 9)
            {
                if(_engine.nextGenome()) //Load game and run next genome
                {
                    Debug.Print(_engine.getGenomeDetail());
                    SaveStateApi.Load(path);
                    _inputCollector.RefreshInputs(_inputs);
                    _timeout = TIMEOUT;
                    _currentFrame = 0;
                    _maxX = 0;
                }
                else //Population has been fully explored.
                {
                    
                }
            }

            _currentlyUpdating = false;
        }

        private void button1_Click(object sender, System.EventArgs e)
        {
            MessageBox.Show(_engine.getGenomeDetail());
        }

        private void ClearController()
        {
            var controls = Emulator.ControllerDefinition.ControlsOrdered.GetEnumerator();
            controls.MoveNext(); //Skip Console Controls
            controls.MoveNext(); //Move to player 1 buttons.
     
            foreach (string button in controls.Current)
            {
                Joypad.Set(button, false);
            }
        }
    }
}
