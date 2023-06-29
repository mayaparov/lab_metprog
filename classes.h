#pragma once
#include<vector>
#include<string>
#include <fstream>
#include<iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
class Apart;
class House
{
	friend class Data_Generator;

public:

	int m_FloorsCount;
	int m_ApartPerFloor;
	//unsigned long long m_ResidentsNumber;
	std::vector<int> m_RoomsPerApart; //in m_RoomsPerApart[0] - the number of studios per floor,
	//in m_RoomsPerApart[1] - the number of one-room apartments per floor, and so on
	std::vector<Apart*> aparts;
	House(Data_Generator* generator);
};

class Street
{
public:

	std::vector<House*> m_HousesList;
	Street(Data_Generator* generator);
};


class Apart
{
	friend class Data_Generator;
public:
	unsigned m_number;
	int area;
	int residents_number;
	int m_rooms_number;
	Apart(unsigned apart_number, int rooms_number, Data_Generator* generator, House* house);
};

class Data_Generator
{
public:
	Street* street;

	std::vector<std::string> m_PossibleMaleFirstNames;
	std::vector<std::string> m_PossibleMaleSecondNames;
	std::vector<std::string> m_PossibleMalePatronymics;

	std::vector<std::string> m_PossibleFemaleFirstNames;
	std::vector<std::string> m_PossibleFemaleSecondNames;
	std::vector<std::string> m_PossibleFemalePatronymics;

	unsigned m_dataset_size;

	std::ofstream f;

	std::string create_full_name();
	void create_table_entry(House* house, Apart* apart);
	Data_Generator(unsigned dataset_size);
	
	bool generate();
};


