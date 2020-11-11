#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N sizeof(struct Book)
#define M sizeof(struct stu)

typedef struct user_data
{
	int stu_id;				   //用户数字id
	char stu_acc[20];		   //学生账号
	char stu_passw[20];		   //学生密码
	char stu_find_passw[15];   //密保问题密码
	char stu_num[10];		   //学生学号
	char stu_name[20];		   //学生姓名
	char stu_tel[15];		   //学生电话
	char stu_bor_book[10][20]; //所借书号
} user_data;

typedef struct stu
{
	struct user_data data;
	struct stu *next; //下位学生
} Student;

typedef struct DATA
{
	char book_num[10];	   //书号
	char book_name[20];	   //书名
	char book_author[30];  //作者名
	char book_publish[30]; //出版社
	char book_type[20];	   //类别
	char book_time[20];
	float book_price; //价格
	int book_rest;	  //库存
} DATA;

typedef struct Book
{
	DATA data;
	struct Book *next; //下本书
} Book;

typedef Student *student;
typedef Book *book;

void menu_common(); //菜单界面
void menu_first();
void menu_user();
void menu_sign(student p);

int login_system(); //登录系统
void account_creat();
void account_delete();
void sign_in();
void change_password();
int manager();

int stuent();

void add_book();
void delete_book();
void change_book();
void search();
void search_number();
void search_name();
void search_author();
void sort(book p); //排序
book ss();
student sss();
void save_book(book q);
void save_user(student p);
void print_book();
void print_user();
void matching(char a[], char b[]);

void menu_first() //初始菜单
{				  //显示开始菜单
	printf("\n\n\t\t欢迎进入狗葱图书馆\n\n");
	printf("*****************************************");
	printf("\n\n\t\t1.进入会员登陆系统\n\n");
	printf("\n\n\t\t2.普通登录\n\n");
	printf("请选择您要使用的功能：");
	char t;
	scanf("%c", &t);
	getchar();
	switch (t)
	{
	case '1':
		menu_user();
		break;
	case '2':
		menu_common();
		break;
	default:
		break;
	}
}

void menu_user() //显示登录菜单
{

	printf("\n\n\t    欢迎使用会员登录系统\n\n");
	printf("**********************************************\n");
	printf("\t\t1.登录系统\n");
	printf("\t\t2.创建账号\n");
	printf("\t\t3.修改密码\n");
	printf("\t\t4.退出系统\n");
	printf("\t\t5.查看用户列表（测试用）\n");
	printf("\t\t6.删除用户（测试用）\n");
	printf("\n\n\t    请按键选择，回车确定\n");
	printf("**********************************************");
	char t;
	scanf("%c", &t);
	getchar();
	switch (t)
	{
	case '1':
		sign_in();
		break;
	case '2':
		account_creat();
		break;
	case '3':
		break;
	case '4':
		exit(0);
	case '5':
		print_user();
		break;
	case '6':
		account_delete();
		break;
	default:
		break;
	}
	return;
}

void menu_common() //菜单
{
	do
	{
		system("cls"); //清屏
		char t;
		printf(" 图书查询管理系统\n");
		printf("|     1.图书入库      |\n");
		printf("|     2.修改信息      |\n");
		printf("|     3.删除信息      |\n");
		printf("|     4.图书查询      |\n");
		printf("|     5.图书总览      |\n");
		printf("|     6.退出软件      |\n");
		printf("请选择您要使用的功能：");
		scanf("%c", &t);
		getchar();
		switch (t)
		{
		case '1':
			add_book();
			break;
		case '2':
			change_book();
			break;
		case '3':
			delete_book();
			break;
		case '4':
			search();
			break;
		case '5':
			print_book();
			break;
		case '6':
			exit(0);
			break;
		default:
			break;
		}
	} while (1);
}

void menu_sign(student p)//登录成功后显示的菜单
{
	char t[10];
	printf("欢迎%c同学！",p->data.stu_name);
	printf("输入任意数字返回：\n");
	fgets(t, 5, stdin);
	exit(0);
}

book ss() //将文件中的内容读出到链表中，返回值为表头地址
{
	FILE *fp; //文件指针
	int n = 0;
	book head = NULL;
	book p2, p, pr = NULL;
	fp = fopen("test.text", "ab+"); //以只读的方式打开文件
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	while (!feof(fp)) //判断文件位置标志是否移动到文件末尾
	{
		n++;
		p = (book)malloc(N); //向内存申请一段空间
		fread(p, N, 1, fp);	 //将fp所指向的文件中的内容赋给p
		if (n == 1)
		{
			head = p;
			p2 = p;
		}
		else //创建链表
		{
			pr = p2;
			p2->next = p;
			p2 = p;
		}
	}
	if (pr != NULL)
		pr->next = NULL;
	else
		head = NULL;
	fclose(fp);	 //关闭文件
	return head; //返回头指针
}

student sss() //将文件中的内容读出到链表中，返回值为表头地址
{
	FILE *fp; //文件指针
	int n = 0;
	student head = NULL;
	student p2, p, pr = NULL;
	fp = fopen("student.text", "ab+"); //以只读的方式打开文件
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	while (!feof(fp)) //判断文件位置标志是否移动到文件末尾
	{
		n++;
		p = (student)malloc(N); //向内存申请一段空间
		fread(p, N, 1, fp);		//将fp所指向的文件中的内容赋给p
		if (n == 1)
		{
			head = p;
			p2 = p;
		}
		else //创建链表
		{
			pr = p2;
			p2->next = p;
			p2 = p;
		}
	}
	if (pr != NULL)
		pr->next = NULL;
	else
		head = NULL;
	fclose(fp);	 //关闭文件
	return head; //返回头指针
}

void save_book(book p) //将p中内容写入文件
{
	FILE *fp;					   //文件指针
	fp = fopen("test.text", "ab"); //以追加的方式打开名字为test的文件
	if (fp == NULL)
	{
		printf("cannot open file");
	}
	if (fwrite(p, N, 1, fp) != 1) //将p所指向的一段大小为N的内容存入fp所指向的文件中
	{
		printf("write error");
	}
	fclose(fp); //关闭文件
}

void save_user(student p)
{
	FILE *fp;						  //文件指针
	fp = fopen("student.text", "ab"); //以追加的方式打开名字为student的文件
	if (fp == NULL)
	{
		printf("cannot open file");
	}
	if (fwrite(p, N, 1, fp) != 1) //将p所指向的一段大小为N的内容存入fp所指向的文件中
	{
		printf("write error");
	}
	fclose(fp); //关闭文件
}

void add_book() //图书录入
{
	do
	{
		system("cls");
		char t;
		book p;
		p = (book)malloc(N); //申请空间
		//输入图书信息
		printf("请输入图书登录号(小于10位数)：");
		scanf("%s", p->data.book_num);
		getchar();

		printf("请输入书名(小于10位数)：");
		scanf("%s", p->data.book_name);
		getchar();

		printf("请输入作者名(小于10位数)：");
		scanf("%s", p->data.book_author);
		getchar();

		printf("请输入图书类别(小于10位数)：");
		scanf("%s", p->data.book_type);
		getchar();

		printf("请输入图书出版单位(小于10位数)：");
		scanf("%s", p->data.book_publish);
		getchar();

		printf("请输入图书出版时间(小于8位数)：");
		scanf("%s", p->data.book_time);
		getchar();

		printf("请输入图书价格：");
		scanf("%f", &p->data.book_price);
		getchar();

		printf("请输入图书数量：");
		scanf("%d", &p->data.book_rest);

		save_book(p);

		printf("正在保存....");

		system("cls");

		printf("-------------------------");

		printf("|                       |");

		printf("| 保存成功！是否继续？  |");

		printf("| 1.是             2.否 |");

		printf("|                       |");

		printf("-------------------------\n");
		while (1) //利用死循环可有效防止其他按键干扰
		{
			t = getchar();
			if (t == '1')
			{
				break;
			}
			else if (t == '2')
			{
				return;
			}
		}

	} while (1);
}
void print_book() //图书总览
{
	system("cls");
	book head, p;
	int sum = 0;
	head = ss();
	printf("***********************************************图书总览******************************************************\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量\n");

	printf("-------------------------------------------------------------------------------------------------------------\n");
	if (head == NULL)
	{

		printf("书库暂时没有书哦~赶快去添加几本吧^_^(输入任意键返回)");
		char t;
		scanf("%c", &t);
		exit(0);
	}
	p = head;
	while (p != NULL)
	{

		printf("%s%14s %14s%14s   %14s   %18s         %.2f%12d\n", p->data.book_num, p->data.book_name, p->data.book_author, p->data.book_type, p->data.book_publish, p->data.book_time, p->data.book_price, p->data.book_rest);
		sum += p->data.book_rest; //计算图书总量
		p = p->next;
	}

	printf("图书总量为：%d", sum);
	printf("输入任意数字返回：\n");
	char t[10];
	fgets(t, 5, stdin);
	return;
}

void print_user() //用户总览
{
	system("cls");
	student head, p;
	int sum = 0;
	head = sss();
	printf("***********************************************用户总览******************************************************\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("用户id        用户姓名        用户学号         用户账号         用户密码         \n");

	printf("-------------------------------------------------------------------------------------------------------------\n");
	if (head == NULL)
	{

		printf("用户库暂时没有用户哦~赶快去添加几个吧^_^(输入任意键退出)");
		char t;
		scanf("%c", &t);
		exit(0);
	}
	p = head;
	while (p != NULL)
	{

		printf("%d%17s %16s%16s   %14s\n", p->data.stu_id, p->data.stu_name, p->data.stu_num, p->data.stu_acc, p->data.stu_passw);
		sum += 1; //计算用户数量
		p = p->next;
	}

	printf("用户数量为：%d", sum);
	printf("输入任意数字返回：\n");
	int t;
	scanf("%d", &t);
	return;
}

void sort() //对图书信息进行排序
{
	system("cls");
	book head, p;
	head = ss();
}
void search() //搜索图书信息
{
	char i, s;
	printf("请输入查找类型：(1 按编号查找 2 按书名查找 3 按作者查找)\n");
	scanf("%c", &i);
	scanf("%c", &s);
	switch (i)
	{
	case '1':
		search_number();
		break;
	case '2':
		search_name();
		break;
	case '3':
		search_author();
		break;
	default:
		break;
	}
	return;
}
void search_number() //按编号进行搜索
{
	system("cls");
	book head, p;
	book q, qr, q2 = NULL;
	char a[20];
	head = ss();
	printf("按图书编号查询\n");
	printf("请输入需要查询的编号：");
	gets(a);
	p = head;
	printf("***********************************************搜索结果******************************************************\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量\n");

	printf("-------------------------------------------------------------------------------------------------------------\n");
	q = (book)malloc(N);
	q->next = NULL;
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->data.book_num, a) == 0)
		{
			q2 = (book)malloc(N);
			q2 = p;
			q2->next = NULL;
			q->next = q2;
			q = q2;
		}
		p = p->next;
	}
	while (q != NULL)
	{
		printf("%s%14s %14s%14s   %14s   %18s         %.2f%12d\n", q->data.book_num, q->data.book_name, q->data.book_author, q->data.book_type, q->data.book_publish, q->data.book_time, q->data.book_price, q->data.book_rest);
		q = q->next;
	}
	printf("输入任意数字返回：\n");
	char t[10];
	fgets(t, 5, stdin);
	return;
}

void search_name() //按书名进行搜索
{
	system("cls");
	book head, p;
	book q, qr, q2 = NULL;
	char a[20];
	head = ss();
	printf("按书名查询\n");
	printf("请输入需要查询的书名：");
	gets(a);
	p = head;
	printf("***********************************************搜索结果******************************************************\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量\n");

	printf("-------------------------------------------------------------------------------------------------------------\n");
	q = (book)malloc(N);
	q->next = NULL;
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->data.book_name, a) == 0)
		{
			q2 = (book)malloc(N);
			q2 = p;
			q2->next = NULL;
			q->next = q2;
			q = q2;
		}
		p = p->next;
	}
	while (q != NULL)
	{
		printf("%s%14s %14s%14s   %14s   %18s         %.2f%12d\n", q->data.book_num, q->data.book_name, q->data.book_author, q->data.book_type, q->data.book_publish, q->data.book_time, q->data.book_price, q->data.book_rest);
		q = q->next;
	}
	printf("输入任意数字返回：\n");
	char t[10];
	fgets(t, 5, stdin);
	return;
}
void search_author() //按作者进行搜索
{
	system("cls");
	book head, p;
	book q, qr, q2 = NULL;
	char a[20];
	head = ss();
	printf("按作者查询\n");
	printf("请输入需要查询的作者：");
	gets(a);
	p = head;
	printf("***********************************************搜索结果******************************************************\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量\n");

	printf("-------------------------------------------------------------------------------------------------------------\n");
	q = (book)malloc(N);
	q->next = NULL;
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->data.book_author, a) == 0)
		{
			q2 = (book)malloc(N);
			q2 = p;
			q2->next = NULL;
			q->next = q2;
			q = q2;
		}
		p = p->next;
	}
	while (q != NULL)
	{
		printf("%s%14s %14s%14s   %14s   %18s         %.2f%12d\n", q->data.book_num, q->data.book_name, q->data.book_author, q->data.book_type, q->data.book_publish, q->data.book_time, q->data.book_price, q->data.book_rest);
		q = q->next;
	}
	printf("输入任意数字返回：\n");
	char t[10];
	fgets(t, 5, stdin);
	return;
}

void sort(book p) //排序,给我一个链表
{
	p = ss();
	book k1 = NULL, k2 = NULL, k3 = NULL;
	k1 = p;
	k2 = p;
	k3 = p;
	DATA temp;
	while (k1 != NULL)
	{
		while (k2 != NULL)
		{
			if (strcmp(k1->data.book_num, k2->data.book_num) == -1)
			{
				temp = k1->data;
				k1->data = k2->data;
				k2->data = temp;
				k2 = k2->next;
			}
			else
				k2 = k2->next;
		}
		k1 = k1->next;
		k2 = k3;
	}
	int sum;
	printf("***********************************************排序总览******************************************************\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("书号        书名        作者名         图书类别         出版单位         出版时间          价格        数量\n");

	printf("-------------------------------------------------------------------------------------------------------------\n");
	if (p == NULL)
	{
		printf("书库暂时没有书哦~赶快去添加几本吧^_^(按任意键返回)");
		exit(0);
	}
	while (p != NULL)
	{
		printf("%s%14s %14s%14s   %14s   %18s         %.2f%12d\n", p->data.book_num, p->data.book_name, p->data.book_author, p->data.book_type, p->data.book_publish, p->data.book_time, p->data.book_price, p->data.book_rest);
		sum += p->data.book_rest; //计算图书总量
		p = p->next;
	}
}

void change_book() //修改图书信息
{
	do
	{
		book p, q;
		int i = 0, j = 0, x;
		char ch, t;
		FILE *fp;
		char name[10];
		q = ss();
		p = q;
		printf("请输入你要修改的图书的书名:");
		gets(name);

		printf("***********************************************图书信息******************************************************\n");
		printf("-------------------------------------------------------------------------------------------------------------\n");
		printf("登录号        书名        作者名         图书类别         出版单位         出版时间          价格        数量\n");
		printf("-------------------------------------------------------------------------------------------------------------\n");
		while (p != NULL)
		{
			if (p != NULL && strcmp(p->data.book_name, name) == 0)
			{
				j++;
				printf("%s%14s %14s%14s   %14s   %18s         %.2f%12d\n", p->data.book_num, p->data.book_name, p->data.book_author, p->data.book_type, p->data.book_publish, p->data.book_time, p->data.book_price, p->data.book_rest);
				i = j;
			}
			p = p->next;
		}
		if (j == 0)
		{
			printf("没有找到相对应的信息!(按0返回，按1重新搜索)");
			while (1)
			{
				ch = getchar();
				if (ch == '0')
				{
					break;
				}
				else if (ch == '1')
				{
					break;
				}
			}
			if (ch == '1')
			{
				continue;
			}
		}
		while (1)
		{
			printf("请输入你想要修改的图书书号:");
			scanf("%d", &i);
			getchar(); //吞掉回车
			if (i > j || i == 0)
			{
				printf("输入错误，重新输入");
			}
			else
			{
				break;
			}
		}
		p = q;
		while (p != NULL && j != i)
		{
			p = p->next;
		}
		if (p)
		{
			printf("请输入图书登录号(小于10位数)：");
			scanf("%s", p->data.book_num);
			getchar();

			printf("请输入书名(小于10位数)：");
			scanf("%s", p->data.book_name);
			getchar();

			printf("请输入作者名(小于10位数)：");
			scanf("%s", p->data.book_author);
			getchar();

			printf("请输入图书类别(小于10位数)：");
			scanf("%s", p->data.book_type);
			getchar();

			printf("请输入图书出版单位(小于10位数)：");
			scanf("%s", p->data.book_publish);
			getchar();

			printf("请输入图书出版时间(小于8位数)：");
			scanf("%s", p->data.book_time);
			getchar();

			printf("请输入图书价格：");
			scanf("%f", &p->data.book_price);
			getchar();

			printf("请输入图书数量：");
			scanf("%d", &p->data.book_rest);
			getchar();
		}
		printf("-------------------------");

		printf("|                       |");

		printf("|      是否确认修改      |");

		printf("| 1.是             2.否 |");

		printf("|                       |");

		printf("-------------------------\n");
		while (1) //利用死循环可有效防止其他按键干扰
		{
			t = getchar();
			if (t == '1')
			{
				break;
			}
			else if (t == '2')
			{
				exit(0);
			}
		}
		fp = fopen("test", "wb");
		if (fp = NULL)
		{
			printf("cannot open file");
		}
		if (fwrite(p, N, 1, fp) != 1)
		{
			printf("write error!");
		}
		fclose(fp);
		if (p != NULL)
		{
			p = q->next;
			fp = fopen("test", "ab");
			if (fp = NULL)
			{
				printf("cannot open file");
			}
			while (p != NULL)
			{
				if (fwrite(p, N, 1, fp) != 1)
				{
					printf("write error!");
				}
				p = p->next;
			}
			fclose(fp);
		}
		system("cls");
		printf("修改成功，返回");
		break;
	} while (1);
}

void delete_book() //删除图书
{
	book p, head, q, pre;
	FILE *fp;
	char delete_number[20];
	head = ss();
	p = head;
	print_book();
	printf("请输入您要删除的书号:");
	scanf("%s", &delete_number);
	while (p != NULL && p->next->data.book_num == delete_number)
	{
		pre = p;
		p = p->next;
	}

	if (p != NULL)
	{

		pre->next = p->next;
	}
	free(p);

	fp = fopen("test.text", "wb");
	if (fp == NULL)
	{
		printf("cannot open file");
	}
	if (fwrite(head, N, 1, fp) != 1) //将p所指向的一段大小为N的内容存入fp所指向的文件中
	{
		printf("write error");
	}
	fclose(fp);
	if (head != NULL)
	{
		p = head->next;
		fp = fopen("text.text", "ab");
		if (fp == NULL)
		{
			printf("cannot open file");
		}
		while (p != NULL)
		{
			if (fwrite(p, N, 1, fp) != 1) //将p所指向的一段大小为N的内容存入fp所指向的文件中
			{
				printf("write error");
			}
			p = p->next;
		}
		fclose(fp);
	}
	printf("删除成功！");
	printf("输入任意数字返回：\n");
	char t[10];
	fgets(t, 5, stdin);
}

void account_creat() //创建账户
{					 //p为文件中的信息，head为文件中的头信息，q为输入的信息
	student p, head, q, num;
	int number = 1;
	int flag;
	head = sss();
	p = head;
	num = head;
	q = (student)malloc(M);
	char s[20], s2[20];
	system("cls");

	while (num)
	{
		number++;
		num = num->next;
	}
	q->data.stu_id = number;
	do
	{ //输入账号
		flag = 1;
		p = head;
		printf("请输入账号：（不大于20位）");
		scanf("%s", &s);
		getchar();
		while (p != NULL)
		{
			if (!strcmp(p->data.stu_acc, s))
			{
				flag = 0;
			}
			p = p->next;
		}
		if (!flag)
		{
			printf("账户名已被使用，请重新输入！\n");
		}
		else
		{
			strcpy(q->data.stu_acc, s);
			break;
		}
	} while (1);

	do
	{ //输入密码
		printf("请输入密码：（不大于20位）");
		scanf("%s", &s);
		getchar();
		printf("请再次输入密码:");
		scanf("%s", &s2);
		getchar();
		if (strcmp(s, s2))
		{
			printf("密码不一致，请重新输入!");
		}
		else
		{
			strcpy(q->data.stu_passw, s);
			break;
		}

	} while (1);

	printf("请完善您的用户信息!\n");
	printf("请输入您的学号:");
	scanf("%s", q->data.stu_num);
	getchar();
	printf("请输入您的姓名:");
	scanf("%s", q->data.stu_name);
	getchar();
	save_user(q);
	printf("输入任意键返回");
	char t;
	scanf("%c", &t);
	getchar();
	menu_user();
}

void account_delete() //删除账户
{
	student p, head, q, pre;
	FILE *fp;
	int delete_number;
	head = sss();
	p = head;
	print_user();
	printf("请输入您要删除的用户id:");
	scanf("%d", &delete_number);
	while (p != NULL && p->next->data.stu_id == delete_number)
	{
		pre = p;
		p = p->next;
	}

	if (p != NULL)
	{

		pre->next = p->next;
	}
	free(p);

	fp = fopen("student.text", "wb");
	if (fp == NULL)
	{
		printf("cannot open file");
	}
	if (fwrite(head, N, 1, fp) != 1) //将p所指向的一段大小为N的内容存入fp所指向的文件中
	{
		printf("write error");
	}
	fclose(fp);
	if (head != NULL)
	{
		p = head->next;
		fp = fopen("student.text", "ab");
		if (fp == NULL)
		{
			printf("cannot open file");
		}
		while (p != NULL)
		{
			if (fwrite(p, N, 1, fp) != 1) //将p所指向的一段大小为N的内容存入fp所指向的文件中
			{
				printf("write error");
			}
			p = p->next;
		}
		fclose(fp);
	}
	printf("删除成功！");
}

void change_password()//修改密码
{

}

void sign_in() //登录
{
	char account[20];
	char password[20];
	char t[10];
	student p, head;
	head = sss();
	
	do{
	p = head;
	printf("请输入账号：");
	gets(account);
	printf("请输入密码：");
	gets(password);
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->data.stu_acc, account) == 0)
		{
			break;
		}
		p = p->next;
	}
	if(p!=NULL){
		if(strcmp(p->data.stu_passw,password)==0){
			printf("登录成功！\n");
			printf("输入任意数字继续：\n");
			fgets(t, 5, stdin);
			menu_sign(p);
		}
		else{
			printf("密码错误，请重新输入!\n");
			printf("输入任意数字返回：\n");
			fgets(t, 5, stdin);
		}
	}
	else{
		printf("账号错误，请重新输入！\n");
		printf("输入任意数字返回：\n");
		fgets(t, 5, stdin);
	}
	}while(1);
}

int main() //主函数
{
	menu_first();
	return 0;
}
