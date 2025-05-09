#include "pch.h"
#include "CppUnitTest.h"
#include "../work7_1.cpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace treeutest
{
	TEST_CLASS(treeutest)
	{
	public:
		
		/* �������� �� ��, ��� ���� ��������� �������� � ���������(� ����� ������)
		fun fact: ���� �� � �� ����� ���� unit-����, �� ������� �� ��������, ����������� ��� ����� 0 */
		TEST_METHOD(RandNum_check)
		{
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> distrib(1, 9999);
			int randnum = distrib(gen);
			string str = "Picked number: " + to_string(randnum);
			Logger::WriteMessage(str.c_str());
			Assert::AreEqual(randnum, function(create_node(to_string(randnum))));
		}
	};
}
