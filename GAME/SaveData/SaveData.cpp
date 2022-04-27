#include"SaveData.h"
#include <fstream>   // ifstream, ofstream
#include<iostream>

SaveData::SaveData()
{

}

SaveData::~SaveData()
{

}

void SaveData::Save(int scere)
{
	std::ofstream writing_file;
	writing_file.open("Resources/SaveData/SaveData.txt", std::ios::out);
	writing_file << scere;
	writing_file.close();
}

int SaveData::Road()
{
	std::ifstream ifs("Resources/SaveData/SaveData.txt");
	int data;
	ifs >> data;
	ifs.close();
	return data;
}