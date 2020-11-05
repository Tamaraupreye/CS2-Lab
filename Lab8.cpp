#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void wait() {
    string c;
    cout << "Press <Return> to continue... ";
    cin.ignore();
    getline(cin, c);
}

struct CurrencyPairNode{
	string lcurrName;
	string fcurrName;
	float sellRate;
	float buyRate;
	CurrencyPairNode *next;
};

int main() {
	int size;
	cout << "Size of array: ";
	cin >> size;
	
	string lcurrName;
	string fcurrName;
	float sellRate;
	float buyRate;

	CurrencyPairNode** arr = new CurrencyPairNode* [size];
	
	// input local currency and some currency pair nodes
	for (int i = 0; i < size; i++) {
		cout << "Local currency: ";
		cin >> lcurrName;
		arr[i] = new CurrencyPairNode {lcurrName, lcurrName, 1, 1, NULL};
		
		CurrencyPairNode * node, * temp;

		node = arr[i];
		while (true) {
			cout << "Foreign currency (use q to quit): ";																			
			cin >> fcurrName;
			if (fcurrName == "q") break;
			cout << "Sell Rate: ";
			cin >> sellRate;
			cout << "Buy Rate: ";
			cin >> buyRate;
			temp = new CurrencyPairNode {lcurrName, fcurrName, sellRate, buyRate, NULL};
			node->next = temp;
			node = node->next;
		}
		clearScreen();
	}
	
	// print
	for (int i = 0; i < size; i++) {
		CurrencyPairNode * node, * temp;
		cout << "{" << arr[i]->lcurrName << ", " << arr[i]->fcurrName << ", ";
		cout << arr[i]->sellRate << ", " << arr[i]->buyRate << "}";
		node = arr[i]->next;
		while (node != NULL) {
			cout << " --> ";
			cout << "{" << node->lcurrName << ", " << node->fcurrName << ", ";
			cout << node->sellRate << ", " << node->buyRate << "}";
			node = node->next;
		}
		cout << endl << endl;
	}

	// delete nodes at the end
	for (int i = 0; i < size; i++) {
		CurrencyPairNode * node, * temp;
		node = arr[i];
		while (node != NULL) {
			temp = node->next;
			delete node;
			node = temp;
		}
	}
}