#pragma once

#include <string>
#include <vector>
#include <memory>

typedef std::vector<std::vector<std::string>> table_of_strings;

namespace csv
{
	class Reader
	{
	public:
		Reader();
		void ReadFromFile(std::string filename, const char delimiter = ',');
		std::unique_ptr<table_of_strings> MoveContent();
		void PrintContent(const std::string delimiter = " : ") const;
	private:
		std::unique_ptr<table_of_strings> mContent;
	};
}