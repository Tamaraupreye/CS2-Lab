#include <iostream>

using namespace std;

// function declarations
void sort(int[], int, int);
void merge(int[], int, int, int);
int search(int[], int, int, int);

// merge sort
void sort(int lst[], int l, int r) {
    if (l < r) {
        int m = (l + r)/2;
        sort(lst, l, m);
        sort(lst, m + 1, r);
        merge(lst, l, m, r);
    }
}

void merge(int lst[], int l, int m, int r) {
    // copy lists
    int nl = m - l + 1;
    int nr = r - m;
    int L[nl],  R[nr];
    for (int i = 0; i < nl; i++) L[i] = lst[l + i];
    for (int j = 0; j < nr; j++) R[j] = lst[m + j + 1];

    // merge sublists
    int i = 0;
    int j = 0;
    int k = l;

    while (i < nl && j < nr) {
        if (L[i] <= R[j]) {
            lst[k] = L[i];
            i++;
        }
        else {
            lst[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < nl) {
        lst[k] = L[i];
        i++;
        k++;
    }

    while (j < nr) {
        lst[k] = R[j];
        j++;
        k++;
    }
}

// binary search
int search(int lst[], int l, int r, int num) {
    if (r >= l) {
        int m = (r + l)/2;
        if (num == lst[m]) return m;
        else if (num > lst[m]) return search(lst, m+1, r, num);
        else return search(lst, l, m-1, num);
    }
    return -1;
}

int main() {
    int lst [50] = {0};

    int sum = 0, max = 0, min = 0, first = 0, last = 0, n = 0, num;
    bool is_empty = true, is_sorted = true;

    // interface for entering the elements of the list
    for (int i = 0; i < 50; i++) {
        cout << "number? (q to quit) ";
        cin >> num;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            break;
        }
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
    
    sort(lst, 0, n-1);

    int x;
    cout << "\nElement to find? ";
    cin >> x;
    
    int found = search(lst, 0, n-1, x);
    if (found != -1) cout << "Found at index " << found << " in the sorted list.\n";
    else cout << "Element not in list.\n";
}
