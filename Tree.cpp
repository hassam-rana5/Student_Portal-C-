#include<iostream>
#include"Tree.h"
#include<cstring>
#include<string.h>
#include <sstream>
#include <fstream>
#include<iomanip>
#include<stdlib.h>
using std::string;
using namespace std;
AttendanceNode::AttendanceNode(Date d,char s)//Constructor of Attendance node
{
        date=d;
        status=s;
        next=NULL;
}
AttendanceRecord::AttendanceRecord()//Constructor of Attendance Record
{
    head=tail=NULL;//Head and tail are equal to NULL;
    size=0;
}
void AttendanceRecord::Add(Date d,char status)//Adding new record
{
    if(head==NULL)//IF list is empty
    {
        tail=head=new AttendanceNode(d,status);
    }
    else//If list is not empty
    {
        tail->next=new AttendanceNode(d,status);
        tail=tail->next;
    }
    size++;//increment in size
}
char AttendanceRecord::DisplaySingle()//Display single node Data
{
    AttendanceNode* temp=head;
    while(temp!=NULL)//Run until list ends
    {

            cout<<temp->date.day<<"/"<<temp->date.month<<"/"<<temp->date.year<<setw(15)<<":  ";
            cout<<temp->status<<endl;

        temp=temp->next;
    }

}
void AttendanceRecord::Display()//To Display total Record
{

    if(head==NULL)
        cout<<"No record"<<endl;
    else
    {
        AttendanceNode* temp=head;
        while(temp!=NULL)
        {
            cout<<setw(10)<<temp->status;
            temp=temp->next;
        }
    }
}
Student::Student()//Default constructor
{

}
Student::Student(int i,string n,string f,int age,string dpt,Subject sub[5],AttendanceRecord A)//Parameterized Constructor
{
    setID(i);//Set ID
    setName(n);//Set Name
    setFname(f);//Set Father Name
    setAge(age);//Set Age
    setDepartment(dpt);//Set Department
    Attendance=A;//Set Attendance
    setCourses(sub);//Set Courses
    right=NULL;//Set right to NULL
    left=NULL;//Set left to NULL
    height=1;//Height is set 1

}
//Setters
void Student::setID(int i)
{
    ID=i;
}
void Student::setName(string n)
{
    Name=n;
}
void Student::setFname(string f)
{
    Fathername=f;
}
void Student::setAge(int a)
{
    age=a;
}
void Student::setDepartment(string D)
{
    Department=D;
}
void Student::setCourses(Subject c[5])
{
    for(int i=0;i<5;i++)
        course[i]=c[i];
}
void Student::setLeft(Student* l)
{
    left=l;
}
void Student::setRight(Student* R)
{
    right=R;
}
void Student::setHeight(int h)
{
    height=h;
}
void Student::setAttendance(Date d,char status)
{
    Attendance.Add(d,status);
}
//Getters
int Student::getID()
{
    return ID;
}
string Student::getName()
{
    return Name;
}
string Student::getFname()
{
    return Fathername;
}
int Student::getAge()
{
    return age;
}

string Student::getDepartment()
{
    return Department;
}
void Student::getCourses()
{
    for(int i=0;i<5;i++)
    {
        cout<<course[i].name<<" : "<<course[i].marks<<endl;
    }
}
AttendanceRecord* Student::getAttendance()
{

    Attendance.Display();
}
Student* Student::getLeft()
{
    return left;
}
Student* Student::getRight()
{
    return right;
}
int Student::getHeight()
{
    return height;
}
AVL::AVL()//Default constructor of AVL class
    {
        root=NULL;
    }
    Student* AVL::getRoot()//getting Root address
    {
        return root;
    }
    int AVL::Height(Student *node)//Getting height of Node
    {
        if(node==NULL)
            return 0;
        return node->getHeight();
    }
    int AVL::Max(int a, int b)//Getting Greater value
    {
        return a>b ? a : b;
    }
    int AVL::getBalance(Student *node)//Getting the Balance value of node
    {
        if(node==NULL)
            return 0;
        return Height(node->getLeft()) - Height(node->getRight());
    }
    Student* AVL::rightRotate(Student *node)//Rotating Right
    {
        Student* left = root->getLeft();
        Student* lRight = left->getRight();
        left->setRight(node);
        node->setLeft(lRight);
        node->setHeight(Max(Height(node->getRight()),Height(node->getLeft()))+1);
        left->setHeight(Max(Height(left->getLeft()),Height(left->getRight()))+1) ;
        return left;
    }
    Student* AVL::rotateLeft(Student *node)//Rotating left
    {
        Student* right = node->getRight();
        Student* rLeft = right->getLeft();
        right->setLeft(node);
        node->setRight(rLeft);
        node->setHeight(Max(Height(node->getRight()),Height(node->getLeft()))+1);
        right->setHeight(Max(Height(node->getLeft()),Height(node->getRight()))+1);
        return right;
    }
    Student* AVL::Insert(Student* node,int id,string name,string fname,int age,string department,Subject c[5],AttendanceRecord A)//Inserting new student Record
    {

        if(node == NULL)
            return new Student(id,name,fname,age,department,c,A);//dynamically inserting Student record
        else if(id > node->getID())
            node->setRight(Insert(node->getRight(),id,name,fname,age,department,c,A));//Calling insert function
        else if (id < node->getID())
            node->setLeft(Insert(node->getLeft(),id,name,fname,age,department,c,A));//Calling insert function
        else
            return node;
        node->setHeight(Max(Height(node->getLeft()), Height(node->getRight())) + 1);
        int balance = getBalance(node);
        if(balance > 1 and node->getID() > id) // left left case
        {
            return rightRotate(node);
        }
        if (balance < -1 and node->getID() < id) //right right case
        {
            return rotateLeft(node);
        }
        if(balance > 1 and node->getID() < id) // left right case
        {
            node->setLeft(rotateLeft(node->getLeft()));
            return rightRotate(node);
        }
        if (balance < -1 and node->getID() > id) //rotate right left
        {
            node->setRight(rightRotate(node->getRight()));
            return rotateLeft(node);
        }
        return node;
    }
    void AVL::inOrder(Student *node,int key)//In order function
    {

        if(node!=NULL)
        {

            inOrder(node->getLeft(),key);
            if(key==1)
            {
                //Displaying Student personal Information
                cout<<"==================================="<<endl;
                cout<<"ID               :";
                if(node->getID()<0)
                    cout<<"0";
                cout<<node->getID()<<endl;
                cout<<"Name             :"<<node->getName()<<endl;
                cout<<"Father Name      :"<<node->getFname()<<endl;
                cout<<"Age              :"<<node->getAge()<<endl;
                cout<<"Department       :"<<node->getDepartment()<<endl;
            }
            else if(key==2)
            {
                //Displaying student Attendance Record
                if(node->getID()<10)
                    cout<<"0";
                cout<<node->getID()<<". "<<setw(10)<<node->getName();
                node->Attendance.Display();

            }
            else if(key==3)
            {
                //Displaying Student Courses and marks
                cout<<node->getID()<<". "<<node->getName()<<endl;
                node->getCourses();
            }
            cout<<endl;
            inOrder(node->getRight(),key);
        }
    }
    void AVL::CreateAttendance(Student* node,Date d)//Creating Attendance
    {
        if(node!=NULL)
        {
            CreateAttendance(node->getLeft(),d);
            char status;
            cout<<node->getID()<<".";
            cout<<node->getName()<<" :";
            cin>>status;
            node->setAttendance(d,status);
            CreateAttendance(node->getRight(),d);
        }
    }
    void AVL::preOrder(Student *node,int key)//Pre Order function
    {
        if(node!=NULL)
        {
            if(key==1)
            {
               //Displaying Student personal Information
                cout<<"==================================="<<endl;
                cout<<"ID               :";
                if(node->getID()<0)
                    cout<<"0";
                cout<<node->getID()<<endl;
                cout<<"Name             :"<<node->getName()<<endl;
                cout<<"Father Name      :"<<node->getFname()<<endl;
                cout<<"Age              :"<<node->getAge()<<endl;
                cout<<"Department       :"<<node->getDepartment()<<endl;
            }
            else if(key==2)
            {
                //Displaying student Attendance Record
                if(node->getID()<10)
                    cout<<"0";
                cout<<node->getID()<<". "<<setw(10)<<node->getName();
                node->Attendance.Display();
            }
            else if(key==3)
            {
                //Displaying Student Courses and marks
                if(node->getID()<10)
                    cout<<"0";
                cout<<node->getID()<<". "<<node->getName()<<endl;
                node->getCourses();
            }
            preOrder(node->getLeft(),key);
            preOrder(node->getRight(),key);
        }
    }
    void AVL::postOrder(Student *node,int key)
    {
        if(node!=NULL)
        {
            postOrder(node->getLeft(),key);
            postOrder(node->getRight(),key);
            if(key==1)
            {
               //Displaying Student personal Information
                cout<<"==================================="<<endl;
                cout<<"ID               :";
                if(node->getID()<0)
                    cout<<"0";
                cout<<node->getID()<<endl;
                cout<<"Name             :"<<node->getName()<<endl;
                cout<<"Father Name      :"<<node->getFname()<<endl;
                cout<<"Age              :"<<node->getAge()<<endl;
                cout<<"Department       :"<<node->getDepartment()<<endl;
            }
            else if(key==2)
            {
                //Displaying student Attendance Record
                if(node->getID()<10)
                    cout<<"0";
                cout<<node->getID()<<". "<<setw(10)<<node->getName();
                node->Attendance.Display();
            }
            else if(key==3)
            {
                //Displaying Student Courses and marks
                if(node->getID()<10)
                    cout<<"0";
                cout<<node->getID()<<". "<<node->getName()<<endl;
                node->getCourses();
            }
        }
    }
    Student* AVL::Delete(int key,Student* node)//Delete function to Delete Record
    {
        if(node==NULL)
            return NULL;
        if(key > node->getID())
            node->setRight(Delete(key, node->getRight()));
        else if (key < node->getID())
            node->setLeft(Delete(key, node->getLeft()));
        else
        {
            if(node->getRight()==NULL and node->getLeft()==NULL)
            {
                delete node;
                return NULL;
            }
            else if(node->getLeft()==NULL)
            {
                Student* temp = node->getRight();
                delete node;
                return temp;
            }
            else if(node->getRight()==NULL)
            {
                Student* temp = node->getLeft();
                delete node;
                return temp;
            } else
            {
                int i = Maximum(node->getLeft())->getID();
                node->setID(i);
                node->setLeft(Delete(i,node->getLeft()));
            }
        }
        node->setHeight(Max(Height(node->getLeft()), Height(node->getRight())) + 1);
        int balance = getBalance(node);
        if(balance > 1 and node->getID() > key) // left left case
        {
            return rightRotate(node);
        }
        if (balance < -1 and node->getID() < key) //right right case
        {
            return rotateLeft(node);
        }
        if(balance > 1 and node->getID() < key) // left right case
        {
            node->setLeft(rotateLeft(node->getLeft()));
            return rightRotate(node);
        }
        if (balance < -1 and node->getID() > key) //rotate right left
        {
            node->setRight(rightRotate(node->getRight()));
            return rotateLeft(node);
        }
        return node;
    }
    Student* AVL::Maximum(Student *node)//To find node with highest Id
    {
        while (node->getRight()!=NULL)
        {
            node = node->getRight();
        }
        return node;
    }
    Student* AVL::Minimum(Student *node)//To find node with smallest id
    {
        while (node->getLeft()!=NULL)
        {
            node = node->getLeft();
        }
        return node;
    }
    Student* AVL::SearchResult(int key,Student *node)//To  Search Result of a student
    {
        while (node!=NULL)
        {
            if(key==node->getID())
            {
                break;
            }
            else if(key > node->getID())
            {
                node = node->getRight();
            } else
            {
                node = node->getLeft();
            }
        }
        if(node==NULL)
        {
            cout<<"Record not found"<<endl;
            return NULL;
        }
        else
        {
            return node;
        }
    }
    Student* AVL::SearchStudent(int key,Student *node)//To  Search Result of a student
    {
        while (node!=NULL)
        {
            if(key==node->getID())
            {
                break;
            }
            else if(key > node->getID())
            {
                node = node->getRight();
            } else
            {
                node = node->getLeft();
            }
        }
        if(node==NULL)
        {
            cout<<"Record not found"<<endl;
            return NULL;
        }
        else
        {
            return node;
        }
    }
    void AVL::SearchAttendance(int key,Student* node)//To search attendance of a student
    {
        bool flag=false;
        while (node!=NULL)
        {
            if(node->getID()==key)
            {
                cout<<node->getID()<<". "<<node->getName()<<":"<<endl;
                node->Attendance.DisplaySingle();
                flag=true;
                break;

            }
            else if(key > node->getID())
            {
                node = node->getRight();
            }
            else
            {
                node = node->getLeft();
            }
        }
        if(flag==false)
            cout<<"Record not found"<<endl;
    }
    void insertCourse(Student* &node)//Inserting to course
    {
        system("CLS");
        cout<<node->getID()<<". "<<node->getName()<<endl;
        string c;
        int m;
        for(int i=0;i<5;i++)
            {
                cout<<"Course"<<i+1<<":";
                cin>>c;
                node->course[i].name=c;
                cout<<"Marks";
                cin>>m;
                node->course[i].marks=m;
            }
    }
    void AVL::CoursesEntry(Student* node)//Course Entry
    {
        if(node!=NULL)
        {
            CoursesEntry(node->getLeft());
            insertCourse(node);
            CoursesEntry(node->getRight());
        }
    }
    void ModifyData(AVL &tree)
    {
            string name,department,fname;
            int age,id;
            cout<<"Enter ID"<<endl;
            cin>>id;
            Student* node=tree.SearchStudent(id,tree.getRoot());
            if(node)
            {
                cout<<"==================================="<<endl;
            cout<<"ID               :";
            if(node->getID()<0)
                cout<<"0";
            cout<<node->getID()<<endl;
            cout<<"Enter Name        :";
            cin>>name;
            cout<<"Enter Father Name :";
            cin>>fname;
            cout<<"Enter Age         :";
            cin>>age;
            cout<<"Enter Department  :";
            cin>>department;
            node->setName(name);
            node->setFname(fname);
            node->setAge(age);
            node->setDepartment(department);
            }
    }
void GUI::menu()//Main Menu Function
{
    int Menu;
    char p;
    int s;
    bool t=true;
    bool read=false;
    while(t)
    {
        system("CLS");
        cout<<"1.Load Data"<<endl;
        cout<<"2.Attendance"<<endl;
        cout<<"3.Students"<<endl;
        cout<<"4.Results"<<endl;
        cout<<"0.Save and Logout"<<endl;
        cout<<"Select an option:";
        cin>>Menu;
        switch(Menu)
        {
        case 1:
            //To load Data and create a tree
                if(!read)
                    {
                		t1.root=db.read(t1.root);
                		read = true;
					}
					else
					{
						cout<<"Your are already load data from file. If you load data again. Data will be duplicate. So, this feature is disable"<<endl;
						getchar();
					}

                    break;
        case 2:
            //Calling Attendance Menu
                AttendanceMenu(t1);
            break;
        case 3:
            //Calling Student Menu
                StudentMenu(t1);
                break;
        case 4:
            //Calling Result Menu
                ResultMenu(t1);
            break;
        case 0:
            t=false;
            break;

        }
    }
if(db.open1())
{
    db.Save(t1.root);
    db.close();
}
}
void GUI::AttendanceMenu(AVL &tree)
{
    int menu,size=0;
    int d,m,y,id,op;
    Date D;
    bool t=true;
    while(t)
    {
        //Attendance menu
        system("CLS");
        cout<<"1.Create Attendance"<<endl;
        cout<<"2.Show Attendance"<<endl;
        cout<<"3.Search Attendance"<<endl;
        cout<<"0.To Return to main menu"<<endl;
        cout<<"Select any option:";
        cin>>menu;
        system("CLS");
        switch(menu)
        {
        case 1:
            //Creating new class attendance
            cout<<"Enter date(day,month,year):"<<endl;
            cin>>d>>m>>y;
            D.setDate(d,m,y);
            tree.CreateAttendance(tree.getRoot(),D);
            size++;
            break;
        case 2:
            //Displaying Data to Class Attendance
            size=tree.root->Attendance.size;
            cout<<"##"<<". "<<setw(10)<<"Class";
            for(int i=1;i<=size;i++)
            {
                cout<<setw(10)<<i;
            }
            cout<<endl;
            tree.inOrder(tree.getRoot(),2);
            cout<<"Enter 0 to return:";
            cin>>op;
            break;
        case 3:
            //Searching attendance record of a particular student
            cout<<"Enter ID"<<endl;
            cin>>id;
            tree.SearchAttendance(id,tree.getRoot());
            cout<<"Enter 0 to return:";
            cin>>op;
            break;
        case 0:
            t=false;
            break;
        }
    }

}
void GUI::ResultMenu(AVL &tree)
{
    int menu,op;
    int id,marks;
    string name;
    Subject C[5];
    bool t=true;
    while(t)
    {
        system("ClS");
        cout<<"1.Add Result"<<endl;
        cout<<"2.Show Results"<<endl;
        cout<<"3.Search Result"<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"Select any option:";
        cin>>menu;
        system("ClS");
        switch(menu)
        {
        case 0:
            t=false;
            break;
        case 1:
            tree.CoursesEntry(tree.getRoot());
            break;
        case 2:
            tree.inOrder(tree.getRoot(),3);
            cout<<"Enter 0 to return:";
            cin>>op;
            break;
        case 3:
            int p;
            cout<<"Enter ID      :";
            cin>>id;
            Student* node=tree.SearchResult(id,tree.getRoot());
            if(node)
            {
                cout<<"1.Display result"<<endl;
                cout<<"2.Enter Result"<<endl;
                cout<<"Select option:";
                cin>>p;
                if(p==1)
                {
                    cout<<node->getID()<<". "<<node->getName()<<endl;
                    node->getCourses();
                }
                else if(p==2)
                {
                    insertCourse(node);
                }
                else
                {
                    cout<<"invalid input"<<endl;
                }
            }
            cout<<"Enter 0 to return:";
            cin>>op;
            break;
        }
    }

}
void GUI::StudentMenu(AVL &tree)
{
    int menu,op;
    int id,age;
    string name,fname,department;
    Student* node;
    Subject c[5];
    for(int i=0;i<5;i++)
    {
        c[i].name="-";
        c[i].marks=0;
    }
    AttendanceRecord A;
    bool t=true;
    while(t)
    {

        system("ClS");
        cout<<"1.Add Student"<<endl;
        cout<<"2.Show Students"<<endl;
        cout<<"3.Search Record"<<endl;
        cout<<"4.Delete Student Record"<<endl;
        cout<<"5.Modify Student Record"<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"Select any option:";
        cin>>menu;
        system("ClS");
        switch(menu)
        {
        case 1:
            cout<<"Enter ID          :";
            cin>>id;
            cout<<"Enter Name        :";
            cin>>name;
            cout<<"Enter Father Name :";
            cin>>fname;
            cout<<"Enter Age         :";
            cin>>age;
            cout<<"Enter Department  :";
            cin>>department;

            tree.root=tree.Insert(tree.getRoot(),id,name,fname,age,department,c,A);
            break;
        case 2:
            tree.inOrder(tree.getRoot(),1);
            cout<<"Enter 0 to return:";
            cin>>op;
            break;
        case 3:
            cout<<"Enter ID"<<endl;
            cin>>id;
            node=tree.SearchStudent(id,tree.getRoot());
            if(node)
            {
                cout<<"==================================="<<endl;
                cout<<"ID               :";
                if(node->getID()<0)
                    cout<<"0";
                cout<<node->getID()<<endl;
                cout<<"Name             :"<<node->getName()<<endl;
                cout<<"Father Name      :"<<node->getFname()<<endl;
                cout<<"Age              :"<<node->getAge()<<endl;
                cout<<"Department       :"<<node->getDepartment()<<endl;
            }
            cout<<"Enter 0 to return:";
            cin>>op;
            break;
        case 4:
            cout<<"Enter ID:";
            cin>>id;
            tree.Delete(id,tree.getRoot());\
            cout<<"Enter 0 to return:";
            cin>>op;
            break;
        case 5:
            ModifyData(tree);
            cout<<"Enter 0 to return:";
            cin>>op;
        case 0:
            t=false;
            break;
        }
    }
}
int Database::toInt(string s)
    {
        return atoi(s.c_str());
    }
void Database::Save(Student *node) {
		if(node!=NULL)
		{
			Save(node->getLeft());
			write1(node);
			Save(node->getRight());
		}
	}
void Database::close()
	{
		file.close();
	}
bool Database::open1()
	{
		file.open("students.txt",ios::out | ios::trunc);
		if(file)
			return true;
		else
			return false;
	}
Database::Database() {

}

Student* Database::read(Student* root) {
	file.open("students.txt",ios::in);
    if(file)
    {
        Student emp;
        string input;
        AVL tree;
        Subject c[5];
        AttendanceRecord A;
        while (getline(file,input))
        {
            emp =  split(input);
            for(int i=0;i<5;i++)
            {
                c[i].name=emp.course[i].name;
                c[i].marks=emp.course[i].marks;
            }
            getline(file,input);
            A=split2(input);
            root = tree.Insert(root,emp.getID(),emp.getName(),emp.getFname(),emp.getAge(),emp.getDepartment(),c,A);

        }
    }
    else
    {
        return NULL;
    }
    file.close();
    return root;
}

void Database::write1(Student *node) {
	if(file)
    if(node!=0)
    {
        AttendanceNode* temp=node->Attendance.head;
        file<<node->getID()<<","<<node->getName()<<","<<node->getFname()<<","<<node->getAge()<<","<<node->getDepartment()<<","<<node->course[0].name<<","<<node->course[0].marks<<","<<node->course[1].name<<","<<node->course[1].marks<<","<<node->course[2].name<<","<<node->course[2].marks<<","<<node->course[3].name<<","<<node->course[3].marks<<","<<node->course[4].name<<","<<node->course[4].marks<<endl;
        while(temp!=NULL)
        {
            file<<temp->date.day<<","<<temp->date.month<<","<<temp->date.year<<","<<temp->status<<",";
            temp=temp->next;
        }
        file<<"-"<<endl;
    }
}
Student Database::split(string line)//Spliting Data in respective data type
{
	string word;
	Student emp;
	stringstream s(line);
    getline(s,word,',');
    emp.setID(toInt(word));
    getline(s,word,',');
    emp.setName(word);
    getline(s,word,',');
    emp.setFname(word);
    getline(s,word,',');
    emp.setAge(toInt(word));
    getline(s,word,',');
    emp.setDepartment(word);
    getline(s,word,',');
    emp.course[0].name=word;
    getline(s,word,',');
    emp.course[0].marks=toInt(word);
    getline(s,word,',');
    emp.course[1].name=word;
    getline(s,word,',');
    emp.course[1].marks=toInt(word);
    getline(s,word,',');
    emp.course[2].name=word;
    getline(s,word,',');
    emp.course[2].marks=toInt(word);
    getline(s,word,',');
    emp.course[3].name=word;
    getline(s,word,',');
    emp.course[3].marks=toInt(word);
    getline(s,word,',');
    emp.course[4].name=word;
    getline(s,word,',');
    emp.course[4].marks=toInt(word);
    return emp;
}
AttendanceRecord Database::split2(string line)
{
    string word;
	AttendanceRecord A;
	Date date;
	char status;
	stringstream s(line);
	getline(s,word,',');
	while(word[0]!='-')
    {
        date.day=toInt(word);
        getline(s,word,',');
        date.month=toInt(word);
        getline(s,word,',');
        date.year=toInt(word);
        getline(s,word,',');
        status=word[0];
        A.Add(date,status);
        getline(s,word,',');

    }
    return A;
}
string getPassword()
{
	string password;
    cin>>password;
    return password;
}


