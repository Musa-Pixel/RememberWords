#include "CSV.h"

#include <fstream>
#include <format>
#include <iostream>


csv::Reader::Reader()
{

}

void csv::Reader::ReadFromFile(std::string filename, const char delimiter)
{
	if (mContent == nullptr)
	{
		mContent = std::make_unique<table_of_strings>();
	}
	mContent->clear();
	if (delimiter == '\n')
	{
		throw std::logic_error("csv::Reader::ReadFromFile\nDelimiter can not be '\\n'");
	}
	std::fstream file(filename);

	if (file.is_open())
	{
		char cursor;
		std::string current_cell = "";
		while (file)
		{
			cursor = file.get();
			if (cursor == '\n')
			{
				if (not current_cell.empty())
				{
					mContent->back().push_back(current_cell);
					current_cell = "";
				}
				
				mContent->push_back(std::vector<std::string>());
			}
			else if (cursor == delimiter)
			{
				if (mContent->empty())
				{
					mContent->push_back(std::vector<std::string>());
				}
				mContent->back().push_back(current_cell);
				current_cell = "";
			}
			else {
				current_cell += cursor;
			}
		}

		if (not current_cell.empty())
		{
			mContent->back().push_back(current_cell);
			current_cell.clear();
		}
	}
	else
	{
		throw std::format("File {} doesn't open.", filename);
	}
}

std::unique_ptr<table_of_strings> csv::Reader::MoveContent()
{
	if (mContent == nullptr)
	{
		std::cout << "csv::Reader::MoveContent()\n";
		std::cout << "\tThere is nothing to move. The content may have been already moved or does not exist.\n";
		return nullptr;
	}
	return std::move(mContent);
}

void csv::Reader::PrintContent(const std::string delimiter) const
{
	if (mContent == nullptr)
	{
		std::cout << "csv::Reader::PrintContent()\n";
		std::cout << "\tThere is nothing to print. The content may have been moved or does not exist.\n";
		return;
	}
	for (auto& row : *mContent.get())
	{
		if (row.empty())
		{
			std::cout << "[empty line]";
		}
		for (size_t i = 0; i < row.size(); i++)
		{
			if (row[i].size() == 0)
				std::cout << "[empty string]";
			else
				std::cout << row[i];
			if (i + 1 != row.size())
			{
				std::cout << delimiter;
			}
		}
		std::cout << "\n";
	}
}
