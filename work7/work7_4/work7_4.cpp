#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool function(int numb, vector<int> available, vector<vector<int>> cube) {
	// добавляем число в пустую клетку, построчно
	for (int n = 0; n < cube.size();n++) {
		for (int m = 0; m < cube.size(); m++) {
			if (cube[n][m] == 0 && numb != 0) {
				cube[n][m] = numb;
				numb = 0;
				break;
			}
		}
	}
	int x0 = cube[0][0] + cube[0][1] + cube[0][2];
	int x1 = cube[1][0] + cube[1][1] + cube[1][2];
	int x2 = cube[2][0] + cube[2][1] + cube[2][2];
	int y0 = cube[0][0] + cube[1][0] + cube[2][0];
	int y1 = cube[0][1] + cube[1][1] + cube[2][1];
	int y2 = cube[0][2] + cube[1][2] + cube[2][2];
	int z0 = cube[0][0] + cube[1][1] + cube[2][2];
	int z1 = cube[0][2] + cube[1][1] + cube[2][0];
	bool is_full = true;
	for (int i = 0; i < cube.size(); i++) {
		if (find(cube[i].begin(), cube[i].end(), 0) != cube[i].end()) is_full = false;
	}

	if (x0 == x1 && x1 == x2 && y0 == y1 && y1 == y2 && z0 == z1 && is_full) {
		// если нашелся квадрат - выводим его
		for (int n = 0; n < cube.size(); n++) {
			for (int m = 0; m < cube[n].size(); m++) {
				cout << cube[n][m] << ' ';
			}
			cout << endl;
		}
		return true;
	}
	// если хоть какая-то сумма больше 15, возвращаемся обратно
	else if (x0 > 15 || x1 > 15 || x2 > 15 || y0 > 15 || y1 > 15 || y2 > 15 || z0 > 15 || z1 > 15) return false;

	bool result = false;
	// начинаем идти по возможным вариантам
	for (int i = 0; i < available.size(); i++) {
		vector<int> new_avlbl = available;
		new_avlbl.erase(new_avlbl.begin() + i);
		result = function(available[i], new_avlbl, cube);
		if (result == true) break;
		// если не ставить break, можно выводить все возможные квадраты
	}
	return result;
}

int main() {
	int numb;
	cout << "Input number: ";
	cin >> numb;
	vector<int> availablenums;
	vector<vector<int>> cube = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	for (int i = 1; i < 10; i++) {
		if (i != numb) availablenums.push_back(i);
	}
	bool result = function(numb, availablenums, cube);
	if (result == false) cout << "-1" << endl;
	return 0;
}