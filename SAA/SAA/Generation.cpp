#include "pch.h"
#include "Generation.h"
#include <stack>

namespace Generation
{
	void Generation(Lex::LEX lex, Log::LOG log)
	{
		*(log.stream) << ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib\n\tincludelib ..\\Debug\\Lib.lib\n\tExitProcess PROTO :DWORD\n\n";
		*(log.stream) << "\treadw PROTO: DWORD\n\treadr PROTO: DWORD\n\tstrln PROTO: DWORD\n\tpower PROTO: DWORD, :DWORD\n";
		*(log.stream) << "\n.stack 4096\n";

		*(log.stream) << ".const\n";
		for (int i = 0; i < lex.idtable.size; i++)			// »щем в таблице идентификаторов ищем литералы и преобразуем в асм
		{
			if (lex.idtable.table[i].idType == IT::IDTYPE_LIT)
			{
				*(log.stream) << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::IDDATATYPE_STR)
				{
					*(log.stream) << " BYTE " << lex.idtable.table[i].value.strValue.str << ", 0\n";
				}
				if (lex.idtable.table[i].idDataType == IT::IDDATATYPE_INT)
				{
					*(log.stream) << " DWORD " << lex.idtable.table[i].value.intValue << endl;
				}
			}
		}

		*(log.stream) << ".data\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_DIM)
			{
				*(log.stream) << "\t" << lex.idtable.table[lex.lextable.table[i + 2].indexTI].id;
				*(log.stream) << " DWORD ?\n";//?начального значени€ нет
				i += 3;
			}
		}

		stack<string> stk; // стек дл€ правильной последовательности передачи параметров в функцию ассемблера
		string func_name = "";					// им€ локальной функции
		bool isHesisForBlockFunctionion = false,				// внутри локальной функции
			isEntry = false;					// внутри главной функции


		*(log.stream) << "\n.code\n\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_PROC:
			{
				*(log.stream) << (func_name = lex.idtable.table[lex.lextable.table[++i].indexTI].id) << " PROC ";
				while (lex.lextable.table[i].lexema != LEX_RIGHTHESIS)
				{
					if (lex.idtable.table[lex.lextable.table[i].indexTI].idType == IT::IDTYPE_PAR)
					{
						*(log.stream) << lex.idtable.table[lex.lextable.table[i].indexTI].id << " : ";
						if (lex.idtable.table[lex.lextable.table[i].indexTI].idDataType == IT::IDDATATYPE_INT)
						{
							*(log.stream) << "SDWORD";
						}
						else
						{
							*(log.stream) << "DWORD";
						}
					}
					if (lex.lextable.table[i].lexema == LEX_COMMA)
					{
						*(log.stream) << ", ";
					}
					i++;
				}
				isHesisForBlockFunctionion = true;
				*(log.stream) << endl;
				break;
			}
			case LEX_ENTRY:
			{
				isEntry = true;
				*(log.stream) << "main PROC\n";
				break;
			}
			case LEX_EQUAL:
			{
				int result_position = i - 1;
				while (lex.lextable.table[i].lexema != LEX_SEMICOLON)
				{
					switch (lex.lextable.table[i].lexema)
					{
					case LEX_ID:
					case LEX_REAL:
					{
						*(log.stream) << "\tpush " << lex.idtable.table[lex.lextable.table[i].indexTI].id << endl;
						stk.push(lex.idtable.table[lex.lextable.table[i].indexTI].id);
						break;
					}
					case LEX_WORD:
					{
						*(log.stream) << "\tpush offset " << lex.idtable.table[lex.lextable.table[i].indexTI].id << endl;
						stk.push("offset " + lex.idtable.table[lex.lextable.table[i].indexTI].id);
						break;
					}
					case LEX_SUBST:
					{
						for (int j = 1; j <= lex.lextable.table[i].priority; j++)
						{
							*(log.stream) << "\tpop edx\n";
						}
						for (int j = 1; j <= lex.lextable.table[i].priority; j++)
						{
							*(log.stream) << "\tpush " << stk.top() << endl;
							stk.pop();
						}
						*(log.stream) << "\t\tcall " << lex.idtable.table[lex.lextable.table[i].indexTI].id << "\n\tpush eax\n";
						break;
					}
					case LEX_ACTION:
					{
						switch (lex.idtable.table[lex.lextable.table[i].indexTI].id[0])
						{
						case LEX_MULTIPLY:
						{
							*(log.stream) << "\tpop eax\n\tpop ebx\n";
							*(log.stream) << "\tmul ebx\n\tpush eax\n";
							break;
						}
						case LEX_PLUS:
						{
							*(log.stream) << "\tpop eax\n\tpop ebx\n";
							*(log.stream) << "\tadd eax, ebx\n\tpush eax\n";
							break;
						}
						case LEX_MINUS:
						{
							*(log.stream) << "\tpop ebx\n\tpop eax\n";
							*(log.stream) << "\tsub eax, ebx\n\tpush eax\n";
							break;
						}
						}
						break;
					}
					}
					i++;
				}
				*(log.stream) << "\tpop " << lex.idtable.table[lex.lextable.table[result_position].indexTI].id << "\n";
				break;
			}
			case LEX_END:
			{
				*(log.stream) << "\tpush ";
				i++;
				if (lex.idtable.table[lex.lextable.table[i].indexTI].idType == IT::IDTYPE_LIT)
				{
					*(log.stream) << lex.idtable.table[lex.lextable.table[i++].indexTI].value.intValue;
				}
				else
				{
					*(log.stream) << lex.idtable.table[lex.lextable.table[i++].indexTI].id;
				}
				*(log.stream) << "\n\tret\n";
				break;
			}
			case LEX_RIGHTBRACE:
			{
				if (isEntry && !isHesisForBlockFunctionion)
				{
					*(log.stream) << "\tpush 0\n\tcall ExitProcess\nmain ENDP\nend main";
				}
				if (isHesisForBlockFunctionion)
				{
					*(log.stream) << func_name << " ENDP\n\n";
					isHesisForBlockFunctionion = false;
				}
				break;
			}
			case LEX_READ:
			{
				if (lex.idtable.table[lex.lextable.table[i + 2].indexTI].idDataType == IT::IDDATATYPE_INT)
				{
					*(log.stream) << "\tpush " << lex.idtable.table[lex.lextable.table[i + 2].indexTI].id << "\n\t\tcall readr\n";
				}
				else
				{
					*(log.stream) << "\tpush offset " << lex.idtable.table[lex.lextable.table[i + 2].indexTI].id << "\n\t\tcall readw\n";
				}
				break;
			}
			}
		}
	}
}