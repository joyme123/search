#include "WordController.h"

InvertedIndexHash WordController::searchWord(std::string word){
	WordDAO wordDao;
	InvertedIndexHash invertedIndexHash = wordDao.searchWord(word);
	return invertedIndexHash;
}