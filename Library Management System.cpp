#include<bits/stdc++.h>
using namespace std;

void cover();

enum Month {jan=1,feb,march,april,may,june,july,aug,sept,october,nov,decm};

struct error_date
{
    int i;
    error_date (int p)
    {
        i = p;
    }
};
class Date
{
private:
    int d,m,y;
public:
    static int MAX_Months[13];
    Date (int dd=0,Month mm=Month(0),int yy=0);
    Date& add_day(int n);
    bool operator>(Date date);
    int operator-(Date date);
    bool leapyear(int n);
    void print_date();
};

bool Date::operator > (Date D)
{
    bool ans=false;
    if(y>D.y) ans=true;
    else
    {
        if(y==D.y)
        {
            if(m>D.m) ans=true;
            else
            {
                if(m==D.m)
                {
                    if(d>D.d) ans=true;
                }
            }
        }
    }
    return ans;
}
int Date::operator -(Date D)
{
    int count =0;
    while(d!=D.d || m!=D.m || y!=D.y)
    {
        D.add_day(1);
        count++;
    }
    return count;
}

int Date::MAX_Months[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

Date :: Date (int dd,Month mm,int yy)
{
    if(yy==0) yy=2000;
    if(mm==0) mm=Month(1);
    if(dd==0) dd=1;
    int maxDays;
    switch(mm)
    {
    case feb:
        maxDays=28+leapyear(yy);
        break;
    case april:
    case june:
    case sept:
    case nov:
        maxDays=30;
        break;
    case jan:
    case march:
    case may:
    case july:
    case aug:
    case october:
    case decm:
        maxDays=31;
        break;
    default:
        throw error_date(dd);
        break;
    }
    if(dd>=1 && dd<=maxDays)
    {
        d=dd;
        m=mm;
        y=yy;
    }
    else
        throw error_date(dd);
}

void Date::print_date()
{
    cout<<d<<" "<<m<<" "<<y<<endl;
}
Date& Date::add_day(int n)
{
    int n_maxdays = MAX_Months[m] +(m==2&&leapyear(y)? 1:0);
    int n_year=y;
    int n_month=m;
    int n_days=d+n;
    while(n_days>n_maxdays)
    {
        n_days-=n_maxdays;
        ++n_month;
        if(n_month>12)
        {
            n_month=1;
            ++n_year;
        }
        n_maxdays=MAX_Months[n_month]+(n_month==2&&leapyear(y)? 1:0);
    }
    d=n_days,
    m=Month(n_month),
    y=n_year;
    return *this;
}
bool Date::leapyear(int year)
{
    if(year%4!=0) return false;
    else
    {
        if(year%100!=0) return true;
        else
        {
            if(year%400==0) return true;
            else return false;
        }
    }
}

class book
{
public:
    string book_name;
    string category;
    string author;
    Date return_d;
    bool issued;
    int book_id;
    book();                        //default constructor for book class
    book(string n, string cat, string au,int bkid);
    book(string n, string cat, string au,int bkid,Date iss_d);
    void dispBook(int x)
    {
        switch(x)
        {
        case 1:
            cout<<"\t "<<book_name<<" \t\t\t "<<category<<" \t\t\t "<<author<<" \t\t\t "<<book_id<<" \t\t\t ";
            if(issued) cout<<"NO\n";
            else cout<<"YES\n";
            break;
        case 2:
            if(issued)
            {
                cout<<"\t "<<book_name<<" \t\t\t "<<category<<" \t\t\t "<<author<<" \t\t\t "<<book_id<<" \t\t\t";
                return_d.print_date();
                cout<<endl;
            }
            break;

        case 3:
            if(!issued)
                cout<<"\t "<<book_name<<" \t\t\t "<<category<<" \t\t\t "<<author<<" \t\t\t "<<book_id<<" \n ";
            break;
        }
    }
};
vector<book> bk;
/*********constructor for book class defined outside the class**************/
book::book(string n, string cat, string au,int bkid,Date iss_d)
{
    book_name=n;
    category=cat;
    author=au;
    book_id=bkid;
    return_d=iss_d;
    issued=0;
    bk.push_back(*this);
}
book::book(string n, string cat, string au,int bkid)
{
    book_name=n;
    category=cat;
    author=au;
    book_id=bkid;
    issued=false;
    bk.push_back(*this);
}


//***************************************************//
//           USER CLASS
//**************************************************//
class user
{
public:
    string id;
    string password;
    void login(int x);
    void displayALL();
    void show_Available_Books();

};
void user:: displayALL()
{
    cout<<"\t Book Name \t\t Category \t\t Author \t\t bookId \t\t Available\n";
    for(int i=0; i<bk.size(); i++)
    {
        bk[i].dispBook(1);
    }
}
void user :: show_Available_Books()
{
    cout<<"\t Book Name \t\t Category \t\t Author \t\t bookId\n";
    for(int i=0; i<bk.size(); i++)
    {
        bk[i].dispBook(3);
    }

}

class student:public user
{
    string names;

    int fine;
public:
    vector<book> issuedbooks;
    student(string n,string r,string p);     //constructor for student class
    student() {}                                                      //default constructor
    student(int x);
    void operator=(student s1);
    void show_profile();
    void issue_S();
    void return_S();
    void stumenu();
    friend class librarian;                                              //librarian is friend class of student
};
student *stu1;

class librarian: public user
{
public:
    string name;
    librarian (string un, string ps);                           //constructor for librarian class
    librarian() {}    //default constructor
    librarian(int x);
    void libmenu();
    void create_user();
    void add_newbook();
    void issue_l();
    void return_l();
    void show_issued_books();

};
//******************************************************************************//
//   FUNCTION DEFINITIONS OF STUDENT CLASS
//******************************************************************************//

vector<student> stu;
vector<librarian> lib;
librarian l(1);
/**************show profile of a student*****************/
void student::show_profile()
{
    cout.width(70);
    cout<<"Student Name:    "<<names<<endl;
    cout.width(70);
    cout<<"Roll number:     "<<id<<endl;
    cout.width(70);
    cout<<"Books issued:    "<<issuedbooks.size()<<endl;
    cout.width(30);

    cout<<"\t Book Name \t\t Category \t\t Author \t\t bookId \t\tReturn Date\n";
    for(int i=0; i<issuedbooks.size(); i++)
    {
        issuedbooks[i].dispBook(2);
    }
    cout.width(70);
    cout<<"Fine: "<<fine;

}
/***********to issue a book to the student this function is called**********/
void student::issue_S()
{   
string st,password1;
    int c=0,c2=0;
    cout<<"                         Librarian Login Required    ";
        cout<<"\nEnter the username";
        cin>>st;
        for(int i=0; i<lib.size(); i++)
        {
            if(st==lib[i].id)
            {
                cout<<"\nEnter the password";
                cin>>password1;
                c=1;
                if(lib[i].password==password1)
                {
                    c2=1;
                    lib[i].issue_l();
                }
                else throw "Invalid password";
                break;
            }
        }
        if(c==1&&c2==0)  throw "invalid username";
    }

/***************called when user returns the book******************/
void student::return_S()
{
      string st,password1;
    int c=0,c2=0;
    cout<<"                         Librarian Login Required    ";
        cout<<"\nEnter the username";
        cin>>st;
        for(int i=0; i<lib.size(); i++)
        {
            if(st==lib[i].id)
            {
                cout<<"\nEnter the password";
                cin>>password1;
                c=1;
                if(lib[i].password==password1)
                {
                    c2=1;
                    lib[i].return_l();
                }
                else throw "Invalid password";
                break;
            }
        }
        if(c==1&&c2==0)  throw "invalid username";
    }


/*************function to create librarian or a student*************/
void librarian::create_user()
{
    cout<<"\n Enter L for librarian or S for student";
    char ch;
    cin>>ch;
    switch(ch)
    {
    case 'L':
    {
        librarian new_l(1);
        break;
    }
    case 'S':
    {
        cout<<"1";
        student new_s(1);
        cout<<"2";
        break;
    }
    default :
        libmenu();
        break;
    }
}
/***********a new book will be added to already existing books***********/
void librarian::add_newbook()
{
    string name,cat,au;
    int id,m,d,y;
    cout<<"\nEnter the book name :  ";
    cin.ignore();
    getline(cin,name);
    cout<<"\nEnter category of book :  ";
    cin.ignore();
    getline(cin,cat);
    cout<<"\nEnter author of book :  ";
    cin.ignore();
    getline(cin,au);
    cout<<"\nEnter book id :  ";
    cin>>id;
    /*cout<<"\nEnter issue date(date, month, year) :  ";
            cin>>d>>m>>y;
         Date d1(d,Month(m),y);
         d1.add_day(7);
    */
    book B(name,cat,au,id);
}
/********for returning a book*********/

void librarian::return_l()
{
    int d,m,y;
    int b_s;
    int x=0;
    stu1->show_profile();
    cout<<"\nEnter the book id to be returned";
    cin>>b_s;
    for(int i=0; i<bk.size(); i++)
    {
        if(bk[i].book_id==b_s)
            for(int i=0; i<stu1->issuedbooks.size(); i++)
            {
                bk[i].issued=0;
            }
        if(b_s==stu1->issuedbooks[i].book_id)
        {
            x=1;
            cout<<"\nEnter current date(day, month,year)";
            cin>>d>>m>>y;
            Date dt(d,Month(m),y);
            if(dt>bk[i].return_d)
                stu1->fine+=dt-bk[i].return_d;
            stu1->issuedbooks.erase(stu1->issuedbooks.begin()+i);
            break;
        }
    }
}

/************book is issued by librarian*********/
void librarian::issue_l()
{   if(stu1->issuedbooks.size()==5)
      { cout<<"\n5 books already issued";
        return;}
    string b_s;
    int x=0;
    cout<<"\nEnter the name of book to be issued :  ";
    cin.ignore();
    getline(cin,b_s);
    for(int i=0; i<bk.size(); i++)
    {
        if(b_s==bk[i].book_name && !bk[i].issued)
        {
            x=1;
            int day,year,month;
            bk[i].issued=true;
            (stu1->issuedbooks).push_back(bk[i]);
           cout<<"\nEnter the issue date(day, month and year) :  ";
            cin>>day>>month>>year;
            Date d(day,Month(month),year);
            stu1->issuedbooks[0].return_d = d.add_day(7);
            cout<<"\nBook issued"<<endl;
            stu1->issuedbooks[0].dispBook(2);
            stu1->show_profile();
            return;
        }
    }
    if( x==0)
        cout<<"\nBook not available";
    return;
}

void librarian :: show_issued_books()
{
    cout<<"\t Book Name \t\t Category \t\t Author \t\t bookId \t\tReturn Date\n";
    for(int i=0; i<bk.size(); i++)
    {
        bk[i].dispBook(2);
    }
}

/************overloaded operator = for student class******************/
void student:: operator=(student s1)
{
    for(int i=0; i<s1.issuedbooks.size(); i++)
        issuedbooks.push_back(s1.issuedbooks[i]);
    names=s1.names;
    fine=s1.fine;
}

/************login function for both librarian and student***********/
void user::login(int x)
{
    string st,password1;
    int c=0,c2=0;
    switch(x)
    {
    case 1:
    {
        cout<<"\nEnter the username";
        cin>>st;
        for(int i=0; i<lib.size(); i++)
        {
            if(st==lib[i].id)
            {
                cout<<"\nEnter the password";
                cin>>password1;
                c=1;
                if(lib[i].password==password1)
                {
                    c2=1;
                    lib[i].libmenu();
                }
                else throw "Invalid password";
                break;
            }
        }
        if(c==1&&c2==0)  throw "invalid username";
    }
    case 2:
    {
        cout<<"\nEnter the username";
        cin>>st;
        for(int i=0; i<stu.size(); i++)
        {
            if(st==stu[i].id)
            {
                cout<<"\nEnter the password";
                cin>>password1;
                c=1;
                if(stu[i].password==password1)
                {
                    c2=1;
                    stu1=&stu[i];
                    stu[i].stumenu();
                }
                else throw "Invalid password";
                break;
            }
        }
        if(c==1&&c2==0) throw "invalid username";
    }
    default:
        break;
    }
}
/************constructor for student class defined outside the class*********/
student:: student(string n,string r,string p)
{
    for(int i=0; i<stu.size(); i++)
    {
        if(stu[i].id==r)
        {
            cout<<"roll no already exists";
            return;
        }
    }
    if(p.length()>=8)
        password=p;
    else {cout<<"password too short";return;}
    names=n;
    id=r;
    fine=0;
}
student::student(int x)
{
    string a;
    string p;
    cout<<"\n\t\t\tNEW STUDENT SIGNUP";
    cout<<"\n\n\tEnter the roll number"<<endl;
    try3: cin>>a;
    for(int i=0; i<stu.size(); i++)
    {
        if(a==stu[i].id)
            {
                cout<<"\n\troll no already exists\n\tre-enter roll_no :   ";
                goto try3;
            }
    }
    cout<<"\nEnter the password "<<endl;
    cin>>p;   
        password=p;
    
    cout<<"\nEnter the name "<<endl;
    cin>>names;
    id=a;
    fine=0;
    stu.push_back(*this);
    system("cls");
}
/********constructor for librarian class defined outside the class********/
librarian::librarian (string un, string ps)
{
    if(ps.length()>=8)
    {
        name=un;
        password=ps;
    }
    else
    {
        cout<<"\npassword too short";
        return;
    }
    lib.push_back(*this);
}

librarian::librarian(int x)                                                //constructor 2
{
    string u,p;
    cout<<"\n\t\t\t\tNew Librarian Signup\n";
    cout<<"\n\tEnter the username :  ";
    try1:cin>>u;
    for(int i=0; i<lib.size(); i++)
    {
        if(u==lib[i].id)
        {
            cout<<"\n\tusername already exists\n\tre-enter new username :  ";
            goto try1;
        }
    }
    id=u;
    cout<<"\n\tEnter the password(length>=8) :  ";
    cin>>p;
    
        password=p;
    
    cout<<"\n\tEnter the name :  ";
    cin>>name;
    lib.push_back(*this);
    system("cls");
}

/********menu card for librarian********/
void librarian::libmenu()
{
    cout<<"\n\n"<<setw(90)<<"Librarian Access\n\n";
    cout<<setw(120)<<"****************************************************************************\n\n";
    cout<<"\t\t\t\t\t   1.Display all books \n\t\t\t\t\t   2.Display issued books \n\t\t\t\t\t   3.Display books available \n\t\t\t\t\t   4.Add new book \n\t\t\t\t\t   5.Create new User \n\t\t\t\t\t   6.Logout";
    cout<<"\n\n\t\t\t\t   Enter: ";
    int i;
    cin>>i;
    system("cls");
    switch(i)
    {
    case 1:
    {
        displayALL();
        break;
    }
    case 2:
    {
        show_issued_books();
        break;
    }
    case 3:
    {
        show_Available_Books();
        break;
    }
    case 4:
    {
        add_newbook();
        break;
    }
    case 5:
    {
        try
        {
            create_user();
        }
        catch(const char* s)
        {
            cout<<s<<"\n";
        }
    }
    default:
    {
        break;
    }
    }
    cout<<"Get back to librarian page else exit: Y / N  ";
    char ch;
    cin>>ch;
    system("cls");
    switch(ch)
    {
    case 'Y':
        libmenu();
        break;
    default:
        cover();
        break;
    }

}
/************menu card for student*********/
void student::stumenu()
{
    cout<<"\n\n"<<setw(90)<<"Student Access\n\n";
    cout<<setw(120)<<"****************************************************************************\n\n";
    cout<<"\t\t\t\t\t   1.Display available books \n\t\t\t\t\t   2.Display issued books \n\t\t\t\t\t   3.Display all Books \n\t\t\t\t\t   4.Issue book \n\t\t\t\t\t   5.Return book \n\t\t\t\t\t   6.Exit\n";
    cout<<" \n\t\t\t\t\t  Enter: ";
    int i;
    cin>>i;
    switch(i)
    {
    case 1:
    {
        show_Available_Books();
        break;
    }
    case 2:
    {
        show_profile();
        break;
    }
    case 3:
    {
        displayALL();
        break;
    }
    case 4:
    {
        issue_S();
        break;
    }
    case 5:
    {
        return_S();
        break;
    }
        case 6:
    {
        cover();
        break;
    }

    default:
        break;
    }

    cout<<"Get back to student page else exit: Y / N  ";
    char ch;
    cin>>ch;
    system("cls");
    switch(ch)
    {
    case 'Y':
        stumenu();
        break;
    default:
        cover();
        break;
    }

}
/*********shows main cover*******/
void cover()
{
    cout<<"\n\n"<<setw(95)<<"Welcome to IIT Jodhpur Library\n";
    cout<<setw(120)<<"****************************************************************************\n\n";
    cout<<setw(110)<<"          1. Admin Login \t     2. Student Login \t    3. New user signup\n\n";
    cout<<setw(80)<<"Enter: ";
    int i,j;
    cin>>i;
    system("cls");
    switch(i)
    {
    case 1:
    case 2:
    {
        user A;
        try
        {
            A.login(i);
        }
        catch(const char* s)
        {
            cout<<s<<endl;
            cout<<" ";
        }
        break;
    }
    case 3:
    {
        librarian A;
        cout<<"librarian login required";
        for(j=0; j<3; j++)
        {
            try
            {
                A.login(1);
                break;
            }
            catch(const char* s)
            {
                cout<<s<<endl;
                cout<<"re-enter: ";
            }
        }
        if(j==3)
        {
            cout<<"3 invalid Attempts\n\n";
            system("cls");
            cover();
        }

    }

    }
}
int main()
{
    cover();
    return 0;
}








