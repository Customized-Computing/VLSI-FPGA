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
// 报告当前布局的布线长度，使用HPWL线长预估模型
int reportWireLength();
// 报告当前布局是否合法
int reportValid();

#endif