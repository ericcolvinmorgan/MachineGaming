#ifndef NEATCONFIG_HPP
#define NEATCONFIG_HPP

namespace MachineGamingEngine {
	namespace NEAT {
		namespace Config {
			extern short population;
			extern float deltaDisjoint;
			extern float deltaWeights;
			extern float deltaThreshold;
			extern short staleSpecies;
			extern float mutateConnectionsChance;
			extern float perturbChance;
			extern float crossoverChance;
			extern float linkMutationChance;
			extern float nodeMutationChance;
			extern float biasMutationChance;
			extern float stepSize;
			extern float disableMutationChance;
			extern float enableMutationChance;

			bool loadConfig();
		}
	}
}

#endif