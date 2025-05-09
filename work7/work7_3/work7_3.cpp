#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> function(vector<int>& numbers) {
	vector<int> result;
	vector<int> part_result;
	if (numbers.size() > 2) {
		int middle = numbers.size() / 2;
		vector<int> left_part;
		vector<int> right_part;
		for (int i = 0;i < middle;i++) {
			left_part.push_back(numbers[i]);
		}
		for (int i = middle; i < numbers.size(); i++) {
			right_part.push_back(numbers[i]);
		}
		auto left = function(left_part);
		auto right = function(right_part);
		left.insert(left.end(), right.begin(), right.end());
		for (int i = 0; i < left.size(); i++) {
			if (left[i] < 0) result.push_back(left[i]);
			else part_result.push_back(left[i]);
		}
		result.insert(result.end(), part_result.begin(), part_result.end());
		return result;
	}
	else return numbers; // базовый случай - размер массива 2 или меньше
}

int main() {
	vector<int> numbers;
	int num;
	cout << "Input numbers: ";
	while (cin >> num) {
		numbers.push_back(num);
		if (cin.peek() == '\n') break;
	}
	auto result = function(numbers);
	cout << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << ' ';
	}
	cout << endl;
	return 0;
}