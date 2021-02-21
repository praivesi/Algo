#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;

vector<int> primes;
vector<int> cipher;
vector<int> plainPrimes;
vector<int> selectedPrimes;

int n, l;
string result;

void decrypt();
void getPrimes();
bool isPrime(int number);
char decryptCharacter(int prime);

int main()
{
	int caseNum, c;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Initialize
		primes.clear();
		cipher.clear();
		plainPrimes.clear();
		selectedPrimes.clear();
		result = "";

		// Input
		cin >> n >> l;

		for (int i = 0; i < l; i++)
		{
			cin >> c;
			cipher.push_back(c);
		}

		// Process
		decrypt();

		// Output
		cout << "CASE #"  << (cIter + 1) << ": " << result << endl << flush;
	}
	_getch();
}

void decrypt()
{
	getPrimes();

	int firstPrime = 0, secondPrime;
	for (int i = 0; i < primes.size(); i++)
	{
		for (int j = 0; j < primes.size(); j++)
		{
			if (primes[i] * primes[j] == cipher[0])
			{
				plainPrimes.push_back(primes[i]);
				plainPrimes.push_back(primes[j]);

				i = primes.size();
				break;
			}
		}
	}
	
	bool isValidFlag = true;
	int firstP = plainPrimes[0];
	int secondP = plainPrimes[1];

	for (int i = 1; i < cipher.size(); i++)
	{
		int tmpPrime = cipher[i] / plainPrimes[i];

		if (tmpPrime < 2)
		{
			isValidFlag = false;
			break;
		}

		plainPrimes.push_back(tmpPrime);
	}

	if (isValidFlag == false)
	{
		plainPrimes.clear();
		plainPrimes.push_back(secondP);
		plainPrimes.push_back(firstP);

		for (int i = 1; i < cipher.size(); i++)
			plainPrimes.push_back(cipher[i] / plainPrimes[i]);
	}

	selectedPrimes = plainPrimes;
	sort(selectedPrimes.begin(), selectedPrimes.end());
	selectedPrimes.erase(unique(selectedPrimes.begin(), selectedPrimes.end()), selectedPrimes.end());

	for(auto prime : plainPrimes)
		result += decryptCharacter(prime);
}

void getPrimes()
{
	for (int num = 3; num <= n; num++)
		if (isPrime(num)) primes.push_back(num);
}

bool isPrime(int number)
{
	for (int i = 2; i < number; i++)
		if (number % i == 0) return false;

	return true;
}

char decryptCharacter(int prime)
{
	if (prime == selectedPrimes[0]) return 'A';
	else if (prime == selectedPrimes[1]) return 'B';
	else if (prime == selectedPrimes[2]) return 'C';
	else if (prime == selectedPrimes[3]) return 'D';
	else if (prime == selectedPrimes[4]) return 'E';
	else if (prime == selectedPrimes[5]) return 'F';
	else if (prime == selectedPrimes[6]) return 'G';
	else if (prime == selectedPrimes[7]) return 'H';
	else if (prime == selectedPrimes[8]) return 'I';
	else if (prime == selectedPrimes[9]) return 'J';
	else if (prime == selectedPrimes[10]) return 'K';
	else if (prime == selectedPrimes[11]) return 'L';
	else if (prime == selectedPrimes[12]) return 'M';
	else if (prime == selectedPrimes[13]) return 'N';
	else if (prime == selectedPrimes[14]) return 'O';
	else if (prime == selectedPrimes[15]) return 'P';
	else if (prime == selectedPrimes[16]) return 'Q';
	else if (prime == selectedPrimes[17]) return 'R';
	else if (prime == selectedPrimes[18]) return 'S';
	else if (prime == selectedPrimes[19]) return 'T';
	else if (prime == selectedPrimes[20]) return 'U';
	else if (prime == selectedPrimes[21]) return 'V';
	else if (prime == selectedPrimes[22]) return 'W';
	else if (prime == selectedPrimes[23]) return 'X';
	else if (prime == selectedPrimes[24]) return 'Y';
	else if (prime == selectedPrimes[25]) return 'Z';
	else return ' ';
}