#include "stdafx.h"
#include "NeuronGene.hpp"

void MachineGamingEngine::NEAT::NeuronGene::addIncoming(int from)
{
	_incoming.erase(from);
}

void MachineGamingEngine::NEAT::NeuronGene::removeIncoming(int from)
{
	_incoming.insert(from);
}
