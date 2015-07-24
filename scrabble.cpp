#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<fstream>
#include<algorithm>

using namespace std;


map <string,pair<vector<string>,int> > hashMap;
pair<vector<string>,int> maxValueString;

ifstream file;

string hash( string str );
int find_score(string s);
void combinations(char arr[], char data[], int start, int end, int index, int r);
void processDictionary( string filePath );



int main() {
    maxValueString.second = 0;
    processDictionary( "sowpods.txt" );

    int j,n;
    string input_str;
    getline(cin,input_str);
    n = input_str.length();

    char inputArray[n];

    for (int i=0;i<n;i++)
    {
     if (isspace(input_str[i]))
        inputArray[i] = '*';
     else
      inputArray[i] = input_str[i];
    }


    for (int r=n;r>1;r--)
    {
    char data[r];
    combinations(inputArray, data, 0, n-1, 0, r);
    }

    cout << "max score" << maxValueString.second << endl;

    for (j=0;j<maxValueString.first.size();j++)
    {
        cout << maxValueString.first[j] << endl;
    }
}


void processDictionary( string filePath )
{
    file.open( filePath.c_str() );
    string word;

    while( getline( file, word ))
    {
        string hashValue = hash( word );

        if ( hashMap.find( hashValue ) == hashMap.end() ) {
        pair<vector<string>,int> wordList;
        wordList.first.push_back(word);
        wordList.second = find_score(hashValue);;
        hashMap.insert( make_pair(hashValue,wordList) );
        }
        else {
            hashMap[ hashValue ].first.push_back( word);

        }

    }

}



string hash( string str ) {
   string sortedString = str;
   sort(sortedString.begin(),sortedString.end());
   return sortedString ;
}

int find_score(string s)
{
    int scores[26];
    for(int i=0;i<26;i++)
    {
        scores[i] = i+1;
    }
    int score=0;

    for (int i=0;i<s.length();i++)
    {
        score=score+scores[s[i]-'a'];
    }
    return score;
}


void combinations(char arr[], char data[], int start, int end, int index, int r)
{
    if (index == r)
    {
    	bool blankAbsent = true;
    	for (int i = 0; data[i]!='\0'; i++)
		{
			if (data[i] == '*')
			{
				blankAbsent = false;
				break;
			}
		}

    	if (blankAbsent)
    	{
    		string combString;
	        combString = data[0];

	        for (int j=1; j<r; j++)
	         {
	          combString = combString + data[j];
	         }

	        sort (combString.begin(),combString.end());

	        if (hashMap.find(combString)!=hashMap.end()) {
	            pair<vector<string>,int> tempPair = hashMap[combString];

	            if (tempPair.second  > maxValueString.second)
	               maxValueString = tempPair;
	        }

	        combString.clear();
		}
    	else
    	{

			for (char k='a'; k<='z'; k++)
			{
		        string combString;
		        combString = data[0];
		        for (int j=1; j<r; j++)
		         {
		       		if(data[j] == '*')
		       			combString = combString + k;
		       		else
		          		combString = combString + data[j];
		         }

		        sort(combString.begin(),combString.end());
		        if(hashMap.find(combString)!=hashMap.end()) {
		            pair<vector<string>,int> tempPair = hashMap[combString];
		            tempPair.second -= find_score(""+k);
		            if(tempPair.second > maxValueString.second)
		               maxValueString = tempPair;
		        }

		        combString.clear();
			}
		}
        return;
    }

    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinations(arr, data, i+1, end, index+1, r);
    }
}





