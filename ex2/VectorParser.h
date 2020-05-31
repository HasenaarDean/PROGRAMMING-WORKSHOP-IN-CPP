//================================ Constants ====================================================
#ifndef CPP2_PARSER_H
#define CPP2_PARSER_H
#define SEPARATORS " \r\n,!;:\""
//================================ Includes =====================================================
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
//================================ Code Segment =================================================

/**
 * This type represents the type of an iterator of a vector of strings.
 */
typedef std::vector<std::string>::const_iterator StringVectorIterator;

/**
 * This class represents a parser which parses and maps files to vectors of
 * words / map of words with a counter value which counts the number of appearances
 * of a word in a text file (we can parse either a frequent words file or an author text file).
 */
class VectorParser
{
	public:

	/**
	 * This function parses the frequent words file to its words ans saves them in a vector.
	 * @param file - the frequent words input file.
	 * @param frequentWordsVec - the vector which stores all the words.
	 */
	static void getFrequentWords(std::ifstream& file, std::vector<std::string>& frequentWordsVec);

	/**
	 * This function parses and maps all the words from the author text file, and counts only
	 * those which are also in the frequent words set.
	 * @param textFile - the input author text file.
	 * @param mapWords - the map where we save the words and how many times they appear in
	 * the text.
	 * @param frequentWordsSet - this is the frequent words stored as an unordered set.
	 */
	static void mapText(std::ifstream& textFile, std::unordered_map<std::string, int>& mapWords,
						std::unordered_set<std::string>& frequentWordsSet);

	/**
	 * This function calculates the int vector (signature) of the author.
	 * @param frequentWordsVector - this is the frequent words stored as a vector of strings.
	 * @param signature - the signature that we return.
	 * @param mapWords - the map of the author text.
	 */
	static void createSignature(std::vector<std::string>& frequentWordsVector,
			                    std::vector<int>& signature,
			                    std::unordered_map<std::string, int>& mapWords);

	/**
	 * This function gets a string and convert each character of it to lowercase.
	 * @param str - the input string that we get.
	 */
	static void toLowercase(std::string& str);

	private:

};


#endif //CPP2_PARSER_H
