#include "speechControl.h"

speechControl::speechControl()
{
	//初始化属性函数
	this->speech_init();

	//创建比赛选手函数
	this->speech_create();

	//获取往届数据
	this->speech_load();
}
speechControl::~speechControl()
{
}

void speechControl::show_ui()
{
	cout << "****************************************************" << endl;
	cout << "***************** 欢迎参加演讲比赛 *****************" << endl;
	cout << "***************** 1、开始演讲比赛   ****************" << endl;
	cout << "***************** 2、查看往届比赛   ****************" << endl;
	cout << "***************** 3、清空比赛记录   ****************" << endl;
	cout << "***************** 4、退出比赛程序   ****************" << endl;
	cout << "****************************************************" << endl;
}

void speechControl::exit_system()                   //退出程序
{
	cout << "请确认是否退出？" << endl;
	cout << "1、退出" << endl;
	cout << "2、取消" << endl;

	int select = -1;
	cin >> select;
	if (select == 1)
	{
		cout << "欢迎下次使用" << endl;
		//sleep(1);
		exit(0);
	}
	system("cls");
	return;
}

void speechControl::speech_init()                   //初始化
{
	//初始化容器
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m1.clear();
	this->m2.clear();

	//初始化比赛轮数
	this->index = 1;

	this->fileIsEmpty = true;

	return ;
}
void speechControl::speech_create()                 //创建选手函数
{
	string nameSeed = "ABCDEFGHIJKLMN";
	for (int i = 0; i < 12; i++)
	{
		string name = "选手";
		name += nameSeed[i];

		spaker sp;
		sp.m_Name = name;
		sp.m_ID = 10000 + i;
		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		this->v1.push_back(sp.m_ID);
		this->m1.insert(make_pair(sp.m_ID,sp));
	}

	return ;
}

void speechControl::speech_draw()                   //比赛抽签函数
{
	cout << "***** 第" << this->index << "轮比赛抽签开始 *****" << endl;
	if (this->index == 1)
	{
		//第一轮抽签
		random_shuffle(v1.begin(),v1.end());
	}
	else
	{
		//第二轮抽签
		random_shuffle(v2.begin(),v2.end());
	}
	Sleep(0);
	cout << "***** 第" << this->index << "轮比赛抽签完毕 *****" << endl;
	
	return ;
}
void speechControl::speech_begin()                  //比赛开始,打分
{
	multimap<double, int, greater<>> group;         //临时容器，用于分组晋级的，key 平均分，value 选手编号，指定大到小排序
	int num = 0;                                    //记录比赛完成的人数

	cout << "***** 第" << this->index << "轮比赛正式开始 *****" << endl;
	vector<int>v;                                                         //比赛选手容器
	if (this->index == 1)
		v = v1;
	else
		v = v2;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		num++;

		deque<double>d;      //存储打分容器
		double score = 0;
		for (int i = 0; i < 10; i++)               //10个评委开始打分
		{
			score = rand() % 41 + 60;
			d.push_back(score);
		}
		sort(d.begin(),d.end());     //评委打分排序
		d.pop_back();
		d.pop_front();               //去掉最高分和最低分

		double sum = accumulate(d.begin(),d.end(),0.0f);   //总分
		double avg = sum / (double)d.size();               //平均分

		//写入选手信息容器中
		this->m1[*it].m_Score[this->index - 1] = avg;

		group.insert(make_pair(avg,*it));        //将比赛信息加入到临时容器

		//6个人一组，开始分组
		if (num % 6 == 0)
		{
			//6个人一小组比赛完成，获取小组前三名
			int count = 0;
			for (multimap<double, int, greater<>>::iterator it = group.begin();
				it != group.end() && count < 3; it++, count++)
			{
				if (this->index == 1)       //第一轮比赛
				{
					v2.push_back(it->second);
				}
				else
				{
					v3.push_back(it->second);
				}
			}
				group.clear();          //清空临时容器

		}
 
	}
	Sleep(0);
	cout << "***** 第" << this->index << "轮比赛完毕 *****" << endl;
	return ;
}
void speechControl::speech_show()                   //展示晋级信息
{
	cout << "***** 第" << this->index << "轮比赛晋级选择如下 *****" << endl;
	
	vector<int>v;      //晋级选手容器如下
	if (this->index == 1)
		v = v2;
	else
		v = v3;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << this->m1[*it].m_Name << "\t编号：" << *it << "\t平均分：" << this->m1[*it].m_Score[this->index - 1] << endl;
	}

	system("pause");
	system("cls");
	return;
}

void speechControl::speech_save()                   //保存晋级选择信息到文件中
{
	ofstream ofs;
	ofs.open(FILENAME,ios::out | ios::app);
	for (vector<int>::iterator it = this->v3.begin(); it != this->v3.end(); it++)
	{
		ofs << this->m1[*it].m_Name << ","
			<< this->m1[*it].m_ID << ","
			<< this->m1[*it].m_Score[1] << ",";
	}
	ofs << endl;

	this->fileIsEmpty = false;                      //有了比赛数据后，文件存在标志改变

	return;
}

void speechControl::speech_Course()                 //比赛过程函数
{
	//第一轮比赛，抽签
	speech_draw();

	//比赛开始
	speech_begin();

	//显示晋级选项信息
	speech_show();

	//第二轮比赛
	this->index++;

	//比赛抽签
	speech_draw();

	//比赛开始
	speech_begin();

	//显示比赛晋级信息
	speech_show();

	//保存比赛结果到文件中
	speech_save();

	//比赛完成后，重置数据
	this->speech_init();

	this->fileIsEmpty = false;

	//重新创建选手
	this->speech_create();

	//重新读取当前比赛数据，历史数据
	this->speech_load();
}

void speechControl::speech_load()                   //历史记录获取函数
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	//第一种情况，文件不存在
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->fileIsEmpty = true;

		ifs.close();
		return;
	}

	//第二种情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//第三种情况，文件存在且有数据
	this->fileIsEmpty = false;
	ifs.putback(ch);                      //将读到的数据返回
	string record;
	
	int index = 0;
	while (ifs >> record)
	{
		//将读到的数据分解写到容器中
		vector<string>vs;
		int pos = -1;
		int start = 0;

		while(1)
		{
			pos = record.find(',',start);
		    if (pos == -1)
		    {
			    break;
		    }
		    string temp = record.substr(start, pos - start);
		    vs.push_back(temp);                            //写到历史记录的容器中
			start = pos + 1;
	    }
		this->m2.insert(make_pair(index,vs));            //连同往届届数一起写到容器中
		index++;
	}
	ifs.close();
	return;
}

void speechControl::speech_record()                 //查看往届记录
{
	if (this->fileIsEmpty)
	{
		cout << "无往届比较记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (map<int, vector<string>>::iterator it = this->m2.begin(); it != this->m2.end(); it++)
	{
		cout << "***** 第" << it->first+1 << "届比赛记录如下 *****" << endl;
		cout << "《冠军》 " << (*it).second[0] << "\t编号：" << (*it).second[1] << "\t得分：" << (*it).second[2] << endl;
		cout << "《亚军》 " << (*it).second[3] << "\t编号：" << (*it).second[4] << "\t得分：" << (*it).second[5] << endl;
		cout << "《季军》 " << (*it).second[6] << "\t编号：" << (*it).second[7] << "\t得分：" << (*it).second[8] << endl;
		cout << endl;
	}
	system("pause");
	system("cls");
	return;
}

void speechControl::speech_clear()                  //清空文件
{
	if (this->fileIsEmpty)
	{
		cout << "清空成功" << endl;
	}
	else
	{
	cout << "请确认是否清空？" << endl;
	cout << "1、清空" << endl;
	cout << "2、取消" << endl;

	int select = -1;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME,ios::out |ios::trunc);
		ofs.close();

		this->m2.clear();
		this->fileIsEmpty = true;

		cout << "清空成功" << endl;
	}
    }
	system("pause");
	system("cls");
	return;
}


