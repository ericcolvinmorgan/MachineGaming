#include "stdafx.h"
#include "Genome.hpp"
#include <iterator>

std::default_random_engine& MachineGamingEngine::NEAT::Genome::_numberGenerator()
{
	static std::default_random_engine generator{};
	return generator;
}

MachineGamingEngine::NEAT::Genome::Genome(int numberInputs, int numberOutputs)
{
	_numberInputs = numberInputs;
	_numberOutputs = numberOutputs;

	for (int i = 0; i < _numberInputs; i++)
		_neuronGenes.push_back(NeuronGene(NEAT::Layer::INPUT));

	_neuronGenes.push_back(NeuronGene(NEAT::Layer::BIAS));

	for (int i = 0; i < _numberOutputs; i++)
		_neuronGenes.push_back(NeuronGene(NEAT::Layer::OUTPUT));
}

bool MachineGamingEngine::NEAT::Genome::containsLink(int fromIndex, int toIndex)
{
	return _connectGenes.find({ fromIndex, toIndex }) != _connectGenes.end();
}

void MachineGamingEngine::NEAT::Genome::setInputs(float* inputs)
{
	for (int i = 0; i < _numberInputs; i++)
	{
		_neuronGenes[i].value(inputs[i]);
	}
}

void MachineGamingEngine::NEAT::Genome::getOutputs(float* outputs)
{
	for (size_t i = 0; i < _numberOutputs; i++)
	{
		outputs[i] = _neuronGenes[(size_t)_numberInputs + 1 + i].value();
	}
}

void MachineGamingEngine::NEAT::Genome::addNeuronGene(int& innovation)
{
	if (_connectGenes.size() == 0)
		return;

	auto generator = _numberGenerator();
	std::uniform_int_distribution<int> distribution(0, (int)_connectGenes.size() - 1);
	auto connection = _connectGenes.begin();
	std::advance(connection, distribution(generator));
	
	//Insert New Node
	_neuronGenes.push_back(NeuronGene(NEAT::Layer::HIDDEN));
	int neuronIndex = (int)_neuronGenes.size() - 1;

	//Insert New Connections
	//The old connection is disabled and two new connections are added to the genome.
	connection->second.enabled(false);
	
	//The new connection leading into the new node receives a weight of 1, and the new connection leading out receives the same weight as the old connection.
	_lastInnovation = innovation;
	_connectGenes.emplace(std::piecewise_construct, 
		std::forward_as_tuple(connection->first.first, neuronIndex), 
		std::forward_as_tuple(connection->first.first, neuronIndex, 1.f, true, innovation++));
	
	//_connectGenes[std::make_pair(connection->first.first, neuronIndex)] = ConnectGene(connection->first.first, neuronIndex, 1.f, true, innovation++);
	_neuronGenes[neuronIndex].addIncoming(connection->first.first);

	_lastInnovation = innovation;
	_connectGenes[std::make_pair(neuronIndex, connection->first.second)] = ConnectGene(neuronIndex, connection->first.second, connection->second.weight(), true, innovation++);
	_neuronGenes[connection->first.second].addIncoming(neuronIndex);
}

void MachineGamingEngine::NEAT::Genome::addConnectGene(int& innovation, int from, int to)
{
	bool connectionFound = false;
	int maxAttempts = 10;

	auto &generator = _numberGenerator();
	while (!connectionFound && maxAttempts > 0)
	{
		//Randomize From Node
		if (from == -1)
		{
			std::uniform_int_distribution<int> distribution(0, (int)_neuronGenes.size() - 1);

		}

		//Randomize To Node
		if (to == -1)
		{

		}

		if ((_neuronGenes[from].layer() >= NEAT::Layer::INPUT && _neuronGenes[to].layer() > NEAT::Layer::INPUT)
			&& _connectGenes.find(std::make_pair(from, to)) == _connectGenes.end())
			connectionFound = true;

		maxAttempts--;
	}

	if (!connectionFound)
		return;

	//Insert Link
}

void MachineGamingEngine::NEAT::Genome::perturbConnections(float perturbChance, float step)
{
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	for (auto& connection : _connectGenes)
	{
		auto generator = _numberGenerator();
		double chance = distribution(generator);
		float weight = connection.second.weight();
		if (chance <= perturbChance)
		{
			//Update Existing
			std::uniform_real_distribution<float> weightDistribution(step * -1.f, step);
			weight += weightDistribution(generator);
		}
		else
		{
			//Generate New
			std::uniform_real_distribution<float> weightDistribution(-1.0f, 1.0f);
			weight = weightDistribution(generator);
		}
		connection.second.weight(weight);
	}
}

void MachineGamingEngine::NEAT::Genome::activate()
{
	//(_numberInputs + _numberOutputs + 1) - Start after inputs, outputs, and bias node.
	for (int n = (_numberInputs + _numberOutputs + 1); n < (int)_neuronGenes.size(); n++)
	{
		float sum = 0.f;
		for (int i : _neuronGenes[n].incoming())
		{
			auto &conn = _connectGenes[std::make_pair(i, n)];
			if (conn.enabled())
			{
				sum += _neuronGenes[i].value() * conn.weight();
			}
		}
		float value = (2.f / (1.f + (exp(-4.9f * sum)))) - 1.f; //Values between -1 and 1;
		_neuronGenes[n].value(value);
	}

	//Calculate Outputs
	for (int n = (_numberInputs + 1); n < (int)_neuronGenes.size(); n++)
	{
		if (_neuronGenes[n].layer() != NEAT::Layer::OUTPUT)
			break;

		float sum = 0.f;
		for (int i : _neuronGenes[n].incoming())
		{
			auto &conn = _connectGenes[std::make_pair(i, n)];
			if (conn.enabled())
			{
				sum += _neuronGenes[i].value() * conn.weight();
			}
		}
		float value = (2.f / (1.f + (exp(-4.9f * sum)))) - 1.f; //Values between -1 and 1;
		_neuronGenes[n].value(value);
	}
}

void MachineGamingEngine::NEAT::Genome::mutateRandomConnection(bool updateStatus)
{
	std::vector<ConnectGene*> connections;
	for (auto connection : _connectGenes)
	{
		if (connection.second.enabled() != updateStatus)
			connections.push_back(&connection.second);
	}

	if (connections.size() == 0)
		return;

	auto generator = _numberGenerator();
	std::uniform_int_distribution<int> distribution(0, (int)connections.size() - 1);
	connections[distribution(generator)]->enabled(updateStatus);
}
