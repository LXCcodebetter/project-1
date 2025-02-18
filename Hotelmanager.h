#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
int menu();
class guest
{
public:
	string name;
	long long id=0;
	int roomnum=0;
	string gender;
	string dayin;
	int day=0;
};
class room
{
public:
	int num=0;
	int price=0;
	string type;
	string roompeople;
	float discount=0;
	string state;
	string principal;

};
