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
    
    }

    void addMultipleCourseRecords() {
    
    }

    void printCourses() {
    
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

}
