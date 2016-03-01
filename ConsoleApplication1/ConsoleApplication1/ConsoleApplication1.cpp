// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;


// functions for strings

bool blnTestForMatch(char * a, char * pattern) {
	
	if (strstr(a, pattern) != NULL)
		return(true);
	else
		return(false);
}


bool blnTestForStartMatch(char * a, char * pattern){

	char x[10] = "";
	bool b;

	strncpy_s(x, a, 8);
	b = blnTestForMatch(x, pattern);

	return(b);
}

char * cptrGetChunk(int index, char * datastring){

	int i = 0;
	char * strptr1;

	rsize_t strmax = sizeof datastring;
	const char *delim = " ";
	char *next_token;

	strptr1 = strtok_s(datastring, delim, &next_token);
	while (i < index - 1){
		strptr1 = strtok_s(NULL, delim, &next_token);
		i++;
	}
	return(strptr1);
}



// used in phase one
// cannot quite get all the way there easily with bash tools

// grep "W3SVC106 STREAM 207.22.66.152 80 GET " access.log | cut -d" " -f3 | grep -v ^"207.114." >> p1_report.csv
// sort p1_report.csv | uniq -c | sort -nr >> p2_report.csv
// ... this gets the result without the quotes and comma...

char target_httpget[] = { "W3SVC106 STREAM 207.22.66.152 80 GET " };
char target_ipexclude[] = { "207.114." };
char * ipaddr;
int SourceIPIndex = 3;

// global item used in phase 2
std::map <string, int> IPL;

// definitions used in phase 3




class SortedIP {

public:

	typedef struct { 
	int count;
	int ip[4];
	}IPTallyEntry;


};



///////////////////////////////////////////////////////////////////////////////////////////////////
// working on alternate, simpler implementation...
///////////////////////////////////////////////////////////////////////////////////////////////////


class IPEntry {

public:

	void GetIPEntryData(int &t, int &f1, int &f2, int &f3, int &f4){
		t = data.count;
		f1 = data.ip[0];
		f2 = data.ip[1];
		f3 = data.ip[2];
		f4 = data.ip[3];
	}

	void PutIPEntryData(const int t, const int f1, const int f2, const int f3, const int f4){
		data.count = t;
		data.ip[0] = f1;
		data.ip[1] = f2;
		data.ip[2] = f3;
		data.ip[3] = f4;
	}

	// define sort operators
	friend inline bool operator< (const IPEntry &lhs, const IPEntry &rhs){
		if (lhs.data.count < rhs.data.count) return true;
		else if (lhs.data.count == rhs.data.count && lhs.data.ip[0] < rhs.data.ip[0]) return true;
		else if (lhs.data.count == rhs.data.count && lhs.data.ip[0] == rhs.data.ip[0] && lhs.data.ip[1] < rhs.data.ip[1]) return true;
		else if (lhs.data.count == rhs.data.count && lhs.data.ip[0] == rhs.data.ip[0] && lhs.data.ip[1] == rhs.data.ip[1] && lhs.data.ip[2] < rhs.data.ip[2]) return true;
		else if (lhs.data.count == rhs.data.count && lhs.data.ip[0] == rhs.data.ip[0] && lhs.data.ip[1] == rhs.data.ip[1] && lhs.data.ip[2] == rhs.data.ip[2] && lhs.data.ip[3] < rhs.data.ip[3]) return true;
		else return false;
	}
	friend inline bool operator> (const IPEntry lhs, const IPEntry rhs){ return (rhs < lhs); }
	friend inline bool operator<=(const IPEntry lhs, const IPEntry rhs){ return !(lhs > rhs); }
	friend inline bool operator>=(const IPEntry lhs, const IPEntry rhs){ return !(lhs < rhs); }

	friend inline bool operator==(const IPEntry lhs, const IPEntry rhs){
		if (lhs.data.count == rhs.data.count && lhs.data.ip[0] == rhs.data.ip[0] && lhs.data.ip[1] == rhs.data.ip[1] && lhs.data.ip[2] == rhs.data.ip[2] && lhs.data.ip[3] == rhs.data.ip[3]) return true;
		else return false;
	}
	friend inline bool operator!=(const IPEntry lhs, const IPEntry rhs){ return !(lhs == rhs); }

private:

	SortedIP::IPTallyEntry data;

};




///////////////////////////////////////////////////////////////////////////////////////////////////


int _tmain(int argc, _TCHAR* argv[])
{
	ifstream stream1;
	ofstream myfile;
	char dataline[10000] = {""};
	char last_ipaddr[16] = { "" };
	int new_ip_ctr = 0;
	int old_ip_ctr = 0;

	// first stage is to read the large file, extract the port 80 GET IP addresses,
	// exclude IP addresses starting with 207.114., eliminating all blank or non-GET log lines
	// ... successive duplicates are counted, and count - IP pairs are pushed out to file q1.log

	stream1.open("C:\\Users\\Bob\\Desktop\\developer-screening-quiz\\access.log");
	if (!stream1.is_open())
		cout << "While opening a file an error is encountered" << endl;
	else
		cout << "File is successfully opened" << endl;

		myfile.open("C:\\Users\\Bob\\Desktop\\developer-screening-quiz\\q1.log");
		//myfile << "Writing this to a file.\n";
	
		while (!stream1.eof())
		{

			stream1.getline(dataline, 10000);
			//cout << dataline << endl;
 
			if (blnTestForMatch(dataline, target_httpget)){
				
					ipaddr = cptrGetChunk(SourceIPIndex, dataline);

					if (!blnTestForStartMatch(ipaddr, target_ipexclude) && strlen(ipaddr) > 7){

						myfile << ipaddr << endl;
					
					}
					
			}
		}


		myfile.close();	
		stream1.close();

		cout << "First pass done." << endl;

		// at this point, the file q1 has counts of successive IP port 80 GETs and the IP addresses
		// the map function will be used to revise the file to unique total port 80 GET counts and IP addresses
		// ... the result is written to q2.log

		stream1.open("C:\\Users\\Bob\\Desktop\\developer-screening-quiz\\q1.log");
		if (!stream1)
			cout << "While opening a file an error is encountered" << endl;
		else
			cout << "File is successfully opened" << endl;

		myfile.open("C:\\Users\\Bob\\Desktop\\developer-screening-quiz\\q2.log");

		char *p1;
		char cbuf1[40];
		//char *p2;
		//char cbuf2[40];
		string s;

		while (!stream1.eof())
		{
			stream1.getline(dataline, 100);
			
			strcpy_s(cbuf1, dataline);
			//strcpy_s(cbuf2, dataline);

			p1 = cptrGetChunk(1, cbuf1);
			//p2 = cptrGetChunk(2, cbuf2);

			if (p1 != nullptr /*&& p2 != nullptr*/){
				s = p1;
				//s = p2;
				//sscanf_s(p1, "%d", &x);
				IPL[s] ++;			
			}

		}
			
		// write output of second stage
		for (const auto& p : IPL)
		{
				myfile << p.second;
				myfile << " ";
				myfile << p.first;
				myfile << endl;
		}
					
		myfile.close();
		stream1.close();

		cout << "Second pass done." << endl;


////////////////////////////////////////////////////////////////////////////////////

		char * strptr1;
		const char *delim = " .";
		char *next_token;
		
		IPEntry qqq;
		IPEntry &workentry = qqq;
		list<IPEntry> mylist;
		list<IPEntry>::iterator iter;

////////////////////////////////////////////////////////////////////////////////////

		// file q2.log is read and sorted per spec, and extruded file report.csv

		stream1.open("C:\\Users\\Bob\\Desktop\\developer-screening-quiz\\q2.log");
		if (!stream1)
			cout << "While opening a file an error is encountered" << endl;
		else
			cout << "File is successfully opened" << endl;

		myfile.open("C:\\Users\\Bob\\Desktop\\developer-screening-quiz\\report.csv");


////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
// trying new version with new class
////////////////////////////////////////////////////////////////////////////////////

		while (!stream1.eof())
		{
			int tally, f1, f2, f3, f4;
			tally = f1 = f2 = f3 = f4 = 0;
			workentry.PutIPEntryData(tally, f1, f2, f3, f4);

			stream1.getline(dataline, 100);

			strptr1 = strtok_s(dataline, delim, &next_token);
			if (strptr1 != nullptr)
				sscanf_s(strptr1, "%d", &tally);

			strptr1 = strtok_s(NULL, delim, &next_token);
			if (strptr1 != nullptr)
				sscanf_s(strptr1, "%d", &f1);

			strptr1 = strtok_s(NULL, delim, &next_token);
			if (strptr1 != nullptr)
				sscanf_s(strptr1, "%d", &f2);

			strptr1 = strtok_s(NULL, delim, &next_token);
			if (strptr1 != nullptr)
				sscanf_s(strptr1, "%d", &f3);

			strptr1 = strtok_s(NULL, delim, &next_token);
			if (strptr1 != nullptr)
				sscanf_s(strptr1, "%d", &f4);

			if (strptr1 != nullptr){
				workentry.PutIPEntryData(tally, f1, f2, f3, f4);
				mylist.push_back(workentry);
			}
		}

		mylist.sort();
		mylist.reverse();

		// build strings
		// write output of second stage
		for (auto& z : mylist)
		{
			int tally, f1, f2, f3, f4;
			tally = f1 = f2 = f3 = f4 = 0;
			int &tr = tally, &f1r = f1, &f2r = f2, &f3r = f3, &f4r = f4;

			z.GetIPEntryData(tr, f1r, f2r, f3r, f4r);

		
			myfile << tally;
			myfile << ", \"";
			myfile << f1 << ".";
			myfile << f2 << ".";
			myfile << f3 << ".";
			myfile << f4;
			myfile << "\"";
			myfile << endl;

		}
		mylist.clear();


////////////////////////////////////////////////////////////////////////////////////


		myfile.close();
		stream1.close();

		cout << "Final pass done." << endl;
		cout << "Finished." << endl;
		
		cin.getline(dataline, 1);
		return 0;
}





