#pragma once
#include "pch.h"
#define FUNC_MAX_SIZE 5

namespace Lex
{
	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable idtable;
	};
	LEX Lexer(ICP::ICP, Log::LOG log);
}
