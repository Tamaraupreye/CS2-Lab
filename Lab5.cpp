#include <iostream>
#include <string>
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

class A {
  private:
    int id = 101;
    float current_CGPA = 3.75;
    int current_credits = 110;

  public:
    int get_id() {
        return id;
    }

    float get_current_CGPA() {
        return current_CGPA;
    }

    int get_current_credits() {
        return current_credits;
    }
};

struct _B {
    string course;
    int student_id;
    int year;
    int semester;
    int credits;
    float grade;
};

class B: protected A {
  protected:
    _B b[6] = {{"CS401", 101, 2020, 1, 3, 4.0}, {"EE347", 101, 2020, 1, 4, 3.0}, {"EE399", 101, 2020, 1, 3, 4.0}, {"CS499", 101, 2020, 1, 4, 4.0}, {"EE469", 101, 2020, 1, 3, 4.0}, {"CS470", 101, 2020, 1, 3, 3.0}};
};

class C {
  public:
    int student_id = 101;
    string student_fname = "David";
    string student_lname = "Britain";
    string program = "Computer Science";
};

class D: public B, public C {
  public:
    float semester_points = 0.0;
    int semester_credits = 0;
    float semester_GPA = 0.0;
    float new_CGPA = 0.0;

    float calculateCGPA() {
        for (int i = 0; i < 6; i++) {
            if (b[i].student_id == C::student_id) {
                semester_points += b[i].credits * b[i].grade;
                semester_credits += b[i].credits;
            }
        }

        semester_GPA = semester_points/semester_credits;

        float cumulative_points = get_current_CGPA() * get_current_credits();

        new_CGPA = (cumulative_points + semester_points)/(get_current_credits() + semester_credits);

        cout << "+----------+------------------+--------------------+-----------------+-------------+---------------+----------------+------------+--------+" << endl;
        cout << "|Student ID|Name              |Program             |Cumulative Points|Total Credits|Semester Points|Semester Credits|Semester GPA|New CGPA|" << endl;
        cout << "+----------+------------------+--------------------+-----------------+-------------+---------------+----------------+------------+--------+" << endl;
        cout << "|" << left << setw(10) << get_id() << "|";
        cout << left << setw(18) << student_fname + " " + student_lname << "|";
        cout << left << setw(20) << program << "|";
        cout << left << setw(17) << cumulative_points << "|";
        cout << left << setw(13) << get_current_credits() << "|";
        cout << left << setw(15) << semester_points << "|";
        cout << left << setw(16) << semester_credits << "|";
        cout << left << setw(12) << semester_GPA << "|";
        cout << left << setw(8) << new_CGPA << "|";
        cout << endl;
        cout << "+----------+------------------+--------------------+-----------------+-------------+---------------+----------------+------------+--------+" << endl;
    }
};

int main() {
    D d;
    d.calculateCGPA();
}
