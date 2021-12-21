#include<iostream>

using namespace std;

const int N = 6;//���þ���Ĵ�С

bool is_choice[N];//��¼�Ƿ񽫵�i�����������
bool picks[N];//��¼�Ѿ��������еĶ���
int pick_sum;//��¼�Ѿ��������еĽڵ���
int pick_max;//��¼����ֵ
int point_sum;//����


//�жϵ�t������Ƿ��ܹ���������
bool is_place(int t, int a[][N])
{
	for (int i = 0; i < t; i++)//�ж�ǰ���t-1������Ƿ���t�������
	{
		if (is_choice[i] && !a[t][i])
		{
			return false;
		}
	}
	return true;
}

//������������
void max_corp(int t, int a[][N])
{
	if (t >= point_sum)
	{
		if (pick_sum > pick_max)//���ڵ�·����������ֵʱ�Ÿ���
		{
			for (int i = 0; i < point_sum; i++)
			{
				picks[i] = is_choice[i];//��¼����ֵ����
			}
			pick_max = pick_sum;//��¼����ֵ
		}
		return;
	}
	if (is_place(t, a))
	{
		is_choice[t] = 1;
		pick_sum++;
		max_corp(t + 1, a);
		pick_sum--;//����
	}
	if (pick_sum + point_sum - t <= pick_max)
		return;
	else//ֻ���Ѿ�ѡ��Ľ���ʣ�µĽڵ�ֵ�������Ž⣬�ż������µݹ�
	{
		is_choice[t] = 0;
		max_corp(t + 1, a);//�����Ҳ�ѡ�����������
	}
}

//��ӡ���Ľ��
void Print(bool picks[N])
{
	for (int i = 0; i < point_sum; i++)
	{
		if (picks[i])
			cout << i << " ";
	}
	cout << endl;
}

int main()
{
	int Graph[N][N] = {//�����ͼ
		{0,1,1,1,0,0},
		{1,0,1,1,0,1},
		{1,1,0,1,1,0},
		{1,1,1,0,1,0},
		{0,0,1,1,0,1},
		{0,1,0,0,1,0} };
	pick_sum = 0;//��¼�Ѿ��������еĽڵ���
	pick_max = 0;//��¼����ֵ
	point_sum = 6;//�ڵ����
	max_corp(0, Graph);


	cout << "����ŵĽ�����Ϊ��" << pick_max << endl;
	cout << "��������ŵĽ��Ϊ��" << endl;
	Print(picks);

	return 0;
}