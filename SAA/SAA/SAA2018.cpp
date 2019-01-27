#include "pch.h"
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])									// Количество аргументов / Массив указателей на строки аргументов при запуске из консоли
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;										// Инициализировали переменную, отвечающую за вывод в .log файл
	try																	// Блок проверки на исключения, в catch заносится первое попавшееся исключение
	{
		Parm::PARM parm = Parm::getparm(argc, argv);					// Инициализируем переменную типа PARM значениями, введенными при запуске проекта через консоль
		log = Log::GetLog(parm.log);									// Задаем значение переменной log, передавая ей имя файла, указанного с консоли
		Log::WriteLog(log);												// Записываем оглавление лог файла
		Log::WriteParm(log, parm);

		ICP::ICP in = ICP::GetIn(parm.in);								// Считываем файл и при встрече любого сепаратора, разделяем слова, записывая их в отдельную структуру
		Log::WriteIn(log, in);

		log = Log::GetLog(parm.lex);
		char header[] = "Lexical and sintaxis analisis\n";
		Log::WriteLine(log, header, "");
		Lex::LEX lex = Lex::Lexer(in, log);								// Лексический анализ. В соответствии со словами, полученными на пред. этапе, составляем таблицу лексем по этим словам. И табл. идент.

		log = Log::GetLog(parm.sin);
		MFST_TRACE_START(log);
		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(log);
		mfst.printRules(log);
		
		CallPolishNotation(&lex.lextable, &lex.idtable);
		LT::Write(log, lex.lextable);
		IT::WriteTable(log, lex.idtable);
		
		log = Log::GetLog(parm.out);
		Generation::Generation(lex, log);

		cout << "\nSuccessfully compleate.\n";
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	_getch();
	return 0;
};