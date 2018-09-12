#ifndef SPECIES_HPP
#define SPECIES_HPP

namespace MachineGamingEngine {
	namespace NEAT {
		class Species
		{
		private:
			int _topFitness = 0;
			int _staleness = 0;
			//STUB - _genomes = {}

		public:
			Species() {};
			~Species() {};
		};
	}
}

#endif // !SPECIES_HPP