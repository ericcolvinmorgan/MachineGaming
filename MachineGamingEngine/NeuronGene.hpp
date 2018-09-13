#ifndef NEURONGENE_HPP
#define NEURONGENE_HPP

namespace MachineGamingEngine {
	namespace NEAT {
		enum Layer {
			INPUT, BIAS, HIDDEN, OUTPUT
		};

		class NeuronGene
		{
		private:
			// Gene List _incoming;
			Layer _layer;
			int _value;

		public:
			NeuronGene() {};
			~NeuronGene() {};
		};
	}
}

#endif // !NEURONGENE_HPP