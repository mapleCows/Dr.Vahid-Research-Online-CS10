#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int NumberOfChats(string filename);									//Total number of chats in session
int NumberOfStudentsWhoTalked(string filename);						//Total number of distinct studnets who talked
bool IsStringUnique(vector<string> v, string s);					//Checks vector if string s is stored
string GetStudentNameFromChatLine(string chatLine);					//helper function to return studnet name from chatline
vector<int>NumberOfChatsInEachMinute(string filename);				//Stores number of chats of each minute in corresponding vector index
void AddOnlyIfUniqueString(vector<string>& v, string s);			//Adds string if not stored in vector 
string TimeChatWasPosted(string chatLine);							//returns the time a chat was posted
int MinuteChatWasPosted(string chatLine);							//returns the minute a chat was posted


int main() 
{

	int numOfTotalChats = 0;
	int numOfStudentsWhoTalked = 0;
	vector<int> numOfChatsPerMinute;
	
	numOfTotalChats = NumberOfChats("meeting_saved_chat.txt");
	cout << "The total chats for this session is: " << numOfTotalChats << endl;		//output of total messsages in file

	numOfStudentsWhoTalked = NumberOfStudentsWhoTalked("meeting_saved_chat.txt");
	cout << "The total number of students who talked is: " << numOfStudentsWhoTalked << endl;
	
	numOfChatsPerMinute = NumberOfChatsInEachMinute("meeting_saved_chat.txt");
	for (int i = 0; i < numOfChatsPerMinute.size(); ++i) {
		cout << "Number of chats in minute " << i << " :" << numOfChatsPerMinute.at(i) << endl;
	}


	return 0;
}



int NumberOfChats(string filename) 
{
	int numOfChats = 0;
	string chatLine;
	ifstream chatLog(filename.c_str());


	if (chatLog.fail()) {
		cout << "failed to open file\n";						//checking if file was opened correctly
		return -1;
	}

	if (chatLog.is_open()) {							        //if opened then do get line until end of
		while (getline(chatLog, chatLine)) {					//file and increment counter each time
			++numOfChats;
		}
	}

	return (numOfChats);
}

int NumberOfStudentsWhoTalked(string filename) 
{

	string chatLine;
	string studentName;
	vector<string> students;
	ifstream chatLog(filename.c_str());

	if (chatLog.fail()) {								//checking if file was opened correctly
		cout << "failed to open file\n";
		return -1;
	}

	if (chatLog.is_open()) {
		while (getline(chatLog, chatLine)) {
			studentName = GetStudentNameFromChatLine(chatLine);		//helper function call to grab username from chat line	
			AddOnlyIfUniqueString(students, studentName);
		}

	}

	return students.size();
}

bool IsStringUnique(vector<string> v, string s)				//check if string is held in vector or not
{
	for (int i = 0; i < v.size(); ++i) {

		if (v.at(i) == s) {
			return true;
		}
	
	}

	return false;
}

string GetStudentNameFromChatLine(string chatLine)			//Grab student name from chat line
{														
	string studentName;
	int indexOfLastLetterOfName = 0;

	indexOfLastLetterOfName = chatLine.find(":", 14) - 1;
	studentName.append(chatLine, 14, indexOfLastLetterOfName - 14);

	return(studentName);
}

vector<int> NumberOfChatsInEachMinute(string filename) 
{
	int currentMinute = 0;
	vector<int> numOfChatsInMinute(100);
	string chatLine;
	ifstream chatLog(filename.c_str());
	unsigned int i = 0;

	if (chatLog.fail()) {													//checking if file was opened correctly
		cout << "failed to open file\n";
	}

	if (chatLog.is_open()) {
		getline(chatLog, chatLine);
		currentMinute = MinuteChatWasPosted(chatLine);						//Getting first minute and incrementing zeroth minute
		++numOfChatsInMinute.at(i);						

		while (getline(chatLog, chatLine)) {
			
			if (currentMinute == MinuteChatWasPosted(chatLine)) {			//checking current minute with new minute and incrementing accordingly
				++numOfChatsInMinute.at(i);
			}
			else {
				currentMinute = MinuteChatWasPosted(chatLine);
				++i;
				++numOfChatsInMinute.at(i);
			}
		
		}

	}

	return numOfChatsInMinute;
}

void AddOnlyIfUniqueString(vector<string> & v, string s)			//Add string to vector if string is not held in vector
{
	if (v.size() == 0) {											//To always pushback first talking user
		v.push_back(s);
	}

	if (!IsStringUnique(v, s)) {									//Using helper function to see if user has talked before
		v.push_back(s);												//pushing name into vector of students who have talk
	}

}

string TimeChatWasPosted(string chatLine)				//returns string time stamp of chat line
{
	string time;

	time.append(chatLine, 0, 8);

	return time;
}

int MinuteChatWasPosted(string chatLine)				//returns int minute chat was posted
{	
	string minute;

	minute.append(chatLine, 4, 1);
	
	return stoi(minute);

}























