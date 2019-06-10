#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::multimap;
using std::vector;
bool Url(const string &word) {
	std::regex rgx("^(http[s]?:\\/\\/(www\\.)?|ftp:\\/\\/(www\\.)?|www\\.){1}([0-9A-Za-z-\\.@:%_\+~#=]+)+((\\.[a-zA-Z]{2,3})+)(/(.)*)?(\\?(.)*)?");
	return std::regex_match(word, rgx);
}
bool specialchar(char & a)
{
	if (std::isalpha(a) or std::isdigit(a)) {
		return false;
	} return true;
}
int main ()
{
	multimap<string, unsigned int> WordCounter;
	vector<string> links;
	string pav;
	cout << "Iveskite studentu failo pavadinima" << endl;
	cin >> pav;
	ifstream file(pav);
	if (!file)
	{
		cout << "Pavadinimas ivestas neteisingai" << endl;
		exit(EXIT_FAILURE);
	}
	unsigned int linenr = 1;
	while (!file.eof())
	{
		string line;
		getline(file, line);
		stringstream eil(line);
		string oneword;
		while (eil >> oneword) {
			std::transform(oneword.begin(), oneword.end(), oneword.begin(), ::tolower);
			if (Url(oneword)) {
				WordCounter.insert({ oneword, linenr });
				links.push_back(oneword);
			} else {
				oneword.erase(std::remove_if(oneword.begin(), oneword.end(), specialchar), oneword.end());
				if (!oneword.empty())
					WordCounter.insert({ oneword, linenr });
			}
		}
		linenr++;
	}
	file.close();
	ofstream ofile("rez" + pav);
	for (auto it = WordCounter.begin(), end = WordCounter.end(); it != end; it = WordCounter.upper_bound(it->first))
	{
		if (WordCounter.count(it->first) > 1)
		{
			ofile << " " << it->first << " pasikartojo " << WordCounter.count(it->first) << " kartus eilutese:";
			for (auto itline = WordCounter.equal_range(it->first).first; itline != WordCounter.equal_range(it->first).second; ++itline) {
				ofile << ' ' << itline->second;
			}
			ofile << endl;
		}
	}
	ofile << "URLs: " << endl;
	for (auto it = links.begin(); it != links.end(); it++)
	{
		ofile << *(it) << endl;
	}
}
