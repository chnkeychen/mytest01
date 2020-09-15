#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <Windows.h>
#include "spaker.h"
using namespace std;

#define FILENAME "speech.csv"
class speechControl
{
public:
	speechControl();
	~speechControl();
	void show_ui();                       //展示界面
	void exit_system();                   //退出程序
	void speech_init();                   //初始化容器函数
	void speech_create();                 //创建选手函数
	void speech_Course();                 //比赛过程函数
	void speech_draw();                   //比赛抽签函数
	void speech_begin();                  //比赛开始
	void speech_show();                   //展示晋级信息的
	void speech_save();                   //保存晋级选择信息到文件中
	void speech_load();                   //历史记录获取函数
	void speech_record();                 //查看往届记录
	void speech_clear();                  //清空文件

public:
	vector<int>v1;        //第一轮比赛选手编号容器
	vector<int>v2;        //第二轮比赛选手编号容器
	vector<int>v3;
	map<int, spaker>m1;   //存放选手编号和选手信息的容器，key 值为选择编号，value 值为选手信息

	map<int, vector<string>>m2;   //历史比赛记录容器

	int index;            //比赛轮数

	bool fileIsEmpty;     //文件是否存在标志
};

