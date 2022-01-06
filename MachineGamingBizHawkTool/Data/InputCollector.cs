using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Waterbox;
using System;
using System.Collections.Generic;
using System.Linq;

namespace MachineGamingBizHawkTool.Data
{
    //Currently written very specifically to SMW, will need to make more generic.
    public struct InputDetail
    {
        public int Index { get; set; }
        public int X { get; set; }
        public int Y { get; set; }
        //public uint Value { get; set; }
    }

    class InputCollector
    {
        const int INPUT_HEIGHT_WIDTH = 6;
        const int MAP16_LOW_BYTE_START = 51200; //7EC800
        const int MAP16_HIGH_BYTE_START = 116736; //7FC800

        //private readonly IntPtr _wramPtr;
        //private readonly IMonitor _monitor;

        private MemoryBase _memoryBase { get; set; }
        private byte[] _wramDump;
        private List<InputDetail> _sprites;
        private List<InputDetail> _extendedSprites;
        private Dictionary<InputDetail, uint> _tileList;

        public Dictionary<InputDetail, short> NeuronInputs { get; private set; }
        public int CharX { get; private set; } = 0;
        public int CharY { get; private set; } = 0;
        public uint LevelStatus { get; private set; } = 0;

        public InputCollector(IMemoryDomains memoryDomains, IEmulator emulator)
        {
            _memoryBase = new MemoryBase(memoryDomains);
            _wramDump = new byte[_memoryBase.MemoryDomains["WRAM"].Size];

            NeuronInputs = new Dictionary<InputDetail, short>();
            _tileList = new Dictionary<InputDetail, uint>();

            short index = 1;
            for (int iy = -INPUT_HEIGHT_WIDTH * 16; iy <= INPUT_HEIGHT_WIDTH * 16; iy += 16)
            {
                for (int ix = -INPUT_HEIGHT_WIDTH * 16; ix <= INPUT_HEIGHT_WIDTH * 16; ix += 16)
                {
                    NeuronInputs.Add(new InputDetail() { Index = index, X = ix, Y = iy }, 0);
                    _tileList.Add(new InputDetail() { Index = index, X = ix, Y = iy }, 0);
                    index++;
                }
            }
        }

        public void RefreshInputs(float[] _inputs)
        {
            _wramDump = _memoryBase.GetMemoryDump("WRAM");
            CharX = _memoryBase.ReadS16Little(Convert.ToInt32("0x94", 16));
            CharY = _memoryBase.ReadS16Little(Convert.ToInt32("0x96", 16));
            LevelStatus = _memoryBase.ReadUnsignedByte(Convert.ToInt32("0x71", 16));

            GetTiles();
            GetSprites();
            GetExtendedSprites();

            foreach (var tile in _tileList)
            {
                NeuronInputs[tile.Key] = 0;
                if (tile.Value == 1 && (CharY + tile.Key.Y) < 432)
                {
                    NeuronInputs[tile.Key] = 1;
                }

                foreach (var sprite in _sprites)
                {
                    int distX = Math.Abs(sprite.X - (CharX + tile.Key.X));
                    int distY = Math.Abs(sprite.Y - (CharY + tile.Key.Y));

                    if (distX <= 8 && distY <= 8)
                    {
                        NeuronInputs[tile.Key] = -1;
                    }
                }

                foreach (var extendedSprite in _extendedSprites)
                {
                    int distX = Math.Abs(extendedSprite.X - (CharX + tile.Key.X));
                    int distY = Math.Abs(extendedSprite.Y - (CharY + tile.Key.Y));

                    if (distX < 8 && distY < 8)
                    {
                        NeuronInputs[tile.Key] = -1;
                    }
                }

                _inputs[tile.Key.Index - 1] = NeuronInputs[tile.Key];
            }
        }

        private void GetTiles()
        {
            //Create Inputs
            //The formula for going from position to index to $7xC800(x and y in tiles):
            //0x7_C800 + (x & 0xF) + (y << 4) + ((x & 0x1FF0) * 27)

            //In vertical levels:
            //0x7_C800 + (x & 0xF) + (y & 0xF << 4) + (x & 0x10 << 4) + (y & 0x1F0 << 5)

            List<InputDetail> inputDetail = _tileList.Keys.ToList();
            foreach (var tile in inputDetail)
            {
                int currentX = (int)Math.Floor((double)(CharX + tile.X + 8) / 16);
                int currentY = (int)Math.Floor((double)(CharY + tile.Y) / 16);

                int pos = ((int)Math.Floor((double)currentX / 16) * 432) + (currentY * 16) + (currentX % 16);
                int addrLowByte = MAP16_LOW_BYTE_START + pos;
                int addrHighByte = MAP16_HIGH_BYTE_START + pos;


                if (MAP16_LOW_BYTE_START <= addrLowByte && addrLowByte <= MAP16_LOW_BYTE_START + 14336)
                {
                    uint tileLowByteDetail = _wramDump[addrLowByte];
                    uint tileHighByteDetail = _wramDump[addrHighByte];
                    //Debug.Print(string.Format("Tile Detail: ix:{0} x:{1} yx:{2} y:{3} value high:{4} address high:{5} value low:{6} address low:{7}", ix, currentX, iy, currentY, tileHighByteDetail, addrHighByte, tileLowByteDetail, addrLowByte));

                    _tileList[tile] = tileHighByteDetail;
                }
                else
                {

                }
            }
        }

        private void GetSprites()
        {
            //Sprite List - https://smwspeedruns.com/index.php/Sprites
            _sprites = new List<InputDetail>();

            for (int i = 0; i <= 11; i++)
            {
                //Position Sprite
                uint spriteNumber = 0;

                //Low byte is the position in pixels on the screen
                uint xLowByte = 0;
                uint yLowByte = 0;

                //High byte is screen number
                uint xHighByte = 0;
                uint yHighByte = 0;

                uint currentStatus = _wramDump[Convert.ToInt32("0x14C8", 16) + i];
                if (currentStatus != 0)
                {
                    spriteNumber = _wramDump[Convert.ToInt32("0x9E", 16) + i];
                    xLowByte = _wramDump[Convert.ToInt32("0xE4", 16) + i];
                    yLowByte = _wramDump[Convert.ToInt32("0xD8", 16) + i];
                    xHighByte = _wramDump[Convert.ToInt32("0x14E0", 16) + i];
                    yHighByte = _wramDump[Convert.ToInt32("0x14D4", 16) + i];

                    uint calcx = (256 * xHighByte) + xLowByte;
                    uint calcy = (256 * yHighByte) + yLowByte;

                    //Debug.Print(string.Format("Pos: {0} Sprite: {1} - xLowByte:{2}  xHighByte:{3} yLowByte:{4} yHighByte:{5} - x calc:{6} || y calc:{7}", i, spriteNumber, xLowByte, xHighByte, yLowByte, yHighByte, calcx, calcy));
                    InputDetail inputDetail = new InputDetail();
                    inputDetail.Index = i;
                    inputDetail.X = (int)calcx;
                    inputDetail.Y = (int)calcy;
                    _sprites.Add(inputDetail);
                }
            }
        }

        private void GetExtendedSprites()
        {
            //Sprite List - http://old.smwiki.net/wiki/RAM_Address/$7E:170B
            _extendedSprites = new List<InputDetail>();

            for (int i = 0; i <= 9; i++)
            {
                //Position Sprite
                uint spriteNumber = _wramDump[Convert.ToInt32("0x170B", 16) + i];

                //Low byte is the position in pixels on the screen
                uint xLowByte = 0;
                uint yLowByte = 0;

                //High byte is screen number
                uint xHighByte = 0;
                uint yHighByte = 0;

                if (spriteNumber != 0)
                {
                    xLowByte = _wramDump[Convert.ToInt32("0x171F", 16) + i];
                    yLowByte = _wramDump[Convert.ToInt32("0x1715", 16) + i];
                    xHighByte = _wramDump[Convert.ToInt32("0x1733", 16) + i];
                    yHighByte = _wramDump[Convert.ToInt32("0x1729", 16) + i];

                    uint calcx = (256 * xHighByte) + xLowByte;
                    uint calcy = (256 * yHighByte) + yLowByte;

                    //Debug.Print(string.Format("Pos: {0} Extended Sprite: {1} - xLowByte:{2}  xHighByte:{3} yLowByte:{4} yHighByte:{5} - x calc:{6} || y calc:{7}", i, spriteNumber, xLowByte, xHighByte, yLowByte, yHighByte, calcx, calcy));
                    InputDetail inputDetail = new InputDetail();
                    inputDetail.Index = i;
                    inputDetail.X = (int)calcx;
                    inputDetail.Y = (int)calcy;
                    _extendedSprites.Add(inputDetail);
                }
            }
        }
    }
}
