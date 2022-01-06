#include "stdafx.h"
#include "Species.hpp"

std::default_random_engine& MachineGamingEngine::NEAT::Species::_numberGenerator()
{
	static std::default_random_engine generator{};
	return generator;
}

void MachineGamingEngine::NEAT::Species::createOrganismCrossover(size_t organism1, size_t organism2)
{

}

void MachineGamingEngine::NEAT::Species::createOrganismCopy(size_t organism)
{

}

void MachineGamingEngine::NEAT::Species::removeLowPerformingOrganisms()
{
	std::sort(_organisms.begin(), _organisms.end(),
		[](const Organism& left, const Organism& right) -> bool {
			return left.getFitness() > right.getFitness();
		});

	size_t mid = _organisms.size() / 2;
	_organisms.erase(_organisms.begin() + mid, _organisms.end());
}


void MachineGamingEngine::NEAT::Species::calculateAverageFitness()
{

}

void MachineGamingEngine::NEAT::Species::breedOrganisms()
{
	auto generator = _numberGenerator();
	std::uniform_int_distribution<float> crossDistribution(0.f, 1.f);
	std::uniform_int_distribution<size_t> organismDistribution(0, _organisms.size());
	size_t o1 = organismDistribution(generator);
	if (crossDistribution(generator) < NEAT::GlobalConfig::config.crossoverChance)
	{
		size_t o2 = organismDistribution(generator);
		createOrganismCrossover(o1, o2);
	}
	else
	{
		createOrganismCopy(o1);
	}
}
