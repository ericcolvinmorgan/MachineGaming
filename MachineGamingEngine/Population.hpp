#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include "Species.hpp"

namespace MachineGamingEngine {
	namespace NEAT {
		struct SpeciesGenome {
			size_t species;
			size_t genome;
		};

		class Population
		{
		private:
			std::vector<Species> _species;
			std::vector<struct SpeciesGenome> _genomeRank;
			int _generation = 0;		
			int _currentSpecies = 0;
			int _currentOrganism = 0;
			int _currentFrame = 0;
			int _maxFitness = 0;
			int _currentInnovation = 1;
			


		public:
			Population();
			~Population() {};

			void newGeneration();
			void rankGenomes();
			void removeStagnantSpecies() {};
			void removeLowPerformingOrgamisms();
			int speciesId() { return _currentSpecies; }
			int organismId() { return _currentOrganism; }
			Species* currentSpecies();
			Organism* currentOrganism();

			bool operator++ (int);
		};
	}
}

#endif // !POPULATION_HPP