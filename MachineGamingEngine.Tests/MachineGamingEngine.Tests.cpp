#include "pch.h"
#include "CppUnitTest.h"
#include "../MachineGamingEngine/MachineGamingEngine.hpp"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MachineGamingEngineTests
{
	TEST_CLASS(MachineGamingEngineTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			MachineGamingEngine::MachineGamingEngine engine(169, 8);
			for (int i = 0; i < 100; i++)
			{
				if (engine.nextGenome()) //Load game and run next genome
				{
					std::cout << "SPECIES: " << engine.currentSpeciesId() << "ORGANISM: " << engine.currentOrganismId() << std::endl;

					std::vector<float> inputs(169);
					engine.populateInputs((float*)&inputs[0]);

					engine.activateCurrent();

					//Collect Output
					std::vector<float> outputs(169);
					engine.retrieveOutputs((float*)&outputs[0]);
					
				}
				else //Population has been fully explored.
				{

				}
			}
		}
	};
}
