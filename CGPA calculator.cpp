#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

// Colors function
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Create structure
struct Course
{
    string name;
    string grade;
    int creditHours;
    double gradePoints;
};

// Function to convert grade into grade point
double getGradePoint(string grade)
{
// Basic grade point criteria 
    if (grade == "A+" || grade == "A")
        return 4.0;
    else if (grade == "A-")
        return 3.7;
    else if (grade == "B+")
        return 3.3;
    else if (grade == "B")
        return 3.0;
    else if (grade == "B-")
        return 2.7;
    else if (grade == "C+")
        return 2.3;
    else if (grade == "C")
        return 2.0;
    else if (grade == "C-")
        return 1.7;
    else if (grade == "D")
        return 1.0;
    else if (grade == "F")
        return 0.0;
    else
        return -1;
}

// Function for GPA calculating
void calculateSemesterGPA()
{
    int numberOfCourses;

    setColor(11); // Light blue

    cout << "-------------------------------------";
    cout << "\n------ CGPA CALCULATOR ------\n";
    cout << "-------------------------------------\n";

p: // Label

    setColor(7); // White

    cout << "Enter number of courses: ";
    cin >> numberOfCourses;

    if (numberOfCourses <= 0 || numberOfCourses > 20)
    {
        setColor(12); // Red

        cout << "Invalid number of courses. "
             << "Enter between 1 and 20.\n";

        setColor(2); // Green

        cout << "\n----Try again----\n";

        setColor(7); // White

        goto p;
    }

    Course courses[20];

    double totalCredits = 0;
    double totalGradePoints = 0;

    for (int i = 0; i < numberOfCourses; i++)
    {
    input: // Label

        setColor(7); // White

        cout << "\nCourse " << i + 1 << endl;

        // Ignore leftover newline before getline
        cin.ignore(1000, '\n');

        cout << "Enter course name: ";
        getline(cin, courses[i].name);

        cout << "Enter grade (A+, A, A-, B+, B, B-, C+, C, C-, D, F): ";
        cin >> courses[i].grade;

        cout << "Enter credit hours: ";
        cin >> courses[i].creditHours;

        // Convert grade into grade point
        courses[i].gradePoints =
            getGradePoint(courses[i].grade);

        // Validate grade and credit hours
        if (courses[i].gradePoints == -1 ||
            courses[i].creditHours <= 0)
        {
            setColor(12); // Red

            cout << "Invalid grade or credit hours.\n";

            setColor(2); // Green

            cout << "\n----Try again----\n";

            goto input;
        }

        // Calculate grade points
        double courseGradePoints =
            courses[i].gradePoints *
            courses[i].creditHours;

        totalCredits += courses[i].creditHours;
        totalGradePoints += courseGradePoints;
    }

    // Calculate GPA
    double GPA = totalGradePoints / totalCredits;

    setColor(9); // Blue

    cout << "\n       ---------------- COURSE DETAILS ----------------\n\n";

    // Table headings
    cout << left
         << setw(25) << "Course Name"
         << setw(10) << "Grade"
         << setw(15) << "Grade Point"
         << setw(15) << "Credit Hours"
         << endl;

    cout << "---------------------------------------------------------------\n";

    // Display course details
    for (int i = 0; i < numberOfCourses; i++)
    {
        cout << left
             << setw(25) << courses[i].name
             << setw(10) << courses[i].grade
             << setw(15) << fixed << setprecision(2)
             << courses[i].gradePoints
             << setw(15) << courses[i].creditHours
             << endl;
    }

    cout << "---------------------------------------------------------------\n";

    cout << "\nTotal Credit Hours: "
         << totalCredits << endl;

    cout << "Total Grade Points: "
         << totalGradePoints << endl;

    cout << "Semester GPA: "
         << GPA << endl;

    setColor(7); // White
}

int main()
{
    calculateSemesterGPA(); // Calling function

    return 0;
}
