#include<iostream>
#include <sstream>
#include <fstream>
#include<iomanip>
#include<stdlib.h>
#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
using namespace std;
struct Date//Dates will be managed using struct Date
{
    int day;
    int month;
    int year;
    Date(int d=0,int m=0,int y=0)//Default parameterized Constructor
    {
        day=d;
        month=m;
        year=y;
    }
    void setDate(int d,int m,int y)//Function to set Dates optional
    {
        day=d;
        month=m;
        year=y;
    }

};
struct Subject//Created for Subject information
{
    string name;//Subject Name
    int marks;//Subject Marks
};
struct AttendanceNode//Node for managing a particular attendance.
{
    Date date;//Attendance Date
    char status;//Attendance status in date
    AttendanceNode* next;//pointer to next node
    AttendanceNode(Date d,char s);//Constructor
    bool isEqual(Date d)//Function to compare Date
    {
        if(date.day==d.day&&date.month==d.month&&date.year==d.year)
            return true;
        else
            false;
    }

};
struct AttendanceRecord//Link list to create attendance
{
    AttendanceNode* head;//Head of list
    AttendanceNode* tail;//Tail of List
    int size;//Size of list
    AttendanceRecord();//Default constructor
    void Add(Date d,char status);//function to append a new node
    char DisplaySingle();//Function display single node Data
    void Display();//Function to Display list
};
class Student//Class of Student
{
    int ID;//Student ID
    string Name;//Student Name
    string Fathername;//Student Father Name
    int age;//Student Age
    string Department;//Student Department
    Student* left;//left pointer
    Student* right;//Right pointer
    int height;//Height of node
public:
    Subject course[5];//Array of subjects of student
    AttendanceRecord Attendance;//list of student Attendance
    Student();//Default Constructor of Student class
    Student(int i,string n,string f,int age,string dpt,Subject sub[5],AttendanceRecord A);//parameterized Constructor
    //Setters
    void setID(int i);
    void setName(string n);
    void setFname(string f);
    void setAge(int a);
    void setDepartment(string D);
    void setCourses(Subject c[5]);
    void setAttendance(Date d,char status);
    void setLeft(Student* l);
    void setRight(Student* R);
    void setHeight(int h);
    //Getters
    int getID();
    string getName();
    string getFname();
    int getAge();
    string getDepartment();
    void getCourses();
    AttendanceRecord* getAttendance();
    Student* getLeft();
    Student* getRight();
    int getHeight();
};
class AVL//AVL tree class
{
int Height(Student *node);//Function to find height
int Max(int a, int b);//function to determine greater value
int getBalance(Student *node);//function to get aware of balancing tree
Student *rightRotate(Student *node);//Function to  Rotate the node to right
Student* rotateLeft(Student *node);//Function to rotate the node to left
public:
Student* root;//Root of the tree
AVL();//Constructor
Student* getRoot();//get Root
Student* Insert(Student* node,int id,string name,string fname,int age,string department,Subject c[5],AttendanceRecord A);//Function to insert a new student record.
void inOrder(Student *node,int key);//InOrder Display
void preOrder(Student *node,int key);//Pre Order Display
void postOrder(Student *node,int key);//Post Order Display
Student* Delete(int key,Student *node);//Function to Delete a student record
Student* Maximum(Student *node);//Function to find the max id record
Student* SearchStudent(int key,Student *node);//Function to Search Student
Student* SearchResult(int key,Student *node);//Function to Search Result
Student* Minimum(Student *node);//Function to find the minimum id record
void CreateAttendance(Student* node,Date d);//Function to create new Attendance of class
void SearchAttendance(int key,Student *node);//Function to search Attendance of a student
void CoursesEntry(Student* node);//Function to insert courses
};
class Database//Database class for file handling
{
public:
    fstream file;//Declaring file
    Database();//Default constructor
    Student* read(Student* root);//Function to read file and generate a tree
    void write1(Student *node);//Function to write data in the file
    Student split(string);//Splits the data in the file.
    AttendanceRecord split2(string);//Splits the data of attendance
    int toInt(string s);//Function to convert from string to int
    void Save(Student *node);//Function used to write all data in file
	void close();//Close file
	bool open1();//Open file

};
class GUI
{
    AVL t1;//Object of AVL tree
    Database db;//Object of Database
public:
    int size;
    void menu();//Main Menu
    void AttendanceMenu(AVL &tree);//Attendance Menu
    void ResultMenu(AVL &tree);//Result Menu
    void StudentMenu(AVL &tree);//Student Menu

};
class Login//Login class
{
    fstream Loginfile;
public:
    Login()
    {

    }
    void open()
    {
        Loginfile.open("Private.txt",ios::in);
    }
    bool login(string user,string password)
    {
    	if(user=="HassamAliRana"&&password=="12345"||user=="Abdullah"&&password=="5678"||user=="Hanzla"&&password=="7890")
    	{
    	    return true;
    	}
    	else
        {
            return false;
        }
    }

};
#endif // TREE_H_INCLUDED
