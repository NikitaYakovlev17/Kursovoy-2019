#pragma once
#include "Log.h"
#define LT_NOPRIORITY 0xffffffff		//нет приоритета
#define LEXEMA_FIXZISE 1				//фиксированный размер лексемы
#define LT_MAXSIZE 4096			//максимальное кол-во строк в таблице лексем   
#define TL_TI_NULLIDX 0xffffffff		//нет элемента таблицы идентификаторов
#define LEX_T			't'				
#define LEX_REAL		'r'				//	digital
#define LEX_WORD		'w'				//	string
#define LEX_DIM			'd'				//	var
#define LEX_PROC		'p'				//	function
#define LEX_ENTRY		'm'				//	start
#define LEX_END			'e'				//	ret
#define LEX_LITERAL		'l'				//	литерал
#define LEX_READ		's'				//	show
#define LEX_POW			'q'				//	pow
#define LEX_STRLN		'n'				//	strlen
#define LEX_ID			'i'				//	идентификатор
#define LEX_ACTION		'a'
#define LEX_SEMICOLON	';'				//	;
#define LEX_COLON		':'				//	:
#define LEX_COMMA		','				//	,
#define LEX_LEFTHESIS	'('				//	(
#define LEX_RIGHTHESIS	')'				//	)
#define LEX_EQUAL		'='				//  =
#define LEX_LEFTBRACE	'['				//	{
#define LEX_RIGHTBRACE	']'				//	}
#define LEX_LESS		'<'
#define LEX_PLUS		'+'				//	+
#define LEX_MINUS		'-'				//	-
#define LEX_MULTIPLY	'*'				//	*
#define LEX_STRLIT		'"'				//  "
#define LEX_SUBST		'@'
#define LEX_L			'L'				//  L
#define LEX_SEP			'|'				// символ конца строки

namespace LT
{										// таблица лексем
	struct Entry
	{
		char lexema;						// лексема
		int lineNo;						// номер строки в исходном коде
		int indexTI;							// индекс в таблице идентификаторов 
		short priority;						// приоритет для операций
	};

	struct LexTable
	{
		int maxize;							// емкость таблицы лексем 
		int size;							// текущий размер таблицы лексем
		Entry* table;						// массив строк табилцы лексем	
	};

	LexTable Create(int size);
	Entry GetEntry(LexTable& lextable, int n);
	Entry Add(LexTable& lextable, Entry entry);
	void ShowTable(LexTable& lexTable);
	void Write(Log::LOG log, LexTable& lexTable);
}