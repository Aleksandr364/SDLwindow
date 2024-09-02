#pragma once

#include <string>
#include <vector>
#include <stdexcept>

const int delta = 1;
bool IntEquality(int, int, int = delta);

void LogDebug1(const char*);
void LogDebug2(uint32_t);

unsigned int from_str_to_uint(std::string);

// Поля класса.
struct newFields
{
	std::string name = ""; // Имя.
	unsigned int r = 0; // Размер.
};