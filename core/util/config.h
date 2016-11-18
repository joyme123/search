#ifndef CONFIG_H
#define CONFIG_H

#define FRISO_DICT_PATH "../../resource/friso.ini"

enum InvertHashIndexType{
	ngramWord = 0,
	splitWord = 1
};

enum DOCUMENT_TYPE{
	html=1,
	pdf=2,
	word=3
};

#endif