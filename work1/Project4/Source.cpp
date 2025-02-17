#include <iostream>
#include <map>
#include <chrono>
#include <cmath>
using namespace std;

template <typename map, typename val, typename len>
int add_to_dict_n_times(map& dict, val val1, len len1) {
    auto start_time = chrono::high_resolution_clock::now();
    for (int i = 1; i < len1+1; i++) {
        dict[i] = val1;
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    return int(duration.count());
}

int main() {
    for (int i = 1; i < 9; i++) {
        int len = pow(10, i);
        cout << len << " len " << i << " i " << endl;
        map<int, string> dict;
        cout << add_to_dict_n_times(dict, "a", len) << "mks, " << len << " operations" << endl;
    }
    map<int, string> dict;
    cout << add_to_dict_n_times(dict, "a", 150000000) << "mks, 150000000 operations" << endl;
    cout << add_to_dict_n_times(dict, "a", 175000000) << "mks, 175000000 operations" << endl; // pc probably dead at this point x_x
    return 0;
}