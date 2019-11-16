#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int NumberOfMessages(string filename);								//Total number of messages in session
int NumberOfDistinctContributors(string filename);						//Total number of distinct studnets who talked
bool DidStudentTalk(vector<string> constributors, string user);					//helper function to see if specific student has talked
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
	int total = 0;	
	string userMessage;
	ifstream transcript (filename.c_str());
	

	if(transcript.fail()){								
		cout<<"failed to open file\n";						//checking if file was opened correctly
		return 0;
	}	
	if(transcript.is_open()){							//if opened then do get line until end of
		while(getline(transcript,userMessage)){					//file and increment counter each time
			++total;
		}
	}
	return (total);
}


bool DidStudentTalk(vector<string> contributors, string user){				//helper function that searches a  vector of students who have talked
											//and returns true if student has talked
	for(int i = 0; i < contributors.size(); ++i){
		if(contributors.at(i) == user){
			return true;
		}
	}
	return false;
}

int NumberOfDistinctContributors(string filename){
	int numOfDistinct = 0;
	int indexOfFrom= 0;					
	int indexOfCol = 0;
	string userMessage;
	string userName;
	vector<string> contributors;
	ifstream transcript (filename.c_str());
	
	if(transcript.fail()){								//checking if file was opened correctly
		cout<<"failed to open file\n";
	}
	if(transcript.is_open()){
		while(getline(transcript,userMessage)){					
			userName.erase();						//clears username string at start of loop
			indexOfFrom = userMessage.find("From");				//searching for index of from and ':' to grab the  chars in the middle 
											//of the two (the username)
			indexOfCol = userMessage.find(":",indexOfFrom);
			userName.append(userMessage,indexOfFrom,indexOfCol-indexOfFrom);//appending char's in the middle of from and ';'
			if(contributors.size() == 0){					//To always pushback first talking user
				contributors.push_back(userName);
				++numOfDistinct;
			}
			if(!DidStudentTalk(contributors,userName)){			//Using helper function to see if user has talked already
				++numOfDistinct;					//incremeneting counter if first time user is talking
				contributors.push_back(userName);			//pushing name into vector of students who have talked
			}	
		}

	}
	return numOfDistinct;
}			












