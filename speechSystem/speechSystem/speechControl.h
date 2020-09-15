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
	void show_ui();                       //չʾ����
	void exit_system();                   //�˳�����
	void speech_init();                   //��ʼ����������
	void speech_create();                 //����ѡ�ֺ���
	void speech_Course();                 //�������̺���
	void speech_draw();                   //������ǩ����
	void speech_begin();                  //������ʼ
	void speech_show();                   //չʾ������Ϣ��
	void speech_save();                   //�������ѡ����Ϣ���ļ���
	void speech_load();                   //��ʷ��¼��ȡ����
	void speech_record();                 //�鿴�����¼
	void speech_clear();                  //����ļ�

public:
	vector<int>v1;        //��һ�ֱ���ѡ�ֱ������
	vector<int>v2;        //�ڶ��ֱ���ѡ�ֱ������
	vector<int>v3;
	map<int, spaker>m1;   //���ѡ�ֱ�ź�ѡ����Ϣ��������key ֵΪѡ���ţ�value ֵΪѡ����Ϣ

	map<int, vector<string>>m2;   //��ʷ������¼����

	int index;            //��������

	bool fileIsEmpty;     //�ļ��Ƿ���ڱ�־
};

