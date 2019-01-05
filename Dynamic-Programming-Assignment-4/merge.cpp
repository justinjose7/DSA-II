#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <list>
using namespace std;

int s1xs2[1002][1002];

int fillMatrix(const string &s1, const string &s2,const string &s3){
	int length_s1 = s1.size();
	int length_s2 = s2.size();
	
	for (int i = 0; i < length_s1+1; i++)
		for (int j = 0; j < length_s2+1; j++)
			s1xs2[i][j] = 0;

	s1xs2[0][0] = 1;

	//matrix style (n+2 X m+2 sized matrix where n = s1.size()-1, m = s2.size()-1)
	//             s2[0] s2[1] s2[..] s2[m] 
	//       | 1    __    __     __    __   |
	// s1[0] | __   __    __     __    __   |
	// s1[1] | __   __    __     __    __   |
	// s1[..]| __   __    __     __    __   |
	// s1[n] | __   __    __     __    __   |

	for (int i = 0; i < length_s1+1; i++){
		
		for (int j = 0; j < length_s2+1; j++){
			
			if (s1xs2[i][j] == 1){
				
				if (s1[i] == s3[i+j])
					s1xs2[i+1][j] = 1;

				if (s2[j] == s3[i+j])
					s1xs2[i][j+1] = 1;
			}
		}
	}
}

void mergeCheck(const string &s1, const string &s2, const string &s3, ofstream &outFile){
	int i = s1.size();
	int j = s2.size();
	list<char> merged;

	if (s1xs2[i][j] == 1 && i+j == s3.size()){ // check if fillMatrix function returned a valid merge
		while(i != 0 || j != 0){ // keep iterating until at position 0,0 of the matrix
			if (s2[j-1] == s3[i+j-1] && s1xs2[i][j-1] == 1) 
				merged.push_front(s2[j-1]);
			
			if (s1[i-1] == s3[i+j-1] && (s2[j-1] != s3[i+j-1] || s1xs2[i][j-1] == 0))  
				merged.push_front(toupper(s1[i-1]));

			if (s1xs2[i-1][j] == 1 && s1xs2[i][j-1] != 1) // move one row up
				i--;
			else if (s1xs2[i][j-1] == 1) // move one column to the left
				j--;
		}
		while (!merged.empty()){
			outFile << merged.front();
			merged.pop_front();
		}
		outFile << endl;
	} else
		outFile << "*** NOT A MERGE ***" << endl;
}

int main() {
	string inFilename, outFilename, string1, string2, string3; 
	
	cout << "Enter name of input file: ";
	getline(cin, inFilename);
	cout << "Enter name of output file: ";
	getline(cin, outFilename);

	ifstream inputFile;
	ofstream outputFile;
	inputFile.open(inFilename.c_str());
	outputFile.open(outFilename.c_str());

	while(getline(inputFile, string1)){
		getline(inputFile, string2);
		getline(inputFile, string3);
		fillMatrix(string1, string2, string3);
		mergeCheck(string1, string2, string3, outputFile);
	}

	inputFile.close();
	outputFile.close();
}