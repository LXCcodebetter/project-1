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
	cout << "|                 欢迎使用酒店管理系统                      |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                     请选择功能                            | " << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                    1.录入客房信息                         |" << endl;
	cout << "|                    2.录入住客信息                         |" << endl;
	cout << "|                    3.修改客房信息                         |" << endl;
	cout << "|                    4.修改住客信息                         |" << endl;
	cout << "|                    5.查询客房信息                         |" << endl;
	cout << "|                    6.查询住客信息                         |" << endl;
	cout << "|                    7.删除住客信息                         |" << endl;
	cout << "|                    8.删除客房信息                         |" << endl;                 
	cout << "|                    9.报表生成                             |" << endl;
	cout << "|                    0.退出该系统                           |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "选择->";
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
			cout << "再次按下回车键退出该程序" << endl;
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
			cout << "输入不合规，请再次输入" << endl;
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
	cout << "请输入客房号:";
	cin >> newroom.num;
	cout << "请输入客房价格:";
	cin >> newroom.price;
	cout << "请输入客房类型:";
	cin >> newroom.type;
	cout << "请输入客房折扣:";
	cin >> newroom.discount;
	cout << "请输入客房状态:";
	cin >> newroom.state;
	cout << "请输入客房中的住客:";
	cin >> newroom.roompeople;
	cout << "请输入客房负责人:";
	cin >> newroom.principal;
	rooms.push_back(newroom);
	backupsroom(rooms);
	cout << "客房信息录入成功" << endl;
	
}
void addguest(vector<guest>& guests)
{
	guest newguest;
	cout << "请输入住客姓名:";
	cin >> newguest.name;
	cout << "请输入住客身份证号:";
	cin >> newguest.id;
	cout << "请输入住客性别:";
	cin >> newguest.gender;
	cout << "请输入住客入住的房间号:";
	cin >> newguest.roomnum;
    cout << "请输入住客入住时间:";
	cin >> newguest.dayin;
	cout << "请输入住客预计入住天数:";
	cin >> newguest.day;
	guests.push_back(newguest);
	cout << "住客信息录入成功！" << endl;
	
	backupsguest(guests);
	for (auto it = rooms.begin(); it != rooms.end(); it++)
	{
		if (it->num == newguest.roomnum)
		{
			it->roompeople = newguest.name;
			it->state = "有人";
			backupsroom(rooms);
		}
	}

}
void modifyroom(vector<room>& rooms)
{
	int c;
	cout << "1.输入客房号并修改" << endl;
	cout << "2.返回主菜单" << endl;
	cout << "选择->";
	cin >> c;
	if (c == 1)
	{
		cout << "请输入要修改的客房号:";
		int num;
		cin >> num;
		
		int s;
		for (auto& room : rooms)
		{
			
			if (room.num == num)
			{
				cout << "客房号:" << room.num << endl;
				cout << "客房类型:" << room.type << endl;
				cout << "客房住客:" << room.roompeople << endl;
				cout << "客房状态:" << room.state << endl;
				cout << "1.客房价格:" << room.price << endl;
				cout << "2.客房折扣:" << room.discount << endl;
				cout << "3.客房负责人:" << room.principal << endl;
				cout << "0.退出修改功能" << endl;
				cout << "请选择要修改的数据前的序号:";
				cin >> s;
					switch (s)
					{
					case 1:
						cout << "请输入新的客房价格:";
						cin >> room.price;
						break;
					case 2:
						cout << "请输入新的客房折扣:";
						cin >> room.discount;				
						break;
					case 3:
						cout << "请输入新的客房负责人:";
						cin >> room.principal;
					
						break;
					case 0:
						cout << "再次按下回车键退出修改功能" << endl;
						return;
						break;
					default:
						cout << "序号输入有误，请重新输入" << endl;
						return;
						break;
					}
					cout << "信息修改成功" << endl;
					backupsroom(rooms);
					return;
			}
			
		}
		cout << "未找到相关信息" << endl;
		return;
		
	}
	 if (c == 2)
	 {
		 cout << "再次按下回车键返回主菜单" << endl;
		 return;
	 }
	if(c!=1&&c!=2)
	{
		cout << "输入选项有误，请重新选择:" << endl;
		modifyroom(rooms);
	}
	
}
void modifyguest(vector<guest>& guests)
{
	cout << "请选择修改方式:" << endl;
	cout << "1.用姓名查询并修改" << endl;
	cout << "2.用身份证号查询并修改" << endl;
	cout << "3.用入住客房号查询并修改" << endl;
	cout << "4.返回主菜单" << endl;
	int c;
	int s;
	cout << "选择->";
	cin >> c;
	if (c == 1)
	{
		cout << "请输入要修改的住客姓名:";
		string name;
		cin >> name;
		for (auto& guest : guests)
		{

			if (guest.name == name)
			{
				cout << "1.住客姓名:" << guest.name << endl;
				cout << "2.住客身份证号:" << guest.id << endl;
				cout << "3.住客性别:" << guest.gender << endl;
				cout << "4.住客房号:" << guest.roomnum << endl;
				cout << "5.住客入住时间:" << guest.dayin << endl;
				cout << "6.住客预计入住天数:" << guest.day << endl;
				cout << "0.退出修改功能" << endl;
				cout << "请选择要修改的数据前的序号:";
				cin >> s;
				switch (s)
				{
				case 1:
					cout << "请输入新的住客姓名:";
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
					cout << "请输入新的住客身份证号:";
					cin >> guest.id;
					break;
				case 3:
					cout << "请输入新的住客性别:";
					cin >> guest.gender;
					break;
				case 4:
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = "无";
							it->state = "无人";
							backupsroom(rooms);
						}
					}
					cout << "请输入新的住客房间号:";
					cin >> guest.roomnum;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							it->state = "有人";
							backupsroom(rooms);
						}
					}
					break;
				case 5:
					cout << "请输入新的住客入住时间:";
					cin >> guest.dayin;				
					break;
				case 6:
					cout << "请输入新的住客预计入住天数:";
					cin >> guest.day;
					break;
				case 0:
					cout << "再次按下回车键退出修改功能";
					return;
					break;
				default:
					cout << "序号输入有误，请重新输入" << endl;
					return;
					break;
				}
				cout << "信息修改成功" << endl;
				backupsguest(guests);
				return;
			}
		}
		cout << "未找到相关信息" << endl;
		return;
	}
	if (c == 2)
	{
		cout << "请输入要修改的住客身份证号:";
		int id;
		cin >> id;
		for (auto& guest : guests)
		{

			if (guest.id == id)
			{
				cout << "1.住客姓名:" << guest.name << endl;
				cout << "2.住客身份证号:" << guest.id << endl;
				cout << "3.住客性别:" << guest.gender << endl;
				cout << "4.住客房号:" << guest.roomnum << endl;
				cout << "5.住客入住时间:" << guest.dayin << endl;
				cout << "6.住客预计入住天数:" << guest.day << endl;
				cout << "0.退出修改功能" << endl;
				cout << "请选择要修改的数据前的序号:";
				cin >> s;
				switch (s)
				{
				case 1:
					cout << "请输入新的住客姓名:";
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
					cout << "请输入新的住客身份证号:";
					cin >> guest.id;
					break;
				case 3:
					cout << "请输入新的住客性别:";
					cin >> guest.gender;
					break;
				case 4:
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = "无";
							it->state = "无人";
							backupsroom(rooms);
						}
					}
					cout << "请输入新的住客房间号:";
					cin >> guest.roomnum;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							it->state = "有人";
							backupsroom(rooms);
						}
					}
					break;
				case 5:
					cout << "请输入新的住客入住时间:";
					cin >> guest.dayin;
					break;
				case 6:
					cout << "请输入新的住客预计入住天数:";
					cin >> guest.day;
					break;
				case 0:
					cout << "再次按下回车键退出修改功能";
					return;
					break;
				default:
					cout << "序号输入有误，请重新输入" << endl;
					return;
					break;
				}
				cout << "信息修改成功" << endl;
				backupsguest(guests);
				return;
			}
		}
		cout << "未找到相关信息" << endl;
		return;
	}
	if (c == 3)
	{
		cout << "请输入要修改的住客客房号:";
		int roomnum;
		cin >> roomnum;
		for (auto& guest : guests)
		{

			if (guest.roomnum == roomnum)
			{
				cout << "1.住客姓名:" << guest.name << endl;
				cout << "2.住客身份证号:" << guest.id << endl;
				cout << "3.住客性别:" << guest.gender << endl;
				cout << "4.住客房号:" << guest.roomnum << endl;
				cout << "5.住客入住时间:" << guest.dayin << endl;
				cout << "6.住客预计入住天数:" << guest.day << endl;
				cout << "0.退出修改功能" << endl;
				cout << "请选择要修改的数据前的序号:";
				cin >> s;
				switch (s)
				{
				case 1:
					cout << "请输入新的住客姓名:";
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
					cout << "请输入新的住客身份证号:";
					cin >> guest.id;
					break;
				case 3:
					cout << "请输入新的住客性别:";
					cin >> guest.gender;
					break;
				case 4:
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num ==guest.roomnum )
						{
							it->roompeople = "无";
							it->state = "无人";
							backupsroom(rooms);
						}
					}
					cout << "请输入新的住客房间号:";
					cin >> guest.roomnum;
					for (auto it = rooms.begin(); it != rooms.end(); it++)
					{
						if (it->num == guest.roomnum)
						{
							it->roompeople = guest.name;
							it->state = "有人";
							backupsroom(rooms);
						}
					}
					break;
				case 5:
					cout << "请输入新的住客入住时间:";
					cin >> guest.dayin;
					break;
				case 6:
					cout << "请输入新的住客预计入住天数:";
					cin >> guest.day;
					break;
				case 0:
					cout << "再次按下回车键退出修改功能";
					return;
					break;
				default:
					cout << "序号输入有误，请重新输入" << endl;
					return;
					break;
				}
				cout << "信息修改成功" << endl;
				backupsguest(guests);
				return;
			}
		}
		cout << "未找到相关信息" << endl;
		return;
	}
	if (c == 4)
	{
		cout << "再次按下回车键返回主菜单" << endl;
		return;
	}
	else
	{
		cout << "输入选项有误，请重新选择:" << endl;
		modifyguest(guests);
	}
	
}
void searchroom(const vector<room>& rooms)
{
	cout << "请选择查询方式" << endl;
	cout << "1.按照客房号查询" << endl;
	cout << "2.按照客房状态查询" << endl;
	cout << "3.按照价格查询" << endl;
	cout << "4.返回主菜单" << endl;
	cout << "选择->";
	int c ;
	cin >> c;
	if (c == 1)
	{
		int num;
		cout << "请输入要查询的客房号:";
		cin >> num;
		for (const auto& room : rooms)
		{
			if (room.num == num)
			{
				cout << "客房号:" << room.num << endl;
				cout << "客房价格:" << room.price << endl;
				cout << "客房类型:" << room.type << endl;
				cout << "客房折扣:" << room.discount << endl;
				cout << "客房状态:" << room.state << endl;
				cout << "客房住客:" << room.roompeople << endl;
				cout << "客房负责人:" << room.principal << endl;
				return;
			}
		}
		cout << "未查询到相关信息" << endl;
		return;
	}
	if (c == 2)
	{
		string state;
		cout << "请输入查询的客房状态:";
		cin >> state;
		bool found = true;
		for (const auto& room : rooms)
		{
			if (room.state == state)
			{
				cout << "客房号:" << room.num << endl;
				cout << "客房价格:" << room.price << endl;
				cout << "客房类型:" << room.type << endl;
				cout << "客房折扣:" << room.discount << endl;
				cout << "客房状态:" << room.state << endl;
				cout << "客房住客:" << room.roompeople << endl;
				cout << "客房负责人:" << room.principal << endl;
				cout << endl;
			}
		}
		if (!found)
		{
			cout << "未查询到相关信息" << endl;
			return;
		}
	}
	if (c == 3)
	{
		int price;
		cout << "请输入查询的客房价格:";
		cin >> price;
		bool found = true;
		for (const auto& room : rooms)
		{
			if (room.price == price)
			{
				cout << "客房号:" << room.num << endl;
				cout << "客房价格:" << room.price << endl;
				cout << "客房类型:" << room.type << endl;
				cout << "客房折扣:" << room.discount << endl;
				cout << "客房状态:" << room.state << endl;
				cout << "客房住客:" << room.roompeople << endl;
				cout << "客房负责人:" << room.principal << endl;
				cout << endl;
				
			}
		}
		if (!found)
		{
			cout << "未查询到相关信息" << endl;
			return;
		}
	}
	if (c == 4)
	{
		cout << "再次按下回车键返回主菜单" << endl;
		return;
	}
	
	if(c!=1&&c!=2&&c!=3&&c!=4)
	{
		cout << "输入选项有误，请重新选择:" << endl;
		searchroom(rooms);
	}
}
void searchguest(const vector<guest>& guests)
{
	cout << "请选择查询方式" << endl;
	cout << "1.按照姓名查询" << endl;
	cout << "2.按照身份证号查询" << endl;
	cout << "3.按照所住客房号查询" << endl;
	cout << "4.返回主菜单" << endl;
	cout << "选择->";
	int c;
	cin >> c;
	if (c == 1)
	{
		cout << "请输入要查询的姓名:";
		string name;
		cin >> name;
		for (const auto& guest : guests)
		{
			if (guest.name == name)
			{
				cout << "住客姓名:" << guest.name << endl;
				cout << "住客身份证号:" << guest.id << endl;
				cout << "住客性别:" << guest.gender << endl;
				cout << "住客房号:" << guest.roomnum << endl;
				cout << "住客入住时间:" << guest.dayin << endl;
				cout << "住客预计入住天数:" << guest.day << endl;
				return;
			}
		}
		cout << "未查询到相关信息" << endl;
		return;
    }

	if (c == 2)
	{
		cout << "请输入要查询的身份证号:";
		long long id;
		cin >> id;
		for (const auto& guest : guests)
		{
			if (guest.id == id)
			{
				cout << "住客姓名:" << guest.name << endl;
				cout << "住客身份证号:" << guest.id << endl;
				cout << "住客性别:" << guest.gender << endl;
				cout << "住客房号:" << guest.roomnum << endl;
				cout << "住客入住时间:" << guest.dayin << endl;
				cout << "住客预计入住天数:" << guest.day << endl;
				return;
			}
		}
		cout << "未查询到相关信息" << endl;
		return;
	}
	if (c == 3)
	{
		cout << "请输入要查询的所住客房:";
		int roomnum;
		cin >> roomnum;
		for (const auto& guest : guests)
		{
			if (guest.roomnum == roomnum)
			{
				cout << "住客姓名:" << guest.name << endl;
				cout << "住客身份证号:" << guest.id << endl;
				cout << "住客性别:" << guest.gender << endl;
				cout << "住客房号:" << guest.roomnum << endl;
				cout << "住客入住时间:" << guest.dayin << endl;
				cout << "住客预计入住天数:" << guest.day << endl;
				return;
			}
		}
		cout << "未查询到相关信息" << endl;
		return;
	}
	if (c == 4)
	{
		cout << "再次按下回车键返回主菜单" << endl;
		return;
	}
	else
	{
		cout << "输入选项有误，请重新选择:" << endl;
		searchguest(guests);
	}

}
void deleteguest(vector<guest>& guests)
{
	cout << "请选择删除方式" << endl;
	cout << "1.按照姓名删除" << endl;
	cout << "2.按照身份证号删除" << endl;
	cout << "3.按照所住客房号删除" << endl;
	cout << "4.返回主菜单" << endl;
	cout << "选择->";
	int c ;
	cin >> c;
	if (c == 1)
	{
		cout << "请输入要删除的住客的姓名:";
		string name;
		cin >> name;
		for (auto it = guests.begin(); it != guests.end(); it++)
		{
			if (it->name == name)
			{
				guests.erase(it);
				cout << "该住客信息删除成功" << endl;
				backupsguest(guests);
				for (auto it = rooms.begin(); it != rooms.end(); it++)
				{
					if (it->roompeople == name)
					{
						it->roompeople = "无";
						it->state = "无人";
						backupsroom(rooms);
					}
				}
				return;
			}
		}

		cout << "未找到该住客信息" << endl;
		return;
	}
	if (c == 2)
	{
		cout << "请输入要删除的住客的身份证号:";
		int id;
		cin >> id;
		for (auto it = guests.begin(); it != guests.end(); it++)
		{
			if (it->id == id)
			{
				string name = it->name;
				guests.erase(it);
				cout << "该住客信息删除成功" << endl;
				backupsguest(guests);
				for (auto it = rooms.begin(); it != rooms.end(); it++)
				{
					if (it->roompeople == name)
					{
						it->roompeople = "无";
						it->state = "无人";
						backupsroom(rooms);
					}
				}
				return;
			}
		}
		cout << "未找到该住客信息" << endl;
	}
	if (c == 3)
	{
		cout << "请输入要删除的住客所住的房号:";
		int roomnum;
		cin >> roomnum;
		for (auto it = guests.begin(); it != guests.end(); it++)
		{
			if (it->roomnum == roomnum)
			{
				string name = it->name;
				guests.erase(it);
				cout << "该住客信息删除成功" << endl;
				backupsguest(guests);
				for (auto it = rooms.begin(); it != rooms.end(); it++)
				{
					if (it->roompeople == name)
					{
						it->roompeople = "无";
						it->state = "无人";
						backupsroom(rooms);
					}
				}
				return;
			}
		}
		cout << "未找到该住客信息" << endl;
		return;
	}
	if (c == 4)
	{
		cout << "再次按下回车键返回主菜单" << endl;
		return;
	}
	else
	{
		cout << "输入选项有误，请重新选择:" << endl;
		deleteguest(guests);
	}

}
void deleteroom(vector<room>& rooms)
{

	int c;
	cout << "1.输入客房号并删除" << endl;
	cout << "2.返回主菜单" << endl;
	cout << "选择->";
	cin >> c;
	if (c == 1)
	{
		cout << "请输入要删除的客房号:";
		int num;
		cin >> num;
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it->num ==num )
			{
				rooms.erase(it);
				cout << "该客房信息删除成功" << endl;
				backupsroom(rooms);
				return;
			}
		}
		cout << "未找到该客房信息" << endl;
		return;
	}
	if (c == 2)
	{
		cout << "再次按下回车键返回主菜单" << endl;
		return;
	}
	else
	{
		cout << "输入选项有误，请重新选择:" << endl;
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
	cout << setw(56) << "客房报表" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << '|' << "客房号   " << '|' << "客房类型   " << '|' << "客房价格   " << '|' << "客房折扣   " << '|' << "客房状态   " << '|' << "客房住客      " << '|' << "客房负责人" << '|' << "入住时间与天数 " << '|' << "营业额   " << '|' << endl;
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
				dayin = "无";
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


