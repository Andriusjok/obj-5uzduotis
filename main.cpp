#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>
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
using std::setw;
bool Url(const string &word) {
	std::regex rgx("^(http[s]?:\\/\\/(www\\.)?|ftp:\\/\\/(www\\.)?|www\\.){1}([0-9A-Za-z-\\.@:%_\+~#=]+)+((\\.[a-zA-Z]{2,3})+)(/(.)*)?(\\?(.)*)?");
	return std::regex_match(word, rgx);
}
bool specialchar(char & a)
{
	if (std::isalpha(a) or std::isdigit(a) or a=="ą" or a=="č" or a=="ę" or a=="ė" or a=="į" or a=="š" or a=="ų" or a=="ū") {
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
	auto  maxCount=1;
	unsigned int maxWord=1;
		for (auto it = WordCounter.begin(), end = WordCounter.end(); it != end; it = WordCounter.upper_bound(it->first))
	{
		if (maxCount<WordCounter.count(it->first))
			maxCount=WordCounter.count(it->first);
		if (maxWord<it->first.length())
			maxWord=it->first.length();

	}

	ofile<<setw(maxWord+1)<<std::left<<"Zodis"<<setw(21)<<"pakartojimu skaicius"<<" "<<"eilutese"<<endl;	
	for(auto a=2;a<=maxCount;a++){
	for (auto it = WordCounter.begin(), end = WordCounter.end(); it != end; it = WordCounter.upper_bound(it->first))
	{

		if (WordCounter.count(it->first) ==a)
		{
			
			ofile<<setw(maxWord+1)<<std::left<< it->first <<setw(21)<<std::left<<WordCounter.count(it->first);
			for (auto itline = WordCounter.equal_range(it->first).first; itline != WordCounter.equal_range(it->first).second; ++itline) {
				auto o = itline;
				o--;
				if(o->second!=itline->second)
				ofile << ' ' << itline->second;
			}
			ofile << endl;
		
		}

	}
}
	ofile << "URLs: " << endl;
	for (auto it = links.begin(); it != links.end(); it++)
	{
		ofile << *(it) << endl;
	}
}