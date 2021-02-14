#ifndef PARSE_ARGS_HPP_
#define PARSE_ARGS_HPP_

#include <iostream>
#include <getopt.h>

namespace args
{
	typedef struct
	{
		const char *iFile = nullptr;
		const char *oFile = nullptr;
	} settings;

	const char* const short_options = "hi:o:";

	const struct option long_options[] =
	{
		{ "help", 0, nullptr, 'h'},
		{ "input", 1, nullptr, 'i'},
		{ "output", 1, nullptr, 'o'},
		{ nullptr, 0, nullptr, 0}
	};

	[[ noreturn ]] void print_usage_and_exit(int);
	void parse_args(int, char **, settings *);
}

#endif
