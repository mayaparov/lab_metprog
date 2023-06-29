#include "classes.h"


Street::Street(Data_Generator* generator)
{
	if (generator->m_dataset_size > 0)
	{
		//std::cout << "Generating a strreet\n";
		unsigned house_numbers = rand() % 150 + 23;
		for (unsigned i = 0; i < house_numbers; i++)
			this->m_HousesList.push_back(new House(generator));
	}
}



House::House(Data_Generator* generator)
{
	//std::cout << "Generating a house\n";
	srand(unsigned(time(0)));
	this->m_FloorsCount = rand() % 20 + 5;
	this->m_ApartPerFloor = rand() % 10;

	for (int i = 0; i < 5; i++) m_RoomsPerApart.push_back(0);

	for (int i = 0; i < m_ApartPerFloor; i++)//�� ������ ����� ���� ������������� ���������� �������, ���������� ���-�� ������ ��� ������ �������� �� �����
		this->m_RoomsPerApart[rand() % 5]++;

	unsigned apart_number = 1;
	//generate data for each apart
	for (;apart_number <= m_FloorsCount * m_ApartPerFloor; apart_number++)
	{
		std::vector<int>rooms_per_apart(m_RoomsPerApart);
		for (int j = 1; j <= m_ApartPerFloor; j++) //���������� �������� �� ��������� �����
		{
			int rooms;
			if (j <= rooms_per_apart[0]) rooms = 0;
			else if (j <= rooms_per_apart[0] + rooms_per_apart[1]) rooms = 1;
			else if (j <= rooms_per_apart[0] + rooms_per_apart[2] + rooms_per_apart[1]) rooms = 2;
			else if (j <= rooms_per_apart[0] + rooms_per_apart[1] + rooms_per_apart[2] + rooms_per_apart[3]) rooms = 3;
			else rooms = 4;
			aparts.push_back(new Apart(apart_number, rooms, generator, this));
			apart_number++;
		}
	}
}

Apart::Apart(unsigned apart_number, int rooms_number, Data_Generator* generator, House* house)
{
	srand(unsigned(time(0)));
	//std::cout << "Generating an apartment\n";
	residents_number = rooms_number + 1;
	m_number = apart_number;
	m_rooms_number = rooms_number;

	switch (rooms_number)
	{
	case 0:
		area = (rand() % 2 + 1) * 14;
		break;
	case 1:
		area = (rand() % 3 + 1) * 18;
		break;
	case 2:
		area = (rand() % 4 + 1) * 33;
		break;
	case 3:
		area = (rand() % 3 + 1) * 31;
		break;
	case 4:
		area = (rand() % 3 + 1) * 97;
		break;
	default:
		break;
	}

	generator->create_table_entry(house, this);

}

std::string Data_Generator::create_full_name()
{
	bool gender = rand() % 2;
	if (gender) return m_PossibleMaleFirstNames[rand() % m_PossibleMaleFirstNames.size()] + " " +
		m_PossibleMaleSecondNames[rand() % m_PossibleMaleSecondNames.size()] + " " + m_PossibleMalePatronymics[rand() % m_PossibleMalePatronymics.size() ];
	else return m_PossibleFemaleFirstNames[rand() % m_PossibleFemaleFirstNames.size()] + " " +
		m_PossibleFemaleSecondNames[rand() % m_PossibleFemaleSecondNames.size()] + " " + m_PossibleFemalePatronymics[rand() % m_PossibleFemalePatronymics.size() ];
}

void Data_Generator::create_table_entry(House* house, Apart* apart)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	srand(m_dataset_size % 97);
	//std::cout << "Generating an entry \n";
	f << rand() % 256 << '\t' << apart->m_number << '\t' <<
		apart->m_rooms_number << '\t' << apart->area << '\t' << create_full_name() << '\t' << apart->residents_number << '\n';
	this->m_dataset_size--;

	if (m_dataset_size <= 0)
	{
		f.close();
		exit(0);
	}

}

Data_Generator::Data_Generator(unsigned dataset_size)
{
	m_dataset_size = dataset_size;

	m_PossibleMaleFirstNames = { "���������", "������", "����", "�������", "�����", "������", "������", "������", "������", "������", "�����", "�������", "����", "��������", "�����", "�����", "����", "�������", "����", "���������", "��������", "����������", "�������", "����", "�����", "�������", "�����", "������", "�������", "�������", "������", "�������", "������", "������", "���", "�����", "��������", "�������", "�����", "�������", "����", "�����", "����", "������", "�������", "������", "��������", "������", "������", "������", "���������", "������", "������", "�����", "�����", "���", "�����", "�����", "�����", "��������", "�����", "������", "�����", "�������", "�����", "������", "�����", "�����", "Ը���", "����", "����", "����", "��", "����", "�����", "�������", "�����", "�������", "�����", "�����", "��������", "�������", "��������", "������", "�������", "��������" };
	m_PossibleMaleSecondNames = { "������", "�������", "��������", "�����", "�������", "�������", "������", "�������", "�������", "������", "������", "��������", "��������", "������", "������", "�������", "�������", "����������", "��������", "��������", "�������", "��������", "������", "�������", "�����", "�������", "�����", "�������", "�������", "�������", "�������", "�����", "�����", "�����", "�������", "���������", "�������", "�������", "��������", "�������", "����������", "������", "�����", "������", "��������", "������", "��������", "�������", "�������", "�������", "�������", "�������", "�������", "���������", "���������", "���������", "�������", "��������", "�����", "�������", "�������", "�����", "�������", "�������", "�������", "��������", "�������", "��������", "������", "������������", "��������", "��������", "��������", "��������", "�������", "������", "��������", "�������", "�������", "��������", "���������", "�������", "��������", "�������", "������", "���������", "���������", "��������", "�������" };
	m_PossibleMalePatronymics = { "�������������", "���������", "�����������", "���������", "����������", "����������", "���������", "���������", "������������", "����������", "����������", "����������", "����������", "������������", "�������������", "������������", "�����������", "����������", "�����������", "���������", "���������", "����������", "����������", "��������", "��������", "�����", "��������������", "����������", "����������", "����������", "�������", "����������", "��������", "��������", "��������", "���������", "���������", "���������", "�������������", "����������", "����������", "���������", "����������", "����������", "�������", "���������", "�����������" };

	m_PossibleFemaleFirstNames = { "����", "�����", "���������", "�����", "���������", "����������", "��������", "������", "�����", "������", "���������", "�������", "�������", "��������", "������", "�����", "������", "�����", "�����", "��������", "�����", "�������", "��������", "�������", "��������", "������", "�����", "����", "���������", "�������", "��������", "����", "�����", "���", "������", "�������", "������", "�������", "�����", "���������", "������", "�������", "�����", "�����", "�����", "����", "������", "��������", "����", "������", "������", "�����", "������", "����", "�����", "����", "�������", "��������", "������", "�����", "�����", "�����", "����", "������", "�����", "����", "���������", "������", "������", "������", "����", "������", "�������", "�����", "����", "������", "�����", "������", "�������", "�����", "������", "����", "�������", "������", "������", "����", "�����", "������", "������", "������", "������", "�������", "�����" };
	m_PossibleFemaleSecondNames = { "�������", "��������", "���������", "������", "��������", "��������", "�������", "��������", "��������", "�������", "�������", "���������", "���������", "�������", "�������", "��������", "��������", "�����������", "���������", "���������", "��������", "���������", "�������", "��������", "������", "��������", "������", "��������", "��������", "��������", "��������", "������", "������", "������", "��������", "����������", "��������", "��������", "���������", "��������", "�����������", "�������", "������", "�������", "���������", "�������", "���������", "��������", "��������", "��������", "��������", "��������", "��������", "����������", "����������", "����������", "��������", "���������", "������", "��������", "��������", "������", "��������", "��������", "��������", "���������", "��������", "���������", "�������", "�������������", "���������", "���������", "���������", "���������", "��������", "�������", "���������", "��������", "��������", "���������", "����������", "��������", "���������", "��������", "�������", "����������", "����������", "���������", "��������" };
	m_PossibleFemalePatronymics = { "�������������", "���������", "�����������", "���������", "���������", "���������", "������������", "����������", "����������", "����������", "����������", "������������", "�������������", "�����������", "����������", "���������", "����������", "����������", "��������", "��������" };
	if (dataset_size < 100 or dataset_size > 100000)
	{
		std::cout << "dataset_size can not be geater than 100000 and less than 100!\n";
		exit(1);
	}

	this->m_dataset_size = dataset_size;

	f.open("Datasets\\" + std::to_string(dataset_size) + ".xls", std::ios::out);

	if (!(f.is_open()))
	{
		//std::cout << "Can not create or open the file " << std::to_string(dataset_size) << ".xls !\n";
		exit(1);
	}

	f << "House number\t" << "Apartment number\t" << "Rooms number\t" << "Square\t" << "Owner's full name\t" << "Residents number\n";
	while (true)
	{
		//std::cout << "Start generating...\n";
		srand(unsigned(time(0)));
		Street sample_street(this);
	}
}
