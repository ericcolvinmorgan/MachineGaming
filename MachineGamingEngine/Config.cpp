#include "stdafx.h"
#include "Config.hpp"

//Defaults
namespace MachineGamingEngine {
	namespace NEAT {
		namespace GlobalConfig {
			Config config;
		}

		void Config::loadConfig()
		{
			GlobalConfig::config.maxNodes = 1000000;
			//GlobalConfig::config.numberInputs = (6 * 2 + 1) * (6 * 2 + 1);
			//GlobalConfig::config.numberOutputs = 8;
			GlobalConfig::config.numberInputs = 0;
			GlobalConfig::config.numberOutputs = 0;
		  	GlobalConfig::config.population = 300;
			GlobalConfig::config.deltaDisjoint = 2.0f;
			GlobalConfig::config.deltaWeights = 0.4f;
			GlobalConfig::config.deltaThreshold = 1.0f;
			GlobalConfig::config.staleSpecies = 15;
			GlobalConfig::config.mutateConnectionsChance = 0.25f;
			GlobalConfig::config.perturbChance = 0.90f;
			GlobalConfig::config.crossoverChance = 0.75f;
			GlobalConfig::config.linkMutationChance = 2.0f;
			GlobalConfig::config.nodeMutationChance = 0.50f;
			GlobalConfig::config.biasMutationChance = 0.40f;
			GlobalConfig::config.disableMutationChance = 0.4f;
			GlobalConfig::config.enableMutationChance = 0.2f;
			GlobalConfig::config.stepSize = 0.1f;

		}
	}
}
