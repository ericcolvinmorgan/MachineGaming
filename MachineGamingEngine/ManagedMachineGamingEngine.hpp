#ifndef MANAGEDMACHINEGAMINGENGINE_HPP
#define MANAGEDMACHINEGAMINGENGINE_HPP

#include "MachineGamingEngine.hpp"

namespace ManagedMachineGamingEngine {
	public ref class ManagedMachineGamingEngine
	{
	private:
		MachineGamingEngine::MachineGamingEngine *_engine;

	public:
		ManagedMachineGamingEngine(int numberInputs, int numberOutputs);
		~ManagedMachineGamingEngine();
		void populateInputs(array<float>^ inputs);
		void retrieveOutputs(array<float>^ outputs);
		void activateCurrent();
		bool nextGenome();
		System::String^ getGenomeDetail();
	};
}

#endif // !MANAGEDMACHINEGAMINGENGINE_HPP