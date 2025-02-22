#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

double monte_carlo_area_calc(double x_st, double x_lim, double y_st, double y_lim, int n) {
    srand(time(0));
    int inside_points = 0;
    for (int i = 0; i < n; ++i) {
        double x = x_st + (double)rand() / RAND_MAX * (x_lim - x_st); // рандомное число от x_st до x_lim
        double y = y_st + (double)rand() / RAND_MAX * (y_lim - y_st);
        if ((y <= pow(x, 2) + 4) and (y >= -pow(x, 2) - 4)) {
            inside_points++;
        }
    }
    int known_area = (x_lim - x_st) * (y_lim - y_st);
    double area = (inside_points / (double)n * known_area);
    return area;
}

double simpson_rule_calc(double x_st, double x_lim, int n) {
    if (n % 2 == 1) n++;
    double h = (x_lim - x_st) / n;
    double sum = (pow(x_st, 2) + 4 + pow(x_lim, 2) + 4);

    for (int i = 1; i < n; i += 2)
        sum += 4 * (pow(x_st + i * h, 2) + 4);

    for (int i = 2; i < n - 1; i += 2)
        sum += 2 * (pow(x_st + i * h, 2) + 4);

    return ((h / 3) * sum)*2; // домножение на 2 т.к. рассчитывалось только для положительных у, а домножая на 2 также учитываем и отрицательные
}

int main() {
    int x1 = 3, x2 = 4, y1 = -20, y2 = 20, n;
    cout << "Enter number N: ";
    cin >> n;
    cout << endl;
    double estimated_area1, estimated_area2;
    estimated_area1 = monte_carlo_area_calc(x1, x2, y1, y2, n);
    estimated_area2 = simpson_rule_calc(x1, x2, n);
    cout << "Estimate area with Monte Carlo: " << estimated_area1 << endl;
    cout << "Estimate area with Simpson: " << estimated_area2 << endl;
    return 0;
}