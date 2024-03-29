#ifndef MACHINEGAMINGENGINE_HPP
#define MACHINEGAMINGENGINE_HPP

#include "Population.hpp"

namespace MachineGamingEngine {
	class MachineGamingEngine
	{
	private:
		NEAT::Population* _population;
		int _numberInputs = 0;
		int _numberOutputs = 0;

	public:
		MachineGamingEngine(int numberInputs, int numberOutputs);
		~MachineGamingEngine();

		void populateInputs(float *inputs);
		void activateCurrent();
		bool nextGenome();
		int currentOrganismId() { return _population->organismId(); }
		int currentSpeciesId() { return _population->speciesId(); }
		void retrieveOutputs(float *outputs);
	};
}

#endif // !MACHINEGAMINGENGINE_HPP