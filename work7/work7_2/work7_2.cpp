#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// сортировка по времени окончания занятия, если совпадают, сравниваем по времени начала
bool comp(pair<double,double> a, pair<double,double> b) {
	if (a.second == b.second) return a.first < b.first;
	else return a.second < b.second;
}

vector<pair<double, double>> function(vector<pair<double, double>>& timetable) {
	vector<pair<double, double>> result;
	double maxtime = 0;
	for (int i = 0; i < timetable.size(); i++) {
		auto lesson = timetable[i];
		if (lesson.first >= maxtime) {
			result.push_back(lesson);
			maxtime = lesson.second;
		}
	}
	return result;
}

int main() {
	int lesscount;
	vector<pair<double, double>> lessons;
	cout << "Input number of lessons: ";
	cin >> lesscount;
	for (int i = 0; i < lesscount; i++) {
		double start, end;
		cout << "Input start/end time for a lesson: ";
		cin >> start;
		cin >> end;
		lessons.push_back(make_pair(start, end));
	}
	sort(lessons.begin(), lessons.end(), comp);
	auto result = function(lessons);
	cout << endl << result.size() << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i].first << ' ' << result[i].second << endl;
	}
	return 0;
}