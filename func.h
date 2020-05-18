#ifndef OP_2_0_3_FUNC_H
#define OP_2_0_3_FUNC_H
#include "Student.h"

void GenerateRandomFiles(int x, int y);
void CalculateV(vector<Student> &stud, bool isMed);
void ReadSplitGenerateV(vector<Student> &stud, std::ofstream &fail, std::ofstream &mldc, bool strat, bool enhanced, int cycle);

void CalculateV2(Vector<Student> &stud, bool isMed);
void ReadSplitGenerateV2(Vector<Student> &stud, std::ofstream &fail, std::ofstream &mldc, bool strat, bool enhanced, int cycle);
#endif