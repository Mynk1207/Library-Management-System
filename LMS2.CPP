#include<stdio.h>
#include<conio.h>
#include<iomanip.h>
#include<string.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>


class book
{
char bno[6];
char bname[50];
char aname[20];
public:

void createbook()
{
cout<<"\n New Book Entry...\n";
cout<<"\n Enter Book Number";
cin>>bno;
cout<<"\n Enter The Book Name";
gets(bname);
cout<<"\n Enter The Author Name";
gets(aname);
cout<<"\n\nBook Created...";
}

void showbook()
{
cout<<"\n Book Number"<<bno;
cout<<"\n Book Nmae :";
puts(bname);
cout<<"\n Book Author :";
puts(aname);
}

void modifybook()
{
cout<<"\n Book Number :"<<bno;
cout<<"\n Modify Book Name";
gets(bname);
cout<<"\n Modify Author Name";
gets(aname);
}
char* retbno()
{
return bno;
}
void report()
{
cout<<bno<<bname<<aname;
}
};

class student
{
char adno[6];
char name[20];
char stbno[6];
int token;
public:

void createstudent()
{
clrscr();
cout<<"\n New Student Entry...\n";
cout<<"\nEnter The Admission Number";
cin>>adno;
cout<<"\nEnter The Student Name";
gets(name);
token = 0;
stbno[0]='\0';
cout<<"\nStudent Record Created...";
}

void showstudent()
{
cout<<"\n Admission Number :"<<adno;
cout<<"\n Student Name :";
puts(name);
cout<<"\n Number OF Book Issued :"<<token;
if(token == 1)
{
cout<<"\n Book Number  :"<<stbno;
}
}
void modifystudent()
{
cout<<"\n Enter Admission Number";
cin>>adno;
cout<<"\n Enter The Student Name";
gets(name);
}
char* retadno()
{
return adno;
}
char* retstbno()
{
return stbno;
}
int rettoken()
{
return token;
}
void addtoken()
{
token=1;
}
void resettoken()
{
token=0;
}
void getstbno(char t[])
{
strcpy(stbno,t);
}
void report()
{
cout<<adno<<name<<token;
}
};

fstream fp , fp1 , fp2;
book bk;
student st;

void writebook()
{
char ch;
fp.open("book.dat",ios::out|ios::app);
do{
    clrscr();
    bk.createbook();
    fp.write((char*)&bk,sizeof(book));
    cout<<"\n\nDo you want to add more record? (y/n)";
    cin>>ch;
}while(ch=='y'|| ch=='Y');
fp.close();
}

void writestudent()
{
char ch;
fp.open("student.dat",ios::out|ios::app);
do{
    clrscr();
    st.createstudent();
    fp.write((char*)&st,sizeof(student));
    cout<<"\n\nDo you want to add more record? (y/n)";
    cin>>ch;
}while(ch=='y'|| ch=='Y');
fp.close();
}

void displayspb(char n[])
{
    cout<<"\nBook Deatails\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char *)&bk,sizeof(book)))
    {
	if(strcmpi(bk.retbno(),n)==0)
	{
	    bk.showbook();
	    flag=1;
	}
    }
    fp.close();
    if(flag==0)
    {
	cout<<"\n\nBook Does Not Exist";
    }
    getch();
}

void displaysps(char n[])
{
    cout<<"\nStudent Deatails\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char *)&st,sizeof(student)))
    {
	if(strcmpi(st.retadno(),n)==0)
	{
	    st.showstudent();
	    flag=1;
	}
    }
    fp.close();
    if(flag==0)
    {
	cout<<"\n\nStudent Does Not Exist";
    }
    getch();
}

void modifybook()
{
    char n[6];
    int found=0;
    clrscr();
    cout<<"\n\nModify Book Record...";
    cout<<"\n\nEnter The Book Number";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
	if(strcmpi(bk.retbno(),n)==0)
	{
	    bk.showbook();
	    cout<<"\nEnter The New Details Of Book";
	    bk.modifybook();
	    int pos = -1*sizeof(bk);
	    fp.seekp(pos,ios::cur);
	    fp.write((char *)&bk,sizeof(book));
	    cout<<"\n\nRecord Updated";
	    found=1;
	}
    }
    fp.close();
    if(found==1)
    {
	cout<<"\n\nRecord Not Found";
    }
    getch();
}

void modifystudent()
{
    char n[6];
    int found=0;
    clrscr();
    cout<<"\n\nModify Student Record...";
    cout<<"\n\nEnter The Admission Number";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
	if(strcmpi(st.retadno(),n)==0)
	{
	    st.showstudent();
	    cout<<"\nEnter The New Details Of Student";
	    st.modifystudent();
	    int pos = -1*sizeof(st);
	    fp.seekp(pos,ios::cur);
	    fp.write((char *)&st,sizeof(student));
	    cout<<"\n\nRecord Updated";
	    found=1;
	}
    }
    fp.close();
    if(found==1)
    {
	cout<<"\n\nRecord Not Found";
    }
    getch();
}

void deletestudent()
{
    char n[6];
    int flag=0;
    clrscr();
    cout<<"\n\n\nDelete Student";
    cout<<"\n\nEnter The Admission Number";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);

    fp2.open("temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
    {
	if(strcmpi(st.retadno(),n)!=0)
	{
	    fp2.write((char*)&st,sizeof(student));
	}
	else
	{
	    flag=1;
	}
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
    if(flag==1)
    {
	cout<<"\n\nRecord Deleted";
    }
    else
    {
	cout<<"\n\nRecord Not Found";
    }

}

void deletebook()
{
    char n[6];
    int flag=0;
    clrscr();
    cout<<"\n\n\nDelete Book";
    cout<<"\n\nEnter The Book Number";
    cin>>n;
    fp.open("book.da  nt",ios::in|ios::out);

    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
	if(strcmpi(bk.retbno(),n)!=0)
	{
	    fp2.write((char*)&bk,sizeof(book));
	}
	else
	{
	    flag=1;
	}
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    if(flag==1)
    {
	cout<<"\n\nRecord Deleted";
    }
    else
    {
	cout<<"\n\nRecord Not Found";
    }

}

void displayalls()
{
    clrscr();
    fp.open("student.dat",ios::in);
    if(!fp)
    {
	cout<<"File Could Not Be Open";
	getch();
	return;
    }
    cout<<"\n\nStudent List";
    cout<<"=========================================================\n";
    cout<<"Admission Number            Name              Book Issued\n";
    cout<<"=========================================================\n";
    while(fp.read((char*)&st,sizeof(student)))
    {
	st.report();
    }
    fp.close();
    getch();
}

void displayallb()
{
    clrscr();
    fp.open("book.dat",ios::in);
    if(!fp)
    {
	cout<<"File Could Not Be Open";
	getch();
	return;
    }
    cout<<"\n\nBook List";
    cout<<"=========================================================\n";
    cout<<"Book Number                Book Name               Author\n";
    cout<<"=========================================================\n";
    while(fp.read((char*)&bk,sizeof(book)))
    {
	bk.report();
    }
    fp.close();
    getch();
}

void bookissue()
{
    char sn[6] , bn[6];
    int found=0, flag=0;
    clrscr();
    cout<<"\n\nBook Issue";
    cout<<"\n\nEnter Admission Number Of Student";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
	if(strcmpi(st.retadno(),sn)==0)
	{
	    found=1;
	    if(st.rettoken()==0)
	    {
		cout<<"\n\nEnter The Book Number";
		cin>>bn;
		while(fp1.read((char*)&bk,sizeof(book)) && flag ==0)
		{
		    if(strcmpi(bk.retbno(),bn)==0)
		    {
			flag=1;
			st.addtoken();
			st.getstbno(bk.retbno());
			int pos = -1*sizeof(st);
			fp.seekg(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\nBook Issued Successfully\n\nPlease NOTE: Write The Book Issue Date In Backside Of Your Bookand Return Book Within 15 Days!!";

		    }
		}
		if(flag==0)
		{
		    cout<<"Book Number Does Not Exist";
		}
	    }
	    else
	    {
	       cout<<"You Have Returned The Last Book";
	    }
	}
    }
    if(found==0)
    {
	cout<<"Student Record Does Not Exist";
    }
    getch();
    fp.close();
    fp1.close();
}

void bookdeposit()
{
    char sn[6] , bn[6];
    int found=0, flag=0,day,fine;
    clrscr();
    cout<<"\n\nBook Deposit";
    cout<<"\n\nEnter Admission Number Of Student";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
	if(strcmpi(st.retadno(),sn)==0)
	{
	    found=1;
	    if(st.rettoken()==1)
	    {
		while(fp1.read((char*)&bk,sizeof(book)) && flag ==0)
		{
		    if(strcmpi(bk.retbno(),st.retstbno())==0)
		    {
			flag=1;
	    bk.showbook();
	    cout<<"\n\nBook Deposited in Number Of Days :";
	    cin>>day;
	    if(day>15)
	    {
		fine=(day-15)*1;
		cout<<"\n\nFine Has To be Deposited Rs:"<<fine;
	    }
			st.resettoken();
			int pos = -1*sizeof(st);
			fp.seekg(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\nBook Deposited Successfully";

		    }
		}
		if(flag==0)
		{
		    cout<<"Book Number Does Not Exist";
		}
	    }
	    else
	    {
	       cout<<"No Book is Issued";
	    }
	}
    }
    if(found==0)
    {
	cout<<"Student Record Does Not Exist";
    }
    getch();
    fp.close();
    fp1.close();
}


void start()
{
clrscr();
gotoxy(35,11);
cout<<"LIBRARY";
gotoxy(33,12);
cout<<"MANAGEMENT";
gotoxy(35,13);
cout<<"SYSTEM";
getch();
}

void admin()
{
clrscr();
int ch2;
cout<<"\n\n\n ADMINISTRATOR MENU";
cout<<"\n\n 1.Create Student Record";
cout<<"\n\n 2.Display All Student Record";
cout<<"\n\n 3.Display Specific Student Record";
printf("\n\n 4.Modify Student Record");
printf("\n\n 5.Delete Student Record");
printf("\n\n 6.Create Book");
printf("\n\n 7.Display All Books");
printf("\n\n 8.Display Specific Book");
printf("\n\n 9.Modify Book Record");
printf("\n\n 10.Back To Main Menu");
printf("\n\n Please Enter Your Choice(1-11)");
cin>>ch2;
switch(ch2)
{
case 1:
writestudent();
break;
case 2:
char num[6];
clrscr();
cout<<"\n\n Please Enter The Admission Number";
cin>>num;
displaysps(num);
break;
case 3:
modifystudent();
break;
case 4:
deletestudent();
break;
case 5:
writebook();
break;
case 6:
displayallb();
 break;
case 7:
clrscr();
cout<<"\n\n Please Enter The Book Number";
cin>>num;
displayspb(num);
break;
case 8:
modifybook();
break;
case 9:
deletebook();
break;
case 10:
return;
default:
cout<<"Invalid Choice";
}
admin();
}
void main()
{
char ch;
start();
do
{
clrscr();
printf("\n\n MAIN MENU");
printf("\n\n 1.BOOK ISSUE");
printf("\n\n 2.BOOK DEPOSIT");
printf("\n\n 3.ADMINISTRATOR MENU");
printf("\n\n 4.EXIT");
printf("\n\nPlease select your option(1-4)");
ch= getche();
switch(ch)
{
case '1' :
bookissue();
break;
case '2' :
bookdeposit();
break;
case '3' :
admin();
break;
case '4' :
exit(0);
break;
default :
printf("Invalid Choice");
}
}while(ch!=4);
}