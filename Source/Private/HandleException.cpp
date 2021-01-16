#include "../Public/HandleException.h"
#include <sstream>

HandleException::HandleException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* HandleException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();	//we cannot return oss.str().c_str() as oss will be a dead memory after this function ends
}

const char* HandleException::GetType() const noexcept
{
	return "An Exception";
}

const std::string& HandleException::GetFile() const noexcept
{
	return file;
}

int HandleException::GetLine() const noexcept
{
	return line;
}

std::string HandleException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}