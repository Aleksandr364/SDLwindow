#pragma once

#include <string>
#include <vector>
#include <stdexcept>

const int delta = 1;
bool IntEquality(int, int, int = delta);

void LogDebug1(const char*);
void LogDebug2(uint32_t);

unsigned int from_str_to_uint(std::string);

// ���� ������.
struct newFields
{
	std::string name = ""; // ���.
	unsigned int r = 0; // ������.
};