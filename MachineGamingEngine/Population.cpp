#include "stdafx.h"
#include "Population.hpp"
#include "Species.hpp"

MachineGamingEngine::NEAT::Species* MachineGamingEngine::NEAT::Population::currentSpecies()
{
	size_t count = _species.size();
	return &_species[_currentSpecies];
}

MachineGamingEngine::NEAT::Organism* MachineGamingEngine::NEAT::Population::currentOrganism()
{
	size_t scount = _species.size();
	_species.push_back(Species());
	size_t scount2 = _species.size();

	size_t count = _species[_currentSpecies].organisms().size();
	return &_species[_currentSpecies].organisms()[_currentOrganism];
}

bool MachineGamingEngine::NEAT::Population::operator++(int)
{
	if (_currentOrganism >= (int)(_species[_currentSpecies].organisms().size()) - 1)
		_currentOrganism = 0;
	else
		_currentOrganism++;


	if (_currentOrganism == 0 && _currentSpecies >= (int)_species.size() - 1)
		_currentSpecies = 0;
	else
		_currentSpecies++;

	if (_currentOrganism == 0 && _currentSpecies == 0)
		return false;

	return true;
}

MachineGamingEngine::NEAT::Population::Population()
{
	_generation = 0;
	_currentSpecies = 0;
	_currentOrganism = 0;
	_currentFrame = 0;
	_maxFitness = 0;
	_currentInnovation = 1;
	_species.emplace_back(Species());
	_species[0].organisms().push_back(Organism());
}

void MachineGamingEngine::NEAT::Population::newGeneration()
{
	//Remove bottom half of organisms in each species
	removeLowPerformingOrgamisms();

	//Rank genomes across all species
	rankGenomes();

	//Remove species that have exceeded the staleSpecies threshold.
	removeStagnantSpecies();
	rankGenomes();

	for(auto &species : _species)
	{
		species.calculateAverageFitness();
	}
}

void MachineGamingEngine::NEAT::Population::rankGenomes()
{
	_genomeRank.clear();
	/*for (auto& species : _species)
	{
		for()
	}*/
}

void MachineGamingEngine::NEAT::Population::removeLowPerformingOrgamisms()
{
	for (auto& species : _species)
	{
		species.removeLowPerformingOrganisms();
	}
}
