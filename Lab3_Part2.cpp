#include <iostream>
#include <string>
#include <iomanip>

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

    void addCourse() {
        cout << "Enter Course Number: ";
        cin >> info[currPtr].number;

        if (currPtr >= 1 && info[currPtr].number < info[currPtr - 1].number) {
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

    void addMultipleCourses() {
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
            addCourse();
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
        else {  
            // do a linear search. makes sense to sort first then do binary search but code for merge sort is long
            // maybe sort as entries are added so list is always corted
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
    int fileSize = 100;
    int currPtr = 0;
    bool sorted = true;
    Instructor *info = new Instructor [fileSize];  // pointer to array

    void addInstructor() {
        cout << "Enter Instructor ID: ";
        cin >> info[currPtr].id;

        if (currPtr >= 1 && info[currPtr].id < info[currPtr - 1].id) {
            sorted = false;
        }

        cout << "Enter Instructor First Name: ";
        cin >> info[currPtr].firstName;

        cout << "Enter Instructor Last Name: ";
        cin >> info[currPtr].lastName;

        cout << "Enter Instructor Title: ";
        cin.ignore();
        getline(cin, info[currPtr].title);

        cout << "Enter Instructor Department: ";
        getline(cin, info[currPtr].department);

        currPtr++;

        cout << endl;
    }

    void addMultipleInstructors() {
        int num;

        cout << "How many instructors to add? ";
        cin >> num;

        while (num + currPtr >= fileSize) {
            Instructor *temp = new Instructor [2 * fileSize];
            for (int i = 0; i < currPtr; i++) {
                temp[i] = info[i];
            }
            delete [] info;
            info = temp;
            fileSize *= 2;
        }

        for (int i = 0; i < num; i++) {
            addInstructor();
        }
    }

    void printInstructors() {
        for (int i = 0; i < currPtr; i++) {
            cout << left << setw(3) << info[i].id << left << setw(20) << info[i].firstName + " "  + info[i].lastName << " ";
            cout << left << setw(12) << info[i].title << left << setw(20) << info[i].department << endl;
        }
        cout << endl;
    }

    Instructor * binarySearch(int l, int r, int num) {
        if (r >= l) {
            int m = (r + l)/2;
            if (num == info[m].id) {
                Instructor *i = &info[m];
                return i;
            }
            else if (num > info[m].id) return binarySearch(m+1, r, num);
            else return binarySearch(l, m-1, num);
        }
        return NULL;
    }

    Instructor * linearSearch(int l, int r, int num) {
        for (int i = l; i < r; i++) {
            if (num == info[i].id) {
                Instructor *x = &info[i];
                return x;
            }
        }
        return NULL;
    }

    Instructor * findInstructor(int instructorID) {
        Instructor * i;
        if (sorted) {  // do a binary search
            i = binarySearch(0, currPtr, instructorID);
        }
        else {  
            // do a linear search. makes sense to sort first then do binary search but code for merge sort is long
            // maybe sort as entries are added so list is always corted
            i = linearSearch(0, currPtr, instructorID);
        }
        return i;
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
    int fileSize = 100;
    int currPtr = 0;
    CourseOffering *info = new CourseOffering [fileSize];  // pointer to array

    void addCourseOffering(CourseFile cf, InstructorFile _if) {
        int id;
        Instructor * instructor;
        cout << "Enter Instructor ID: ";
        cin >> id;
        instructor = _if.findInstructor(id);
        if (instructor == NULL) {
            cout << "No instructor with id " << id << endl << endl;
            return addCourseOffering(cf, _if);
        }
        else {
            info[currPtr].instructor = instructor;
        }
        addCourseOfferingB(cf, _if);
    }

    void addCourseOfferingB(CourseFile cf, InstructorFile _if) {
        int courseNo;
        Course * course;
        cout << "Enter Course Number: ";
        cin >> courseNo;
        course = cf.findCourse(courseNo);
        if (course == NULL) {
            cout << "No course with number " << courseNo << endl << endl;
            return addCourseOfferingB(cf, _if);
        }
        else {
            info[currPtr].course = course;
        }

        cout << "Enter Year: ";
        cin >> info[currPtr].year;

        cout << "Enter Semester: ";
        cin >> info[currPtr].semester;

        cout << "Enter Section Number: ";
        cin >> info[currPtr].sectionNumber;

        cout << "Enter Time: ";
        cin >> info[currPtr].time;

        cout << "Enter Room: ";
        cin.ignore();
        getline(cin, info[currPtr].room);

        currPtr++;

        cout << endl;
    }

    void addMultipleCourseOfferings(CourseFile cf, InstructorFile _if) {
        int num;

        cout << "How many course offerings to add? ";
        cin >> num;

        while (num + currPtr >= fileSize) {
            CourseOffering *temp = new CourseOffering [2 * fileSize];
            for (int i = 0; i < currPtr; i++) {
                temp[i] = info[i];
            }
            delete [] info;
            info = temp;
            fileSize *= 2;
        }

        for (int i = 0; i < num; i++) {
            addCourseOffering(cf, _if);
        }
    }

    void printCourseOfferings() {
        for (int i = 0; i < currPtr; i++) {
            cout << left << setw(20) << info[i].course->title;
            cout << left << setw(8) << to_string(info[i].course->number)+"-"+to_string(info[i].sectionNumber);
            cout << left << setw(20) << info[i].instructor->firstName+" "+info[i].instructor->lastName;
            cout << left << setw(13) << info[i].semester+" "+to_string(info[i].year);
            cout << left << setw(8) << info[i].time;
            cout << left << setw(15) << info[i].room << endl; 
        }
        cout << endl;
    }
};

int main() {
    CourseFile courseFile;
    courseFile.addMultipleCourses();
    courseFile.printCourses();

    InstructorFile instructorFile;
    instructorFile.addMultipleInstructors();
    instructorFile.printInstructors();

    CourseOfferingFile courseOfferingFile;
    courseOfferingFile.addMultipleCourseOfferings(courseFile, instructorFile);
    courseOfferingFile.printCourseOfferings();
}
