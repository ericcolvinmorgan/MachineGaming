#ifndef GENOME_HPP
#define GENOME_HPP

#include "Config.hpp"
#include "ConnectGene.hpp"
#include "NeuronGene.hpp"
#include <random>
#include <map>
#include <vector>

namespace MachineGamingEngine {
	namespace NEAT {
		class Genome
		{
		private:
			int _lastInnovation = -1;
			unsigned int _globalRank = std::numeric_limits<unsigned int>::max();
			unsigned int _fitness = std::numeric_limits<unsigned int>::max();
			int _numberInputs;
			int _numberOutputs;
			std::vector<NeuronGene> _neuronGenes;
			std::map<std::pair<int, int>, ConnectGene> _connectGenes;
			std::default_random_engine& _numberGenerator();

		public:
			Genome(int numberInputs, int numberOutputs);
			~Genome() {};

			bool containsLink(int fromIndex, int toIndex);
			void setInputs(float* inputs);
			void getOutputs(float* outputs);

			void setGlobalRank(unsigned int rank) { _globalRank = rank; };
			const unsigned int getGlobalRank() const { return _globalRank; };

			void setFitness(unsigned int fitness) { _fitness = fitness; };
			const unsigned int getFitness() const { return _fitness; };

			//Mutation in NEAT can change both connection weights and network structures.
			//Connection weights mutate as in any NE system, with each connection either perturbed or not at each generation
			void addNeuronGene(int& innovation);
			void addConnectGene(int& innovation, int from = -1, int to = -1);
			void perturbConnections(float chance, float step);
			void activate();

			//This mutation isn't part of the original paper.
			void mutateRandomConnection(bool updateStatus);
		};
	}
}

#endif // !GENOME_HPP