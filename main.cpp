#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int TotalMessages(string filename);


int main(){

	int numOfTotalMessages = 0;					
	numOfTotalMessages = TotalMessages("meeting_saved_chat.txt");			//calling TotalMessages function
	cout<<"The total messages for this session is: "<<numOfTotalMessages;		//output of total messsages in file
	return 0;
}



int TotalMessages(string filename){
	int total = 0;	
	string userMessage;
	ifstream transcrip (filename.c_str());
	

	if(transcrip.fail()){								
		cout<<"failed to open file\n";						//checking if file was opened correctly
		return 0;
	}	
	if(transcrip.is_open()){							//if opened then do get line until end of
		while(getline(transcrip,userMessage)){					//file and increment counter each time
			++total;
		}
	}
	return (total);
}
