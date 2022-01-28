#include <iostream>
#include "queue.h"
#include <string>
#include <fstream>
#include <sstream>
#include "AVL.h"
#include "Hash.h"
#include "List.h"
using namespace std;

class EventNode
{
public:
	unsigned long int event_id;
	int year;
	int month;
	int day;
	bool ext_24hour;
	int country_id;
	string country_name;
	int region_id;
	string region_txt;
	string prov_state; //
	string city;
	string summary;
	bool success;
	int suicide;
	int attack_id;
	string attack_type_desc;
	int target_id;
	string target_type_desc;
	string target_name;
	string group_name;
	string motive; //
	int weapontype_id;
	string weapontype_desc;
	string weapon_detail;	   //
	unsigned long kills;	   //
	unsigned long wounded;	   //
	string prop_damage_amount; //
	unsigned long prop_value;  //
	string prop_desc;		   //
	bool ransom;
	unsigned long ransom_amount; //
	friend bool operator>(EventNode e1, EventNode e2)
	{
		return e1.event_id > e2.event_id;
	};
	friend bool operator<(EventNode e1, EventNode e2)
	{
		return e1.event_id < e2.event_id;
	};
	friend bool operator==(EventNode e1, EventNode e2)
	{
		return e2.event_id == e2.event_id;
	};
	friend bool operator!=(EventNode e1, EventNode e2)
	{
		return e2.event_id != e2.event_id;
	}
	friend ostream &operator<<(ostream &output, EventNode &E)
	{
		output << "\nEvent Id: " << E.event_id << endl;
		return output;
	}
};



class CountryNode
{
public:
	AVL<EventNode> event_root; // root node of tree
	string countryName;
	int countryID;
	CountryNode() : event_root() {}
	friend bool operator<(CountryNode, CountryNode);
	friend bool operator>(CountryNode, CountryNode);
	friend ostream &operator<<(ostream &output, CountryNode &C);
	friend bool operator==(CountryNode, CountryNode);
	friend bool operator!=(CountryNode, CountryNode);
};

bool operator>(CountryNode c1, CountryNode c2)
{
	return c1.countryID > c2.countryID;
}
bool operator<(CountryNode c1, CountryNode c2)
{
	return c1.countryID < c2.countryID;
}
bool operator==(CountryNode c1, CountryNode c2)
{
	return c1.countryID == c2.countryID;
}
bool operator!=(CountryNode c1, CountryNode c2)
{
	return c1.countryID != c2.countryID;
}
ostream &operator<<(ostream &output, CountryNode &C)
{
	output << "Country Name :: " << C.countryName << "\tCountry ID :: " << C.countryID;
	return output;
}

void PrintHash(string name, HashTable<CountryNode> &list)
{
	int index = list.getIndex(name);
	if (index != -1)
	{
		auto itr = list.hashTable[index].list.begin();

		for (; itr != list.hashTable[index].list.end(); itr++)
		{
			cout << "Value exists in the Hash table with following details \n";
			cout << "Country Name :: " << itr.currentNode->data.countryName << endl;
			cout << "Country ID :: " << itr.currentNode->data.countryID << endl;
		}
	}
	else
	{
		cout << "Value does not exist in hash table";
	}
}
void Print(string name, HashTable<CountryNode> &list)
{
	auto itr = list.hashTable[0].list.begin();

	for (; itr != list.hashTable[1499].list.end(); itr++)
	{
		cout << "Value exists in the Hash table with following details ";
		cout << itr.currentNode->data.countryName << endl;
	}
}
//HashTable<CountryNode> &list,
void Parse(AVL<EventNode> &x, HashTable<CountryNode> &list)
{
	int count = 0;
	ifstream myFileStream;
	myFileStream.open("terror2.csv"); // open selected file
	if (myFileStream.fail())
		cout << "File does not exist" << endl; // Show error message if the file failed to open
	string line;
	getline(myFileStream, line); // reading a single line from csv
	cout << "Enter number of records to parse: ";
	long num;
	cin >> num;
	while (num < 1 && num > 181691)
	{
		cout << "\nEnter a valid number between 1 to 181691: ";
		cin >> num;
	}
	for (long i = 0; i < num; i++)
	{
		getline(myFileStream, line); // reading a single line from csv
		EventNode m;
		stringstream ss(line); // breaking a complete line into single attributes
		string temp;
		getline(ss, temp, '|');
		m.event_id = stoul(temp);
		getline(ss, temp, '|');
		m.year = stoi(temp);
		getline(ss, temp, '|');
		m.month = stoi(temp);
		getline(ss, temp, '|');
		m.day = stoi(temp);
		getline(ss, temp, '|');
		if (stoi(temp) == 0 || temp.empty())
			m.ext_24hour = false;
		else
			m.ext_24hour = true;
		getline(ss, temp, '|');
		m.country_id = stoi(temp);
		getline(ss, temp, '|');
		m.country_name = temp;
		getline(ss, temp, '|');
		m.region_id = stoi(temp);
		getline(ss, temp, '|');
		m.region_txt = temp;
		getline(ss, temp, '|');
		if (temp.empty())
			m.prov_state = "N\\A";
		else
			m.prov_state = temp;
		getline(ss, temp, '|');
		m.city = temp;
		getline(ss, temp, '|');
		if (temp.empty())
			m.summary = "N\\A";
		else
			m.summary = temp;
		getline(ss, temp, '|');
		if (temp == "0")
			m.success = true;
		else
			m.success = false;
		getline(ss, temp, '|');
		m.suicide = stoi(temp);
		getline(ss, temp, '|');
		m.attack_id = stoi(temp);
		getline(ss, temp, '|');
		m.attack_type_desc = temp;
		getline(ss, temp, '|');
		m.target_id = stoi(temp);
		getline(ss, temp, '|');
		m.target_type_desc = temp;
		getline(ss, temp, '|');
		m.target_name = temp;
		getline(ss, temp, '|');
		m.group_name = temp;
		getline(ss, temp, '|');
		if (temp.empty())
			m.motive = "N\\A";
		else
			m.motive = temp;
		getline(ss, temp, '|');
		m.weapontype_id = stoi(temp);
		getline(ss, temp, '|');
		m.weapontype_desc = temp;
		getline(ss, temp, '|');
		if (temp.empty())
			m.weapon_detail = "N\\A";
		else
			m.weapon_detail = temp;
		getline(ss, temp, '|');
		if (temp.empty())
			m.kills = 0;
		else
			m.kills = stoul(temp);
		getline(ss, temp, '|');
		if (temp.empty())
			m.wounded = 0;
		else
			m.wounded = stoul(temp);
		getline(ss, temp, '|');
		if (temp.empty())
			m.prop_damage_amount = "N\\A";
		else
			m.prop_damage_amount = temp;
		getline(ss, temp, '|');
		if (temp.empty())
			m.prop_value = 0;
		else
			m.prop_value = stoul(temp);
		getline(ss, temp, '|');
		if (temp.empty())
			m.prop_desc = "N\\A";
		else
			m.prop_desc = temp;
		getline(ss, temp, '|');
		if (temp == "0")
			m.ransom = false;
		else
			m.ransom = true;
		getline(ss, temp, '|');
		if (temp.empty())
			m.ransom_amount = 0;
		else
			m.ransom_amount = stoul(temp);

		CountryNode country;
		country.countryID = m.country_id;
		country.countryName = m.country_name;

		list.quadraticHashInsert(country.countryName, country);
		x.insert(m, x.root); // creation of event tree
	}
}
//  list.doubleHashInsert(country.countryName,country);
//list.displayHash();
//PrintHash("Pakistan",list);
// list.displayHash();
int main()
{
	cout << "\n\t\tWELCOME TO DSA PROJECT\n\n\n";
	cout << "This project is based on terrorism events dataset.\n\n\n";
	cout << "For fast searching AVL data structure is primarily used for fast searching and accessing nodes.\n";
	cout << "The values are of country nodes are stored in a HashTable data structure\n\n";
	int x = 0;
	string name;
	AVL<EventNode> *tree = new AVL<EventNode>();
	cout << "Please select number of buckets for HashTable :: ";
	cin >> x;
	HashTable<CountryNode> country_list(x);
	Parse(*tree, country_list);
	int instruction = 0;
	while (instruction != -1)
	{
		cout << "\n1.Print a particular hash value\n";
		cout << "2.Print the complete hash\n";
		cout << "3.Exit\n";
		cout << "Type instruction number :: ";
		cin >> instruction;
		switch (instruction)
		{
		case 1:
			cout << "\nEnter country name :: ";
			cin >> name;
			PrintHash(name, country_list);
			break;
		case 2:
			country_list.displayHash();
			break;
		case 3:
			instruction = -1;
			break;
		}
	}
}
