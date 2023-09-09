#include "CSV.h"
#include "QuizMaker.h"
#include <iostream>

int main()
{
	try
	{
		csv::Reader reader;
		reader.ReadFromFile("english_words.csv", ':');
		reader.PrintContent();

		std::unique_ptr<table_of_strings> table = reader.MoveContent();
		QuizMaker quizMaker(table);
		quizMaker.CreateQuizFromSource(0);
		while (!quizMaker.Finished())
		{
			std::string temp;
			std::cout << quizMaker.AskQuestion() << std::endl;
			std::cout << "wait for enter: ";
			std::cin >> temp;
			std::cout << quizMaker.GetAnswer() << std::endl;
			quizMaker.NextQuestion();
		}
		
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}