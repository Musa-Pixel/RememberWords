#include "QuizMaker.h"
#include "Utility.h"

#include <algorithm>
#include <random>

QuizMaker::QuizMaker(std::unique_ptr<table_of_strings>& source, bool titled_col)
	: mTitledCol(titled_col),
	mCurrentQuestionIndex(0)
{
	mSource = std::move(source);
}

void QuizMaker::CreateQuizFromSource(int type)
{
	mType = type;
	int count = mSource->size();
	mOrder.clear();
	mOrder.resize(count);
	for (int i = 0; i < count; i++)
	{
		mOrder[i] = i;
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(mOrder.begin() + (int) mTitledCol, mOrder.end(), g);
	mCurrentQuestionIndex = (int)mTitledCol;
}

void QuizMaker::NextQuestion()
{
	mCurrentQuestionIndex++;
}

std::string QuizMaker::AskQuestion(int type)
{
	if (type == -1)
		type = mType;

	std::string output = to_string(mCurrentQuestionIndex - mTitledCol + 1) + " ) ";
	// TODO: when type is 2
	switch (type)
	{
	case 0:
	{
		output += mSource->at(mOrder[mCurrentQuestionIndex])[0];
		break;
	}
	case 1:
	{
		output += mSource->at(mOrder[mCurrentQuestionIndex])[1];
		break;
	}
	default:
		output += mSource->at(mOrder[mCurrentQuestionIndex])[0];
	}
	return output;
}

std::string QuizMaker::GetAnswer()
{
	std::string output = "";
	for (auto& e : mSource->at(mOrder[mCurrentQuestionIndex]))
	{
		output += e + " : ";
	}
	return output;
}

std::unique_ptr<table_of_strings> QuizMaker::MoveSource()
{
	return std::move(mSource);
}

bool QuizMaker::Finished()
{
	return mCurrentQuestionIndex >= mSource->size();
}
