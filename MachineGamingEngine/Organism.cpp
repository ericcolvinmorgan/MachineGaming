#include "stdafx.h"
#include "Organism.hpp"

std::default_random_engine& MachineGamingEngine::NEAT::Organism::_numberGenerator()
{
	static std::default_random_engine generator{};
	return generator;
}

MachineGamingEngine::NEAT::Organism::Organism()
{
	int inp = NEAT::GlobalConfig::config.numberInputs;
	int outp = NEAT::GlobalConfig::config.numberOutputs;
	_mutateConnectionsChance = NEAT::GlobalConfig::config.mutateConnectionsChance;
	_linkMutationChance = NEAT::GlobalConfig::config.linkMutationChance;
	_nodeMutationChance = NEAT::GlobalConfig::config.nodeMutationChance;
	_biasMutationChance = NEAT::GlobalConfig::config.biasMutationChance;
	_disableMutationChance = NEAT::GlobalConfig::config.disableMutationChance;
	_enableMutationChance = NEAT::GlobalConfig::config.enableMutationChance;
	_genome = new Genome(inp, outp);
}

void MachineGamingEngine::NEAT::Organism::mutate()
{
	auto generator = _numberGenerator();
	std::uniform_int_distribution<float> distribution(0.f, 1.f);
	_mutateConnectionsChance *= (distribution(generator) >= .5f ? .95f : 1.05f);
	_linkMutationChance *= (distribution(generator) >= .5f ? .95f : 1.05f);
	_nodeMutationChance *= (distribution(generator) >= .5f ? .95f : 1.05f);
	_biasMutationChance *= (distribution(generator) >= .5f ? .95f : 1.05f);
	_disableMutationChance *= (distribution(generator) >= .5f ? .95f : 1.05f);
	_enableMutationChance *= (distribution(generator) >= .5f ? .95f : 1.05f);

	if (distribution(generator) < _mutateConnectionsChance)
	{
		_genome->perturbConnections(NEAT::GlobalConfig::config.perturbChance, NEAT::GlobalConfig::config.stepSize);
	}

	if (distribution(generator) < _linkMutationChance)
	{
		//Adds a new connect gene between random neurons.
		//_genome.linkMutate(false)
	}

	if (distribution(generator) < _nodeMutationChance)
	{
		//_genome.nodeMutate(true)
	}

	if (distribution(generator) < _biasMutationChance)
	{
		//Adds a new connect gene between random neuron and bias neuron.
		//_genome->addConnectGene()
		//addConnectGene
	}

	if (distribution(generator) < _disableMutationChance)
	{
		//_genome.enableDisableMutate(false)
	}

	if (distribution(generator) < _enableMutationChance)
	{
		//_genome.enableDisableMutate(true)
	}

}
