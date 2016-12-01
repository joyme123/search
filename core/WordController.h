#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include"WordDAO.h"

class WordController{
public:
	InvertedIndexHash searchWord(std::string word);

};
#endif