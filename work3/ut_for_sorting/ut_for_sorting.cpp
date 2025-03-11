#include "pch.h"
#include "CppUnitTest.h"
#include "../Project5/main.cpp"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace utforsorting
{
	TEST_CLASS(utforsorting)
	{
	public:
		
		TEST_METHOD(are_algos_working_correctly)
		{
			vector<int> arr1;
			genArr(arr1, pow(10, 3), 1, pow(10, 3));
			vector<int> arr2 = arr1;
			vector<int> arr3 = arr1;
			gnomeSort(arr1);
			radixSort(arr2);
			quickSort(arr3, 0, arr3.size() - 1);
			Assert::IsTrue(checkArrs(arr1, arr2, arr3));
		}
	};
}
