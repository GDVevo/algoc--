#include "pch.h"
#include "CppUnitTest.h"
#include "../work7_4.cpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cubeunittest
{
	TEST_CLASS(cubeunittest)
	{
	public:
		
		TEST_METHOD(IsRandomNumACube)
		{
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> distrib(1, 9);
			int randnum = distrib(gen);
			vector<int> availablenums;
			vector<vector<int>> cube = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
			for (int i = 1; i < 10; i++) {
				if (i != randnum) availablenums.push_back(i);
			}
			string str = "Checking number: " + to_string(randnum); 
			Logger::WriteMessage(str.c_str()); // вывод проверяемого числа
			Assert::IsTrue(function(randnum, availablenums, cube));
		}
		TEST_METHOD(Is2ACube)
		{
			int num = 2;
			vector<int> availablenums;
			vector<vector<int>> cube = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
			for (int i = 1; i < 10; i++) {
				if (i != num) availablenums.push_back(i);
			}
			Assert::IsTrue(function(num, availablenums, cube));
		}
	};
}
