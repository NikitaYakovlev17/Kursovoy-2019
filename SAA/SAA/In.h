#pragma once
#include "pch.h"
#define ICP_MAX_LEN_TEXT 1024*1024			// максимальный размер исходного кода 1МБ
#define ICP_WORD_MAX_LEN 255					// максимальный размер слова

#define STR_NUMB_SEP	'|'					// сепаратор для новой строки
#define ICP_CODE_SPACE	' '					// пробел
#define ICP_CODE_ENDL    '\n'				// переход на новую строку

//  ICP::F -- запрещенный символ,
//  ICP::T  --  разрешенный символ,
//  ICP::S -- сепараторы	(	)	*	+   ,	-   =	;   :	[	]

#define ICP_CODE_TABLE {\
	   	 /* 0 */ /* 1 */ /* 2 */ /* 3 */ /* 4 */ /* 5 */ /* 6 */ /* 7 */ /* 8 */ /* 9 */ /* A */ /* B */ /* C */ /* D */ /* E */ /* F */ \
/*0*/    ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::T, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, \
/*1*/    ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, \
/*2*/    ICP::T, ICP::F, ICP::T, ICP::T, ICP::F, ICP::F, ICP::F, ICP::T, ICP::S, ICP::S, ICP::S, ICP::S, ICP::S, ICP::S, ICP::T, ICP::F, \
/*3*/    ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::S, ICP::S, ICP::S, ICP::S, ICP::T, ICP::F, \
/*4*/	 ICP::F, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, \
/*5*/    ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::S, ICP::F, ICP::S, ICP::F, ICP::F, \
/*6*/    ICP::F, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, \
/*7*/    ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, \
     \
/*8*/    ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, \
/*9*/    ICP::F, ICP::F, ICP::F, ICP::T, ICP::T, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, \
/*A*/    ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, \
/*B*/    ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, ICP::F, \
/*C*/    ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, \
/*D*/    ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, \
/*E*/    ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, \
/*F*/    ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T, ICP::T \
}


namespace ICP
{
	struct Word
	{
		string word;
		int line;
	};

	struct ICP
	{
		enum { T = 1, F = 2, S = 3 };		
		int size;							// Текущий размер исходного кода
		int lines;							// Количество строк
		int ignor;							// Количество проигнорированных символов
		queue<Word> Words;
		int code[256] = ICP_CODE_TABLE;		// Таблица проверки
	};

	ICP GetIn(wchar_t Infile[]);
};