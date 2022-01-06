#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include "Genome.hpp"

namespace MachineGamingEngine {
	namespace NEAT {
		class Organism
		{
		private:
			int _fitness = 0;
			int _globalRank = 0;
			Genome *_genome;
			int& _currentInnovation;
			float _mutateConnectionsChance;
			float _linkMutationChance;
			float _nodeMutationChance;
			float _biasMutationChance;
			float _disableMutationChance;
			float _enableMutationChance;
			std::default_random_engine& _numberGenerator();

		public:
			Organism();
			~Organism() {};
			const int getFitness() const { return _fitness; };
			void setInputs(float* inputs) { _genome->setInputs(inputs); };
			void activate() { _genome->activate(); };
			void getOutputs(float* outputs) { _genome->getOutputs(outputs); };
			void mutate();
		};
	}
}
#endif // !ORGANISM_HPP