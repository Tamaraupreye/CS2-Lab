#include <iostream>

using namespace std;

int main() {
    int lst [50] = {0};

    int sum = 0, max = 0, min = 0, first = 0, last = 0, n = 0, num;
    bool is_empty = true, is_sorted = true;

    // interface for entering the elements of the list
    for (int i = 0; i < 50; i++) {
        cout << "number? (q to quit) ";
        cin >> num;
        if (cin.fail()) break;
        is_empty = false;
        sum += num;
        n += 1;
        if (i == 0) {
            first = num;
            max = num;
            min = num;
        }
        if (num < last) is_sorted = false;
        lst[i] = num;
        last = num;
        max = num > max ? num : max;
        min = num < min ? num : min;
    }

    cout << "\nsum: " << sum << "\n";
    cout << "min: " << min << "\n";
    cout << "max: " << max << "\n";
    cout << "first: " << first << "\n";
    cout << "last: " << last << "\n";
    cout << "num of elements: " << n << "\n";
    if (is_sorted) cout << "is_sorted: True\n";
    else cout << "is_sorted: False\n";
    if (is_empty) cout << "is_empty: True\n";
    else cout << "is_empty: False\n";
}
