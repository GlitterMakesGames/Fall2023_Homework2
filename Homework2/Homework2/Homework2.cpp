/*
* Author: Delaina Hardwick
* Date: Sep 19 2023
* Assignment: Write a C++ program that reads a list of students
*             and their grades from a file, and ultimately evaluates
*             and displays that data in a number of ways.
* Requirement #1: Create a class called Student that holds a student's
*             first name, last name, and grade.
* Requirement #2: Create a vector of Student objects.
* Requirement #3: Your program should read each line from the text file,
*             and break that line into 3 pieces. Store that line's data
*             in a Student object, then add it to the Students vector.
* Requirement #4: After all lines are read, sort the list by highest
*             grade to lowest, and display the sorted list of students
*             with their grades.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class Student
{
public:
    string firstName = "";
    string lastName = "";
    int grade = 0;

    Student(string fn, string ln, string gr)
    {
        firstName = fn;
        lastName = ln;
        try
        {
            grade = stoi(gr);
        }
        catch (...)
        {
            throw std::invalid_argument("");
        }
    }
};

Student* createStudentEntry(string data, int lineNum)
{
    Student* student = nullptr;
    stringstream my_stream(data);
    vector<string> result;

    while (my_stream.good())
    {
        string substr;
        char last;
        getline(my_stream, substr, ' ');
        last = substr[substr.length() - 1];

        if ((last >= 65 && last <= 90)
            || (last >= 97 && last <= 122)
            || (last >= 48 && last <= 57))
        {
            result.push_back(substr);
        }
        else
        {
            substr = substr.substr(0, substr.length() - 1);
            result.push_back(substr);
        }
    }

    try
    {
        student = new Student(result[0], result[1], result[2]);
    }
    catch (std::invalid_argument)
    {
        cout << "The student grade recorded in line " << lineNum << " could not be converted into an integer value;" << "\n";
        cout << "Please double check your text file and try again." << "\n";
        cout << "For now, a default value of 0 will be used." << "\n" << "\n";
        student = new Student(result[0], result[1], "0");
    }

    return student;
}

void swap(Student*& a, Student*& b)
{
    Student* temp = a;
    a = b;
    b = temp;
}

void sort(vector<Student*>& vect)
{
    int vSize = vect.size();
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < vSize - 1; i++)
        {
            if (vect[i]->grade < vect[i + 1]->grade)
            {
                swap(vect[i], vect[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

int main()
{
    fstream newFile;
    string fileName;
    string line;
    int lineNum = 0;

    Student* student;
    vector<Student*> studentRoster;

    cout << "Please enter the name of the file you will be using: ";
    cin >> fileName;

    try
    {
        newFile.open(fileName);
    }
    catch (...)
    {
        cout << "\n" << "Your file was unable to be opened.";
        cout << "\n" << "Please restart the program and try again." << "\n" << "\n";

        cout << "Tips:" << "\n";
        cout << "--- Be sure that your spelling is exact. Do not include quotation marks." << "\n";
        cout << "--- Verify that your file is located within the same directory as this source code." << "\n" << "\n";
    }

    if (newFile.is_open())
    {
        while (getline(newFile, line))
        {
            lineNum++;
            while (line.length() == 0)
            {
                if (!getline(newFile, line))
                {
                    break;
                }
                else
                {
                    lineNum++;
                    continue;
                }
            }
            student = createStudentEntry(line, lineNum);
            studentRoster.push_back(student);
        }
    }

    sort(studentRoster);

    cout << "\n";
    for (int i = 0; i<studentRoster.size(); i++)
    {
        cout << studentRoster[i]->firstName << " " << studentRoster[i]->lastName << ": " << studentRoster[i]->grade << "\n";
    }
}