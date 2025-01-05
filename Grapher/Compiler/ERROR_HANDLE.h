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

	std::string GetErrorList() {
		std::string List;
		for (int i = 0; i < errorList.size(); i++) {
			switch (errorList[i].type) {
			case ERROR::WARNING:
				List += "WARNING: " + errorList[i].Message + "\n";
				break;
			case ERROR::SYNTAX:
				List += "SYNTAX: " + errorList[i].Message + "\n";
				break;
			case ERROR::UNDEFINED:
				List += "UNDEFINED: " + errorList[i].Message + "\n";
				break;
			}
		}
		return List;
	}
};

