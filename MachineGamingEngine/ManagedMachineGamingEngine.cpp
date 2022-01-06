#include "stdafx.h"
#include "ManagedMachineGamingEngine.hpp"

ManagedMachineGamingEngine::ManagedMachineGamingEngine::ManagedMachineGamingEngine(int numberInputs, int numberOutputs)
{
	_engine = new MachineGamingEngine::MachineGamingEngine(numberInputs, numberOutputs);
}

ManagedMachineGamingEngine::ManagedMachineGamingEngine::~ManagedMachineGamingEngine()
{
	if (_engine != nullptr)
		delete _engine;

	_engine = nullptr;
}

void ManagedMachineGamingEngine::ManagedMachineGamingEngine::populateInputs(array<float>^ inputs)
{
	//pin_ptr<float> inputsPin = &inputs[0];
	//float* inputsPtr = (float*)inputsPin;

	float copy[169];
	for (int i = 0; i < 169; i++)
	{
		copy[i] = inputs[i];
	}

	float* vars;
	float val = 1.f;
	vars = &val;
	//float* values = { 1.f, 1.f, 1.f };
	int lskdjf = _engine->currentOrganismId();
	int lskdjfd = _engine->currentSpeciesId();
	_engine->populateInputs(vars);
}

void ManagedMachineGamingEngine::ManagedMachineGamingEngine::retrieveOutputs(array<float>^ outputs)
{
	pin_ptr<float> outputsPin = &outputs[0];
	float* outputsPtr = (float*)outputsPin;
	_engine->retrieveOutputs(outputsPtr);
}

void ManagedMachineGamingEngine::ManagedMachineGamingEngine::activateCurrent()
{
	if (_engine != nullptr)
		_engine->activateCurrent();
}

bool ManagedMachineGamingEngine::ManagedMachineGamingEngine::nextGenome()
{
	if (_engine != nullptr)
		return _engine->nextGenome();

	return false;
}

System::String^ ManagedMachineGamingEngine::ManagedMachineGamingEngine::getGenomeDetail()
{
	if (_engine != nullptr)
	{
		return "SPECIES: " + _engine->currentSpeciesId() + " ORGANISM: " + _engine->currentOrganismId();
	}

	return "NO GENOME DETAIL AVAILABLE";
}
