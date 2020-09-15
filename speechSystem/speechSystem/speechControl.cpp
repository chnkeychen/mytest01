#include "speechControl.h"

speechControl::speechControl()
{
	//��ʼ�����Ժ���
	this->speech_init();

	//��������ѡ�ֺ���
	this->speech_create();

	//��ȡ��������
	this->speech_load();
}
speechControl::~speechControl()
{
}

void speechControl::show_ui()
{
	cout << "****************************************************" << endl;
	cout << "***************** ��ӭ�μ��ݽ����� *****************" << endl;
	cout << "***************** 1����ʼ�ݽ�����   ****************" << endl;
	cout << "***************** 2���鿴�������   ****************" << endl;
	cout << "***************** 3����ձ�����¼   ****************" << endl;
	cout << "***************** 4���˳���������   ****************" << endl;
	cout << "****************************************************" << endl;
}

void speechControl::exit_system()                   //�˳�����
{
	cout << "��ȷ���Ƿ��˳���" << endl;
	cout << "1���˳�" << endl;
	cout << "2��ȡ��" << endl;

	int select = -1;
	cin >> select;
	if (select == 1)
	{
		cout << "��ӭ�´�ʹ��" << endl;
		//sleep(1);
		exit(0);
	}
	system("cls");
	return;
}

void speechControl::speech_init()                   //��ʼ��
{
	//��ʼ������
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m1.clear();
	this->m2.clear();

	//��ʼ����������
	this->index = 1;

	this->fileIsEmpty = true;

	return ;
}
void speechControl::speech_create()                 //����ѡ�ֺ���
{
	string nameSeed = "ABCDEFGHIJKLMN";
	for (int i = 0; i < 12; i++)
	{
		string name = "ѡ��";
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

void speechControl::speech_draw()                   //������ǩ����
{
	cout << "***** ��" << this->index << "�ֱ�����ǩ��ʼ *****" << endl;
	if (this->index == 1)
	{
		//��һ�ֳ�ǩ
		random_shuffle(v1.begin(),v1.end());
	}
	else
	{
		//�ڶ��ֳ�ǩ
		random_shuffle(v2.begin(),v2.end());
	}
	Sleep(0);
	cout << "***** ��" << this->index << "�ֱ�����ǩ��� *****" << endl;
	
	return ;
}
void speechControl::speech_begin()                  //������ʼ,���
{
	multimap<double, int, greater<>> group;         //��ʱ���������ڷ�������ģ�key ƽ���֣�value ѡ�ֱ�ţ�ָ����С����
	int num = 0;                                    //��¼������ɵ�����

	cout << "***** ��" << this->index << "�ֱ�����ʽ��ʼ *****" << endl;
	vector<int>v;                                                         //����ѡ������
	if (this->index == 1)
		v = v1;
	else
		v = v2;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		num++;

		deque<double>d;      //�洢�������
		double score = 0;
		for (int i = 0; i < 10; i++)               //10����ί��ʼ���
		{
			score = rand() % 41 + 60;
			d.push_back(score);
		}
		sort(d.begin(),d.end());     //��ί�������
		d.pop_back();
		d.pop_front();               //ȥ����߷ֺ���ͷ�

		double sum = accumulate(d.begin(),d.end(),0.0f);   //�ܷ�
		double avg = sum / (double)d.size();               //ƽ����

		//д��ѡ����Ϣ������
		this->m1[*it].m_Score[this->index - 1] = avg;

		group.insert(make_pair(avg,*it));        //��������Ϣ���뵽��ʱ����

		//6����һ�飬��ʼ����
		if (num % 6 == 0)
		{
			//6����һС�������ɣ���ȡС��ǰ����
			int count = 0;
			for (multimap<double, int, greater<>>::iterator it = group.begin();
				it != group.end() && count < 3; it++, count++)
			{
				if (this->index == 1)       //��һ�ֱ���
				{
					v2.push_back(it->second);
				}
				else
				{
					v3.push_back(it->second);
				}
			}
				group.clear();          //�����ʱ����

		}
 
	}
	Sleep(0);
	cout << "***** ��" << this->index << "�ֱ������ *****" << endl;
	return ;
}
void speechControl::speech_show()                   //չʾ������Ϣ
{
	cout << "***** ��" << this->index << "�ֱ�������ѡ������ *****" << endl;
	
	vector<int>v;      //����ѡ����������
	if (this->index == 1)
		v = v2;
	else
		v = v3;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << this->m1[*it].m_Name << "\t��ţ�" << *it << "\tƽ���֣�" << this->m1[*it].m_Score[this->index - 1] << endl;
	}

	system("pause");
	system("cls");
	return;
}

void speechControl::speech_save()                   //�������ѡ����Ϣ���ļ���
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

	this->fileIsEmpty = false;                      //���˱������ݺ��ļ����ڱ�־�ı�

	return;
}

void speechControl::speech_Course()                 //�������̺���
{
	//��һ�ֱ�������ǩ
	speech_draw();

	//������ʼ
	speech_begin();

	//��ʾ����ѡ����Ϣ
	speech_show();

	//�ڶ��ֱ���
	this->index++;

	//������ǩ
	speech_draw();

	//������ʼ
	speech_begin();

	//��ʾ����������Ϣ
	speech_show();

	//�������������ļ���
	speech_save();

	//������ɺ���������
	this->speech_init();

	this->fileIsEmpty = false;

	//���´���ѡ��
	this->speech_create();

	//���¶�ȡ��ǰ�������ݣ���ʷ����
	this->speech_load();
}

void speechControl::speech_load()                   //��ʷ��¼��ȡ����
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	//��һ��������ļ�������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->fileIsEmpty = true;

		ifs.close();
		return;
	}

	//�ڶ������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//������������ļ�������������
	this->fileIsEmpty = false;
	ifs.putback(ch);                      //�����������ݷ���
	string record;
	
	int index = 0;
	while (ifs >> record)
	{
		//�����������ݷֽ�д��������
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
		    vs.push_back(temp);                            //д����ʷ��¼��������
			start = pos + 1;
	    }
		this->m2.insert(make_pair(index,vs));            //��ͬ�������һ��д��������
		index++;
	}
	ifs.close();
	return;
}

void speechControl::speech_record()                 //�鿴�����¼
{
	if (this->fileIsEmpty)
	{
		cout << "������Ƚϼ�¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (map<int, vector<string>>::iterator it = this->m2.begin(); it != this->m2.end(); it++)
	{
		cout << "***** ��" << it->first+1 << "�������¼���� *****" << endl;
		cout << "���ھ��� " << (*it).second[0] << "\t��ţ�" << (*it).second[1] << "\t�÷֣�" << (*it).second[2] << endl;
		cout << "���Ǿ��� " << (*it).second[3] << "\t��ţ�" << (*it).second[4] << "\t�÷֣�" << (*it).second[5] << endl;
		cout << "�������� " << (*it).second[6] << "\t��ţ�" << (*it).second[7] << "\t�÷֣�" << (*it).second[8] << endl;
		cout << endl;
	}
	system("pause");
	system("cls");
	return;
}

void speechControl::speech_clear()                  //����ļ�
{
	if (this->fileIsEmpty)
	{
		cout << "��ճɹ�" << endl;
	}
	else
	{
	cout << "��ȷ���Ƿ���գ�" << endl;
	cout << "1�����" << endl;
	cout << "2��ȡ��" << endl;

	int select = -1;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME,ios::out |ios::trunc);
		ofs.close();

		this->m2.clear();
		this->fileIsEmpty = true;

		cout << "��ճɹ�" << endl;
	}
    }
	system("pause");
	system("cls");
	return;
}


