#include "../Classification/Classifyer.h"

namespace tcc {
	double NaiveBayesClassifyer::_logLike(std::string& word) const {
		auto word_inf = bow->find_word(word);

		if (word_inf.freq > 100)
		{
			auto like = double(word_inf.categories_freq[_ind]) / word_inf.freq;
			auto unlike = (word_inf.freq - double(word_inf.categories_freq[_ind])) / word_inf.freq;

			return log(like / unlike);
		}

		return 0;
	}

	double NaiveBayesClassifyer::run(textVec& text) const {
		double labelProb = 0.5;

		for (auto word : text) {
			auto p = _logLike(word);
			
			labelProb += p;
		}

		return 1 / (exp(-labelProb) + 1);
	}
}