#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <cstdio>

using namespace std;

int NumberOfChats(string filename);									//Total number of chats in session
int NumberOfStudentsWhoTalked(string filename);						//Total number of distinct studnets who talked
bool IsStringUnique(vector<string> v, string s);					//Checks vector if string s is stored
string GetStudentNameFromChatLine(string chatLine);					//helper function to return studnet name from chatline
vector<int>NumberOfChatsInEachMinute(string filename);				//Stores number of chats of each minute in corresponding vector index
void AddOnlyIfUniqueString(vector<string>& v, string s);			//Adds string if not stored in vector 
string GetTimeChatWasPosted(string chatLine);						//returns the time a chat was posted
int GetMinuteChatWasPosted(string chatLine);						//returns the minute a chat was posted
vector<string> NamesOfStudentsWhoTalked(string fileName);			//return a list of student names who talked
void PrintStudentNames(vector<string> students, string outFile);	//prints students names to an output file
vector<string> GetQuestionResponses(string fileName);				//Returns chats that are responding to a question proposed by proffesor
vector<string> GetFullChatLog(string fileName);						//Returns vector of all chats
vector<vector<string>> GetAllChatsPerMinute(string fileName);		//returns a 2d vector of all chats per minute index
void OutputResponses(vector<string> questionResponses,string outFile);									//Prints question responses to output file
void RemoveQuestionresponsesFromChat(vector<string>& fullChatLog, vector<string> questionresponses);	//Removed question responses from chat log to leave only normal responses
void OutputQuestionResponses(vector<string> questionResponses, string outFile);							//Prints question responses with question number to output file
vector<int> NumberOfChatsInEachMinute_Normal(vector<vector<string>> full, vector<vector<string>> questionReponses);



int main()
{
	ofstream outfile;
	outfile.open("Full_Results.csv");
	int numOfTotalChats = 0;
	int numOfStudentsWhoTalked = 0;
	vector<int> numOfChatsPerMinute;
	vector<string> students;
	
	//All responses

	numOfTotalChats = NumberOfChats("meeting_saved_chat.txt");
	outfile << "The total chats for this session is: " << numOfTotalChats << endl;						//output of total messsages in file

	numOfStudentsWhoTalked = NumberOfStudentsWhoTalked("meeting_saved_chat.txt");						//Outputing number of students who talked
	outfile << "The total number of students who talked is: " << numOfStudentsWhoTalked << endl;			

	students = NamesOfStudentsWhoTalked("meeting_saved_chat.txt");							
	PrintStudentNames(students, "Full_ListOfStudents.txt");													//Outputing names of studnets who talked

	numOfChatsPerMinute = NumberOfChatsInEachMinute("meeting_saved_chat.txt");							//Outputing table of number of chats vs minute
	outfile << "Minute , Number of chats" << endl;					

	for (int i = 0; i < numOfChatsPerMinute.size(); ++i) {
		outfile << i << "," << numOfChatsPerMinute.at(i) << endl;
	}




	//Question responses
	ofstream Question_responses;
	Question_responses.open("Question_responses_Results.csv");

	vector<string> questionResponses = GetQuestionResponses("meeting_saved_chat.txt");											//Returning vector of question responses
	OutputResponses(questionResponses, "Question_Responses_temp.txt");														//Outputing to "Question_Responses.txt" list of chats that are responding to a question
	vector<vector<string>> questionResponses_V = GetAllChatsPerMinute("Question_Responses_temp.txt");

	numOfTotalChats = NumberOfChats("Question_Responses_temp.txt");
	Question_responses << "The total question responses for this session is: " << numOfTotalChats << endl;						//output of total number of respones to questions

	numOfStudentsWhoTalked = NumberOfStudentsWhoTalked("Question_Responses_temp.txt");												//Outputing number of students who responded to a question
	Question_responses << "The total number of students who responded to a question is: " << numOfStudentsWhoTalked << endl;

	students = NamesOfStudentsWhoTalked("Question_Responses_temp.txt");																//Getting names of students who responded to a question
	PrintStudentNames(students, "Question_Responses_Students.txt");																//Outputing names of studnets who responded to a question

	numOfChatsPerMinute = NumberOfChatsInEachMinute("Question_Responses_temp.txt");													//Outputing table of  Question responses vs Question number
	Question_responses << "Question , Number of responses" << endl;
	for (int i = 0; i < numOfChatsPerMinute.size(); ++i) {
		
		if (numOfChatsPerMinute.at(i) == 0) {
			i = numOfChatsPerMinute.size();
			break;
		}

		Question_responses << i+1 << "," << numOfChatsPerMinute.at(i) << endl;
	}
	
	
	const int result_q = remove("Question_Responses_temp.txt");																		//Deleting temp file without question number
	OutputQuestionResponses(questionResponses, "Question_Responses.txt");														//Recreating file with question number for each set of chat lines



	//Normal responses
	ofstream normal_responses;
	vector<string> normalResponses = GetFullChatLog("meeting_saved_chat.txt");									
	
	RemoveQuestionresponsesFromChat(normalResponses, questionResponses);											//Removing question reponses from total responses
	
	
	normal_responses.open("Normal_responses_Results.csv");														
	OutputResponses(normalResponses, "Normal_Responses_temp.txt");													//printing responses to temp file

	numOfTotalChats = NumberOfChats("Normal_Responses_temp.txt");
	normal_responses << "The total number of normal responses for this session is: " << numOfTotalChats << endl;						//output of total number of normal respones 

	numOfStudentsWhoTalked = NumberOfStudentsWhoTalked("Normal_Responses_temp.txt");												//Outputing number of students who chatted
	normal_responses << "The total number of students who responded normally: " << numOfStudentsWhoTalked << endl;

	students = NamesOfStudentsWhoTalked("Normal_Responses_temp.txt");															//Getting names of students who chatted
	PrintStudentNames(students, "Normal_Responses_Students.txt");																//Outputing names of studnets who chatted


	vector<vector<string>> full = GetAllChatsPerMinute("meeting_saved_chat.txt");
	
	vector<int>numOfChatsPerMinute_normal = NumberOfChatsInEachMinute_Normal(full , questionResponses_V);							//Outputing table of number of chats vs minute
	normal_responses << "Minute , Number of chats" << endl;

	for (int i = 0; i < numOfChatsPerMinute.size(); ++i) {
		normal_responses << i << "," << numOfChatsPerMinute_normal.at(i) << endl;
	}

	const int result_n = remove("Normal_Responses_temp.txt");																	//Deleting temp file 
	OutputResponses(normalResponses, "Normal_Responses.txt");																	//Recreating file 

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
		currentMinute = GetMinuteChatWasPosted(chatLine);						//Getting first minute and incrementing zeroth minute
		++numOfChatsInMinute.at(i);						

		while (getline(chatLog, chatLine)) {
			
			if (currentMinute == GetMinuteChatWasPosted(chatLine)) {			//checking current minute with new minute and incrementing accordingly
				++numOfChatsInMinute.at(i);
			}
			else {
				currentMinute = GetMinuteChatWasPosted(chatLine);
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

string GetTimeChatWasPosted(string chatLine)				//returns string time stamp of chat line
{
	string time;

	time.append(chatLine, 0, 8);

	return time;
}

int GetMinuteChatWasPosted(string chatLine)				//returns int minute chat was posted
{	
	string minute;

	minute.append(chatLine, 4, 1);
	
	return stoi(minute);

}

vector<string> NamesOfStudentsWhoTalked(string fileName)
{
	string chatLine;
	string studentName;
	vector<string> students;
	ifstream chatLog(fileName.c_str());

	if (chatLog.fail()) {								//checking if file was opened correctly
		cout << "failed to open file\n";
	}

	if (chatLog.is_open()) {
		while (getline(chatLog, chatLine)) {
			studentName = GetStudentNameFromChatLine(chatLine);		//helper function call to grab username from chat line	
			AddOnlyIfUniqueString(students, studentName);
		}

	}

	return students;
}

void PrintStudentNames(vector<string> students, string outFile)
{
	ofstream outfile;
	outfile.open(outFile);

	outfile << "List of students who talked\n";

	for (int i = 0; i < students.size(); ++i) {
		outfile << students.at(i) << endl;
	}

}

vector<string> GetQuestionResponses(string fileName)
{
	vector<string> questionResponses;
	vector<vector<string>> allChats = GetAllChatsPerMinute(fileName);
	
	for (int i = 0; i < allChats.size(); ++i) {

		if (allChats.at(i).size() >= 8) {								//Pushing back the minutes that had greather than or equal to 8 chats
			
			for (int j = 0; j < allChats.at(i).size(); ++j) {
				
				questionResponses.push_back(allChats.at(i).at(j));
			}

		}
	}
	

	return questionResponses;
}

vector<string> GetFullChatLog(string fileName)
{
	string chatLine;
	vector<string> fullChatLog;
	ifstream chatLog(fileName.c_str());

	if (chatLog.fail()) {								//checking if file was opened correctly
		cout << "failed to open file\n";
	}

	if (chatLog.is_open()) {
		
		while (getline(chatLog, chatLine)) {			//pushing back full chat line for all chats in the meeting txt file
			fullChatLog.push_back(chatLine);
		}

	}


	return fullChatLog;
}

vector<vector<string>> GetAllChatsPerMinute(string fileName)
{
	vector<string> fullChat = GetFullChatLog(fileName);
	vector<vector<string>> allChatsPerMinute(100);
	int currentMinute = GetMinuteChatWasPosted(fullChat.at(0));
	int minuteIndex = 0;

	for (int i = 0; i < fullChat.size(); ++i) {
		
		if (currentMinute == GetMinuteChatWasPosted(fullChat.at(i))) {				//checking if next chat is in the same minute as previouse one
			allChatsPerMinute.at(minuteIndex).push_back(fullChat.at(i));			//pushing if same minute
		}
		else {		
			++minuteIndex;															//if not then incrementing minute index 
			currentMinute = GetMinuteChatWasPosted(fullChat.at(i));					//setting current minute to new current minute
			allChatsPerMinute.at(minuteIndex).push_back(fullChat.at(i));			//pushing back the new minute chat
		}

	}

	return allChatsPerMinute;
}

void OutputResponses(vector<string> Responses, string outFile)
{
	ofstream outfile;
	outfile.open(outFile);
	
	for (int i = 0; i < Responses.size(); ++i) {
		outfile << Responses.at(i) << endl;											//priting chat line response
	}

}

void RemoveQuestionresponsesFromChat(vector<string>& fullChatLog, vector<string> questionresponses)
{
	int currentReponseIndex = 0;
	vector<string>::const_iterator it = fullChatLog.begin();
		for (int i = 0; i < fullChatLog.size(); ++i) {
			
			if (fullChatLog.at(i) == questionresponses.at(currentReponseIndex)) {							//checking if chatLine is in question reponses 
				fullChatLog.erase(it + i);																	//If true then erase chat line 
				++currentReponseIndex;
				--i;
			}
			
			if (currentReponseIndex >= questionresponses.size()) {
				return;
			}
		}

}

void OutputQuestionResponses(vector<string> questionResponses, string outFile)
{

	ofstream outfile;
	int currentMinute = GetMinuteChatWasPosted(questionResponses.at(0));			//Setting current minute for first response
	int currentQuestion = 1;

	outfile.open(outFile);

	outfile << "List of responses to all questions\n";
	outfile << "Question " << currentQuestion << endl << endl;

	for (int i = 0; i < questionResponses.size(); ++i) {

		if (currentMinute != GetMinuteChatWasPosted(questionResponses.at(i))) {				//if not the same minute then increment the question number
			++currentQuestion;											
			currentMinute = GetMinuteChatWasPosted(questionResponses.at(i));				
			outfile << "\nQuestion " << currentQuestion << endl << endl;						//print new question number
		}

		outfile << questionResponses.at(i) << endl;											//priting chat line response
	}
}

vector<int> NumberOfChatsInEachMinute_Normal(vector<vector<string>> full, vector<vector<string>> questionReponses)
{
	int questionIndex = 0;
	vector<int> numOfChatsNormal = NumberOfChatsInEachMinute("meeting_saved_chat.txt");

	for (int i = 0; i < full.size(); ++i) {
		
		if (GetTimeChatWasPosted(full.at(i).at(0)) == GetTimeChatWasPosted(questionReponses.at(questionIndex).at(0))) {
			numOfChatsNormal.at(i) = 0;
			++questionIndex;
			if (questionReponses.at(questionIndex).size() == 0) {
				return numOfChatsNormal;
			}
		}
	}

	return numOfChatsNormal;

}
	
























