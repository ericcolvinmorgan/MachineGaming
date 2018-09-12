#ifndef POOL_HPP
#define POOL_HPP

namespace MachineGamingEngine {
	namespace NEAT {
		class Pool
		{
		private:
			//STUB - _species
			int _generation = 0;
			//pool.innovation = Outputs - Total count of number of outputs available? - Seems only innovation on gene is utilized, is this one necessary?
			int _currentSpecies = 1;
			int _currentGenome = 1;
			int _currentFrame = 0;
			int _maxFitness = 0;

		public:
			Pool() {};
			~Pool() {};

			void newGeneration();
		};
	}
}

#endif // !POOL_HPP