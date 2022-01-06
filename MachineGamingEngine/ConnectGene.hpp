#ifndef CONNECTGENE_HPP
#define CONNECTGENE_HPP

namespace MachineGamingEngine {
	namespace NEAT {
		class ConnectGene
		{
		private:
			int _from = 0;
			int _to = 0;
			float _weight = 0.f;
			bool _enabled = false;
			int _innovation = 0;

		public:
			ConnectGene() {}
			ConnectGene(int from, int to, float weight, bool enabled, int innovation) {
				_from = from;
				_to = to;
				_weight = weight;
				_enabled = enabled;
				_innovation = innovation;
			};
			bool enabled() const { return _enabled; }
			void enabled(bool enabled) { _enabled = enabled; }
			float weight() const { return _weight; }
			void weight(float weight) { _weight = weight; }
			int innovation() { return _innovation; };
		};
	}
}

#endif // !CONNECTGENE_HPP