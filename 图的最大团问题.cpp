#include<iostream>
#include<vector>

using namespace std;

const int N = 6;//���þ���Ĵ�С

vector<bool> is_choice(N);//��¼�Ƿ񽫵�i�����������
bool picks[N];//��¼�Ѿ��������еĶ���
int pick_sum;//��¼�Ѿ��������еĽڵ���
int pick_max;//��¼����ֵ
int point_sum;//������
int c[N];//c[i]Ϊǰi�����㹹�ɵ����������
vector<int> i_link;//��¼��i���ڵĶ���ļ���

//��ǰ�ҵ���t�������ڵ�����Ķ���
int tLink(int t,int a[][N])//j�����Ǵӵ�jλ��ǰ��
{
	int flag = 1;
	for (int i = t - 1; i >= 0; i--) {
		if (a[t][i] && flag) {
			i_link.push_back(i);
			continue;
		}
		if (a[t][i]) {
			i_link.push_back(i);
		}
	}
	return i_link.size() > 0 ? i_link[0] : -1;
}
void findCi(int a[][N]) {
	for (int i = 1; i < N; i++) {
		is_choice[i] = 1;
		int j = tLink(i,a);
		//��iû�����ڵģ��������������ڶ�������1С���������
		if (j == -1 || i_link.size()+1 <= pick_max) {
			c[i] = c[i - 1];
			continue;
		}
		else {
			is_choice[j] = 1;
			pick_sum++;
			if (pick_sum + c[j] <= pick_max) {
				c[i] = c[i - 1];
				break;
			}
			while (tLink(i, j, a) != -1) {
				int k = tLink(i, j, a);
				is_choice[k] = 1;
				pick_sum++;
				if (pick_sum + c[k] <= pick_max) {
					c[i] = c[i - 1];
					break;
				}
				else {
					j = k;
				}
			}
			if (pick_sum > pick_max)//���ڵ�·����������ֵʱ�Ÿ���
			{
				for (int k = 0; k <= i; k++)
				{
					picks[k] = is_choice[k];//��¼����ֵ����
				}
				pick_max = pick_sum;//��¼����ֵ
				c[i] = c[i - 1] + 1;
			}
			is_choice.clear();
			is_choice.resize(N);
			pick_sum = 1;
		}
	}
}
//������������
//void max_corp(int t, int a[][N])
//{
//	if (pick_sum > pick_max)//���ڵ�·����������ֵʱ�Ÿ���
//	{
//		for (int i = 0; i < N; i++)
//		{
//			picks[i] = is_choice[i];//��¼����ֵ����
//		}
//		pick_max = pick_sum;//��¼����ֵ
//		return;
//	}
//	if (tLink(t,t,a) == -1) {//t������ǰ��Ķ��㶼�����ڣ�ֱ�ӷ���
//		c[t] = c[t - 1];
//		return;
//	}
//	else {
//		int j = tLink(t,t, a);//jΪ��t���ڵ�����Ķ���
//		is_choice[t] = 1;
//		if (pick_sum + c[j] <= pick_max) {
//			c[t] = c[t - 1];
//			s.push_back(t);
//			return;
//		}
//		else {
//			is_choice[j] = 1;
//			pick_sum++;
//			max_corp(j, a);
//		}
//	}
//}

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
	pick_sum = 1;//��¼�Ѿ��������еĽڵ���
	pick_max = 1;//��¼����ֵ
	point_sum = 6;//�ڵ����
	c[0] = 1;
	is_choice[0] = 1;
	i_link = { 0,1,1,1,0,0 };
	findCi(Graph);


	cout << "����ŵĽ�����Ϊ��" << pick_max << endl;
	cout << "��������ŵĽ��Ϊ��" << endl;
	Print(picks);

	return 0;
}