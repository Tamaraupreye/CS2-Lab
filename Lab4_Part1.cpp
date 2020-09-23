#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// TODO:
// input course first in course offering
// allow no instructor (to be decided) in course offering

void clearScreen(){
  cout << "\033[2J\033[1;1H";
}

struct Course {
    int number;
    string title;
    int credit;

    void print() {
        cout << number << " " << credit << " " << title << endl;
    }
};

struct Instructor {
    int id;
    string firstName;
    string lastName;
    string title;
    string department;

    void print() {
        cout << left << setw(5) << id << left << setw(20) << firstName + " "  + lastName << " ";
        cout << left << setw(23) << title << left << setw(20) << department << endl;
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

    void print() {
        cout << left << setw(20) << course->title;
        cout << left << setw(8) << to_string(course->number) + "-" + to_string(sectionNumber);
        cout << left << setw(20) << instructor->firstName + " " + instructor->lastName;
        cout << left << setw(13) << semester + " " + to_string(year);
        cout << left << setw(8) << time;
        cout << left << setw(15) << room << endl; 
    }
};

class CourseFile {
    private:
        int fileSize;
        int currPtr;
        bool sorted;
        Course *info;  // pointer to array
        friend struct CourseOffering;
        friend class CourseOfferingFile;

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

    public:
        CourseFile() {
            fileSize = 10;
            currPtr = 0;
            sorted = true;
            info = new Course [fileSize];
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
                info[i].print();
            }
            cout << endl;
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

        ~CourseFile() {
            delete [] info;
        }
};

class InstructorFile {
    private:
        int fileSize;
        int currPtr;
        bool sorted;
        Instructor *info;  // pointer to array
        friend struct CourseOffering;
        friend class CourseOfferingFile;

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

    public:
        InstructorFile() {
            fileSize = 10;
            currPtr = 0;
            sorted = true;
            info = new Instructor [fileSize];
        }

        ~InstructorFile() {
            delete [] info;
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
                info[i].print();
            }
            cout << endl;
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

class CourseOfferingFile {
    public:
        int fileSize;
        int currPtr;
        CourseOffering *info;  // pointer to array

        void addCourseOffering(CourseFile * cf, InstructorFile * _if) {
            int courseNo;
            Course * course;
            cout << "Enter Course Number: ";
            cin >> courseNo;
            course = cf->findCourse(courseNo);
            if (course == NULL) {
                cout << "No course with number " << courseNo << endl << endl;
                return addCourseOffering(cf, _if);
            }
            else {
                info[currPtr].course = course;
            }
            addCourseOfferingB(cf, _if);
        }

        void addCourseOfferingB(CourseFile * cf, InstructorFile * _if) {
            int id;
            Instructor * instructor;
            cout << "Enter Instructor ID: ";
            cin >> id;
            instructor = _if->findInstructor(id);
            if (instructor == NULL) {
                cout << "No instructor with id " << id << endl << endl;
                return addCourseOfferingB(cf, _if);
            }
            else {
                info[currPtr].instructor = instructor;
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

    public:
        CourseOfferingFile() {
            fileSize = 10;
            currPtr = 0;
            info = new CourseOffering [fileSize];
        }

        ~CourseOfferingFile() {
            delete [] info;
        }

        void addMultipleCourseOfferings(CourseFile * cf, InstructorFile * _if) {
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
                info[i].print();
            }
            cout << endl;
        }

        CourseOffering * findCourseOffering(int year, string semester, int courseNo) {
            // linear search because not sure how to do binary search using multiple fields at once
            for (int i = 0; i < currPtr; i++) {
                CourseOffering *ans;
                if (info[i].course->number == courseNo && info[i].year == year && info[i].semester == semester) {
                    ans = &info[i];
                    return ans;
                }
            }
            return NULL;
        }
};

int main() {
    CourseFile courseFile;
    InstructorFile instructorFile;
    CourseOfferingFile courseOfferingFile;

    courseFile.addMultipleCourses();
    courseFile.printCourses();

    instructorFile.addMultipleInstructors();
    instructorFile.printInstructors();

    courseOfferingFile.addMultipleCourseOfferings(&courseFile, &instructorFile);
    courseOfferingFile.printCourseOfferings();
    CourseOffering *c = courseOfferingFile.findCourseOffering(2020, "Fall", 135);
    // if (c != NULL) cout << c->course->title << " " << c->semester << " " << c->year << endl;
}
