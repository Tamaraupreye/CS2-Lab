#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int OPEN = 900;
const int CLOSE = 1600;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void wait() {
    string c;
    cout << "Press <Return> to continue... ";
    cin.ignore();
    getline(cin, c);
}

struct DeqNode {
	int appStartTime;
	int appEndTime;
	string fName;
	string lName;
	DeqNode *prev;
	DeqNode *next;

	void print() {
		cout << fName << " " << lName << " ";
		cout << setw(2) << setfill('0') << appStartTime/100 << ":" << setw(2) << setfill('0') << appStartTime % 100;
		cout << "-" << setw(2) << setfill('0') << appEndTime/100 << ":" << setw(2) << setfill('0') << appEndTime % 100;
		cout << endl;
	}
};

class AppSystem {
  private:
	DeqNode *front, *rear;
	int count;
  public:
	AppSystem() {
		front = NULL;
		rear = NULL;
		count = 0;
	}

	int addAppnt(string fName, string lName, int appStartTime) {
		if ((appStartTime/100 < 0) || (appStartTime/100 > 23) || (appStartTime % 100 < 0) || (appStartTime % 100 > 59)) {
			cout << "Invalid time" << endl << endl;
			return -1;
		}

		int appEndTime = appStartTime + 100;

		if ((appStartTime < OPEN) || (appEndTime > CLOSE)) {
			cout << "We are not open at that time. Hours are 0900-1600" << endl << endl;
			return -1;
		}

		DeqNode *node, *d = new DeqNode;
		d->fName = fName;
		d->lName = lName;
		d->appStartTime = appStartTime;
		d->appEndTime = appEndTime;
		d->prev = NULL;
		d->next = NULL;

		bool put = false;

		if (count == 0) {
			front = d;
			rear = d;
			put = true;
		} else {
			if (d->appStartTime >= OPEN && front->appStartTime - d->appStartTime >= 100) {
				front->prev = d;
				d->next = front;
				front = d;
				put = true;
			} else if (d->appStartTime >= rear->appEndTime && CLOSE - d->appStartTime >= 100) {
				d->prev = rear;
				rear->next = d;
				rear = d;
				put = true;
			} else {
				node = front->next;
				int lastEndTime = front->appEndTime;
				while (node != NULL) {
					if (d->appStartTime >= lastEndTime && node->appStartTime - d->appStartTime >= 100) {
						node->prev->next = d;
						d->prev = node->prev;
						node->prev = d;
						d->next = node;
						put = true;
						break;
					}
					lastEndTime = node->appEndTime;
					node = node->next;
				}
			}
		}
		if (put) {
			cout << "Customer successfully added!" << endl << endl;
			count++;
			return 1;
		} else {
			cout << "We cannot accomodate that time..." << endl << endl;
			return -1;
		}
	}

	int deleteAppnt(string fName, string lName) {
		if (count == 1 && front->fName == fName && front->lName == lName) {
			DeqNode *t1 = front, *t2 = rear;
			int prevStartTime = front->appStartTime;
			front = NULL;
			rear = NULL;
			delete t1, t2;
			cout << "Customer successfully deleted!" << endl << endl;
			count--;
			return prevStartTime;
		} else if (front->fName == fName && front->lName == lName) {
			DeqNode *temp = front;
			int prevStartTime = front->appStartTime;
			front->next->prev = NULL;
			front = front->next;
			delete temp;
			cout << "Customer successfully deleted!" << endl << endl;
			count--;
			return prevStartTime;
		} else if (rear->fName == fName && rear->lName == lName) {
			DeqNode *temp = rear;
			int prevStartTime = rear->appStartTime;
			rear->prev->next = NULL;
			rear = rear->prev;
			delete temp;
			cout << "Customer successfully deleted!" << endl << endl;
			count--;
			return prevStartTime;
		} else {
			DeqNode *node = front;
			while (node != NULL) {
				if (node->fName == fName && node->lName == lName) {
					node->prev->next = node->next;
					node->next->prev = node->prev;
					int prevStartTime = node->appStartTime;
					delete node;
					cout << "Customer successfully deleted!" << endl << endl;
					count--;
					return prevStartTime;
				}
				node = node->next;
			}
		}
		cout << "No appointment with name " << fName << " " << lName << endl << endl;
		return -1;
	}

	void changeAppnt(string fName, string lName, int newStartTime) {
		int prevStartTime = deleteAppnt(fName, lName);
		if (prevStartTime == -1) {
			cout << "No previous appointment with name " << fName << " " << lName << endl << endl;
			return;
		}
		int succeeded = addAppnt(fName, lName, newStartTime);
		if (succeeded == -1) addAppnt(fName, lName, prevStartTime);
	}

	void printAppnts() {
		DeqNode *node = front;
		while (node != NULL) {
			node->print();
			node = node->next;
		}
	}
};

int main() {
	AppSystem a;
	string fName;
	string lName;
	int appStartTime, option;

	do {
		clearScreen();
		cout << "Select an option: " << endl;
        cout << "1: Add Appointment" << endl;
        cout << "2: Delete Appointment" << endl;
        cout << "3: Change Appointment" << endl;
        cout << "4: Print Appointments" << endl;
		cout << "Use any other number to quit" << endl << endl;

		cin >> option;

		switch (option) {
			case 1:
				clearScreen();
				cout << "First name of customer for appointment: ";
				cin >> fName;
				cout << "Last name of customer for appointment: ";
				cin >> lName;
				cout << "Appointment start time (in military time): ";
				cin >> appStartTime;
				a.addAppnt(fName, lName, appStartTime);
				wait();
				break;
			case 2:
				clearScreen();
				cout << "First name of customer to delete: ";
				cin >> fName;
				cout << "Last name of customer to delete: ";
				cin >> lName;
				a.deleteAppnt(fName, lName);
				wait();
				break;
			case 3:
				clearScreen();
				cout << "First name of customer to change: ";
				cin >> fName;
				cout << "Last name of customer to change: ";
				cin >> lName;
				cout << "New appointment start time (in military time): ";
				cin >> appStartTime;
				a.changeAppnt(fName, lName, appStartTime);
				wait();
				break;
			case 4:
				clearScreen();
				a.printAppnts();
				wait();
				break;
			default:
				break;
		}
	} while (option > 0 && option < 5);
	// a.addAppnt("Tam", "Benni", 900);
	// a.addAppnt("Osato", "Obaze", 1230);
	// a.addAppnt("Damola", "Ajayi", 1130);
	// a.addAppnt("Omon", "Iyoha", 1000);
	// a.printAppnts();
	// a.deleteAppnt("Damola", "Ajayi");
	// a.deleteAppnt("Tam", "Benni");
	// a.deleteAppnt("Osato", "Obaze");
	// a.deleteAppnt("Omon", "Iyoha");
	// cout << endl;
	// a.printAppnts();
	// cout << endl;
	// a.addAppnt("GG", "gg", 1000);
	// a.addAppnt("RR", "rr", 1200);
	// cout << endl;
	// a.printAppnts();
	// cout << endl;
	// a.changeAppnt("RR", "rr", 1000);
	// cout << endl;
	// a.printAppnts();
	// cout << endl;
	// a.changeAppnt("GG", "gg", 1500);
	// cout << endl;
	// a.printAppnts();
	// cout << endl;
	// a.changeAppnt("Good", "Work", 900);
	return 0;
}