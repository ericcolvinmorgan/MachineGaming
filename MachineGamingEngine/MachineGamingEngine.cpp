#include "stdafx.h"
#include "MachineGamingEngine.hpp"
#include "Config.hpp"

MachineGamingEngine::MachineGamingEngine::MachineGamingEngine(int numberInputs, int numberOutputs)
{
	NEAT::GlobalConfig::config.loadConfig();
	NEAT::GlobalConfig::config.numberInputs = numberInputs;
	NEAT::GlobalConfig::config.numberOutputs = numberOutputs;
	_population = new NEAT::Population();
}

MachineGamingEngine::MachineGamingEngine::~MachineGamingEngine()
{
	if (_population != nullptr)
	{
		delete _population;
		_population = nullptr;
	}
}

void MachineGamingEngine::MachineGamingEngine::populateInputs(float *inputs)
{	
	auto org = _population->currentOrganism();
	org->setInputs(inputs);
}

void MachineGamingEngine::MachineGamingEngine::activateCurrent()
{
	auto org = _population->currentOrganism();
	org->activate();
}

bool MachineGamingEngine::MachineGamingEngine::nextGenome()
{
	auto pop = *_population;
	return pop++;

	//return (*_population)++;
}

void MachineGamingEngine::MachineGamingEngine::retrieveOutputs(float *outputs)
{
	auto org = _population->currentOrganism();
	org->getOutputs(outputs);
}