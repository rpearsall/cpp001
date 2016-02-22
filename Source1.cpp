/////////////////////////////////////////////////////////////////////////
// console project to scan log for GET requests and tabulate by IP
// exclude expected address range 207.114.x.x
/////////////////////////////////////////////////////////////////////////

// include libraries
#include <iostream>
#include <fstream>

#include <list>

//using namespace std;

// declare / initialize variables


typedef listitem int[5];




// grep "W3SVC106 STREAM 207.22.66.152 80 GET " access.log | cut -d" " -f3 | grep -v ^"207.114." >> p1_report.csv
// sort p1_report.csv | uniq -c | sort -nr >> p2_report.csv
// ... this gets the result without the quotes and comma...

char * target_httpget[] = "W3SVC106 STREAM 207.22.66.152 80 GET ";
char * target_ipexclude[] = "207.114.";
char * ipaddr;
int SourceIPIndex = 3;

// functions for strings

bool blnTestForMatch(char * a, char * pattern){

	if strstr(a, pattern)
		return(true);
	else
		return(false);
}


bool blnTestForStartMatch(char * a, char * pattern){

	char x[10] = "";
	bool b;

	strncpy(x, a, 8);
	b = blnTestForMatch(x, pattern);

	return(b);
}

char * cptrGetChunk(int index, char * datastring){

	int i;
	char * strptr1;
	
	strptr1 = strtok(datastring, " ");
	while (int i = 0; i < index-1)
		strptr1 = strtok(NULL, " ");

	return(strptr1);
}

// functions for IP listitems

bool blnIPListItemEqual(listitem * a, listitem * b){

	bool r = false;

	for (int i = 1; i < 5; i++)
		if (a[i] != b[i])
			return (r);

	return (true);

}



int main() {

	// basic file operations

		ofstream myfile;
		myfile.open("C:\Users\Bob\Desktop\developer-screening-quiz\q.log");
		myfile << "Writing this to a file.\n";
		myfile.close();
		return 0;
	}


	/*
	std::list<listitem> IPs;

	listitem * q;
	char * ipaddr, * s1;
	int x;
	bool test1;

//open file
// for each line

if (blnTestForMatch(dataline, target_httpget)){

	ipaddr = cptrGetChunk(SourceIPIndex, dataline);

	if (!blnTestForStartMatch(ipaddr, target_ipexclude)){

		
		// add to data

		q = malloc(sizeof(listitem));

		q[0] = 0;
		
		s1 = strtok(ipaddr, ".");
		for (int i = 1; i < 5; i++){
			sscanf(s1, "%d", &x);
			q[i] = x;
			s1 = strtok(NULL, ".");
		}
			
		test1 = false;
		for (auto&& i : IPs){
			if blnIPListItemEqual(i, q)
				i[0]++;
		}





		}





	}
}
//close file



}



// test function is kernel operator for sorting

bool blnSwapTest(char * a, char * b) {

bool result = false;			// do nothing
char * valaptr, char * valbptr;
char vala[30], char valb[30];

memset(vala, \0, 30);
memset(valb, \0, 30);


valaptr = strtok(a, " ,.\"");
valbptr = strtok(b, " ,.\"");

	while ( valaptr != NULL && valbptr != NULL){

		if (vala != valb){
			if (vala < valb)
				result = true;	// need to swap to descend
		}

		vala = strtok(NULL, " ,.\"");
		valb = strtok(NULL, " ,.\"");
	}

	return(result);
}




	// check if IP in list
		// True - increment count
		// False - add IP to list & start count

// end while loop

/////////////////////////////////////////////////////////////////////////
// on EOF, write output data summary to CSV, 
//     sorted by number of requests, then IP octets, values descending
/////////////////////////////////////////////////////////////////////////

// first sort



// then open file, write, close


sprintf(outbuf, "%d , \"%d\.%d\.%d\.%d\"\n", ival, oct1, oct2, oct3, oct4);


// exit

*/
