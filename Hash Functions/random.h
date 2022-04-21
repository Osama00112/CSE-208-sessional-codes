#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX = 26;
string randomString()
{
	string str = "AAAAAAA";
  
    // string sequence
	str[0] = rand() % 26 + 65;
	str[1] = rand() % 26 + 65;
	str[2] = rand() % 26 + 65;
	
    // number sequence
	str[3] = rand() % 10 + 48;
	str[4] = rand() % 10 + 48;
	str[5] = rand() % 10 + 48;

	return str;
}

string printRandomString(int n)
{
    char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
 
    string res = "";
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % MAX];
     
    return res;
}

static const char alphanum[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{

    return alphanum[rand() % 52];
}

string getRandomStr(int len){
    srand(time(0));
    string Str;
    for(unsigned int i = 0; i < len; ++i)
    {
    Str += genRandom();

    }
    return Str;
}

