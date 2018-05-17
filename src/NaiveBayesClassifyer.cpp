#include "Classification\Classifyer.h"

namespace tcc {
	double NaiveBayesClassifyer::_logLike(std::string& word) const {
		return bow->extract_feature(word, [](double x)
		{
			return std::log((x + 1) / (x + 1));
		}
		);
	}

	double NaiveBayesClassifyer::run(textVec& text) const {
		double labelProb = 0.5;

		for (auto word : text) {
			labelProb += _logLike(word);
		}

		return std::exp(labelProb) / std::exp(labelProb + 1);
	}
}