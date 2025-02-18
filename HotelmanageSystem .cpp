#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "Hotelmanager.h"
using namespace std;
void addroom(vector<room>& rooms);
void addguest(vector<guest>& guests);
void modifyroom(vector<room>& rooms);
void modifyguest(vector<guest>& guests);
void searchroom(const vector<room>& rooms);
void searchguest(const vector<guest>& guests);
void deleteguest(vector<guest>& guests);
void deleteroom(vector<room>& rooms);
void backupsguest(vector<guest>& guests);
void backupsroom(vector<room>& rooms);
void initguest(vector<guest>& guests);
void initroom(vector<room>& rooms);
void report();
int menu()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                 ��ӭʹ�þƵ����ϵͳ                      |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                     ��ѡ����                            | " << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                    1.¼��ͷ���Ϣ                         |" << endl;
	cout << "|                    2.¼��ס����Ϣ                         |" << endl;
	cout << "|                    3.�޸Ŀͷ���Ϣ                         |" << endl;
	cout << "|                    4.�޸�ס����Ϣ                         |" << endl;
	cout << "|                    5.��ѯ�ͷ���Ϣ                         |" << endl;
	cout << "|                    6.��ѯס����Ϣ                         |" << endl;
	cout << "|                    7.ɾ��ס����Ϣ                         |" << endl;
	cout << "|                    8.ɾ���ͷ���Ϣ                         |" << endl;                 
	cout << "|                    9.��������                             |" << endl;
	cout << "|                    0.�˳���ϵͳ                           |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "ѡ��->";
	int s = -1;
	cin>>s;
		return s;
}
vector<guest>guests;
vector<room>rooms;
int main()
{
	initguest(guests);
	initroom(rooms);
	while (1)
	{
		switch (menu())
		{
		case 0:
			cout << "�ٴΰ��»س����˳��ó���" << endl;
			return 0;
			break;
		case 1:
			addroom(rooms);
			break;
		case 2:
			addguest(guests);
			break;
		case 3:
			modifyroom(rooms);
			break;
		case 4:
			modifyguest(guests);
			break;
		case 5:
			searchroom(rooms);
			break;
		case 6:
			searchguest(guests);
			break;
		case 7:
			deleteguest(guests);
			break;
		case 8:
			deleteroom(rooms);
			break;
		case 9:
			report();
			break;
		default:
			cout << "���벻�Ϲ棬���ٴ�����" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	
	return 0;
}
void initguest(vector<guest>& guests)
{
	ofstream outfile;
	outfile.open("guest.txt", ios::app);
	ifstream ifs("guest.txt");
	char c = 0;

	while(!ifs.eof())
	{
		guest g;
		while (ifs.get(c) && c != ' ')
		{
			g.name += c;
		}

		ifs >> g.id;

		ifs.get(c);
		while (ifs.get(c) && c != ' ')
		{
			g.gender += c;
		}

		ifs >> g.roomnum;

		ifs.get(c);
		while (ifs.get(c) && c != ' ')
		{
			g.dayin += c;
		}

		ifs >> g.day;

		ifs.get(c);
		if (ifs.eof()) break;
		guests.push_back(g);
	}
	ifs.close();
}
void initroom(vector<room>& rooms)
{
	ofstream outfile;
	outfile.open("room.txt", ios::app);
	ifstream ifs("room.txt");
	char c = 0;
	while (!ifs.eof())
	{
		room r;
		
		ifs >> r.num;
		

		ifs >> r.price;

		ifs.get(c);
		while (ifs.get(c) && c != ' ')
		{
			r.type+= c;
		}

		ifs >>r.discount;

		ifs.get(c);
		while (ifs.get(c) && c != ' ')
		{
			r.state += c;
		}

		ifs >>r.roompeople;
		ifs >> r.principal;
		ifs.get(c);
		if (ifs.eof()) break;
		rooms.push_back(r);
	}
	ifs.close();
}
void addroom(vector<room>&rooms)
{
	room newroom;
	cout << "������ͷ���:";
	cin >> newroom.num;
	cout << "������ͷ��۸�:";
	cin >> newroom.price;
	cout << "������ͷ�����:";
	cin >> newroom.type;
	cout << "������ͷ��ۿ�:";
	cin >> newroom.discount;
	cout << "������ͷ�״̬:";
	cin >> newroom.state;
	cout << "������ͷ��е�ס��:";
	cin >> newroom.roompeople;
	cout << "������ͷ�������:";
	cin >> newroom.principal;
	rooms.push_back(newroom);
	backupsroom(rooms);
	cout << "�ͷ���Ϣ¼��ɹ�" << endl;
	
}
void addguest(vector<guest>& guests)
{
	guest newguest;
	cout << "������ס������:";
	cin >> newguest.name;
	cout << "������ס�����֤��:";
	cin >> newguest.id;
	cout << "������ס���Ա�:";
	cin >> newguest.gender;
	cout << "������ס����ס�ķ����:";
	cin >> newguest.roomnum;
    cout << "������ס����סʱ��:";
	cin >> newguest.dayin;
	cout << "������ס��Ԥ����ס����:";
	cin >> newguest.day;
	guests.push_back(newguest);
	cout << "ס����Ϣ¼��ɹ���" << endl;
	
	backupsguest(guests);
	for (auto it = rooms.begin(); it != rooms.end(); it++)
	{
		if (it->num == newguest.roomnum)
		{
			it->roompeople = newguest.name;
			it->state = "����";
			backupsroom(rooms);
		}
	}

}
void modifyroom(vector<room>& rooms)
{
	int c;
	cout << "1.����ͷ��Ų��޸�" << endl;
	cout << "2.�������˵�" << endl;
	cout << "ѡ��->";
	cin >> c;
	if (c == 1)
	{
		cout << "������Ҫ�޸ĵĿͷ���:";
		int num;
		cin >> num;
		
		int s;
		for (auto& room : rooms)
		{
			
			if (room.num == num)
			{
				cout << "�ͷ���:" << room.num << endl;
				cout << "�ͷ�����:" << room.type << endl;
				cout << "�ͷ�ס��:" << room.roompeople << endl;
				cout << "�ͷ�״̬:" << room.state << endl;
				cout << "1.�ͷ��۸�:" << room.price << endl;
				cout << "2.�ͷ��ۿ�:" << room.discount << endl;
				cout << "3.�ͷ�������:" << room.principal << endl;
				cout << "0.�˳��޸Ĺ���" << endl;
				cout << "��ѡ��Ҫ�޸ĵ�����ǰ�����:";
				cin >> s;
					switch (s)
					{
					case 1:
						cout << "�������µĿͷ��۸�:";
						cin >> room.price;
						break;
					case 2:
						cout << "�������µĿͷ��ۿ�:";
						cin >> room.discount;				
						break;
					case 3:
						cout << "�������µĿͷ�������:";
						cin >> room.principal;
					
						break;
					case 0:
						cout << "�ٴΰ��»س����˳��޸Ĺ���" << endl;
						return;
						break;
					default:
						cout << "���������������������" << endl;
						return;
						break;
					}
					cout << "��Ϣ�޸ĳɹ�" << endl;
					backupsroom(rooms);
					return;
			}
			
		}
		cout << "δ�ҵ������Ϣ" << endl;
		return;
		
	}
	 if (c == 2)
	 {
		 cout << "�ٴΰ��»س����������˵�" << endl;
		 return;
	 }
	if(c!=1&&c!=2)
	{
		cout << "����ѡ������������ѡ��:" << endl;
		modifyroom(rooms);
	}
	
}
void modifyguest(vector<guest>& guests)
{
	cout << "��ѡ���޸ķ�ʽ:" << endl;
	cout << "1.��������ѯ���޸�" << endl;
	cout << "2.�����֤�Ų�ѯ���޸�" << endl;
	cout << "3.����ס�ͷ��Ų�ѯ���޸�" << endl;
	cout << "4.�������˵�" << endl;
	int c;
	int s;
	cout << "ѡ��->";
	cin >> c;
	if (c == 1)
	{
		cout << "������Ҫ�޸ĵ�ס������:";
		string name;
		cin >> name;
		for (auto& guest : guests)
		{

			if (guest.name == name)
			{
				cout << "1.ס������:" << guest.name << endl;
				cout << "2.ס�����֤��:" << guest.id << endl;
				cout << "3.ס���Ա�:" << guest.gender << endl;
				cout << "4.ס�ͷ���:" << guest.roomnum << endl;
				cout << "5.ס����סʱ��:" << guest.dayin << endl;
				cout << "6.ס��Ԥ����ס����:" << guest.day << endl;
				cout << "0.�˳��޸Ĺ���" << endl;
				cout << "��ѡ��Ҫ�޸ĵ�����ǰ�����:";
				cin >> s;
				switch (s)
				{
				case 1:
					cout << "�������µ�ס������:";
					cin >> guest.name;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							backupsroom(rooms);
						}
					}
					break;
				case 2:
					cout << "�������µ�ס�����֤��:";
					cin >> guest.id;
					break;
				case 3:
					cout << "�������µ�ס���Ա�:";
					cin >> guest.gender;
					break;
				case 4:
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = "��";
							it->state = "����";
							backupsroom(rooms);
						}
					}
					cout << "�������µ�ס�ͷ����:";
					cin >> guest.roomnum;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							it->state = "����";
							backupsroom(rooms);
						}
					}
					break;
				case 5:
					cout << "�������µ�ס����סʱ��:";
					cin >> guest.dayin;				
					break;
				case 6:
					cout << "�������µ�ס��Ԥ����ס����:";
					cin >> guest.day;
					break;
				case 0:
					cout << "�ٴΰ��»س����˳��޸Ĺ���";
					return;
					break;
				default:
					cout << "���������������������" << endl;
					return;
					break;
				}
				cout << "��Ϣ�޸ĳɹ�" << endl;
				backupsguest(guests);
				return;
			}
		}
		cout << "δ�ҵ������Ϣ" << endl;
		return;
	}
	if (c == 2)
	{
		cout << "������Ҫ�޸ĵ�ס�����֤��:";
		int id;
		cin >> id;
		for (auto& guest : guests)
		{

			if (guest.id == id)
			{
				cout << "1.ס������:" << guest.name << endl;
				cout << "2.ס�����֤��:" << guest.id << endl;
				cout << "3.ס���Ա�:" << guest.gender << endl;
				cout << "4.ס�ͷ���:" << guest.roomnum << endl;
				cout << "5.ס����סʱ��:" << guest.dayin << endl;
				cout << "6.ס��Ԥ����ס����:" << guest.day << endl;
				cout << "0.�˳��޸Ĺ���" << endl;
				cout << "��ѡ��Ҫ�޸ĵ�����ǰ�����:";
				cin >> s;
				switch (s)
				{
				case 1:
					cout << "�������µ�ס������:";
					cin >> guest.name;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							backupsroom(rooms);
						}
					}
					break;
				case 2:
					cout << "�������µ�ס�����֤��:";
					cin >> guest.id;
					break;
				case 3:
					cout << "�������µ�ס���Ա�:";
					cin >> guest.gender;
					break;
				case 4:
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = "��";
							it->state = "����";
							backupsroom(rooms);
						}
					}
					cout << "�������µ�ס�ͷ����:";
					cin >> guest.roomnum;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							it->state = "����";
							backupsroom(rooms);
						}
					}
					break;
				case 5:
					cout << "�������µ�ס����סʱ��:";
					cin >> guest.dayin;
					break;
				case 6:
					cout << "�������µ�ס��Ԥ����ס����:";
					cin >> guest.day;
					break;
				case 0:
					cout << "�ٴΰ��»س����˳��޸Ĺ���";
					return;
					break;
				default:
					cout << "���������������������" << endl;
					return;
					break;
				}
				cout << "��Ϣ�޸ĳɹ�" << endl;
				backupsguest(guests);
				return;
			}
		}
		cout << "δ�ҵ������Ϣ" << endl;
		return;
	}
	if (c == 3)
	{
		cout << "������Ҫ�޸ĵ�ס�Ϳͷ���:";
		int roomnum;
		cin >> roomnum;
		for (auto& guest : guests)
		{

			if (guest.roomnum == roomnum)
			{
				cout << "1.ס������:" << guest.name << endl;
				cout << "2.ס�����֤��:" << guest.id << endl;
				cout << "3.ס���Ա�:" << guest.gender << endl;
				cout << "4.ס�ͷ���:" << guest.roomnum << endl;
				cout << "5.ס����סʱ��:" << guest.dayin << endl;
				cout << "6.ס��Ԥ����ס����:" << guest.day << endl;
				cout << "0.�˳��޸Ĺ���" << endl;
				cout << "��ѡ��Ҫ�޸ĵ�����ǰ�����:";
				cin >> s;
				switch (s)
				{
				case 1:
					cout << "�������µ�ס������:";
					cin >> guest.name;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							backupsroom(rooms);
						}
					}
					break;
				case 2:
					cout << "�������µ�ס�����֤��:";
					cin >> guest.id;
					break;
				case 3:
					cout << "�������µ�ס���Ա�:";
					cin >> guest.gender;
					break;
				case 4:
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num ==guest.roomnum )
						{
							it->roompeople = "��";
							it->state = "����";
							backupsroom(rooms);
						}
					}
					cout << "�������µ�ס�ͷ����:";
					cin >> guest.roomnum;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							it->state = "����";
							backupsroom(rooms);
						}
					}
					break;
				case 5:
					cout << "�������µ�ס����סʱ��:";
					cin >> guest.dayin;
					break;
				case 6:
					cout << "�������µ�ס��Ԥ����ס����:";
					cin >> guest.day;
					break;
				case 0:
					cout << "�ٴΰ��»س����˳��޸Ĺ���";
					return;
					break;
				default:
					cout << "���������������������" << endl;
					return;
					break;
				}
				cout << "��Ϣ�޸ĳɹ�" << endl;
				backupsguest(guests);
				return;
			}
		}
		cout << "δ�ҵ������Ϣ" << endl;
		return;
	}
	if (c == 4)
	{
		cout << "�ٴΰ��»س����������˵�" << endl;
		return;
	}
	else
	{
		cout << "����ѡ������������ѡ��:" << endl;
		modifyguest(guests);
	}
	
}
void searchroom(const vector<room>& rooms)
{
	cout << "��ѡ���ѯ��ʽ" << endl;
	cout << "1.���տͷ��Ų�ѯ" << endl;
	cout << "2.���տͷ�״̬��ѯ" << endl;
	cout << "3.���ռ۸��ѯ" << endl;
	cout << "4.�������˵�" << endl;
	cout << "ѡ��->";
	int c ;
	cin >> c;
	if (c == 1)
	{
		int num;
		cout << "������Ҫ��ѯ�Ŀͷ���:";
		cin >> num;
		for (const auto& room : rooms)
		{
			if (room.num == num)
			{
				cout << "�ͷ���:" << room.num << endl;
				cout << "�ͷ��۸�:" << room.price << endl;
				cout << "�ͷ�����:" << room.type << endl;
				cout << "�ͷ��ۿ�:" << room.discount << endl;
				cout << "�ͷ�״̬:" << room.state << endl;
				cout << "�ͷ�ס��:" << room.roompeople << endl;
				cout << "�ͷ�������:" << room.principal << endl;
				return;
			}
		}
		cout << "δ��ѯ�������Ϣ" << endl;
		return;
	}
	if (c == 2)
	{
		string state;
		cout << "�������ѯ�Ŀͷ�״̬:";
		cin >> state;
		bool found = true;
		for (const auto& room : rooms)
		{
			if (room.state == state)
			{
				cout << "�ͷ���:" << room.num << endl;
				cout << "�ͷ��۸�:" << room.price << endl;
				cout << "�ͷ�����:" << room.type << endl;
				cout << "�ͷ��ۿ�:" << room.discount << endl;
				cout << "�ͷ�״̬:" << room.state << endl;
				cout << "�ͷ�ס��:" << room.roompeople << endl;
				cout << "�ͷ�������:" << room.principal << endl;
				cout << endl;
			}
		}
		if (!found)
		{
			cout << "δ��ѯ�������Ϣ" << endl;
			return;
		}
	}
	if (c == 3)
	{
		int price;
		cout << "�������ѯ�Ŀͷ��۸�:";
		cin >> price;
		bool found = true;
		for (const auto& room : rooms)
		{
			if (room.price == price)
			{
				cout << "�ͷ���:" << room.num << endl;
				cout << "�ͷ��۸�:" << room.price << endl;
				cout << "�ͷ�����:" << room.type << endl;
				cout << "�ͷ��ۿ�:" << room.discount << endl;
				cout << "�ͷ�״̬:" << room.state << endl;
				cout << "�ͷ�ס��:" << room.roompeople << endl;
				cout << "�ͷ�������:" << room.principal << endl;
				cout << endl;
				
			}
		}
		if (!found)
		{
			cout << "δ��ѯ�������Ϣ" << endl;
			return;
		}
	}
	if (c == 4)
	{
		cout << "�ٴΰ��»س����������˵�" << endl;
		return;
	}
	
	if(c!=1&&c!=2&&c!=3&&c!=4)
	{
		cout << "����ѡ������������ѡ��:" << endl;
		searchroom(rooms);
	}
}
void searchguest(const vector<guest>& guests)
{
	cout << "��ѡ���ѯ��ʽ" << endl;
	cout << "1.����������ѯ" << endl;
	cout << "2.�������֤�Ų�ѯ" << endl;
	cout << "3.������ס�ͷ��Ų�ѯ" << endl;
	cout << "4.�������˵�" << endl;
	cout << "ѡ��->";
	int c;
	cin >> c;
	if (c == 1)
	{
		cout << "������Ҫ��ѯ������:";
		string name;
		cin >> name;
		for (const auto& guest : guests)
		{
			if (guest.name == name)
			{
				cout << "ס������:" << guest.name << endl;
				cout << "ס�����֤��:" << guest.id << endl;
				cout << "ס���Ա�:" << guest.gender << endl;
				cout << "ס�ͷ���:" << guest.roomnum << endl;
				cout << "ס����סʱ��:" << guest.dayin << endl;
				cout << "ס��Ԥ����ס����:" << guest.day << endl;
				return;
			}
		}
		cout << "δ��ѯ�������Ϣ" << endl;
		return;
    }

	if (c == 2)
	{
		cout << "������Ҫ��ѯ�����֤��:";
		long long id;
		cin >> id;
		for (const auto& guest : guests)
		{
			if (guest.id == id)
			{
				cout << "ס������:" << guest.name << endl;
				cout << "ס�����֤��:" << guest.id << endl;
				cout << "ס���Ա�:" << guest.gender << endl;
				cout << "ס�ͷ���:" << guest.roomnum << endl;
				cout << "ס����סʱ��:" << guest.dayin << endl;
				cout << "ס��Ԥ����ס����:" << guest.day << endl;
				return;
			}
		}
		cout << "δ��ѯ�������Ϣ" << endl;
		return;
	}
	if (c == 3)
	{
		cout << "������Ҫ��ѯ����ס�ͷ�:";
		int roomnum;
		cin >> roomnum;
		for (const auto& guest : guests)
		{
			if (guest.roomnum == roomnum)
			{
				cout << "ס������:" << guest.name << endl;
				cout << "ס�����֤��:" << guest.id << endl;
				cout << "ס���Ա�:" << guest.gender << endl;
				cout << "ס�ͷ���:" << guest.roomnum << endl;
				cout << "ס����סʱ��:" << guest.dayin << endl;
				cout << "ס��Ԥ����ס����:" << guest.day << endl;
				return;
			}
		}
		cout << "δ��ѯ�������Ϣ" << endl;
		return;
	}
	if (c == 4)
	{
		cout << "�ٴΰ��»س����������˵�" << endl;
		return;
	}
	else
	{
		cout << "����ѡ������������ѡ��:" << endl;
		searchguest(guests);
	}

}
void deleteguest(vector<guest>& guests)
{
	cout << "��ѡ��ɾ����ʽ" << endl;
	cout << "1.��������ɾ��" << endl;
	cout << "2.�������֤��ɾ��" << endl;
	cout << "3.������ס�ͷ���ɾ��" << endl;
	cout << "4.�������˵�" << endl;
	cout << "ѡ��->";
	int c ;
	cin >> c;
	if (c == 1)
	{
		cout << "������Ҫɾ����ס�͵�����:";
		string name;
		cin >> name;
		for (auto it = guests.begin(); it != guests.end(); it++)
		{
			if (it->name == name)
			{
				guests.erase(it);
				cout << "��ס����Ϣɾ���ɹ�" << endl;
				backupsguest(guests);
				for (auto it = rooms.begin(); it != rooms.end(); it++)
				{
					if (it->roompeople == name)
					{
						it->roompeople = "��";
						it->state = "����";
						backupsroom(rooms);
					}
				}
				return;
			}
		}

		cout << "δ�ҵ���ס����Ϣ" << endl;
		return;
	}
	if (c == 2)
	{
		cout << "������Ҫɾ����ס�͵����֤��:";
		int id;
		cin >> id;
		for (auto it = guests.begin(); it != guests.end(); it++)
		{
			if (it->id == id)
			{
				string name = it->name;
				guests.erase(it);
				cout << "��ס����Ϣɾ���ɹ�" << endl;
				backupsguest(guests);
				for (auto it = rooms.begin(); it != rooms.end(); it++)
				{
					if (it->roompeople == name)
					{
						it->roompeople = "��";
						it->state = "����";
						backupsroom(rooms);
					}
				}
				return;
			}
		}
		cout << "δ�ҵ���ס����Ϣ" << endl;
	}
	if (c == 3)
	{
		cout << "������Ҫɾ����ס����ס�ķ���:";
		int roomnum;
		cin >> roomnum;
		for (auto it = guests.begin(); it != guests.end(); it++)
		{
			if (it->roomnum == roomnum)
			{
				string name = it->name;
				guests.erase(it);
				cout << "��ס����Ϣɾ���ɹ�" << endl;
				backupsguest(guests);
				for (auto it = rooms.begin(); it != rooms.end(); it++)
				{
					if (it->roompeople == name)
					{
						it->roompeople = "��";
						it->state = "����";
						backupsroom(rooms);
					}
				}
				return;
			}
		}
		cout << "δ�ҵ���ס����Ϣ" << endl;
		return;
	}
	if (c == 4)
	{
		cout << "�ٴΰ��»س����������˵�" << endl;
		return;
	}
	else
	{
		cout << "����ѡ������������ѡ��:" << endl;
		deleteguest(guests);
	}

}
void deleteroom(vector<room>& rooms)
{

	int c;
	cout << "1.����ͷ��Ų�ɾ��" << endl;
	cout << "2.�������˵�" << endl;
	cout << "ѡ��->";
	cin >> c;
	if (c == 1)
	{
		cout << "������Ҫɾ���Ŀͷ���:";
		int num;
		cin >> num;
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it->num ==num )
			{
				rooms.erase(it);
				cout << "�ÿͷ���Ϣɾ���ɹ�" << endl;
				backupsroom(rooms);
				return;
			}
		}
		cout << "δ�ҵ��ÿͷ���Ϣ" << endl;
		return;
	}
	if (c == 2)
	{
		cout << "�ٴΰ��»س����������˵�" << endl;
		return;
	}
	else
	{
		cout << "����ѡ������������ѡ��:" << endl;
		deleteroom(rooms);
	}

}
void backupsguest(vector<guest>& guests)			
{
	
	ofstream ofs;
	ofs.open("guest.txt" ,ios::out);
	for (int i = 0; i < guests.size(); i++)
	{
		ofs << guests[i].name <<" "<< guests[i].id <<" " << guests[i].gender 
		<<" " << guests[i].roomnum<<" " << guests[i].dayin << " " << guests[i].day << endl;
	}
	ofs.close();
}
void backupsroom(vector<room>& rooms)
{

	ofstream ofs;
	ofs.open("room.txt", ios::out);
	for (int i = 0; i < rooms.size(); i++)
	{
		ofs << rooms[i].num << " " << rooms[i].price << " " << rooms[i].type
			<< " " << rooms[i].discount<< " " << rooms[i].state<< " " << rooms[i].roompeople<<" "<<rooms[i].principal << endl;
	}

	ofs.close();
}
void report()
{

	system("cls");
	cout << setw(56) << "�ͷ�����" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << '|' << "�ͷ���   " << '|' << "�ͷ�����   " << '|' << "�ͷ��۸�   " << '|' << "�ͷ��ۿ�   " << '|' << "�ͷ�״̬   " << '|' << "�ͷ�ס��      " << '|' << "�ͷ�������" << '|' << "��סʱ�������� " << '|' << "Ӫҵ��   " << '|' << endl;
	int money;
	string dayin;
	int day;
	for (int i = 0; i < rooms.size(); i++)
	{
		for (auto it = guests.begin(); it != guests.end(); it++)
		{
			if (it->name == rooms[i].roompeople)
			{
				money = rooms[i].price * (rooms[i].discount / 10) * (it->day);
				dayin = it->dayin;
				day = it->day;
				break;
			}
			else
			{
				dayin = "��";
				day = 0;
				money = 0;
			}
		}
		cout << '|' << left << setw(9) << rooms[i].num;
		cout << '|' << left << setw(11) << rooms[i].type;
		cout << '|' << left << setw(11) << rooms[i].price;
		cout << '|' << left << setw(11) << rooms[i].discount;
		cout << '|' << left << setw(11) << rooms[i].state;
		cout << '|' << left << setw(14) << rooms[i].roompeople;
		cout << '|' << left << setw(10) << rooms[i].principal;
		cout << '|' << left << setw(10) << dayin << setw(5) << day;
		cout << '|' << left << setw(9) << money << '|' << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}


