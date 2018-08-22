#pragma once

#include <string>
#include <iostream>


typedef std::string String;

static String ReadFile(const String& filepath)
{
	FILE* file = fopen(filepath.c_str(), "rt");
	if (file == nullptr)
		std::cout << "file could not be found: " << filepath.c_str() << std::endl;

	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	char* data = new char[length + 1];
	memset(data, 0, length + 1);
	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);
	fclose(file);

	String result(data);
	delete[] data;

	return result;
}
