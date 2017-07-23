#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nEnter The book no. ";
		cin.ignore();
		cin.getline(bno,6);
		cout<<"\n\nEnter The Name of The Book: ";
		cin.getline(bname,50);
		cout<<"\n\nEnter The Author's Name: ";
		cin.getline(aname,20);
		cout<<"\n\n\nBook Created..";
	}

	void show_book()
	{
		cout<<"\nBook no. "<<bno;
		cout<<"\nBook Name: "<<bname;
		cout<<"\nAuthor Name: "<<aname;
	}

	void modify_book()
	{
		cout<<"\nBook no. "<<bno;
		cout<<"\nModify Book Name: ";
		cin.ignore();
		cin.getline(bname,50);
		cout<<"\nModify Author's Name of Book: ";
		cin.getline(aname,20);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{
        cout<<bno<<" "<<bname<<" "<<aname<<" "<<endl;
    }


};         //class ends here

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void create_student()
	{
		system("clear");
	 	cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter The admission no. ";
		cin.ignore();
		cin.getline(admno,6);
		cout<<"\n\nEnter The Name of The Student: ";
		cin.getline(name,20);
		token=0;
		stbno[0]='/0';
		cout<<"\n\nStudent Record Created..";
	}

	void show_student()
	{
		cout<<"\nAdmission no. "<<admno;
		cout<<"\nStudent Name: ";
		cout<<name;
		cout<<"\nNo of Book issued: "<<token;
		if(token==1)
			cout<<"\nBook No: "<<stbno;
	}

	void modify_student()
	{
		cout<<"\nAdmission no. "<<admno;
		cout<<"\nModify Student Name: ";
		cin.ignore();
		cin.getline(name,20);
	}

	char* retadmno()
	{
		return admno;
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
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);

	}

	void report()
	{
	cout<<"\t"<<admno<<" "<<name<<" "<<token<<" "<<endl;}
};         //class ends here

//*****************************************************
//  Global declaration for stream object, object.

fstream fp,fp1;
book bk;
student st;

//*********************************
//  Functions to write to file.

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		system("clear");
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

//***************************************************
//  Function to read specific record from file.

void display_spb(char n[])
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcasecmp(bk.retbno(),n)==0)
		{
			bk.show_book();
		 	flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}

void display_sps(char n[])
{
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcasecmp(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
    		cout<<"\n\nStudent does not exist";
 	getch();
}

//*********************************************
//  Function to modify records from file.

void modify_book()
{
	char n[6];
	int found=0;
	system("clear");
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book: ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcasecmp(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\nEnter The New Details of book: "<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
		    	fp.seekp(pos,ios::cur);
		    	fp.write((char*)&bk,sizeof(book));
		    	cout<<"\n\n\t Record Updated";
		    	found=1;
		}
	}

    	fp.close();
    	if(found==0)
    		cout<<"\n\n Record Not Found ";
    	getch();
}

void modify_student()
{
	char n[6];
	int found=0;
	system("clear");
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student: ";
	cin.ignore();
	cin.getline(n,6);
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcasecmp(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\nEnter The New Details of student: "<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//**********************************************
//  Functions to delete records from file.

void delete_student()
{
	char n[6];
	int flag=0;
	system("clear");
    	cout<<"\n\n\n\tDELETE STUDENT...";
    	cout<<"\n\nEnter The admission no. of the Student You Want To Delete: ";
    	cin.ignore();
    	cin.getline(n,6);
    	fp.open("student.dat",ios::in|ios::out);
    	fstream fp2;
    	fp2.open("Temp.dat",ios::out);
    	fp.seekg(0,ios::beg);
    	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcasecmp(st.retadmno(),n)!=0)
	     		fp2.write((char*)&st,sizeof(student));
		else
	   		flag=1;
	}

	fp2.close();
    	fp.close();
    	remove("student.dat");
    	rename("Temp.dat","student.dat");
    	if(flag==1)
     		cout<<"\n\n\tRecord Deleted ..";
    	else
     		cout<<"\n\nRecord not found";
    	getch();
}

void delete_book()
{
	char n[6];
	system("clear");
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete: ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcasecmp(bk.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}

	fp2.close();
    	fp.close();
    	remove("book.dat");
    	rename("Temp.dat","book.dat");
    	cout<<"\n\n\tRecord Deleted ..";
    	getch();
}

//****************************************
//Display all students list function.

void display_alls()
{
	system("clear");
     	fp.open("student.dat",ios::in);
     	if(!fp)
     	{
       		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
       		return;
     	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"==================================================================\n";
	cout<<"\tAdmission No. "<<"Name "<<"Book Issued \n";
	cout<<"==================================================================\n";

	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}

	fp.close();
	cin.ignore();
	cin.get();
}

//***********************************
// Display books list function.

void display_allb()
{
	system("clear");
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
       		return;
     	}

	cout<<"\n\n\t\tBook LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"Book Number "<<"Book Name "<<"Author \n";
	cout<<"=========================================================================\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
     	fp.close();
     	cin.ignore();
        cin.get();
}

//************************
//  Issue book funtion.

void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	system("clear");
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's admission no. ";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
    	fp1.open("book.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(student)) && found==0)
       	{
		if(strcasecmp(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
		      		cout<<"\n\n\tEnter the book no. ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
			   		if(strcasecmp(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
       						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date";
						cout<<"\n\n\t in backside of book and submit within 15 days fine Rs. 1 for each day";
						cout<<"\n\n\t after 15 days period";
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book no. "<<bn<<" does not exist";
			}
	    		else
		  		cout<<"You have not returned the last book";

		}
	}
      	if(found==0)
		cout<<"Student record not exist...";
	getch();
  	fp.close();
  	fp1.close();
}

//**************************
// Deposit book function.

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    system("clear");
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student admission no. ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcasecmp(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcasecmp(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				cout<<"\n\nBook deposited in no. of days ";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine has to deposited Rs. "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Book no "<<bn<<" does not exist";
		      }
		 else
			cout<<"No book is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"Student record not exist...";
	getch();
    fp.close();
    fp1.close();
}

//************************
//  Administrator Menu.

void admin_menu()
{
    int ch2 = 0;
    while(ch2 != 11)
    {
        system("clear");
        cout<<"\n\n\n\tADMINISTRATOR MENU";
        cout<<"\n\n\t1.CREATE STUDENT RECORD";
        cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
        cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
        cout<<"\n\n\t4.MODIFY STUDENT RECORD";
        cout<<"\n\n\t5.DELETE STUDENT RECORD";
        cout<<"\n\n\t6.CREATE BOOK ";
        cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
        cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
        cout<<"\n\n\t9.MODIFY BOOK ";
        cout<<"\n\n\t10.DELETE BOOK ";
        cout<<"\n\n\t11.BACK TO MAIN MENU";
        cout<<"\n\n\tPlease Enter Your Choice (1-11) ";

        do{
            cin >> ch2;
            if(cin.fail())     //An  error will occur if alphabetic characters are input.
            {
                cin.clear();
                cin.ignore();
            }
        }while(ch2 < 0 || ch2 > 11);

        switch(ch2)
        {
            case 1: system("clear");
                write_student();
                break;
            case 2:
                display_alls();
                break;
            case 3:
                char num[6];
                system("clear");
                cout<<"\n\n\tPlease Enter The Admission No. ";
                cin.ignore();
                cin.getline(num,6);
                display_sps(num);
                break;
            case 4:
                modify_student();
                break;
            case 5:
                delete_student();
                break;
            case 6:
                system("clear");
                write_book();
                break;
            case 7: display_allb();
                break;
            case 8: {
                char num[6];
                system("clear");
                cout<<"\n\n\tPlease Enter The book No. ";
                cin.ignore();
                cin.getline(num,6);
                display_spb(num);
                break;
            }
            case 9:
                modify_book();
                break;
            case 10:
                delete_book();
                break;
            case 11:
                return;
            default:
                cout<<"\nInternal error!";
        }
    }
}

int main()
{
	char ch;
	do
	{
		system("clear");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
	  	cout<<"\n\n\t03. ADMINISTRATOR MENU";
	  	cout<<"\n\n\t04. EXIT";
	  	cout<<"\n\n\tPlease Select Your Option (1-4) ";
	  	cin>>ch;
	  	switch(ch)
	  	{
			case '1':system("clear");
				 book_issue();
			   	 break;
		  	case '2':book_deposit();
			    	 break;
		  	case '3':admin_menu();
				 break;
		  	case '4':exit(0);
		  	default :cout<<"\a";
		}
    }while(ch!='4');
    return(0);
}
