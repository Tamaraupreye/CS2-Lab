#include <iostream>
#include <string>

using namespace std;

struct Course {
    int number;
    string title;
    int credit;
};

struct CourseFile {
    int fileSize = 100;
    int currPtr = 0;
    bool sorted = true;
    Course *info = new Course [fileSize];  // pointer to array

    void addCourseRecord() {
        cout << "Enter Course Number: ";
        cin >> info[currPtr].number;

        if (info[currPtr].number < info[currPtr - 1].number) {
            sorted = false;
        }

        cout << "Enter Course Title: ";
        cin.ignore();
        getline(cin, info[currPtr].title);

        cout << "Enter Course Credit: ";
        cin >> info[currPtr].credit;

        currPtr++;

        cout << endl;
    }

    void addMultipleCourseRecords() {
        int num;

        cout << "How many courses to add? ";
        cin >> num;

        while (num + currPtr >= fileSize) {
            Course *temp = new Course [2 * fileSize];
            for (int i = 0; i < currPtr; i++) {
                temp[i] = info[i];
            }
            delete [] info;
            info = temp;
            fileSize *= 2;
        }

        for (int i = 0; i < num; i++) {
            addCourseRecord();
        }
    }

    void printCourses() {
        for (int i = 0; i < currPtr; i++) {
            cout << info[i].number << " " << info[i].credit << " " << info[i].title << endl;
        }
        cout << endl;
    }

    Course * binarySearch(int l, int r, int num) {
        if (r >= l) {
            int m = (r + l)/2;
            if (num == info[m].number) {
                Course *c = &info[m];
                return c;
            }
            else if (num > info[m].number) return binarySearch(m+1, r, num);
            else return binarySearch(l, m-1, num);
        }
        return NULL;
    }

    Course * linearSearch(int l, int r, int num) {
        for (int i = l; i < r; i++) {
            if (num == info[i].number) {
                Course *c = &info[i];
                return c;
            }
        }
        return NULL;
    }

    Course * findCourse(int courseNo) {
        Course * c;
        if (sorted) {  // do a binary search
            c = binarySearch(0, currPtr, courseNo);
        }
        else {  // do a linear search. makes sense to sort first then do binary search but code for merge sort is long
            c = linearSearch(0, currPtr, courseNo);
        }
        return c;
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

int main() {
    CourseFile courseFile;
    courseFile.addMultipleCourseRecords();
    courseFile.printCourses();
    Course * c = courseFile.findCourse(136);
    if (c != NULL) cout << c->title << endl << endl;
}
