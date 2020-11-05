#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>

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

const float tax = 20;
const int bonus = 10;

class EmployeeData {
  protected:
	float gross;
	float deductions;
	float netPay;
	float netYTD;
	float DedYTD;
  public:
	int idNum;
	char fName[15];
	char lName[15];
	char contract;
	
	EmployeeData() {
		//Feel free to add anything in here.
	}

	float getNetYTD() {
		return netYTD;
	}

	float getDedYTD() {
		return DedYTD;
	}

	virtual void CalculateGross() {
		cout << "Inside EmployeeData? Wrong...Look again at the pointer.." << endl;
	}

	EmployeeData & operator -= (const float tax) {
		this->deductions = this->gross * (tax/100.0);
		this->netPay = this->gross - this->deductions;
		// cout << "BITCHHHH!!!" << endl;
		return *this;
	}

	EmployeeData & operator ++ () {  // prefix
		this->netYTD += this->netPay;
		// cout << "DOGGGGG!!!" << endl;
		return *this;
	}

	EmployeeData & operator ++ (int) {  // postfix
		this->DedYTD += this->deductions;
		// cout << "HOOOO!!!" << endl;
		return *this;
	}
};

class FullTime: public EmployeeData {
  protected:
	float earnings;
  public:
	FullTime(int idNum=0, string fName=" ", string lName=" ", char contract=' ', float DedYTD=0, float netYTD=0) {
		this->idNum = idNum;
		strcpy(this->fName, fName.c_str());
		strcpy(this->lName, lName.c_str());
		this->contract = contract;
		this->earnings = 0;
		this->gross = 0;
		this->deductions = 0;
		this->netPay = 0;
		this->DedYTD = DedYTD;
		this->netYTD = netYTD;
		// cout << "FullTime constructor..." << endl;
	}

	void CalculateGross() {
		this->gross = this->earnings;
		// cout << "Inside FullTime..." << endl;
	}

	friend istream & operator >> (istream &,  FullTime &);

	friend ostream & operator << (ostream &,  FullTime &);

	FullTime & operator = (const FullTime & f) {
		this->DedYTD = f.DedYTD;
		this->deductions = f.deductions;
		this->netYTD = f.netYTD;
		this->netPay = f.netPay;
		// cout << "Assign that bitch lol!!!" << endl;
		return *this;
	}

	FullTime & operator + (const FullTime & f) {
		this->DedYTD += f.DedYTD;
		this->deductions += f.deductions;
		this->netYTD += f.netYTD;
		this->netPay += f.netPay;
		// cout << "Sum up these kids!!!" << endl;
		return *this;
	}
};

class PartTime: public EmployeeData {
  protected:
	float payRate;
	int hours;
	int workDays;
  public:
	PartTime(int idNum=0, string fName=" ", string lName=" ", char contract=' ', float DedYTD=0, float netYTD=0) {
		this->idNum = idNum;
		strcpy(this->fName, fName.c_str());
		strcpy(this->lName, lName.c_str());
		this->contract = contract;
		this->payRate = 0;
		this->workDays = 0;
		this->deductions = 0;
		this->gross = 0;
		this->netPay = 0;
		this->DedYTD = DedYTD;
		this->netYTD = netYTD;
		// cout << "PartTime constructor..." << endl;
	}

	void CalculateGross() {
		this->gross = (this->payRate * this->hours * this->workDays);
		// cout << "Inside PartTime..." << endl;
	}

	friend istream & operator >> (istream &,  PartTime &);

	friend ostream & operator << (ostream &,  PartTime &);

	bool operator > (PartTime &p) {
		// cout << "Compare that ho!!!!" << endl;
		return (this->workDays * this->hours) > (p.workDays * p.hours);
	}

	PartTime & operator () (const int bonus) {
		this->netPay += this->gross * (bonus/100.0);
		// cout << "Man's rich now so don't chat to me!!!" << endl;
		return *this;
	}

	PartTime & operator = (const PartTime & p) {
		this->DedYTD = p.DedYTD;
		this->deductions = p.deductions;
		this->netYTD = p.netYTD;
		this->netPay = p.netPay;
		// cout << "Assign that bitch lol!!!" << endl;
		return *this;
	}

	PartTime & operator + (const PartTime & p) {
		this->DedYTD += p.DedYTD;
		this->deductions += p.deductions;
		this->netYTD += p.netYTD;
		this->netPay += p.netPay;
		// cout << "Sum up these kids!!!" << endl;
		return *this;
	}
};

istream & operator >> (istream &in,  PartTime &p) {
	cout << "Enter hours for " << p.fName << " " << p.lName << ": ";
	in >> p.hours;
	cout << "Enter days worked for " << p.fName << " " << p.lName << ": ";
	in >> p.workDays;
	cout << "Enter pay rate for " << p.fName << " " << p.lName << ": ";
	in >> p.payRate;
	return in;
}

istream & operator >> (istream &in,  FullTime &f) {
	cout << "Enter earnings for " << f.fName << " " << f.lName << ": ";
	in >> f.earnings;
	return in;
}

ostream & operator << (ostream &out,  PartTime &p) {
	cout << p.idNum << " P " << p.fName << " " << p.lName << " " << p.getNetYTD() << " " << p.getDedYTD();
	return out;
}

ostream & operator << (ostream &out,  FullTime &f) {
	cout << f.idNum << " F " << f.fName << " " << f.lName << " " << f.getNetYTD() << " " << f.getDedYTD();
	return out;
}

int main() {
	EmployeeData *objptr;
	FullTime ftobj1(101, "Michael", "Smith", 'F', 10000, 40000);
	PartTime ptobj1(102, "Maria", "Rodriguez", 'P', 7000, 28000);
	FullTime ftobj2(105, "Kyndra", "Hernandez", 'F', 8000, 32000);
	PartTime ptobj2(103, "James", "Robert", 'P', 4800, 19200); 
	PartTime ptobj3(104, "Kenny", "Mercedes", 'P', 7200, 32000);

	// Use the input operator to enter hour and earnings
	cin >> ftobj1;
	cout << endl;
	cin >> ftobj2;
	cout << endl;
	cin >> ptobj1;
	cout << endl;
	cin >> ptobj2;
	cout << endl;
	cin >> ptobj3;
	cout << endl;

	// Calculate gross income using member function and the EmployeeData pointer (objptr);
	objptr = &ftobj1;
	objptr->CalculateGross();
	objptr = &ftobj2;
	objptr->CalculateGross();
	objptr = &ptobj1;
	objptr->CalculateGross();
	objptr = &ptobj2;
	objptr->CalculateGross();
	objptr = &ptobj3;
	objptr->CalculateGross();
	
	// Calculate deduction and netPay using the substraction assignment operator overloading
	ftobj1 -= tax;
	ftobj2 -= tax;
	ptobj1 -= tax;
	ptobj2 -= tax;
	ptobj3 -= tax;

	// Use (++) Prefix operator to update netYTD with netPay to reflect YTD-netPay
	++ftobj1;
	++ftobj2;
	++ptobj1;
	++ptobj2;
	++ptobj3;

	// Use Postfix (++) operator to update dedYTP with deductions to reflect total deductions to date in the financial year
	ftobj1++;
	ftobj2++;
	ptobj1++;
	ptobj2++;
	ptobj3++;

	//  Use the relational operator overloading to find Part-time staff with the highest worked hours (workday*hours) and use function call () operator to add bonus (10% of gross) to the netPay
	if (ptobj1 > ptobj2) {
		if (ptobj1 > ptobj3) {
			ptobj1(bonus);
		}
	} else {
		if (ptobj2 > ptobj3) {
			ptobj2(bonus);
		} else {
			ptobj3(bonus);
		}
	}

	// Declared for data summary manipulations
	FullTime totalftobj;
	PartTime totalptobj;
	PartTime totalptobj1;
	PartTime totalptobj2;

	//  First use assignment operator to assign ptobj1 to totalptobj1 because you can’t pass more than two arguments
	totalptobj1 = ptobj1;

	// Use the + operator to sum the Deductions, netPay, DedYTD and netYTD for each group
	totalptobj2 = ptobj2 + ptobj3;
	totalptobj = totalptobj1 + totalptobj2;
	totalftobj = ftobj1 + ftobj2;

	// Use output operator to display/print for example: cout << ftobj1 << endl;
	cout << ftobj1 << endl;
	cout << ftobj2 << endl;
	cout << ptobj1 << endl;
	cout << ptobj2 << endl;
	cout << ptobj3 << endl;
	// and continue as required.

	return 0;
}
