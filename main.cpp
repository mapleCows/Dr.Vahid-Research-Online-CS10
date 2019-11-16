#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int NumberOfMessages(string filename);								//Total number of messages in session
int NumberOfDistinctContributors(string filename);						//Total number of distinct studnets who talked
bool DidStudentTalk(vector<string> constributors, string user);					//helper function to see if specific student has talked
string GetStudentNameFromChatLine(string chatLine);						//helper function to return studnet name from chatline
vector<int>NumberOfMessagesPerMinute(string filename);					

int main(){

	int numOfTotalMessages = 0;
	int numOfDistinctContributors = 0;					

	numOfTotalMessages = NumberOfMessages("meeting_saved_chat.txt");			//calling NumberOfMessagesfunction
	cout<<"The total messages for this session is: "<<numOfTotalMessages<<endl;		//output of total messsages in file

	numOfDistinctContributors = NumberOfDistinctContributors("meeting_saved_chat.txt");
	cout<<"The total number of distinct contributors is: "<<numOfDistinctContributors<<endl;

	return 0;
}



int NumberOfMessages(string filename){
	int numOfMessages = 0;	
	string chatLine;
	ifstream chatLog (filename.c_str());
	

	if(chatLog.fail()){								
		cout<<"failed to open file\n";						//checking if file was opened correctly
		return -1;
	}	

	if(chatLog.is_open()){							        //if opened then do get line until end of
		while(getline(chatLog,chatLine)){					//file and increment counter each time
			++numOfMessages;
		}
	}

	return (numOfMessages);
}


bool DidStudentTalk(vector<string> students, string student){				//helper function that searches a  vector of students who have talked
											//and returns true if student has talked
	for(int i = 0; i < students.size(); ++i){
		if(students.at(i) == student){
			return true;
		}
	}

	return false;
}


string GetStudentNameFromChatLine(string chatLine){					//helper function to grab student name from chat line
	string studentName;
	int indexOfLastLetterOfName = 0;
	
	indexOfLastLetterOfName = chatLine.find(":",14) - 1;	
	studentName.append(chatLine,14,indexOfLastLetterOfName-14);
	
	return(studentName);
}


int NumberOfDistinctContributors(string filename){

	string chatLine;
	string studentName;
	vector<string> students;
	ifstream chatLog (filename.c_str());
	
	if(chatLog.fail()){								//checking if file was opened correctly
		cout<<"failed to open file\n";
		return -1;
	}
	
	if(chatLog.is_open()){
		while(getline(chatLog,chatLine)){					
			studentName = GetStudentNameFromChatLine(chatLine);		//helper function call to grab username from chat line	
			if(students.size() == 0){					//To always pushback first talking user
				students.push_back(studentName);
			}
	
			if(!DidStudentTalk(students,studentName)){			//Using helper function to see if user has talked before
				students.push_back(studentName);			//pushing name into vector of students who have talk
			}	
		}

	}

	return students.size();
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













