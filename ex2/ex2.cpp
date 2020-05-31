//================================ Includes =====================================================
#include "VectorParser.h"
#include <numeric>
#include <math.h>
//================================ Constants ====================================================
#define PRINT_BEST_MATCHING_RESULT "Best matching author is "
#define PRINT_SCORE " score "
#define SPACE " "
#define NOT_ENOUGH_ARGUMENTS_ERROR "Usage: find_the_author<frequent_words.txt> <text1> ...\n"
#define MINIMAL_NUMBER_OF_ARGUMENTS 4
#define FIRST_KNOWN_AUTHOR_INDEX 3
#define UNKNOWN_AUTHOR_INDEX 2
#define FREQUENT_WORDS_FILE_INDEX 1
#define EXIT_RETURN_VALUE_FOR_USAGE_ERROR 0
//================================ Code Segment =================================================

/**
 * This function calculates the l2-norm of a vector of ints.
 * @param vector - the int vector which we calculate its norm.
 * @return the l2_norm of a vector of ints.
 */
double l2Norm(std::vector<int> const &vector)
{
	double resultSquared = inner_product(std::begin(vector), std::end(vector),
			                             std::begin(vector), 0.0);
	return sqrt(resultSquared);
}

/**
 * This function calculates the cos angle between two int vectors, while the norm of the first
 * vector is already known. If one of the norms equals zero - we return zero, in order not to
 * divide by zero.
 * @param firstVector - the first input int vector.
 * @param secondVector - the second input int vector.
 * @param normOfFirstVector - the norm of the first vector.
 * @return the cos angle between two int vectors.
 */
double calculateCosThetaAngle(std::vector<int>& firstVector,
						      std::vector<int>& secondVector, double const normOfFirstVector)
{
	double normOfSecondVector = l2Norm(secondVector);

	if(normOfFirstVector == 0 || normOfSecondVector == 0)
	{
		return 0;
	}
	double scalarProduct = inner_product(std::begin(firstVector),
										 std::end(firstVector),
										 std::begin(secondVector), 0.0);
	return scalarProduct / (normOfFirstVector * normOfSecondVector);
}

/**
 * This function prints all the results + best author + her/his best score.
 * @param argc - argument counter for input
 * @param argv - argument values for input
 * @param sizeOfSignature - size of frequent words vector.
 * @param frequentWordsSet - frequent words stored as a set.
 * @param frequentWordsVector - frequent words stored as a vector.
 * @param signatureOfUnknownAuthor - the signature of the unknown input author.
 * @param normOfUnknownAuthorVector - the l2-norm of the unknown input author.
 */
void printResults(int const argc, char const *argv[], unsigned long const sizeOfSignature,
		          std::unordered_set<std::string>& frequentWordsSet,
				  std::vector<std::string>& frequentWordsVector,
				  std::vector<int>& signatureOfUnknownAuthor,
				  double const normOfUnknownAuthorVector)
{
	double bestScore = 0;
	std::string bestAuthor;
	for(int fileIndex = FIRST_KNOWN_AUTHOR_INDEX ; fileIndex < argc ; ++fileIndex)
	{
		std::unordered_map<std::string, int> mapTempFile;
		std::ifstream tempFile(argv[fileIndex]);
		std::vector<int> tempSignature(sizeOfSignature, 0);
		VectorParser::mapText(tempFile, mapTempFile, frequentWordsSet);
		VectorParser::createSignature(frequentWordsVector, tempSignature, mapTempFile);
		double tempScore = calculateCosThetaAngle(signatureOfUnknownAuthor, tempSignature,
				                                  normOfUnknownAuthorVector);
		std::cout << argv[fileIndex] << SPACE << tempScore << std::endl;
		if(tempScore > bestScore)
		{
			bestScore = tempScore;
			bestAuthor = argv[fileIndex];
		}
	}

	std::cout << PRINT_BEST_MATCHING_RESULT << bestAuthor << PRINT_SCORE << bestScore <<
	std::endl;
}

/**
 * This function gets the frequent words stored as a vector and saves them in
 * an unordered set.
 * @param frequentWordsVector - the frequent words stored as a vector.
 * @param frequentWordsSet - the frequent words stored as a set.
 */
void createFrequentWordsUnorderedSet(const std::vector<std::string>& frequentWordsVector,
		                             std::unordered_set<std::string>& frequentWordsSet)
{
	for (const auto &i : frequentWordsVector)
	{
		frequentWordsSet.insert(i);
	}
}

/**
 * This function checks if there are enough input arguments.
 * If not: exit with exit failure. otherwise: don't do anything.
 * @param numOfArgs - number of input arguments.
 */
void checkNumOfArgs(int const numOfArgs)
{
	if(numOfArgs < MINIMAL_NUMBER_OF_ARGUMENTS)
	{
		std :: cout << NOT_ENOUGH_ARGUMENTS_ERROR;
		exit(EXIT_RETURN_VALUE_FOR_USAGE_ERROR);
	}
}

/**
 * This is the main function of the program. it parses all the input data,
 * stores the words in a map and calculates and prints all the results.
 * @param argc - argument counter for input
 * @param argv - argument values for input
 * @return 0 if succeeds, non-zero otherwise.
 */
int main(int const argc, char const *argv[])
{
	checkNumOfArgs(argc);
	std::ifstream frequentWordsFile(argv[FREQUENT_WORDS_FILE_INDEX]);
	std::vector<std::string> frequentWordsVector;
	std::unordered_map<std::string, int> mapUnknownAuthor;
	std::ifstream unknownAuthorFile(argv[UNKNOWN_AUTHOR_INDEX]);
	VectorParser::getFrequentWords(frequentWordsFile, frequentWordsVector);
	std::unordered_set<std::string> frequentWordsSet;
	//create unordered set of frequent words
	createFrequentWordsUnorderedSet(frequentWordsVector, frequentWordsSet);
	//count words from frequent words set in text by using an unordered map
	VectorParser::mapText(unknownAuthorFile, mapUnknownAuthor, frequentWordsSet);
	unsigned long sizeOfVector = (long) frequentWordsVector.size();
	std::vector<int> vectorOfUnknownAuthor(sizeOfVector, 0);
	VectorParser::createSignature(frequentWordsVector, vectorOfUnknownAuthor, mapUnknownAuthor);
	double normOfUnknownAuthorVector = l2Norm(vectorOfUnknownAuthor);

	//print all the results
	printResults(argc, argv, sizeOfVector, frequentWordsSet, frequentWordsVector,
			     vectorOfUnknownAuthor, normOfUnknownAuthorVector);
	return 0;
}