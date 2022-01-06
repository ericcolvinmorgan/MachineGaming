#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace MachineGamingEngine {
	namespace NEAT {
		class Config 
		{
		public:
			int maxNodes = 0;
			int numberInputs = 0;
			int numberOutputs = 0;
			short population = 0;
			float deltaDisjoint = 0.f;
			float deltaWeights = 0.f;
			float deltaThreshold = 0.f;
			short staleSpecies = 0;
			float mutateConnectionsChance = 0.f;
			float perturbChance = 0.f;
			float crossoverChance = 0.f;
			float linkMutationChance = 0.f;
			float nodeMutationChance = 0.f;
			float biasMutationChance = 0.f;
			float stepSize = 0.f;
			float disableMutationChance = 0.f;
			float enableMutationChance = 0.f;

			Config() {};
			~Config() {};
			void loadConfig();
		};

		namespace GlobalConfig
		{
			extern Config config;
		}
	}
}

#endif