#include "pch.h"
#include "CppUnitTest.h"
#include "../Project4/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
	TEST_CLASS(pclivepls)
	{
	public:
		map<int, string> dict;
		TEST_METHOD(max_num_test)
		{
			Assert::IsTrue(pow(10, 7) >= add_to_dict_n_times(dict, "a", 5000000));
		}
		TEST_METHOD(lesser_num_test)
		{
			Assert::IsTrue(pow(10, 5) >= add_to_dict_n_times(dict, "a", 100000));
		}
		TEST_METHOD(even_lesser_num_test)
		{
			Assert::IsTrue(pow(10, 4) >= add_to_dict_n_times(dict, "a", 10000));
		}
	};
}
