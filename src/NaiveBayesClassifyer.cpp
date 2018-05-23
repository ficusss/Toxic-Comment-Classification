#include "Classification\Classifyer.h"

namespace tcc {
	double NaiveBayesClassifyer::_logLike(std::string& word) const {
		auto word_inf = bow->find_word(word);

		if (word_inf.freq)
			return double(word_inf.categories_freq[_ind]) / word_inf.freq;

		return 0;
	}

	double NaiveBayesClassifyer::run(textVec& text) const {
		double labelProb = 1;
		double not_labelProb = 1;

		for (auto word : text) {
			auto p = _logLike(word);

			labelProb *= p;
			not_labelProb *= 1 - p;

		}

		return labelProb / (labelProb + not_labelProb);
	}
}