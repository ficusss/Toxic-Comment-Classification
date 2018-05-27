#include "Core.h"

namespace tcc {
	std::vector<double> RandomCore::run(textVec& t) const {
		std::vector<double> result;

		for (auto el : _model)
			result.push_back(el->run(t));

		return result;
	};
}