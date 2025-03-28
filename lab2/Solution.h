#pragma once
#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include "Global.h"
#include "Object.h"

class Solution
{
public:
};

int readBenchMarkFile(std::string i_file_name);

int outputSolution(std::string i_file_name);

int reportWireLength();

#endif