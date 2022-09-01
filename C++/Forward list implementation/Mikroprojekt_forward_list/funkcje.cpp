#include "funkcje.h"

string get_text_input(int argc, char* argv[])
{
	string text_input;
	for (int i = 1; i < argc; i++)
	{
		string a = argv[i];
		if (a == "-ti" && argv[i + 1])
		{
			text_input = argv[i + 1];
			i++;

		}
	}
	return text_input;
}

string get_bin_input(int argc, char* argv[])
{
	string bin_input;
	for (int i = 1; i < argc; i++)
	{
		string a = argv[i];
		if (a == "-bi" && argv[i + 1])
		{
			bin_input = argv[i + 1];
			i++;

		}
	}
	return bin_input;
}

string get_text_output(int argc, char* argv[])
{
	string text_output;
	for (int i = 1; i < argc; i++)
	{
		string a = argv[i];
		if (a == "-to" && argv[i + 1])
		{
			text_output = argv[i + 1];
			i++;
		}
	}
	return text_output;
}

string get_bin_output(int argc, char* argv[])
{
	string bin_output;
	for (int i = 1; i < argc; i++)
	{
		string a = argv[i];
		if (a == "-bo" && argv[i + 1])
		{
			bin_output = argv[i + 1];
			i++;
		}
	}
	return bin_output;
}

int get_choice(int argc, char* argv[])
{
	string choice_str;
	int choice;
	for (int i = 1; i < argc; i++)
	{
		string a = argv[i];
		if (a == "-c" && argv[i + 1])
		{
			choice_str = argv[i + 1];
			i++;
		}
	}

	stringstream ss;
	ss << choice_str;
	ss >> choice;

	return choice;
}