/*
Program name: String search V2
Program Purpose:
- Comparison of 2 string search Algorithms. Rabin Karp Vs Boyer Moore
- 2 data structures. Lists & vectors

Rabin Karp: adapted a C implementation of Rabin Karp in the CLRS book
(Link : http://www.geeksforgeeks.org/searching-for-patterns-set-3-rabin-karp-algorithm/)	[accessed 23/11/2017]

Boyer Moore: Adapted from Adam Sampson's String search Lab exersiese in Data structures & Algorithms 1
(Link : https://blackboard.abertay.ac.uk/bbcswebdav/pid-450521-dt-content-rid-1254154_1/courses/CMP201.2017-8.S1.A/LabWorksheets/lab09-stringsearch.pdf) [accessed 23/11/2017]

text used in testing
(Link: http://www.blindtextgenerator.com/lorem-ipsum)

Varaibel Breakdown :
pat			->		pattern
txt			->		text
prime		->		A prime number
M			->		size of patern
N			->		size of text
num_alpha   ->		number of characters in input alphabet
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

using std::cout;
using std::endl;
using std::list;
using std::string;

//required for an accurate clock
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

//required for testing times
typedef std::chrono::steady_clock the_clock;

using std::ofstream;


/*rabin karp (plain)
void Rabin_Karp(string pat, string txt, int prime, int num_alpha)
{
	int M = pat.size();
	int N = txt.size();


	int i, j;			//counters
	int hashp = 0;		//hash value for pattern
	int hasht = 0;		//hash value for txt
	int h = 1;

	//loop for length of pat 
	for (i = 0; i < M - 1; i++)
	{
		h = (h*num_alpha) % prime;	//h is the remainder of (h*num_alpha) / 2
	}
	//calculate the hash value of pattern and first substring
	for (i = 0; i < M; i++)
	{
		hashp = (num_alpha*hashp + pat[i]) % prime;
		hasht = (num_alpha*hasht + txt[i]) % prime;
	}

	//slide the pattern accross by one substring 
	for (i = 0; i <= N - M; i++)
	{
		if (hashp == hasht)	//checks if the hash of the pattern is equal to the hash of the substring
		{

			for (j = 0; j < M; j++)		//check for characters in p Vs the substring one at a time)
			{
				if (txt[i + j] != pat[j])
					break;
			}
			if (j == M)			//if all characters match up by the end of the comparison stage : pattern was found in the text
				printf("Pattern found at index %d \n", i);
		}

		if (i < N - M)
		{
			hasht = (num_alpha*(hasht - txt[i] * h) + txt[i + M]) % prime; //calculates the next substring hash

			if (hasht < 0)						//if t is a negative value it's converted to positive
				hasht = (hasht + prime);
		}
	}
}
*/

//rabin karp (list)
list <int> Rabin_Karp_L(const string& pat, const string& txt, int prime, int num_alpha)
{
	int M = pat.size();
	int N = txt.size();
	int i, j;		//counters
	int hashp = 0;	 //hash value for pattern
	int hasht = 0;	//hash value for txt
	int h = 1;
	list<int> found; //list of results

					 //the value of h would be "pow(d, M-1)%q"
	for (i = 0; i < M - 1; i++)
		h = (h*num_alpha) % prime;

	//calculate the hash value of pattern and first substring
	for (i = 0; i < M; i++)
	{
		hashp = (num_alpha*hashp + pat[i]) % prime;
		hasht = (num_alpha*hasht + txt[i]) % prime;
	}

	//slide the pattern over text one by one
	for (i = 0; i <= N - M; i++)
	{
		if (hashp == hasht)	//checks if the hash of the pattern is equal to the hash of the substring
		{

			for (j = 0; j < M; j++)		//check for characters in p Vs the substring one at a time)
			{
				if (txt[i + j] != pat[j])
					break;
			}
			if (j == M)			//if all characters match up by the end of the comparison stage : pattern was found in the text
				found.push_front(i); //adds position to list
		}

		if (i < N - M)		//calculate hash value for next window of text: Removeleading digit, add trailing digit
		{
			hasht = (num_alpha*(hasht - txt[i] * h) + txt[i + M]) % prime;

			if (hasht < 0)						//if t is a negative value it's converted to positive
				hasht = (hasht + prime);
		}
	}

	if (found.size()>0)
	{
		return found;
	}

	return found;
}
//

//rabin karp (vector)
std::vector<int> Rabin_Karp_V(const string& pat, const string& txt, int prime, int num_alpha)
{
	int M = pat.size();
	int N = txt.size();
	int i, j;		//counters
	int hashp = 0;	 //hash value for pattern
	int hasht = 0;	//hash value for txt
	int h = 1;
	std::vector<int> found; //vector of results

							//the value of h would be "pow(d, M-1)%q"
	for (i = 0; i < M - 1; i++)
		h = (h*num_alpha) % prime;		//remainder of (h multiplied by 256) / prime number 

										//calculate the hash value of pattern and first substring
	for (i = 0; i < M; i++)
	{
		hashp = (num_alpha*hashp + pat[i]) % prime;
		hasht = (num_alpha*hasht + txt[i]) % prime;
	}

	//slide the pattern over text one by one
	for (i = 0; i <= N - M; i++)
	{
		if (hashp == hasht)	//checks if the hash of the pattern is equal to the hash of the substring
		{

			for (j = 0; j < M; j++)		//check for characters in p Vs the substring one at a time)
			{
				if (txt[i + j] != pat[j])
					break;
			}
			if (j == M)			//if all characters match up by the end of the comparison stage : pattern was found in the text
				found.push_back(i); //adds position to vector
		}

		if (i < N - M)		//calculate hash value for next window of text: Removes leading num & adds trailing num
		{
			hasht = (num_alpha*(hasht - txt[i] * h) + txt[i + M]) % prime;

			if (hasht < 0)						//if t is a negative value it's converted to positive
				hasht = (hasht + prime);
		}
	}

	if (found.size()>0)
	{
		return found;
	}

	return found;
}
//

/* Boyer-Moore (plain)
void Boyer_Moore(const string& pat, const string& text) {

	int M = pat.size();
	int N = text.size();
	int i;

	int skip[256];
	for (i = 0; i < 256; ++i)
		skip[i] = M;				//not in the pattern. 
	for (i = 0; i < M; ++i)
		skip[int(pat[i])] = (M - 1) - i;

	for (i = 0; i < N - M; ++i)
	{
		int j;

		int s = skip[int(text[i + M - 1])];
		if (s != 0) {
			i += s - 1;					//skips forwards.
			continue;
		}

		for (j = 0; j < M; j++) {
			if (text[i + j] != pat[j]) {
				break;					//doesn't match here.
			}
		}
		if (j == M) {
			cout << "Pat found at " << i << "\n";	//displays where the pattern was found 
		}
	}
}
*/

// Boyer-Moore (list)
list<int> Boyer_Moore_L(const string& pat, const string& text) {
	int M = pat.size();
	int N = text.size();
	int i;
	list<int> found; //list of results

					 //like hash table but syncs up values "dsadadas"
					 //										   |
					 //									     "cats"
					 //look up table not hash table
	int skip[256];
	for (i = 0; i < 256; ++i)
		skip[i] = M; // not in the pattern.
	for (i = 0; i < M; ++i)
		skip[int(pat[i])] = (M - 1) - i;

	for (i = 0; i < N - M; ++i) {
		int j;

		int s = skip[int(text[i + M - 1])];
		if (s != 0) {
			i += s - 1; // skips forwards.
			continue;
		}

		for (j = 0; j < M; j++) {
			if (text[i + j] != pat[j]) {
				break; // doesn't match here.
			}
		}

		if (j == M) {
			found.push_front(i); // matches here.
		}

	}
	if (found.size()>0)
	{
		return found;
	}

	return found;
}
//

//Boyer Moore (vector)
std::vector<int> Boyer_Moore_V(const string& pat, const string& text) {
	int pat_len = pat.size();
	int text_len = text.size();
	int i;
	std::vector <int> found; //vector of results

							 //like hash table but syncs up values "dsadadas"
							 //										   |
							 //									     "cats"
							 //look up table not hash table
	int skip[256];
	for (i = 0; i < 256; ++i)
		skip[i] = pat_len; // not in the pattern.
	for (i = 0; i < pat_len; ++i)
		skip[int(pat[i])] = (pat_len - 1) - i;

	for (i = 0; i < text_len - pat_len; ++i) {
		int j;

		int s = skip[int(text[i + pat_len - 1])];
		if (s != 0) {
			i += s - 1; // skips forwards.
			continue;
		}

		for (j = 0; j < pat_len; j++) {
			if (text[i + j] != pat[j]) {
				break; // doesn't match here.
			}
		}

		if (j == pat_len) {
			found.push_back(i); //adds position to vector
		}

	}
	if (found.size()>0)
	{
		return found;
	}

	return found;
}
//

int main()
{
	string txt = "";
	string pat = "dolor";
	//string pat = "super cool";
	string output = "";

	int num_alpha = 256;
	int prime = 2;				// prime number required for the hashing algorithm
	std::vector<int> V_pos;		// used to store the positions of vectors
	list<int> pos;				// used to store the positions for lists
	int size = 0;				// size variable of lists & vectors 
	int x;						// used as counter icon to display number of results per algorithm
	int i;						// counter used in for loops in main
	int j;						// second counter used in main
	string path;				//	the file path 
	string fileST = "";			//	conversts thevar file to striing 
	int file;					//	determines which file is used

	ofstream listFile, vectorFile;

	listFile.open("list output.csv");		//opens CVS file called test data
	vectorFile.open("Vector output.csv");	//opens CVS file called test data

	//titles for each spead sheet
	listFile << "List Results\n\n,,,Boyer-Moore,,,,Rabin-Karp\n\nInput size,,BM 1,BM 2,BM 3,,RK 1,RK 2,RK 3" << ",\n";
	vectorFile << "Vector Results\n\n,,,Rabin-Karp,,,,Boyer-Moore\n\nInput size,,BM 1,BM 2,BM 3,,Rk 1,Rk 2,RK 3" << ",\n";
	for (file = 10000; file < 200001; file = file + 10000)
	{
		fileST = std::to_string(file);
		path = "text\\" + fileST;
		path = path + ".txt";
		cout << path;

		//reading txt file
		std::ifstream inFile;	//creating variable for the file
		inFile.open(path);

		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				inFile >> output;
				//cout << output;
				txt = txt + output;
			}
			inFile.close();
		}
		else { cout << "Unable to open file"; }

		listFile << "" << file << ",,";
		//boyer moore (list)
		for (j = 0; j < 3; j++)
		{
			the_clock::time_point start = the_clock::now();
			pos = Boyer_Moore_L(pat, txt);
			the_clock::time_point end = the_clock::now();
			size = pos.size();
			//
			cout << "\nBM List\n========\n\n";
			for (i = 0; i < size; i++)
			{
				cout << "Found: '" << pat << "' at position: " << pos.front() << "\n";		//displays it
				pos.pop_front();	//deletes it
			}
	
			//
			auto time_taken = duration_cast<nanoseconds>(end - start).count();
			cout << "\n" << time_taken << "\n";
			listFile << "" << time_taken << ",";
		}
		//
		listFile << ",";
		//rabin karp (list)
		for (j = 0; j < 3; j++)
		{
			the_clock::time_point start = the_clock::now();
			pos = Rabin_Karp_L(pat, txt, prime, num_alpha);
			the_clock::time_point end = the_clock::now();
			size = pos.size();
			x = 0;

			cout << "\nRK List\n========\n\n";
			for (i = 0; i < size; i++)
			{
				cout << "Found: '" << pat << "' at position: " << pos.front() << "\n";		//displays it
				pos.pop_front();	//deletes it
				x++;
			}

			size = pos.size();
			auto time_taken = duration_cast<nanoseconds>(end - start).count();
			cout << "\n" << time_taken << "\n";
			listFile << "" << time_taken << ",";
		}


		vectorFile << "" << file << ",,";
		//rabin karp (vector)
		for (j = 0; j < 3; j++)
		{
			the_clock::time_point start = the_clock::now();
			V_pos = Rabin_Karp_V(pat, txt, prime, num_alpha);
			the_clock::time_point end = the_clock::now();
			size = V_pos.size();


			cout << "\nRK Vector\n========\n\n";
			for (i = 0; i < size; i++)
			{
				cout << "Found: '" << pat << "' at position: " << V_pos[i] << "\n";		//loops through all of the items in the vector
			}
			
			auto time_taken = duration_cast<nanoseconds>(end - start).count();
			cout << "\nVector" << time_taken << "\n";
			vectorFile << "" << time_taken << ",";
		}
		listFile << "\n";
		//

		//boyer moore (vector)	
		vectorFile << ",";
		for (j = 0; j < 3; j++)
		{

			the_clock::time_point start = the_clock::now();
			V_pos = Boyer_Moore_V(pat, txt);
			the_clock::time_point end = the_clock::now();
			size = V_pos.size();
			x = 0;

			cout << "\nBM Vector\n========\n\n";
			for (i = 0; i < size; i++)
			{
				cout << "Found: '" << pat << "' at position: " << V_pos[i] << "\n";		//loops through all of the items in the vector
				x++;
			}
	

			auto time_taken = duration_cast<nanoseconds>(end - start).count();
			cout << "\n" << time_taken << "\n";
			vectorFile << "" << time_taken << ",";
		}
		//
		vectorFile << "\n";

	}
	vectorFile.close();
	listFile.close();
	//return 0;
}