#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
using namespace std;

/*通讯录数据元素*/
typedef struct {
	int num;		 //编号
	string name;     //姓名
	string phonenum; //电话
	string address;  //地址
	string relation; //分组
}ElemType;

/*通讯录链表*/
typedef struct Node {
	ElemType data;
	struct Node* next;
}Node, * LinkList;

/*函数声明列表*/
void Read_LinkList(LinkList& L);                         //读取信息
void Save_LinkList(const LinkList& L);                   //保存信息
void Init_LinkList(LinkList& L);                         //初始化通讯录链表
void Create_LinkList(LinkList& L);                       //添加联系人
void Delete_LinkList(LinkList& L);                       //删除联系人
void Query_LinkList(const LinkList& L);                  //查询联系人
void Modify_LinkList(LinkList& L);                       //修改联系人
void Print_LinkList(const LinkList& L);                  //通讯录显示
bool compare(const ElemType& t1, const ElemType& t2);    //定义sort函数的关系
void Sort_LinkList(LinkList& L);                         //通讯录排序
void Clear_LinkList(LinkList& L);                        //通讯录清空
void menu(LinkList& L);                                  //主控菜单

/*程序入口---主函数*/
int main()
{
	system("color 70");
	LinkList L;
	Init_LinkList(L);
	Read_LinkList(L);
	menu(L);
	return 0;
}

/*读取信息函数*/
void Read_LinkList(LinkList& L)
{
	Node* p = L;
	ifstream infile("contact.txt", ios::in);
	int len = 0;
	infile >> len;
	ElemType tem;
	while (len--)
	{
		infile >> tem.num >> tem.name >> tem.phonenum >> tem.address >> tem.relation;
		Node* t = new Node;
		t->data = tem;
		t->next = NULL;
		p->next = t;
		p = p->next;
	}
	infile.close();
}

/*保存信息函数*/
void Save_LinkList(LinkList& L)
{
	Node* t = L, * cnt = L;
	ofstream outfile("contact.txt", ios::out);
	int len = 0;
	while (cnt->next)
	{
		len++;
		cnt = cnt->next;
	}
	outfile << len << endl;
	while (t)
	{
		if (t != L)
			outfile << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
		t = t->next;
	}
	outfile.close();
}

/*初始化通讯录链表函数*/
void Init_LinkList(LinkList& L)
{
	L = new Node;
	L->next = NULL;
}

/*添加联系人函数*/
void Create_LinkList(LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************欢迎来到添加联系人功能***************" << endl;
	Node* t = L;
	int i = 1, flag = 1;
	while (t->next)
	{
		i++;
		t = t->next;
	}
	while (flag)
	{
		Node* p = new Node;
		cout << "\t\t\t输入姓名：";
		cin >> p->data.name;
		cout << "\t\t\t输入电话：";
		cin >> p->data.phonenum;
		cout << "\t\t\t输入地址：";
		cin >> p->data.address;
		cout << "\t\t\t输入分组：";
		cin >> p->data.relation;
		p->data.num = i++;
		p->next = NULL;
		t->next = p;
		t = t->next;
		Save_LinkList(L); //将改动保存至文件中
		cout << "\t\t\t添加成功！是否继续添加？（1 是 0 否）" << endl;
		cout << "\t\t\t请选择【0-1】：";
		cin >> flag;
	}
}

/*删除联系人函数*/
void Delete_LinkList(LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************欢迎来到删除联系人功能***************" << endl;
	int sel = 0;
	Node* p = L, * t = NULL;
	ElemType tem;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 按编号删除" << endl;
	cout << "\t\t\t2 按姓名删除" << endl;
	cout << "\t\t\t3 返回主菜单" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t请选择【1-3】：";
	cin >> sel;
	while (sel < 1 || sel>3)
	{
		cout << "\t\t\t输入不合法,请重新选择【1-3】：";
		cin >> sel;
	}
	if (sel == 1)
	{
		int flag = 0;
		cout << "\t\t\t请输入待删除联系人的编号：";
		cin >> tem.num;
		while (p->next)
		{
			t = p->next;
			if (t->data.num == tem.num)
			{
				cout << "\t\t\t待删除联系人信息如下：" << endl;
				cout << "\t\t\t编号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
			p = p->next;
		}
		if (flag == 0) cout << "\t\t\t查无此人，无法删除！" << endl;
		else
		{
			cout << "\t\t\t确认删除？（1 是 0 否）" << endl;
			cout << "\t\t\t请选择【0-1】：";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t输入不合法,请重新选择【0-1】：";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				p->next = t->next;
				delete t;
				cout << "\t\t\t删除成功！" << endl;
				Save_LinkList(L); //改动保存至文件中
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Delete_LinkList(L);
	}
	else if (sel == 2)
	{
		int flag = 0;
		cout << "\t\t\t请输入待删除联系人的姓名：";
		cin >> tem.name;
		while (p->next)
		{
			t = p->next;
			if (t->data.name == tem.name)
			{
				cout << "\t\t\t待删除联系人信息如下：" << endl;
				cout << "\t\t\t序号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
			p = p->next;
		}
		if (flag == 0) cout << "\t\t\t查无此人，无法删除！" << endl;
		else
		{
			cout << "\t\t\t确认删除？（1 是 0 否）" << endl;
			cout << "\t\t\t请选择【0-1】：";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t输入不合法,请重新选择【0-1】：";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				p->next = t->next;
				delete t;
				cout << "\t\t\t删除成功！" << endl;
				Save_LinkList(L); //改动保存至文件中
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Delete_LinkList(L);
	}
	else if (sel == 3) return;
}

/*查询联系人函数*/
void Query_LinkList(const LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************欢迎来到查询联系人功能***************" << endl;
	int sel = 0;
	Node* t = L;
	ElemType tem;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 按编号查询" << endl;
	cout << "\t\t\t2 按姓名查询" << endl;
	cout << "\t\t\t3 返回主菜单" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t请选择【1-3】：";
	cin >> sel;
	while (sel < 1 || sel>3)
	{
		cout << "\t\t\t输入不合法,请重新选择【1-3】：";
		cin >> sel;
	}
	if (sel == 1)
	{
		int flag = 0;
		cout << "\t\t\t请输入待查询联系人的编号：";
		cin >> tem.num;
		while (t->next)
		{
			t = t->next;
			if (t->data.num == tem.num)
			{
				cout << "\t\t\t待查询联系人信息如下：" << endl;
				cout << "\t\t\t序号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t查无此人！" << endl;
		cout << "\n\t\t\t";
		system("pause");
		Query_LinkList(L);
	}
	else if (sel == 2)
	{
		int flag = 0;
		cout << "\t\t\t请输入待查询联系人的姓名：";
		cin >> tem.name;
		while (t->next)
		{
			t = t->next;
			if (t->data.name == tem.name)
			{
				cout << "\t\t\t待查询联系人信息如下：" << endl;
				cout << "\t\t\t序号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t查无此人！" << endl;
		cout << "\n\t\t\t";
		system("pause");
		Query_LinkList(L);
	}
	else if (sel == 3)
	{
		return;
	}
}

/*修改联系人函数*/
void Modify_LinkList(LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************欢迎来到修改联系人功能***************" << endl;
	int sel = 0;
	Node* t = L;
	ElemType tem;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 按编号修改" << endl;
	cout << "\t\t\t2 按姓名修改" << endl;
	cout << "\t\t\t3 返回主菜单" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t请选择【1-3】：";
	cin >> sel;
	while (sel < 1 || sel>3)
	{
		cout << "\t\t\t输入不合法,请重新输入【1-3】：";
		cin >> sel;
	}
	if (sel == 1)
	{
		int flag = 0;
		cout << "\t\t\t请输入待修改联系人的编号：";
		cin >> tem.num;
		while (t->next)
		{
			t = t->next;
			if (t->data.num == tem.num)
			{
				cout << "\t\t\t待修改联系人信息如下：" << endl;
				cout << "\t\t\t序号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t查无此人，无法修改！" << endl;
		else
		{
			ElemType tem;
			cout << "\t\t\t输入修改后的联系人信息：" << endl;
			cout << "\t\t\t输入姓名：";
			cin >> tem.name;
			cout << "\t\t\t输入电话：";
			cin >> tem.phonenum;
			cout << "\t\t\t输入地址：";
			cin >> tem.address;
			cout << "\t\t\t输入分组：";
			cin >> tem.relation;
			tem.num = t->data.num;
			cout << "\t\t\t确认修改？（1 是 0 否）" << endl;
			cout << "\t\t\t请选择【0-1】：";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t输入不合法,请重新选择【0-1】：";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				t->data = tem;
				cout << "\t\t\t修改成功！" << endl;
				Save_LinkList(L); //将改动保存至文件中
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Modify_LinkList(L);
	}
	else if (sel == 2)
	{
		int flag = 0;
		cout << "\t\t\t请输入待修改联系人的姓名：";
		cin >> tem.name;
		while (t->next)
		{
			t = t->next;
			if (t->data.name == tem.name)
			{
				cout << "\t\t\t待修改联系人信息如下：" << endl;
				cout << "\t\t\t序号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t查无此人，无法修改！" << endl;
		else
		{
			ElemType tem;
			cout << "\t\t\t输入修改后的联系人信息：" << endl;
			cout << "\t\t\t输入姓名：";
			cin >> tem.name;
			cout << "\t\t\t输入电话：";
			cin >> tem.phonenum;
			cout << "\t\t\t输入地址：";
			cin >> tem.address;
			cout << "\t\t\t输入分组：";
			cin >> tem.relation;
			tem.num = t->data.num;
			cout << "\t\t\t确认修改？（1 是 0 否）" << endl;
			cout << "\t\t\t请选择【0-1】：";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t输入不合法,请重新选择【0-1】：";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				t->data = tem;
				cout << "\t\t\t修改成功！" << endl;
				Save_LinkList(L); //将改动保存至文件中
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Delete_LinkList(L);
	}
	else if (sel == 3) return;
}

/*通讯录显示函数*/
void Print_LinkList(const LinkList& L)
{
	system("cls");
	cout << "\t\t\t***************欢迎来到通讯录显示功能***************" << endl;
	Node* t = L->next;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	cout << "\t\t\t序号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	while (t)
	{
		cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
		t = t->next;
	}
	cout << "\t\t\t-----------------------------------------------------" << endl;
	cout << "\t\t\t";
	system("pause");
}

/*通讯录排序函数中sort函数的第三个参数*/
bool compare(const ElemType& t1, const ElemType& t2)
{
	return t1.name < t2.name;
}

/*通讯录排序函数*/
void Sort_LinkList(LinkList& L)
{
	system("cls");
	cout << "\t\t\t***************欢迎来到通讯录排序功能***************" << endl;
	Node* p = L;
	int cnt = 0, i = 0;
	while (p->next)
	{
		p = p->next;
		cnt++;
	}
	ElemType* arr = new ElemType[cnt];
	p = L;
	while (p->next)
	{
		p = p->next;
		arr[i++] = p->data;
	}
	sort(arr, arr + cnt, compare);
	p = L, i = 0;
	while (p->next)
	{
		p = p->next;
		p->data = arr[i++];
		p->data.num = i;
	}
	cout << "\t\t\t对通讯录进行排序并整理如下：" << endl;
	Node* t = L->next;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	cout << "\t\t\t序号\t" << "姓名\t" << "联系电话\t" << "家庭地址\t" << "分组" << endl;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	while (t)
	{
		cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
		t = t->next;
	}
	cout << "\t\t\t-----------------------------------------------------" << endl;
	Save_LinkList(L); //改动保存至文件中
	cout << "\t\t\t";
	system("pause");
}

/*清空通讯录函数*/
void Clear_LinkList(LinkList& L)
{
	int sel = 0;
	system("cls");
	cout << "\t\t\t**************欢迎来到通讯录清空功能*************" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 确认清空通讯录" << endl;
	cout << "\t\t\t2 返回主菜单" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t请慎重选择【1-2】：";
	cin >> sel;
	while (sel < 1 || sel>2)
	{
		cout << "\t\t\t输入不合法,请重新输入【1-2】：";
		cin >> sel;
	}
	if (sel == 1)
	{
		Node* head = L;
		if (head == NULL)
		{
			return;
		}
		//清空链表,是不清空头节点的，因此从第一个有数据的节点开始释放
		Node* curNode = head->next;
		while (curNode != NULL)
		{
			//先保住下一个节点的位置
			Node* nextNode = curNode->next;
			free(curNode);
			curNode = nextNode;
		}
		//将头结点next指针置空
		head->next = NULL;
		Save_LinkList(L);
		cout << "\n\t\t\t";
		system("pause");
	}
	else if (sel == 2) return;
}

/*主控菜单函数*/
void menu(LinkList& L)
{
	char sel;
	system("cls");
	cout << "\t\t\t***********欢迎来到通讯录管理系统***********" << endl;
	cout << "\t\t\t你可以进行以下操作:" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             1   添加联系人               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             2   删除联系人               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             3   修改联系人               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             4   查询联系人               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             5   通讯录显示               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             6   通讯录排序               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             7   通讯录清空               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             0   退出                     |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t请选择【0-7】：";
	cin >> sel;
	while (sel < '0' || sel>'7')
	{
		cout << "\t\t\t输入非法,请重新选择【0-7】：";
		cin >> sel;
	}
	switch (sel)
	{
	case '1':
		Create_LinkList(L);
		menu(L);
		break;
	case '2':
		Delete_LinkList(L);
		menu(L);
		break;
	case '3':
		Modify_LinkList(L);
		menu(L);
		break;
	case '4':
		Query_LinkList(L);
		menu(L);
		break;
	case '5':
		Print_LinkList(L);
		menu(L);
		break;
	case '6':
		Sort_LinkList(L);
		menu(L);
		break;
	case '7':
		Clear_LinkList(L);
		menu(L);
		break;
	case '0':
		exit(0);
	default:
		menu(L);
	}
}