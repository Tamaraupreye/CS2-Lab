#include <iostream>
#include <string>

using namespace std;

struct Course {
    int number;
    string title;
    int credit;
};

struct CourseFile {
    Course *info;  // pointer to array
    int fileSize;
    int currPtr;

    void addCourseRecord() {
        cout << "Enter Course Number: ";
        cin >> this->info[this->currPtr].number;

        cout << "Enter Course Title: ";
        cin.ignore();
        getline(cin, this->info[this->currPtr].title);

        cout << "Enter Course Credit: ";
        cin >> this->info[this->currPtr].credit;

        this->fileSize++;
        this->currPtr++;

        cout << endl;
    }

    void addMultipleCourseRecords() {
        int num;

        cout << "How many courses to add? ";
        cin >> num;

        for (int i = 0; i < num; i++) {
            addCourseRecord();
        }
    }

    void printCourses() {
        for (int i = 0; i < this->fileSize; i++) {
            cout << this->info[i].number << " " << this->info[i].credit << " " << this->info[i].title << endl;
        }
        cout << endl;
    }

    int findCourse() {
        return 0;
    }

    void modifyCourse() {

    }
};

struct Student {
    int id;
    string firstName;
    string lastName;
    string program;
};

struct StudentFile {
    Student *info;  // pointer to array
    int fileSize;
    int currPtr;

    void addStudent() {

    }

    void addMultipleStudents() {

    }

    void printStudents() {

    }

    int findStudent() {
        return 0;
    }

    void modifyStudent() {
        
    }

    int calculateGPA() {
        
    }
};

struct Instructor {
    int id;
    string firstName;
    string lastName;
    string title;
    string department;
};

struct InstructorFile {
    Instructor *info;  // pointer to array
    int fileSize;
    int currPtr;

    void addInstructor() {

    }

    void addMultipleInstructors() {
        
    }

    void printInstructors() {

    }

    int findInstructor() {
        return 0;
    }

    void modifyInstructor() {
        
    }
};

struct CourseOffering {
    Course *course;
    int year;
    string semester;
    int sectionNumber;
    Instructor *instructor;
    int time;
    string room;
};

struct CourseOfferingFile {
    CourseOffering *info;  // pointer to array
    int fileSize;
    int currPtr;

    void addCourseOffering() {

    }

    void addMultipleCourseOfferings() {

    }

    void printCourseOfferings() {

    }

    int findCourseOffering() {
        return 0;
    }

    void modifyCourseOffering() {
        
    }
};

struct CourseEnrollment {  // also contains course grade
    CourseOffering *courseOffering;
    Student *student;
    char grade;
};

struct CourseEnrollmentFile {
    CourseEnrollment *info;  // pointer to array
    int fileSize;
    int currPtr;

    void addCourseEnrollment() {

    }

    void addMultipleCourseEnrollments() {

    }

    void printCourseEnrollments() {

    }

    void findEnrollment() {

    }
    
    void assignGrade() {

    }
};

int main() {
    CourseFile courseFile = {new Course[100], 0, 0};
    courseFile.addMultipleCourseRecords();
    courseFile.printCourses();
}
