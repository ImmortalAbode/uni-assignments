#ifndef CONSTANTS_H_
#define CONSTANTS_H_

enum class Blank {
	INPUT,
	OUTPUT
};
enum class Select {
	CONSOLE,
	FILE
};
const std::string DEFAULT_NAME_FILE_IN{ "in.txt" };
const std::string DEFAULT_NAME_FILE_OUT{ "out.txt" };

#endif /*CONSTANTS_H_*/
