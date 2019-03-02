#pragma once
#include <vector>
#include <cmath>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "note.h"
using std::string;
using std::vector;

vector<note> vReadFile(string filePath);

void loadTheme(string filePath);

char calculateRank(int score);

// y-mx = b
// y = position to reach
// m = speed
// x = time to reach target position in seconds
// b = offset
int calculateOffset(int y, int m, int x);

// Linearly interpolate between two values
template <typename T>
T lerp(const T& a, const T& b, float t)
{
	return a + (b - a) * t;
}