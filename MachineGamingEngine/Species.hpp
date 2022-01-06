#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <vector>
#include "Organism.hpp"

namespace MachineGamingEngine {
	namespace NEAT {
		class Species
		{
		private:
			int _topFitness = 0;
			int _averageFitness = 0;
			int _staleness = 0;
			int& _currentInnovation;
			std::vector<Organism> _organisms;
			std::default_random_engine& _numberGenerator();

		public:
			Species(int& currentInnovation) {
				_currentInnovation = currentInnovation;
			};
			~Species() {};

			void createOrganismCrossover(size_t organism1, size_t organism2);
			void createOrganismCopy(size_t organism);
			void removeLowPerformingOrganisms();
			void calculateAverageFitness();
			void breedOrganisms();
			std::vector<Organism>& organisms() { return _organisms; };
		};
	}
}

#endif // !SPECIES_HPP