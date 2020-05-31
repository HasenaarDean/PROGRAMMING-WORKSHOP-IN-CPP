//================================ Includes =====================================================
#include "VectorParser.h"
//================================ Code Segment =================================================

/**
 * This class represents a parser which parses and maps files to words (either a frequent words
 * file or an author text file).
 */

/**
 * This function parses the frequent words file to its words ans saves them in a vector.
 * @param file - the frequent words input file.
 * @param frequentWordsVec - the vector which stores all the words.
 */
void VectorParser::getFrequentWords(std::ifstream& file,
		                            std::vector<std::string>& frequentWordsVec)
{

	std::string line;
	while (std::getline(file, line))
	{
		frequentWordsVec.push_back(line);
	}
}

/**
 * This function parses and maps all the words from the author text file, and counts only
 * those which are also in the frequent words set.
 * @param textFile - the input author text file.
 * @param mapWords - the map where we save the words and how many times they appear in
 * the text.
 * @param frequentWordsSet - this is the frequent words stored as an unordered set.
 */
void VectorParser::mapText(std::ifstream &textFile, std::unordered_map<std::string,
		                   int>& mapWords, std::unordered_set<std::string>& frequentWordsSet)
{
	std::string separator{SEPARATORS};
	std::string tempLine;
	while(getline (textFile, tempLine))
	{ // we will read the file line by line
		size_t tempEndOfWord, tempStartOfWord = 0;
		do  {
			// we want to ignore all the separators
			tempStartOfWord = tempLine.find_first_not_of(separator, tempStartOfWord);
			// we want to stop if there are no word left anymore
			if (tempStartOfWord == std :: string :: npos)
			{
				break;
			}
			// now we will look for the next separator
			tempEndOfWord = tempLine.find_first_of(separator, tempStartOfWord);
			//now we will create the next word
			std :: string tempWord(tempLine.substr(tempStartOfWord,
					                               tempEndOfWord - tempStartOfWord));
			toLowercase(tempWord); //we convert word to lowercase
			if(frequentWordsSet.count(tempWord))
			{
				mapWords[tempWord]++;
			}
			// now we will update the position of the start of next word to be after the separator
			tempStartOfWord = tempEndOfWord + 1;
			}
		while (tempEndOfWord != std :: string :: npos); // continue as long as there are lines
	}
}

/**
 * This function calculates the int vector (signature) of the author.
 * @param frequentWordsVector - this is the frequent words stored as a vector of strings.
 * @param signature - the signature that we return.
 * @param mapWords - the map of the author text.
 */
void VectorParser :: createSignature(std::vector<std::string>& frequentWordsVector,
		                             std::vector<int>& signature,
		                             std::unordered_map<std::string, int>& mapWords)
{
	int j = 0;

	for (StringVectorIterator i = frequentWordsVector.begin();
		 i != frequentWordsVector.end(); ++i)
	{
		signature[j] = mapWords[*i];
		++j;
	}
}

/**
 * This function gets a string and convert each character of it to lowercase.
 * @param str - the input string that we get.
 */
void VectorParser :: toLowercase(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}