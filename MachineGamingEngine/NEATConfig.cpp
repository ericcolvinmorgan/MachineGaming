#include "stdafx.h"
#include "neatConfig.hpp"

//Defaults
namespace MachineGamingEngine {
	namespace NEAT {
		namespace Config {
			short population = 300;
			float deltaDisjoint = 2.0f;
			float deltaWeights = 0.4f;
			float deltaThreshold = 1.0f;
			short staleSpecies = 15;
			float mutateConnectionsChance = 0.25f;
			float perturbChance = 0.90f;
			float crossoverChance = 0.75f;
			float linkMutationChance = 2.0f;
			float nodeMutationChance = 0.50f;
			float biasMutationChance = 0.40f;
			float stepSize = 0.1f;
			float disableMutationChance = 0.4f;
			float enableMutationChance = 0.2f;
		}
	}
}

bool MachineGamingEngine::NEAT::Config::loadConfig()
{
	//STUB - TO IMPLEMENT
	return true;
}
