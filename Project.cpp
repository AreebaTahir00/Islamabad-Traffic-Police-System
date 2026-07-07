#include<iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<conio.h>
#include<string>
// ANSI escape codes for text colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// ANSI escape codes for background colors
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

using namespace std;

class setup
{
 public:
        setup()
        {
            cout<<"\n\n\n\n\n\n\n\t\t\t\t Loading........";
            cout<<"\n\t\t\t\t Please Wait!:)\n\n";
            char a=177,b=219;
            cout<<"\t\t\t\t"; 
            cout<<MAGENTA;
            for(int i=0;i<=22;i++)
            {
                cout<<a;
            }
            cout<<"\r";
            cout<<"\t\t\t\t";
            for(int i=0;i<=22;i++)
            {
                cout<<b;
                for(int j=1;j<1e7;j++);
            }
            
            system("CLS");
            welcome();
        }
        void welcome()
        {
           cout<<"_______________________________________________________________________________________________\n";
           cout<<"\t\t  .##...##..######..##.......####....####...##......##...#######.. "<<endl;
 	       cout<<"\t\t  .##...##..##......##......##..    ##..##..##.#..#.##...##....... "<<endl;
 	       cout<<"\t\t  .##.#.##..####....##......##......##..##..##..##..##...#######.. "<<endl;
 	       cout<<"\t\t  .#######..##......##......##......##..##..##......##...##....... "<<endl;
 	       cout<<"\t\t  ..##.##...######..######...####....####...##......##...#######.. "<<endl;
           cout<<"\n______________________________________________________________________________________________";
           cout<<"\n \t\t\t ";
           cout<<RESET;
           cout<<"ISLAMABAD TRAFFIC POLICE SCHEDULING SYSTEM";
           for (int j=0;j<=1e9;j++);
           system("CLS");
        }
        
};

struct Policeman
{
   string name;
   string ID;
   int dutydays;
   string dutystarttime;
   string dutyendtime;
};

bool isDuplicateID(const string& newID) //Checking of duplicate ID.
{
    ifstream file("Scheduling_system.txt");
    if (!file.is_open())
    {
        cout << "Error opening file!\n";
        return false; // Assuming no duplicate if file cannot be opened
    }

    string line;
    while (getline(file, line))
    {
        size_t pos = line.find(":");
        if (pos != string::npos)
        {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);

            if ((key == "ID") && (value == newID))
            {
                file.close();
                return true; // Duplicate ID found
            }
        }
    }

    file.close();
    return false; // No duplicate ID found
}

void addScheduleToFile(const Policeman& data) //Add schedule to file
{
    if (isDuplicateID(data.ID))
    {
        cout << "Error: Duplicate ID found. Please use a different ID.\n";
        return;
    }

   ofstream file("Scheduling_system.txt", ios::app);
   if (!file.is_open())
   {
    cout << "Error opening file!\n";
    return ;
   }
    file << "ID:" << data.ID << endl << "Name:" << data.name << endl << "Duty Days:" << data.dutydays << endl
         << "Duty Start Time:" << data.dutystarttime << endl << "Duty end time:" << data.dutyendtime << endl;
    file << "_________________________________________________________________________________________________\n";
    cout<<endl;
    cout<<"Schedule added successfully.\n";
   file.close();
}

void displayAllSchedules() //Display schedule from file.
{
    ifstream file("Scheduling_system.txt");
    if (!file.is_open())
    {
    cout << "Error opening file!\n";
    return ;
    }
    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }
    file.close();
}

void check() //Checking who check the schedule. 
{
    ifstream file("Check.txt");
    if (!file.is_open())
    {
    cout << "Error opening file!\n";
    return ;
    }
    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }
    file.close();

}

void searchSchedule(const string &searchName) //Search for a specific data of a Traffic Policeman through ID.
{
    ifstream file("Scheduling_system.txt");
    if (!file.is_open())
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    Policeman schedule;
    bool found = false;

    while (getline(file, line))
    {
        size_t pos = line.find(":");
        if (pos != string::npos)
        {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);

            if ((key == "ID") && (value == searchName))
            {
                found = true;
               
                cout << key << ": " << value << endl;

                while (getline(file, line))
                {
                    if (line.find("_") != string::npos) // Check for the separator line
                        break;

                    pos = line.find(":");
                    if (pos != string::npos)
                    {
                        key = line.substr(0, pos);
                        value = line.substr(pos + 1);

                        // Display details
                        cout << key << ": " << value << endl;

                        if (key == "ID")
                            schedule.ID = value;
                        else if (key == "Name")
                            schedule.name = value;
                        else if (key == "Duty Days")
                            schedule.dutydays = stoi(value);
                        else if (key == "Duty Start Time")
                            schedule.dutystarttime = value;
                        else if (key == "Duty end time")
                            schedule.dutyendtime = value;
                    }
                }

                break;
            }
        }
    }

    file.close();
    if (!found)
    {
        cout << "No schedule found for the given ID: " << searchName << endl;
    }
}


void deleteSchedule(const string &idToDelete) //Delete data of a specific Traffic Policeman through ID.
{
    ifstream inFile("Scheduling_system.txt");
    if (!inFile.is_open())
    {
        cout << "Error opening file!\n";
        return;
    }
    ofstream outFile("system.txt", ios::out);
    if (!outFile.is_open())
    {
        cout << "Error opening file!\n";
        inFile.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line))
    {
        istringstream iss(line);
        string id;
        if (getline(iss, id, ':') && id == "ID")
        {
            getline(iss, id);
            if (id == idToDelete)
            {
                for (int i = 0; i < 4; ++i)
                {
                    getline(inFile, line);
                }
                found = true;
            }
            else
            {
                // Write the line to the new file
                outFile << line << endl;
            }
        }
        else
        {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (!found)
    {
        cout << "No schedule found for the given ID: " << idToDelete << endl;
    }
    else
    {
        cout << "Schedule deleted successfully." << endl;
    }

    // Replace the original file with the modified file
    remove("Scheduling_system.txt");
    rename("system.txt", "Scheduling_system.txt");
}


int main()
{
    int choice;
    setup stp;
    int name1;
    cout<<"\n\n\n\n";
    cout<<MAGENTA;
    cout<<"\n\t\t\t===========================\n";
    cout<<"\n\t\t\t         CHOOSE          \n";       //Choose who are you? Means you are owner or employee/outsider.
	cout<<"\n\t\t\t===========================\n\n";
    cout<<RED;
    cout<<"\t\t\t 1) "<<RESET<<"---> Administator.\n"<<RED;
    cout<<"\t\t\t 2) "<<RESET<<"---> Employe/Outsider.\n\n";
    cout<<"\t\t\t Choose one: ";
    cout<<RED;
    cin>>name1;
    system("CLS");
    if(name1== 1)  //If the user choose option 1),then the rest of the program is executed.
    {
        string name2,name3;
        string c="CTRLG";
        string a="Areeba Tahir";
        string b="Malyika Riasat";
        cout<<RESET;
        cout<<"Enter your name:";
        cout<<RED;
        cin.ignore();
        getline(cin,name2);
        cout<<RESET;
        cout<<"Enter the password: ";
        cout<<RED;
        getline(cin,name3);
        system("CLS");

        if(((name2==a) || (name2==b)) && (name3==c))  //Checks the Administator Name and Password.If correct,the rest of 
        {                                             //the program is executed.
        do
        {
        cout<<MAGENTA;
        cout<<"\n\t\t\t===========================\n";
        cout<<"\n\t\t\t        HOME PAGE          \n";   //Choose options.
	    cout<<"\n\t\t\t===========================\n";
        cout<<RESET;
        cout<<"\n__________________________________________________________________________________\n";
       cout<<" 1: Want to store data of Traffic POLICE.\n";
       cout<<" 2: Want to show the schedule of a Traffic Policeman.\n";
       cout<<" 3: Want to search a specific Traffic Policeman.\n";
       cout<<" 4: Want to delete the data of a specific Traffic Policeman.\n";
       cout<<" 5: About.\n";
       cout<<" 6: Check who see this.\n";
       cout<<" 7: Exit.";
       cout<<"\n__________________________________________________________________________________\n\n";
       cout<<" Now,\n";
       cout<<"Enter your choice:";
       cout<<RED;
       cin>>choice;
       system("CLS");

       switch(choice)
       {
        case 1:
        {
            Policeman Schedule;
            cout<<MAGENTA;
            cout<<"\n\t\t\t==========================="<<endl;
	        cout<<"\n\t\t\t        ENTER DATA           "<<endl;   //Enter data of Traffic Policeman.
	        cout<<"\n\t\t\t==========================="<<endl;
            cout<<RESET;
            cout<<"__________________________________________________________________________________\n";
            cout<<"Enter ID: ";
            cin.ignore();
            getline(cin,Schedule.ID);
            cout<<"Enter Name of a Traffic Policeman: ";
            getline(cin,Schedule.name);
            cout<<"Enter his/her duty days: ";
            cin>>Schedule.dutydays;
            cout<<"Enter his/her duty start time: ";
            cin.ignore();
            getline(cin,Schedule.dutystarttime);
            cout<<"Enter his/her duty end time: ";
            getline(cin,Schedule.dutyendtime);
            cout<<"\n__________________________________________________________________________________\n\n";
            addScheduleToFile(Schedule);
            
            system("pause");
            system("CLS");
            break;
        }
        case 2:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t          DISPLAY          "<<endl; //Display the whole data which is stored in file.
	       cout<<"\n\t\t\t==========================="<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
    
           displayAllSchedules();
           system("pause");
           system("CLS");
           break;
        }
        case 3:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t           SEARCH           "<<endl;  //Search the data of a Specific Traffic policeman.
	       cout<<"\n\t\t\t==========================="<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
           string searchName;
           cout<<"Enter the ID to search data: ";
           cin.ignore();
           getline(cin,searchName);
           cout<<"\nSearch Result.\n";
           cout<<"__________________________________________________________________________________\n";
           
           searchSchedule(searchName);
           string Enter;
           cout<<"\n---> Press 'ENTER Key' to next:";
           getline(cin,Enter);
           system("CLS");
           break;
        }
        case 4:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t           DELETE          "<<endl;  //Delete Data of a specific Traffic policeman.
	       cout<<"\n\t\t\t==========================="<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
           string idToDelete;
           cout<<"Enter the ID to delete data: ";
           cin.ignore();
           getline(cin,idToDelete);

           deleteSchedule(idToDelete);
           string Enter;
           cout<<"\n---> Press 'ENTER Key' to next:";
           getline(cin,Enter);
           system("CLS");
           break;
        }
        case 5:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t           ABOUT          "<<endl;   //Showing why we need to built this program.
	       cout<<"\n\t\t\t==========================="<<endl;
	       cout<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
           
           cout<<"This is a scheduling system for Islamabad Traffic Police. It tells you the duty time table\n\n" 
           <<" of Islamabad Traffic Policeman. This program automates the scheduling process, eliminating the\n\n"
           <<" need for manual record-keeping and reducing the likelihood of errors. You can enter, display,\n\n"
           <<" search, delete data of a specific Traffic Policeman.You can also check who see the stored time table.\n\n"
           <<" It provide an organized and automated solution for managing the schedules of traffic police officers.\n\n"
           <<" It aligns with the principles of effective data management.\n\n\n";
           
           cout<<"\t\t\t*********** CREATED BY *************** \n";   // Names of the Creators.
	       cout<<CYAN;
	       cout<<"\n\t\t\t\t |   Areeba Tahir    |"<<endl ;                          
           cout<<"\n\t\t\t\t |  Malyika Riasat   |"<<endl; 
           cout<<RESET;
	       cout<<"\n__________________________________________________________________________________\n";     

           system("pause");
           system("CLS");
           break;
        }
        case 6:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t           CHECKING         "<<endl;  //Check who this timetable of a Traffic Policeman.
	       cout<<"\n\t\t\t==========================="<<endl;
	       cout<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
           cout<<"Data in check file is:\n";
           check();
           cout<<endl;
           cout<<"__________________________________________________________________________________\n";
           system("pause");
           system("CLS");
           cout<<RESET;
           break;
        }
        case 7:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t           EXIT            "<<endl;  //Exit of Program.
	       cout<<"\n\t\t\t==========================="<<endl;
	       cout<<endl;
           cout<<"__________________________________________________________________________________\n";
           cout<<RESET;
           cout<<"Exiting the Program.\n";
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t       THANK YOU           "<<endl;  //Displaying Thank You.
	       cout<<"\n\t\t\t==========================="<<endl;
           cout<<RESET;
           break;
        }
        default:
          cout<<RED;
          cout<<"\nInvalid choice! Please try again.\n\n";    //Showing error,if Administator opt wrong choice.
       }
      }
       while (choice != 7);
      }
    else   // If the Name or Password of Administator is wrong, It will show an error.
        {
            cout<<"\n\n\n";
            cout<<RED;
            cout<<" \t\t\tYou are not Administator.";
            cout<<RESET;
        }
    }
    else if(name1==2) //Checks You are Employee or Outsider.
    {  
        cout<<RESET;
        string naam;
        cout<<"Enter your name: ";   //Name of Employee or Outsider.
        cout<<RED;
        cin.ignore();
        getline(cin,naam);
        ofstream ofile("Check.txt", ios::app);  //Store the name of the Employee or Outsider.
        if (!ofile.is_open())
        {
          cout<<RED; 
          cout << "Error opening file!\n";
          cout<<RESET;
          return 0;
        }
        ofile<<naam<<endl;
        ofile.close();

        system("pause");
        system("CLS");
        do
        {
        cout<<MAGENTA;
        cout<<"\n\t\t\t===========================\n";  
        cout<<"\n\t\t\t        HOME PAGE          \n";    //Home Page for Employee or Outsider.
	    cout<<"\n\t\t\t===========================\n";
        cout<<RESET;
        cout<<"\n__________________________________________________________________________________\n";
       cout<<" 2: Want to show the schedule of a Traffic Policeman.\n";
       cout<<" 3: Want to search a specific Traffic Policeman.\n";
       cout<<" 6: Exit.";
       cout<<"\n__________________________________________________________________________________\n\n";
       cout<<" Now,\n";
       cout<<"Enter your choice:";
       cout<<RED;
       cin>>choice;
       system("CLS");
       
       switch(choice)
       {
        case 2:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t          DISPLAY          "<<endl;  //Display data 
	       cout<<"\n\t\t\t==========================="<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
    
           displayAllSchedules();
           system("pause");
           system("CLS");
           break;
        }
        case 3:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t           SEARCH           "<<endl;   //Search data of a specific Traffic Policeman.
	       cout<<"\n\t\t\t==========================="<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
           string searchName;
           cout<<"Enter the ID to search data: ";
           cin.ignore();
           cout<<RED;
           getline(cin,searchName);
           cout<<RESET;
           cout<<"\nSearch Result.\n";
           cout<<"__________________________________________________________________________________\n";
           
           searchSchedule(searchName);
           string Enter;
           cout<<"\n---> Press 'ENTER Key' to next:";
           getline(cin,Enter);
           system("CLS");
           break;
        }
        case 6:
        {
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl;
	       cout<<"\n\t\t\t           EXIT            "<<endl;  //Exit the program
	       cout<<"\n\t\t\t==========================="<<endl;
	       cout<<endl;
           cout<<RESET;
           cout<<"__________________________________________________________________________________\n";
           cout<<"Exiting the Program.\n";
           cout<<MAGENTA;
           cout<<"\n\t\t\t==========================="<<endl; 
	       cout<<"\n\t\t\t       THANK YOU           "<<endl;  //Showing the Thank you.
	       cout<<"\n\t\t\t==========================="<<endl;
           cout<<RESET;
           break;
        }
        default:
        {
          cout<<RED; 
          cout<<"Invalid choice! Please try again.";  //Error showing You choose wrong option.
          cout<<RESET;
        }
       }
       }
       while(choice !=6);
       
    }
    else
    {
        cout<<RED;
        cout<<"Invalid choice! Try again.";  //This error shows that you are not an Administator and employee/outsider.
        cout<<RESET;
    }

     return 0;
}