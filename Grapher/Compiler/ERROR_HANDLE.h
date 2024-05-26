#pragma once
#include <string>
#include <vector>




struct ERROR {
	

	enum ErrType {
		WARNING, SYNTAX, UNDEFINED, 
	};
	std::string Message;
	ErrType type;

};

class ERROR_HANDLE
{
public:
	std::vector<ERROR> errorList;
};

