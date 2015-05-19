#include "utility.h"
#include <utility>
#include <iostream>
#include <fstream>


bool fileIsExist(const std::string& path){
	struct stat buffer;
	return (stat(path.data(), &buffer) == 0);
}

std::string getSource(const std::string& path){
	if (!fileIsExist(path)){
		fprintf(stderr, "File not found: \"%s\"", path.data());
	}
	std::fstream fin(path);
	if (!fin.is_open()){
		fprintf(stderr, "Error while opening file %s\n", path);
		exit(EXIT_FAILURE);
	}
	std::string shaderSource((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	fin.close();

	return shaderSource;
}