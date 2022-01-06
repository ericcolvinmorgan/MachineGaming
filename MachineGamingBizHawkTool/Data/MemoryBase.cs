using BizHawk.Common;
using BizHawk.Emulation.Common;
using BizHawk.Emulation.Cores.Waterbox;
using System;
using System.Reflection;
using System.Runtime.InteropServices;

namespace MachineGamingBizHawkTool.Data
{
    public class MemoryBase
    {
        public MemoryBase(IMemoryDomains memoryDomains)
        {
            MemoryDomains = memoryDomains;
        }

        public IMemoryDomains MemoryDomains { get; private set; }

        private int U2S(uint u, int size)
        {
            var s = (int)u;
            s <<= 8 * (4 - size);
            s >>= 8 * (4 - size);
            return s;
        }

        public int ReadS16Little(int addr)
        {
            return ReadSignedLittleCore(addr, 2);
        }

        public int ReadSignedLittleCore(int addr, int size, string domain = null)
        {
            return U2S(ReadUnsignedLittle(addr, size, domain), size);
        }

        public uint ReadUnsignedLittle(int addr, int size, string domain = null)
        {
            uint v = 0;
            for (var i = 0; i < size; ++i)
            {
                v |= ReadUnsignedByte(addr + i, domain) << (8 * i);
            }

            return v;
        }

        public uint ReadUnsignedByte(int addr, string domain = null)
        {
            var d = string.IsNullOrEmpty(domain) ? MemoryDomains.MainMemory : MemoryDomains[VerifyMemoryDomain(domain)];
            if (addr < d.Size)
            {
                return d.PeekByte(addr);
            }

            return 0;
        }

        public byte[] GetMemoryDump(string domain = null)
        {
            IntPtr memoryPtr;
            IMonitor monitor;
            string currentDomain = VerifyMemoryDomain(domain);


            var memoryField = typeof(WaterboxMemoryDomain).GetField("_data", BindingFlags.NonPublic | BindingFlags.GetField | BindingFlags.Instance);
            memoryPtr = (System.IntPtr)memoryField.GetValue(MemoryDomains[currentDomain]);          

            var monitorField = typeof(WaterboxMemoryDomain).GetField("_monitor", BindingFlags.NonPublic | BindingFlags.GetField | BindingFlags.Instance);
            monitor = (IMonitor)monitorField.GetValue(MemoryDomains[currentDomain]);

            byte[] memoryDump = new byte[MemoryDomains[currentDomain].Size];

            using (monitor.EnterExit())
            {
                Marshal.Copy(source: memoryPtr, destination: memoryDump, startIndex: 0, length: (int)MemoryDomains[currentDomain].Size);
            }
            return memoryDump;
        }

        public string VerifyMemoryDomain(string domain)
        {
            if (MemoryDomains[domain] == null)
            {
                return MemoryDomains.MainMemory.Name;
            }

            return domain;
        }
    }
}
