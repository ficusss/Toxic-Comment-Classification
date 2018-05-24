#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Stemmer.h"

//основная функция стеммера, приклеивает not к след слову и обрезает окончания
//на вход - то, что отдал провайдер
//на выходе - вектор векторов (матрица), где строка матрицы - один комментарий, все слова приведены к начальной форме
tcc::BOW tcc::PorterStemming::stem(std::vector<json> text) {

	std::vector<std::vector<std::string>> all_text(text.size(), std::vector<std::string>());
	std::string buf_comment;
	std::string buf_word;
	std::string tag = "comment_text";
	std::string neg = "not";
	bool for_not = false;

	size_t i = 0;
	tcc::BOW res = tcc::BOW();
	int k = 0;

	for (json el : text) {

		buf_comment = el[tag];

		std::istringstream iss(buf_comment, std::istringstream::in);
		while (iss >> buf_word) {
			std::cout << buf_word;
			if (buf_word == "not") {
				for_not = true;
				continue;
			}

			if (for_not)
				buf_word = neg + buf_word;
			trim(buf_word);
			stem_word(buf_word);

			res.add_word(buf_word, el["rating"]);
			for_not = false;
		}
		i++;

	}

	return res;
}

std::vector<std::string> tcc::PorterStemming::stem_string_to_vec(std::string text)
{
	std::vector<std::string> res;
	//std::string buf_comment;
	std::string buf_word;
	bool for_not = false;
	std::string neg = "not";

	std::istringstream iss(text, std::istringstream::in);
	while (iss >> buf_word) {
		if (buf_word == "not") {
			for_not = true;
			continue;
		}

		if (for_not)
			buf_word = neg + buf_word;
		trim(buf_word);
		stem_word(buf_word);

		if (buf_word.size() != 0)
			res.push_back(buf_word);
		for_not = false;
	}

	return res;
}

std::vector<json> tcc::PorterStemming::stem_for_print(std::vector<json> text) {

	std::vector<std::vector<std::string>> all_text(text.size(), std::vector<std::string>());
	std::string buf_comment;
	std::string buf_word;
	std::string tag = "comment_text";
	std::string neg = "not";
	bool for_not = false;

	size_t i = 0;
	for (json el : text) {

		buf_comment = el[tag];

		std::istringstream iss(buf_comment, std::istringstream::in);
		while (iss >> buf_word) {
			if (buf_word == "not") {
				for_not = true;
				continue;
			}

			if (for_not)
				buf_word = neg + buf_word;
			all_text[i].push_back(buf_word);
			for_not = false;
		}

		i++;

	}
	for (auto it = all_text.begin(); it != all_text.end(); ++it) {
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			trim(*it2);
			stem_word((*it2));
		}
	}

	std::vector<json> res = {};
	json buf;

	int id = 0;
	for (auto comment : all_text)
	{
		buf["id"] = id;
		buf["comment_text"] = comment;
		res.push_back(buf);
		id++;
	}

	return res;
}

void tcc::PorterStemming::stem_word(std::string& word) {

	ignore(word);
	if (word.size() == 0)
		return;

	// special case short words or sentence tags
	if (word.size() <= 2 || word == "<s>" || word == "</s>")
		return;

	// max word length is 35 for English
	if (word.size() > 35)
		word = word.substr(0, 35);

	if (word[0] == '\'')
		word = word.substr(1, word.size() - 1);

	if (special(word))
		return;

	changeY(word);
	size_t startR1 = getStartR1(word);
	size_t startR2 = getStartR2(word, startR1);

	step0(word);

	if (step1A(word))
	{
		std::replace(word.begin(), word.end(), 'Y', 'y');
		return;
	}

	step1B(word, startR1);
	step1C(word);
	step2(word, startR1);
	step3(word, startR1, startR2);
	step4(word, startR2);
	step5(word, startR1, startR2);

	std::replace(word.begin(), word.end(), 'Y', 'y');
	return;
}

void tcc::PorterStemming::ignore(std::string & word)
{
	static const std::vector<std::pair<std::string, std::string>> subs
		= { { "a", "" },
		{ "the", "" },
		{ "at", "" },
		{ "and", "" },
		{ "an", "" },
		{ "all", "" },
		{ "am", "" },
		{ "another", "" },
		{ "any", "" },
		{ "are", "" },
		{ "arent", "" },
		{ "as", "" },
		{ "at", "" },
		{ "be", "" },
		{ "but", "" },
		{ "by", "" },
		{ "can", "" },
		{ "cant", "" },
		{ "did", "" },
		{ "didnt", "" },
		{ "do", "" },
		{ "does", "" },
		{ "doesnt", "" },
		{ "dont", "" },
		{ "each", "" },
		{ "end", "" },
		{ "had", "" },
		{ "have", "" },
		{ "hasnt", "" },
		{ "havent", "" },
		{ "was", "" },
		{ "wasnt", "" },
		{ "that", "" },
		{ "on", "" } };

	for (auto& sub : subs)
		if (replaceIfExists(word, sub.first, sub.second, 0))
			return;
}

void tcc::PorterStemming::trim(std::string& word)
{
	if (word == "<s>" || word == "</s>")
		return;

	//std::count_if(word.begin(), word.end(), [](const char& a) { return ::isupper(a); });
	//		word.info = UPPERCASE;
	//	else
	//		word.info = LOWERCASE;

	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	for (std::string::iterator i = word.begin(); i != word.end();) {
		if (!('a' <= *i && *i <= 'z')) {
			word.erase(word.find(*i), 1);
			continue;
		}
		i++;
		if (i == word.end())
			break;
	}
}

size_t tcc::PorterStemming::getStartR1(const std::string& word)
{
	// special cases
	if (word.size() >= 5 && word[0] == 'g' && word[1] == 'e' && word[2] == 'n'
		&& word[3] == 'e' && word[4] == 'r')
		return 5;
	if (word.size() >= 6 && word[0] == 'c' && word[1] == 'o' && word[2] == 'm'
		&& word[3] == 'm' && word[4] == 'u' && word[5] == 'n')
		return 6;
	if (word.size() >= 5 && word[0] == 'a' && word[1] == 'r' && word[2] == 's'
		&& word[3] == 'e' && word[4] == 'n')
		return 5;

	// general case
	return firstNonVowelAfterVowel(word, 1);
}

size_t tcc::PorterStemming::getStartR2(const std::string& word,
	size_t startR1)
{
	if (startR1 == word.size())
		return startR1;

	return firstNonVowelAfterVowel(word, startR1 + 1);
}

size_t tcc::PorterStemming::firstNonVowelAfterVowel(const std::string& word,
	size_t start)
{
	for (size_t i = start; i != 0 && i < word.size(); ++i)
	{
		if (!isVowelY(word[i]) && isVowelY(word[i - 1]))
			return i + 1;
	}

	return word.size();
}

void tcc::PorterStemming::changeY(std::string& word)
{
	if (word[0] == 'y')
		word[0] = 'Y';

	for (size_t i = 1; i < word.size(); ++i)
	{
		if (word[i] == 'y' && isVowel(word[i - 1]))
			word[i++] = 'Y'; // skip next iteration
	}
}

/**
Step 0
*/
void tcc::PorterStemming::step0(std::string& word)
{
	// short circuit the longest suffix
	replaceIfExists(word, "'s'", "", 0) || replaceIfExists(word, "'s", "", 0)
		|| replaceIfExists(word, "'", "", 0);
}

/*
Step 1a:

sses
replace by ss

ied   ies
replace by i if preceded by more than one letter, otherwise by ie
(so ties -> tie, cries -> cri)

us   ss
do nothing

s
delete if the preceding word part contains a vowel not immediately before
the
s (so gas and this retain the s, gaps and kiwis lose it)
*/
bool tcc::PorterStemming::step1A(std::string& word)
{
	if (!replaceIfExists(word, "sses", "ss", 0))
	{
		if (endsWith(word, "ied") || endsWith(word, "ies"))
		{
			// if preceded by only one letter
			if (word.size() <= 4)
				word.pop_back();
			else
			{
				word.pop_back();
				word.pop_back();
			}
		}
		else if (endsWith(word, "s") && !endsWith(word, "us")
			&& !endsWith(word, "ss"))
		{
			if (word.size() > 2 && containsVowel(word, 0, word.size() - 2))
				word.pop_back();
		}
	}

	// special case after step 1a
	return word == "inning" || word == "outing" || word == "canning"
		|| word == "herring" || word == "earring" || word == "proceed"
		|| word == "exceed" || word == "succeed";
}
/*
Step 1b:

eed   eedly
replace by ee if in R1

ed   edly   ing   ingly
delete if the preceding word part contains a vowel, and after the
deletion:
if the word ends at, bl or iz add e (so luxuriat -> luxuriate), or
if the word ends with a double remove the last letter (so hopp -> hop), or
if the word is short, add e (so hop -> hope)
*/


void tcc::PorterStemming::step1B(std::string& word, size_t startR1)
{
	bool exists = endsWith(word, "eedly") || endsWith(word, "eed");

	if (exists) // look only in startR1 now
		replaceIfExists(word, "eedly", "ee", startR1)
		|| replaceIfExists(word, "eed", "ee", startR1);
	else
	{
		size_t size = word.size();
		bool deleted = (containsVowel(word, 0, size - 2)
			&& replaceIfExists(word, "ed", "", 0))
			|| (containsVowel(word, 0, size - 4)
				&& replaceIfExists(word, "edly", "", 0))
			|| (containsVowel(word, 0, size - 3)
				&& replaceIfExists(word, "ing", "", 0))
			|| (containsVowel(word, 0, size - 5)
				&& replaceIfExists(word, "ingly", "", 0));

		if (deleted && (endsWith(word, "at") || endsWith(word, "bl")
			|| endsWith(word, "iz")))
			word.push_back('e');
		else if (deleted && endsInDouble(word))
			word.pop_back();
		else if (deleted && startR1 == word.size() && isShort(word))
			word.push_back('e');
	}
}

/*
Step 1c:

Replace suffix y or Y by i if preceded by a non-vowel which is not the first
letter of the word (so cry -> cri, by -> by, say -> say)
*/

void tcc::PorterStemming::step1C(std::string& word)
{
	size_t size = word.size();
	if (size > 2 && (word[size - 1] == 'y' || word[size - 1] == 'Y'))
		if (!isVowel(word[size - 2]))
			word[size - 1] = 'i';
}

/*
Step 2:

If found and in R1, perform the action indicated.

tional:               replace by tion
enci:                 replace by ence
anci:                 replace by ance
abli:                 replace by able
entli:                replace by ent
izer, ization:        replace by ize
ational, ation, ator: replace by ate
alism, aliti, alli:   replace by al
fulness:              replace by ful
ousli, ousness:       replace by ous
iveness, iviti:       replace by ive
biliti, bli:          replace by ble
fulli:                replace by ful
lessli:               replace by less
ogi:                  replace by og if preceded by l
li:                   delete if preceded by a valid li-ending
*/


void tcc::PorterStemming::step2(std::string& word, size_t startR1)
{
	static const std::vector<std::pair<std::string, std::string>> subs
		= { { "ational", "ate" },
		{ "tional", "tion" },
		{ "enci", "ence" },
		{ "anci", "ance" },
		{ "abli", "able" },
		{ "entli", "ent" },
		{ "izer", "ize" },
		{ "ization", "ize" },
		{ "ation", "ate" },
		{ "ator", "ate" },
		{ "alism", "al" },
		{ "aliti", "al" },
		{ "alli", "al" },
		{ "fulness", "ful" },
		{ "ousli", "ous" },
		{ "ousness", "ous" },
		{ "iveness", "ive" },
		{ "iviti", "ive" },
		{ "biliti", "ble" },
		{ "bli", "ble" },
		{ "fulli", "ful" },
		{ "lessli", "less" } };

	for (auto& sub : subs)
		if (replaceIfExists(word, sub.first, sub.second, startR1))
			return;

	if (!replaceIfExists(word, "logi", "log", startR1 - 1))
	{
		// make sure we choose the longest suffix
		if (endsWith(word, "li") && !endsWith(word, "abli")
			&& !endsWith(word, "entli") && !endsWith(word, "aliti")
			&& !endsWith(word, "alli") && !endsWith(word, "ousli")
			&& !endsWith(word, "bli") && !endsWith(word, "fulli")
			&& !endsWith(word, "lessli"))
			if (word.size() > 3 && word.size() - 2 >= startR1
				&& isValidLIEnding(word[word.size() - 3]))
			{
				word.pop_back();
				word.pop_back();
			}
	}
}

/*
Step 3:

If found and in R1, perform the action indicated.

ational:            replace by ate
tional:             replace by tion
alize:              replace by al
icate, iciti, ical: replace by ic
ful, ness:          delete
ative:              delete if in R2
*/

void tcc::PorterStemming::step3(std::string& word, size_t startR1,
	size_t startR2)
{
	static const std::vector<std::pair<std::string, std::string>> subs
		= { { "ational", "ate" },
		{ "tional", "tion" },
		{ "alize", "al" },
		{ "icate", "ic" },
		{ "iciti", "ic" },
		{ "ical", "ic" },
		{ "ful", "" },
		{ "ness", "" } };

	for (auto& sub : subs)
		if (replaceIfExists(word, sub.first, sub.second, startR1))
			return;

	replaceIfExists(word, "ative", "", startR2);
}

/*
Step 4:

If found and in R2, perform the action indicated.

al ance ence er ic able ible ant ement ment ent ism ate
iti ous ive ize
delete
ion
delete if preceded by s or t
*/

void tcc::PorterStemming::step4(std::string& word, size_t startR2)
{
	static const std::vector<std::pair<std::string, std::string>> subs
		= { { "al", "" },
		{ "ance", "" },
		{ "ence", "" },
		{ "er", "" },
		{ "ic", "" },
		{ "able", "" },
		{ "ible", "" },
		{ "ant", "" },
		{ "ement", "" },
		{ "ment", "" },
		{ "ism", "" },
		{ "ate", "" },
		{ "iti", "" },
		{ "ous", "" },
		{ "ive", "" },
		{ "ize", "" } };

	for (auto& sub : subs)
		if (replaceIfExists(word, sub.first, sub.second, startR2))
			return;

	// make sure we only choose the longest suffix
	if (!endsWith(word, "ement") && !endsWith(word, "ment"))
		if (replaceIfExists(word, "ent", "", startR2))
			return;

	// short circuit
	replaceIfExists(word, "sion", "s", startR2 - 1)
		|| replaceIfExists(word, "tion", "t", startR2 - 1);
}

/*
Step 5:

e     delete if in R2, or in R1 and not preceded by a short syllable
l     delete if in R2 and preceded by l
*/

void tcc::PorterStemming::step5(std::string& word, size_t startR1,
	size_t startR2)
{
	size_t size = word.size();
	if (word[size - 1] == 'e')
	{
		if (size - 1 >= startR2)
			word.pop_back();
		else if (size - 1 >= startR1 && !isShort(word.substr(0, size - 1)))
			word.pop_back();
	}
	else if (word[word.size() - 1] == 'l')
	{
		if (word.size() - 1 >= startR2 && word[word.size() - 2] == 'l')
			word.pop_back();
	}
}

/*
Determines whether a word ends in a short syllable.
Define a short syllable in a word as either

(a) a vowel followed by a non-vowel other than w, x or Y and preceded by a
non-vowel
(b) a vowel at the beginning of the word followed by a non-vowel.
*/

bool tcc::PorterStemming::isShort(const std::string& word)
{
	size_t size = word.size();

	if (size >= 3)
	{
		if (!isVowelY(word[size - 3]) && isVowelY(word[size - 2])
			&& !isVowelY(word[size - 1]) && word[size - 1] != 'w'
			&& word[size - 1] != 'x' && word[size - 1] != 'Y')
			return true;
	}
	return size == 2 && isVowelY(word[0]) && !isVowelY(word[1]);
}

bool tcc::PorterStemming::special(std::string& word)
{
	static const std::unordered_map<std::string, std::string> exceptions
		= { { "skis", "ski" },
		{ "skies", "sky" },
		{ "dying", "die" },
		{ "lying", "lie" },
		{ "tying", "tie" },
		{ "idly", "idl" },
		{ "gently", "gentl" },
		{ "ugly", "ugli" },
		{ "early", "earli" },
		{ "only", "onli" },
		{ "singly", "singl" } };

	// special cases
	auto ex = exceptions.find(word);
	if (ex != exceptions.end())
	{
		word = ex->second;
		return true;
	}

	// invariants
	return word == "sky" || word == "news" || word == "howe" || word == "atlas"
		|| word == "cosmos" || word == "bias" || word == "andes";
}

bool tcc::PorterStemming::isVowelY(char ch)
{
	return ch == 'e' || ch == 'a' || ch == 'i' || ch == 'o' || ch == 'u'
		|| ch == 'y';
}

bool tcc::PorterStemming::isVowel(char ch)
{
	return ch == 'e' || ch == 'a' || ch == 'i' || ch == 'o' || ch == 'u';
}

bool tcc::PorterStemming::endsWith(const std::string& word,
	const std::string& str)
{
	return word.size() >= str.size()
		&& std::equal(word.begin() + (word.size() - str.size()), word.end(),
			str.begin());
}

bool tcc::PorterStemming::endsInDouble(const std::string& word)
{
	if (word.size() >= 2)
	{
		char a = word[word.size() - 1];
		char b = word[word.size() - 2];

		if (a == b)
			return a == 'b' || a == 'd' || a == 'f' || a == 'g' || a == 'm'
			|| a == 'n' || a == 'p' || a == 'r' || a == 't';
	}

	return false;
}


bool tcc::PorterStemming::replaceIfExists(std::string& word, const std::string& suffix, const std::string& replacement, size_t start)
{
	int idx = (int)word.size() - (int)suffix.size();
	if (idx < start || idx < 0)
		return false;

	if (std::equal(word.begin() + idx, word.end(), suffix.begin()))
	{
		word = word.substr(0, word.size() - suffix.size()) + replacement;
		return true;
	}
	return false;
}

bool tcc::PorterStemming::isValidLIEnding(char ch)
{
	return ch == 'c' || ch == 'd' || ch == 'e' || ch == 'g' || ch == 'h'
		|| ch == 'k' || ch == 'm' || ch == 'n' || ch == 'r' || ch == 't';
}

bool tcc::PorterStemming::containsVowel(const std::string& word,
	size_t start, size_t end)
{
	if (end <= word.size())
	{
		for (size_t i = start; i < end; ++i)
			if (isVowelY(word[i]))
				return true;
	}
	return false;
}