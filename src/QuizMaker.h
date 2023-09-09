#pragma once

#include "CSV.h"

class QuizMaker
{
public:
	QuizMaker(std::unique_ptr<table_of_strings>& source, bool titled_col = true);

	/**
	* @param type: 0 - ask word, 1 - ask definition or translation, 2 - one of them
	*/
	void CreateQuizFromSource(int type = 0);
	void NextQuestion();
	/*
	* @param type: -1 - use mType
	*/
	std::string AskQuestion(int type = -1);
	std::string GetAnswer();

	std::unique_ptr<table_of_strings> MoveSource();
	bool Finished();
private:
	QuizMaker();
	std::unique_ptr<table_of_strings> mSource;
	/*
	* Columns is titled or not
	*/
	bool mTitledCol;
	std::vector<int> mOrder;
	int mType;
	int mCurrentQuestionIndex;
};

