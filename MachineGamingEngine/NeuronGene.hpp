#ifndef NEURONGENE_HPP
#define NEURONGENE_HPP

#include <set>

namespace MachineGamingEngine {
	namespace NEAT {
		enum class Layer {
			INPUT, BIAS, HIDDEN, OUTPUT
		};

		class NeuronGene
		{
		private:
			std::set<int> _incoming;
			Layer _layer;
			float _value;

		public:
			NeuronGene(Layer layer) {
				_layer = layer;
				_value = 0.f;
			};
			~NeuronGene() {};

			float value() const { return _value; }
			void value(float value) { _value = value; }
			Layer layer() const { return _layer; }
			void addIncoming(int from);
			void removeIncoming(int from);
			const std::set<int> incoming() { return _incoming; }
		};
	}
}

#endif // !NEURONGENE_HPP