using namespace std;


enum Days {TBA, MON, TUE, WED, THU, FRI};
enum amOrPm {AM, PM};

struct Time{
int hour;
char colon;
char minute1;
char minute2;
amOrPm amPm;};

struct Meeting {
Days day1;
Days day2;
Time startTime;
char through;
Time endTime;};

struct Location{
string building;
string room;};

struct CourseName{
string subject;
int level;};

struct Course{
int courseId;
CourseName courseName;
Meeting meeting;
Location location;};

struct cinTime{
char hour1;
char hour2;
char colon;
char minute1;
char minute2;
char spaceCh;
char AmPm;};

void DisplayCourses();
void GetDay (ifstream&, Days&);
void GetAmPm (ifstream&, amOrPm&);
void GetLocation(ifstream&, string&, string&);
void PrintDay(Days);
void PrintDayToFile (Days meetDay, ofstream& ocout);
void PrintAmPm(amOrPm);
void PrintAmPmToFile(amOrPm, ofstream& ocout);
void LookUp(ifstream& icin);
void ReturnCourse(ifstream& icin, int courseID);
void GetDayCin (Days& meetDay);
void AddCourse();
void GetStartTimeCin (ofstream& ocout, string& startTime);
void GetEndTimeCin (ofstream& ocout, string& endTime);
void GetUserOption (ifstream& icin);
void LookUp();
void GetDay(ifstream& icin, Days& meetDay){
    string dayStr;  //variable for day

    icin >> setw(3) >> dayStr;  //get day from input file stream

    switch ((toupper(dayStr.at(0)))) {  //get first letter of input
    case 'M' : meetDay = MON;
                break;

    case 'T' : if ((toupper(dayStr.at(1))) == 'U') meetDay = TUE;
               else if ((toupper(dayStr.at(1))) == 'H')meetDay = THU;
               else meetDay = TBA;
               break;

    case 'W' : meetDay = WED;
                break;

    case 'F' : meetDay = FRI;
                break;
    }
}
void GetDayCin (Days& meetDay){
    string dayStr;  //variable for day

    cin >> setw(3) >> dayStr; //get day from user using first 3 letters
    cin.ignore(100, '\n');  //ignore the rest of the input stream

    switch ((toupper(dayStr.at(0)))) { //determine which day by first letter
    case 'M' : meetDay = MON;
                break;

    case 'T' : if ((toupper(dayStr.at(1))) == 'U') meetDay = TUE;
               else if ((toupper(dayStr.at(1))) == 'H')meetDay = THU;
               else meetDay = TBA;
               break;

    case 'W' : meetDay = WED;
                break;

    case 'F' : meetDay = FRI;
                break;
    }
}
void PrintDay (Days meetDay){

switch (meetDay){   //different cases in which to print day to output device

    case MON:   cout << "MON ";
                break;
    case TUE:   cout << "TUE ";
                break;
    case WED:   cout << "WED ";
                break;
    case THU:   cout << "THU ";
                break;
    case FRI:   cout << "FRI ";
                break;
    case TBA:   cout << "TBA ";
                break;
}
}
void PrintDayToFile (Days meetDay, ofstream& ocout){

switch (meetDay){   //different cases in which to print day to output file

    case MON:   ocout << "MON ";
                break;
    case TUE:   ocout << "TUE ";
                break;
    case WED:   ocout << "WED ";
                break;
    case THU:   ocout << "THU ";
                break;
    case FRI:   ocout << "FRI ";
                break;
    case TBA:   ocout << "TBA";
                break;
}
}

void PrintAmPm (amOrPm meetAmPm){

switch (meetAmPm){  //different cases in which to print day to output device

    case AM:   cout << "AM ";
                break;
    case PM:   cout << "PM ";
                break;
}
}
void PrintAmPmToFile(amOrPm meetAmPm, ofstream& ocout){

switch (meetAmPm){  //different cases in which to print day to output file

    case AM:   ocout << "AM";
                break;
    case PM:   ocout << "PM";
                break;
}
}

void GetAmPm (ifstream& icin, amOrPm& meetAmPm){

    string amPm;    //variable for am/pm

    icin >> setw(2) >> amPm;    //get am/pm from input file

    switch (toupper(amPm.at(0))) { //switch case for the first letter of variable
                                    //different cases in which to store am or pm
    case 'A' : meetAmPm = AM;

    case 'P' : meetAmPm = PM;
    }
}
void GetAmPmCin (amOrPm& meetAmPm){

    string amPm;    //variable to store am or pm

    cin >> setw(2) >> amPm; //get input from user

    switch (toupper(amPm.at(0))) { //determine am or pm by first letter
                                    //different cases in which to store am or pm
    case 'A' : meetAmPm = AM;

    case 'P' : meetAmPm = PM;
    }
}

void GetLocation(ifstream& icin, string& bldg, string& rm){

    string zoom1, zoom2, zoom3, virt1, virt2, virt3;    //variables for input possibilities
    zoom1 = "Zoom";
    zoom2 = "ZOOM";
    zoom3 = "zoom";
    virt1 = "Virtual";
    virt2 = "VIRTUAL";
    virt3 = "virtual";
    icin.ignore(2); //ignore whitespace and comma in input file
    icin >> bldg;   //get building variable from input file
    if (bldg == zoom1)  //case scenarios for if building variable is one of the input possibilities
        rm = " ";
    else if (bldg == zoom2)
        rm = " ";
    else if (bldg == zoom3)
        rm = " ";
    else if (bldg == virt1)
        rm = " ";
    else if (bldg == virt2)
        rm = " ";
    else if (bldg == virt3)
        rm = " ";

}

void DisplayCourses()
{
    ifstream icin;  //declare input stream variable
    icin.open("program2.dat");  //open input file

    Course stuCourse; //declare course information variable
    icin >> setw(5) >> stuCourse.courseId;  //get course ID
    icin.ignore(2); //IGNORE COMMA AND WHITESPACE

    while (icin){ //EOF WHILE LOOP
    icin >> setw(3) >> stuCourse.courseName.subject;    // GET COURSE SUBJECT
    icin >> setw(3) >> stuCourse.courseName.level;  //GET COURSE LEVEL
    icin.ignore(2); //IGNORE COMMA AND WHITESPACE

    GetDay(icin, stuCourse.meeting.day1); //GET DAY
    if (stuCourse.meeting.day1 != TBA){ //IF DAY IS NOT TBA GET REST OF INFO
    GetDay(icin, stuCourse.meeting.day2);   //GET DAY 2

    icin >> stuCourse.meeting.startTime.hour;   //GET START TIME
    icin >> stuCourse.meeting.startTime.colon;
    icin >> stuCourse.meeting.startTime.minute1;
    icin >> stuCourse.meeting.startTime.minute2;

    GetAmPm(icin, stuCourse.meeting.startTime.amPm );   //GET AM OR PM

    icin >> stuCourse.meeting.through; //GET "-" CHARACTER

    icin >> stuCourse.meeting.endTime.hour; //GET END TIME
    icin >> stuCourse.meeting.endTime.colon;
    icin >> stuCourse.meeting.endTime.minute1;
    icin >> stuCourse.meeting.endTime.minute2;

    GetAmPm(icin, stuCourse.meeting.endTime.amPm );}    //GET AM OR PM

    GetLocation(icin, stuCourse.location.building, stuCourse.location.room);    //GET LOCATION

    cout << " Course ID: " << stuCourse.courseId << endl;   //OUTPUT COURSE ID

    cout <<" Course Name: " << stuCourse.courseName.subject << " "  //OUTPUT COURSE SUBJECT
                            << stuCourse.courseName.level << endl;  //OUTPUT COURSE LEVEL

    cout << " Meeting Day & Time: ";
                              PrintDay(stuCourse.meeting.day1); //OUTPUT MEETING DAY
                              if (stuCourse.meeting.day1 != TBA){   //IF NOT TBA OUTPUT OTHER INFO
                              PrintDay(stuCourse.meeting.day2);

                               cout << stuCourse.meeting.startTime.hour //OUTPUT START TIME
                                    << stuCourse.meeting.startTime.colon
                                    << stuCourse.meeting.startTime.minute1
                                    << stuCourse.meeting.startTime.minute2;

                             PrintAmPm(stuCourse.meeting.startTime.amPm);   //OUTPUT AM OR PM

                               cout << stuCourse.meeting.through << " " //OUTPUT END TIME
                                    << stuCourse.meeting.endTime.hour
                                    << stuCourse.meeting.endTime.colon
                                    << stuCourse.meeting.endTime.minute1
                                    << stuCourse.meeting.endTime.minute2;

                             PrintAmPm(stuCourse.meeting.endTime.amPm);}    //OUTPUT AM OR PM

    cout << endl;
    cout << " Location: "           << stuCourse.location.building  //OUTPUT BUILDING
                                    << stuCourse.location.room << endl << endl; //OUTPUT ROOM

                                    icin >> setw(5) >> stuCourse.courseId;  //GET NEXT COURSE ID TO TEST IF EOF
                                    icin.ignore(2);}

icin.close();   //CLOSE INPUT FILE
}

void LookUp(){
int searchID;   //VARIABLE FOR USER SEARCH
int courseID;   //VARIABLE FOR COURSE IDs WITHIN FILE
char addCourse; //HOLDS OPTIONS TO ADD COURSE
ifstream icin;  //DECLARE INPUT STREAM VARIABLE
 icin.open("program2.dat"); //OPEN INPUT FILE

   cout << "Enter a 5 digit Course ID then press ENTER to search: ";    //PROMPT USER FOR COURSE ID THEIR SEARCHING FOR
   cin >> searchID;

           while (!cin){    //INPUT VALIDATION LOOP
            cout << endl << "Invalid Input!" << endl << endl;
            cin.clear();    //CLEAR INPUT STREAM
            cin.ignore(10,'\n');
            cout << "Enter a 5 digit Course ID then press ENTER to search: ";
            cin >> searchID;
           }

    icin >> setw(5) >> courseID;    //TEST IF FIRST COURSE ID MATCHES

    while (icin){   //EOF WHILE LOOP
    if(courseID == searchID)
    {ReturnCourse(icin, courseID);  //RETURN COURSE IF IT MATCHES AND BREAK FROM LOOP
    break;}


    if(courseID != searchID){   //IF COURSE ID DOESNT MATCH,
    icin.ignore(200, '\n');     //IGNORE REST OF LINE UNTIL NEWLINE CHARACTER
    icin >> setw(5) >> courseID;} } // AND GET THE NEXT COURSE ID FROM THE IMPUT STREAM


    if ((!icin)&& (courseID != searchID)) { //IF END OF FILE AND NO MATCH OUTPUT NO MATCH
        cout << endl << "No match found." << endl;
        cout << endl << "Would you like to add Course ID: " << searchID << " ? ( Y / N )" << endl;
        cin >> addCourse;   //PROMPT USER TO ADD COURSE THAT COULD NOT BE FOUND
    addCourse = char(toupper(addCourse));   //MAKE USER ENTRY CAPITALIZED
    if (addCourse = 'Y')    //IF Y, ADD COURSE
        AddCourse();
    if (addCourse = 'N')    // IF N, RETURN TO OPTIONS SCREEN
        GetUserOption (icin);}
    icin.close();   //CLOSE INPUT FILE
    return;

}
void GetUserOption (ifstream& icin){

    char userInput; //store user option
    cout << endl << "Please choose from one of the following options: " << endl;
    cout << "D: Display Courses" << endl;
    cout << "L: Look Up Courses" << endl;
    cout << "A: Add Courses" << endl;
    cout << "Q: Quit" << endl;
    cin >> userInput;

    userInput = toupper(userInput); //make user option capital

    while (userInput != 'Q'){
        if (userInput == 'D')
            DisplayCourses();
        if (userInput == 'L')
            LookUp ();
        if (userInput == 'A')
            AddCourse ();

    cout << "Please choose from one of the following options: " << endl;
    cout << "D: Display Courses" << endl;
    cout << "L: Look Up Courses" << endl;
    cout << "A: Add Courses" << endl;
    cout << "Q: Quit" << endl;
    cin >> userInput;
    userInput = toupper(userInput);}

cout << "Goodbye! Thank you for using the student course program." << endl; //show goodbye message

return;}

void ReturnCourse(ifstream& icin, int courseID){
Course stuCourse;   //declare course variable
    stuCourse.courseId = courseID;  //user entered course ID == course ID
    icin.ignore(2);
    //get info from input file
    icin >> setw(3) >> stuCourse.courseName.subject;
    icin >> setw(3) >> stuCourse.courseName.level;
    icin.ignore(2);

    GetDay(icin, stuCourse.meeting.day1);
    if (stuCourse.meeting.day1 != TBA){
    GetDay(icin, stuCourse.meeting.day2);

    icin >> stuCourse.meeting.startTime.hour;
    icin >> stuCourse.meeting.startTime.colon;
    icin >> stuCourse.meeting.startTime.minute1;
    icin >> stuCourse.meeting.startTime.minute2;

    GetAmPm(icin, stuCourse.meeting.startTime.amPm );

    icin >> stuCourse.meeting.through;

    icin >> stuCourse.meeting.endTime.hour;
    icin >> stuCourse.meeting.endTime.colon;
    icin >> stuCourse.meeting.endTime.minute1;
    icin >> stuCourse.meeting.endTime.minute2;

    GetAmPm(icin, stuCourse.meeting.endTime.amPm );}

    GetLocation(icin, stuCourse.location.building, stuCourse.location.room);
    //output info to output device
    cout << " Course ID: " << stuCourse.courseId << endl;

    cout <<" Course Name: " << stuCourse.courseName.subject << " "
                            << stuCourse.courseName.level << endl;

    cout << " Meeting Day & Time: ";
                              PrintDay(stuCourse.meeting.day1);
                              if (stuCourse.meeting.day1 != TBA){
                              PrintDay(stuCourse.meeting.day2);

                               cout << stuCourse.meeting.startTime.hour
                                    << stuCourse.meeting.startTime.colon
                                    << stuCourse.meeting.startTime.minute1
                                    << stuCourse.meeting.startTime.minute2;

                             PrintAmPm(stuCourse.meeting.startTime.amPm);

                               cout << stuCourse.meeting.through << " "
                                    << stuCourse.meeting.endTime.hour
                                    << stuCourse.meeting.endTime.colon
                                    << stuCourse.meeting.endTime.minute1
                                    << stuCourse.meeting.endTime.minute2;

                             PrintAmPm(stuCourse.meeting.endTime.amPm);}

    cout << endl;
    cout << " Location: "           << stuCourse.location.building
                                    << stuCourse.location.room << endl << endl;

                                    icin >> setw(5) >> stuCourse.courseId;
                                    //icin.ignore(2);

return;}

void GetStartTimeCin (ofstream& ocout, string& startTime){

string TimeStr; //time variable

cout << endl << "At what time does this course start? (Format 'HH:MM AM/PM')" << endl;
getline(cin, TimeStr);  //get time

TimeStr.at(5) = toupper(TimeStr.at(5)); //make am/pm capital
TimeStr.at(6) = toupper(TimeStr.at(6));
startTime = TimeStr;

return;}

void GetEndTimeCin (ofstream& ocout, string& endTime){

string TimeStr; //time variable

cout << endl << "At what time does this course start? (Format 'HH:MMAM/PM' *NO SPACES*)" << endl;
getline(cin, TimeStr);  //get time entry

TimeStr.at(5) = toupper(TimeStr.at(5)); //make am/pm capital
TimeStr.at(6) = toupper(TimeStr.at(6));
endTime = TimeStr;  //store in variable to return to caller

return;}

void AddCourse(){


    ofstream ocout("program2.dat", ios::app); // open file in append mode to add at the end of file

   //DECLARE VARIABLES
    char meetYorN, meetMode;
    string meetDay;
    string startTime;
    string endTime;
    string location;
    Course stuCourse;
//GET INFORMATION ABOUT COURSE
cout << "Please enter the 5 digit Course ID: " << endl;
cin >> setw(5) >> stuCourse.courseId;
cout << "Please enter the 3 letter course subject: " << endl;
cin >> setw(3) >> stuCourse.courseName.subject;
stuCourse.courseName.subject.at(0) = toupper(stuCourse.courseName.subject.at(0));
stuCourse.courseName.subject.at(1) = toupper(stuCourse.courseName.subject.at(1));
stuCourse.courseName.subject.at(2) = toupper(stuCourse.courseName.subject.at(2));
cout << "Please enter the 3 digit course level: " << endl;
cin >> setw(3) >>stuCourse.courseName.level;
cout << "Does this course have scheduled meeting times? " << endl;
cin >> meetYorN;
meetYorN = toupper(meetYorN);
if (meetYorN == 'N'){
        meetDay = "TBA";
        location = "Virtual";
        stuCourse.location.building = "";
        stuCourse.location.room = " ";};
if (meetYorN == 'Y'){
        cout << "What are the scheduled meeting days for this course?" << endl << "Day 1: ";
        GetDayCin (stuCourse.meeting.day1);
        cout << "Day 2: ";
        GetDayCin (stuCourse.meeting.day2);
        GetStartTimeCin(ocout, startTime);
        GetEndTimeCin(ocout, endTime);

        cout << "Enter 'I' if this course meets in-person or 'O' if this course meets online." << endl;
        cin >> meetMode;
        meetMode = toupper(meetMode);
        if (meetMode == 'O'){
            stuCourse.location.building = "Zoom";
            stuCourse.location.room = " ";}
        if (meetMode == 'I'){
        cout << "In what building does this course meet?" << endl;
        cin >> stuCourse.location.building;
        cout << "In what room does this course meet?" << endl;
        cin >> stuCourse.location.room;}
}
    ocout << stuCourse.courseId << ", "
          << stuCourse.courseName.subject << " "
          << stuCourse.courseName.level << ", ";

    if (meetDay == "TBA")
        ocout << meetDay << ", " << location;
    if (meetDay != "TBA"){
        PrintDayToFile(stuCourse.meeting.day1, ocout);
        PrintDayToFile(stuCourse.meeting.day2, ocout);
        ocout << startTime << " - " << endTime << ", ";}
        ocout << stuCourse.location.building << " ";
    if (meetMode == 'I'){
        ocout << stuCourse.location.room;}

ocout.close();  //CLOSE OUTPUT FILE

return;}
