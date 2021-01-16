#pragma once
#include <exception>
#include <string>

class HandleException : public std::exception // HandleException inherits from std::exception
{
public:
	HandleException(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer; //it is protected so it can be used by all the classes that inherit HandleException
};