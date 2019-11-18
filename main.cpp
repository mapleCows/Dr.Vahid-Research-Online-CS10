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
string TimeChatWasPosted(string chatLine);								//returns the time a chat was posted
int MinuteChatWasPosted(string chatLine);							//returns the minute a chat was posted



int main() {

	int numOfTotalChats = 0;
	int numOfStudentsWhoTalked = 0;

	numOfTotalChats = NumberOfChats("meeting_saved_chat.txt");
	cout << "The total chats for this session is: " << numOfTotalChats << endl;		//output of total messsages in file

	numOfStudentsWhoTalked = NumberOfStudentsWhoTalked("meeting_saved_chat.txt");
	cout << "The total number of students who talked is: " << numOfStudentsWhoTalked << endl;

	string chat = "15:34:19	 From BrianTaylor : why’s it so quiet?";
	TimeChatWasPosted(chat);

	return 0;
}



int NumberOfChats(string filename) {
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

int NumberOfStudentsWhoTalked(string filename) {

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

bool IsStringUnique(vector<string> v, string s) {				//helper function that searches a  vector of students who have talked
																			//and returns true if student has talked
	for (int i = 0; i < v.size(); ++i) {

		if (v.at(i) == s) {
			return true;
		}

	}

	return false;
}


string GetStudentNameFromChatLine(string chatLine) {					//helper function to grab student name from chat line
	string studentName;
	int indexOfLastLetterOfName = 0;

	indexOfLastLetterOfName = chatLine.find(":", 14) - 1;
	studentName.append(chatLine, 14, indexOfLastLetterOfName - 14);

	return(studentName);
}

vector<int> NumberOfChatsInEachMinute(string filename) {
	int currentMinute = 0;




	return vector<int>();
}

void AddOnlyIfUniqueString(vector<string> & v, string s) {
	if (v.size() == 0) {					//To always pushback first talking user
		v.push_back(s);
	}

	if (!IsStringUnique(v, s)) {			//Using helper function to see if user has talked before
		v.push_back(s);					//pushing name into vector of students who have talk
	}

}

string TimeChatWasPosted(string chatLine) {
	string time;

	time.append(chatLine, 0, 8);
	cout << "this is the time: " << time;

	return time;
}

int MinuteChatWasPosted(string timeStamp)
{
	return 0;
}





/*
vector<int>NumberOfMessagesPerMinute(string filename){
	string currentTime;
	string newTime;
	vector<int>numOfMessagesInMin;
	string userMessage;
	ifstream(transcript (filename.c_str());

	if(transcript.fail()){
		cout<<"\nfailed to open file\n";
		return -1;
	}

	if(transcript.is_open()){
		while(getline(transcript,userMessage)){


*/













