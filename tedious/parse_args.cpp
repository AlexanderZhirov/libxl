#include "parse_args.hpp"

[[ noreturn ]] void args::print_usage_and_exit(int code)
{
	puts("Использование: tedious [option] [arguments] ...\n");
	puts("  -h,  --help               Получить информацию об использовании");
	puts("  -i,  --input   <file>     Указать исходный файл");
	puts("  -o,  --output  <file>     Указать конечный файл\n");
	exit(code);
}

void args::parse_args(int argc, char *argv[], args::settings *parameters)
{
	int next_option;
	do{
		next_option = getopt_long(argc, argv, args::short_options, args::long_options, nullptr);
		switch(next_option)
		{
			case 'i':
				parameters->iFile = optarg;
				break;
			case 'o':
				parameters->oFile = optarg;
				break;
			case 'h':
				args::print_usage_and_exit(0);
				break;
			case '?':
				args::print_usage_and_exit(-1);
				break;
		}
	} while (next_option != -1);
}
