#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void waitx() {
    string c;
    cout << "Press <Return> to continue... ";
    cin.ignore();
    getline(cin, c);
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

struct Student {
    int id;
    string firstName;
    string lastName;
    string program;

    void print() {
        cout << left << setw(5) << id << left << setw(20) << firstName + " "  + lastName << " ";
        cout << left << setw(20) << program << endl;
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

struct CourseRegistration {
    CourseOffering *courseOffering;
    Student *student;
    int grade = 0;

    void print() {
        cout << left << setw(20) << courseOffering->course->title;
        cout << left << setw(8) << courseOffering->course->number;
        cout << left << setw(13) << courseOffering->semester + " " + to_string(courseOffering->year);
        cout << left << setw(20) << student->firstName + " " + student->lastName;
        cout << left << setw(5) << grade << endl; 
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
                    return &info[m];
                }
                else if (num > info[m].number) return binarySearch(m+1, r, num);
                else return binarySearch(l, m-1, num);
            }
            return NULL;
        }

        Course * linearSearch(int l, int r, int num) {
            for (int i = l; i < r; i++) {
                if (num == info[i].number) {
                    return &info[i];
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

        ~CourseFile() {
            delete [] info;
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
            if (c != NULL) c->print();
            return c;
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
                    return &info[m];
                }
                else if (num > info[m].id) return binarySearch(m+1, r, num);
                else return binarySearch(l, m-1, num);
            }
            return NULL;
        }

        Instructor * linearSearch(int l, int r, int num) {
            for (int i = l; i < r; i++) {
                if (num == info[i].id) {
                    return &info[i];
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
            if (i != NULL) i->print();
            return i;
        }
};

class StudentFile {
    private:
        int fileSize;
        int currPtr;
        bool sorted;
        Student *info;  // pointer to array
        friend struct CourseRegistration;
        friend class CourseRegistrationFile;

        Student * binarySearch(int l, int r, int num) {
            if (r >= l) {
                int m = (r + l)/2;
                if (num == info[m].id) {
                    return &info[m];
                }
                else if (num > info[m].id) return binarySearch(m+1, r, num);
                else return binarySearch(l, m-1, num);
            }
            return NULL;
        }

        Student * linearSearch(int l, int r, int num) {
            for (int i = l; i < r; i++) {
                if (num == info[i].id) {
                    return &info[i];
                }
            }
            return NULL;
        }

        void addStudent() {
            cout << "Enter Student ID: ";
            cin >> info[currPtr].id;

            if (currPtr >= 1 && info[currPtr].id < info[currPtr - 1].id) {
                sorted = false;
            }

            cout << "Enter Student First Name: ";
            cin >> info[currPtr].firstName;

            cout << "Enter Student Last Name: ";
            cin >> info[currPtr].lastName;

            cout << "Enter Student Program: ";
            cin.ignore();
            getline(cin, info[currPtr].program);

            currPtr++;

            cout << endl;
        }

    public:
        StudentFile() {
            fileSize = 10;
            currPtr = 0;
            sorted = true;
            info = new Student [fileSize];
        }

        ~StudentFile() {
            delete [] info;
        }

        void addMultipleStudents() {
            int num;

            cout << "How many students to add? ";
            cin >> num;

            while (num + currPtr >= fileSize) {
                Student *temp = new Student [2 * fileSize];
                for (int i = 0; i < currPtr; i++) {
                    temp[i] = info[i];
                }
                delete [] info;
                info = temp;
                fileSize *= 2;
            }

            for (int i = 0; i < num; i++) {
                addStudent();
            }
        }

        void printStudents() {
            for (int i = 0; i < currPtr; i++) {
                info[i].print();
            }
            cout << endl;
        }

        Student * findStudent(int studentID) {
            Student * s;
            if (sorted) {  // do a binary search
                s = binarySearch(0, currPtr, studentID);
            }
            else {  
                // do a linear search. makes sense to sort first then do binary search but code for merge sort is long
                // maybe sort as entries are added so list is always corted
                s = linearSearch(0, currPtr, studentID);
            }
            if (s != NULL) s->print();
            return s;
        }
};

class CourseOfferingFile {
    private:
        int fileSize;
        int currPtr;
        CourseOffering *info;  // pointer to array

        void addCourseOffering(CourseFile * cf, InstructorFile * _if) {
            int courseNo;
            Course * course;
            do {
                cout << "Enter Course Number: ";
                cin >> courseNo;
                course = cf->findCourse(courseNo);
                if (course == NULL) {
                    cout << "No course with number " << courseNo << endl << endl;
                    return addCourseOffering(cf, _if);
                }
            }
            while (course == NULL);
            info[currPtr].course = course;

            int id;
            Instructor * instructor;
            do {
                cout << "Enter Instructor ID: ";
                cin >> id;
                instructor = _if->findInstructor(id);
                if (instructor == NULL) {
                    cout << "No instructor with id " << id << endl << endl;
                }
            }
            while (instructor == NULL);
            info[currPtr].instructor = instructor;

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
                    info[i].print();
                    return &info[i];
                }
            }
            return NULL;
        }
};

class CourseRegistrationFile {
    private:
        int fileSize;
        int currPtr;
        CourseRegistration *info;  // pointer to array

        void addCourseRegistration(CourseOfferingFile * cof, Student * s, int year, string semester) {
            int courseNo;
            CourseOffering * courseOffering;
            do {
                cout << "Enter Course Number: ";
                cin >> courseNo;
                courseOffering = cof->findCourseOffering(year, semester, courseNo);
                if (courseOffering == NULL) {
                    cout << "Course " << courseNo << " is not offered in " << semester << " " << year << " semester." << endl;
                }
            }
            while (courseOffering == NULL);
            info[currPtr].student = s;
            info[currPtr].courseOffering = courseOffering;
            currPtr++;
        }

        void registerStudent(CourseOfferingFile * cof, StudentFile * sf) {
            int studentID;
            Student * student;
            do {
                cout << "Adding new class registration for a student..." << endl;
                cout << "Enter Student ID: ";
                cin >> studentID;
                student = sf->findStudent(studentID);
                if (student == NULL) {
                    cout << "No student with ID " << studentID << endl;
                }
            }
            while (student == NULL);

            int year;
            cout << "Enter Year: ";
            cin >> year;

            string semester;
            cout << "Enter Semester: ";
            cin >> semester;

            int num;
            cout << "How many courses to register student for? ";
            cin >> num;

            for (int i = 0; i < num; i++) {
                addCourseRegistration(cof, student, year, semester);
            }
        }

    public:
        CourseRegistrationFile() {
            fileSize = 10;
            currPtr = 0;
            info = new CourseRegistration [fileSize];
        }

        ~CourseRegistrationFile() {
            delete [] info;
        }

        void registerMultipleStudents(CourseOfferingFile * cof, StudentFile * sf) {
            int num;
            cout << "How many students to register for courses? ";
            cin >> num;

            while (num + currPtr >= fileSize) {
                CourseRegistration *temp = new CourseRegistration [2 * fileSize];
                for (int i = 0; i < currPtr; i++) {
                    temp[i] = info[i];
                }
                delete [] info;
                info = temp;
                fileSize *= 2;
            }

            for (int i = 0; i < num; i++) {
                registerStudent(cof, sf);
            }
        }

        void printCourseRegistrations() {
            for (int i = 0; i < currPtr; i++) {
                info[i].print();
            }
            cout << endl;
        }

        CourseRegistration * findCourseRegistration(int year, string semester, int courseNo, int studentID) {
            // linear search because not sure how to do binary search using multiple fields at once
            for (int i = 0; i < currPtr; i++) {
                CourseRegistration *ans;
                if (info[i].courseOffering->course->number == courseNo && info[i].courseOffering->year == year && info[i].courseOffering->semester == semester && info[i].student->id == studentID) {
                    info[i].print();
                    return &info[i];
                }
            }
            return NULL;
        }

        void assignGrades() {
            int num;
            cout << "How many grades to assign? ";
            cin >> num;

            int year;
            string semester;
            int courseNo;
            int studentID;
            CourseRegistration * courseRegistration;

            for (int i = 0; i < num; i++) {
                do {
                    cout << "Enter Student ID: ";
                    cin >> studentID;

                    cout << "Enter Course Number: ";
                    cin >> courseNo;

                    cout << "Enter Semester: ";
                    cin >> semester;

                    cout << "Enter Year: ";
                    cin >> year;

                    courseRegistration = findCourseRegistration(year, semester, courseNo, studentID);
                    if (courseRegistration == NULL) {
                        cout << "Can't find this course registration" << endl << endl;
                    }
                }
                while (courseRegistration == NULL);

                int grade;
                cout << "Enter Student Grade: ";
                cin >> courseRegistration->grade;
            }
        }
};

int main() {
    CourseFile courseFile;
    InstructorFile instructorFile;
    StudentFile studentFile;
    CourseOfferingFile courseOfferingFile;
    CourseRegistrationFile courseRegistrationFile;

    int option;
    do {
        clearScreen();
        cout << "Select an option: " << endl;
        cout << "1: Add Courses" << endl;
        cout << "2: Add Instructors" << endl;
        cout << "3: Add Students" << endl;
        cout << "4: Add Course Offerings" << endl;
        cout << "5: Register students" << endl;
        cout << "6: View Courses" << endl;
        cout << "7: View Instructors" << endl;
        cout << "8: View Students" << endl;
        cout << "9: View Course Offerings" << endl;
        cout << "10: View Course Registrations" << endl;
        cout << "11: Assign grades" << endl;
        cout << "Use any other number to quit" << endl << endl;

        cin >> option;

        switch (option) {
            case 1:
                clearScreen();
                courseFile.addMultipleCourses();
                break;
            case 2:
                clearScreen();
                instructorFile.addMultipleInstructors();
                break;
            case 3:
                clearScreen();
                studentFile.addMultipleStudents();
                break;
            case 4:
                clearScreen();
                courseOfferingFile.addMultipleCourseOfferings(&courseFile, &instructorFile);
                break;
            case 5:
                clearScreen();
                courseRegistrationFile.registerMultipleStudents(&courseOfferingFile, &studentFile);
                break;
            case 6:
                clearScreen();
                courseFile.printCourses();
                waitx();
                break;
            case 7:
                clearScreen();
                instructorFile.printInstructors();
                waitx();
                break;
            case 8:
                clearScreen();
                studentFile.printStudents();
                waitx();
                break;
            case 9:
                clearScreen();
                courseOfferingFile.printCourseOfferings();
                waitx();
                break;
            case 10:
                clearScreen();
                courseRegistrationFile.printCourseRegistrations();
                waitx();
                break;
            case 11:
                clearScreen();
                courseRegistrationFile.assignGrades();
                break;
            default:
                break;
        }
    }
    while (option > 0 && option < 12);
}
