#include<iostream>
#include<vector>

using namespace std;

const int N = 6;//���þ���Ĵ�С

vector<bool> is_choice(N);//��¼�Ƿ񽫵�i�����������
vector<int> picks(N);//��¼�Ѿ��������еĶ���
int pick_sum;//��¼�Ѿ��������еĽڵ���
int pick_max;//��¼����ֵ
int point_sum;//������
int c[N];//c[i]Ϊǰi�����㹹�ɵ����������
vector<vector<int>> link(N);//link[i]��ʾ���С��i����i���ڵĶ���

//�ҵ����С��i����i���ڵĶ���,��������
void flink(int a[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i][j])link[i].push_back(j);
		}
	}
}

//��jΪ��ʼ�㣬Ѱ��link[i]����j���ڵĶ���
int tLink(int t, int j,int a[][N])
{
	for (int i = link[t].size()-pick_sum; i >= 0; i--) {
		for (int k = t - 1; k >= 0; k--) {
			//ѡ�еĵ����Ҫ������ѡ�еĵ�����
			if (is_choice[k] && a[k][link[t][i]] == 0)
				return -1;
		}
		if (a[link[t][i]][j]) {
			return link[t][i];
		}
	}
	return -1;
}

void findCi(int a[][N]) {
	for (int i = 1; i < N; i++) {
		is_choice[i] = 1;
		int n = link[i].size();
		//��iû�����ڵģ��������������ڶ�������1С���������
		if (n == 0 || n + 1 <= pick_max) {
			c[i] = c[i - 1];
			is_choice[i] = 0;
			continue;
		}
		else {
			for (int j = n - 1; j >= 0; j--) {
 				is_choice[link[i][j]] = 1;
				pick_sum++;
				if (pick_sum + c[link[i][j]] <= pick_max) {
					c[i] = c[i - 1];
					break;
				}
				int k = tLink(i, link[i][j], a);
				while (k != -1) {
					is_choice[k] = 1;
					pick_sum++;
					if (pick_sum + c[k] <= pick_max) {
						c[i] = c[i - 1];
						break;
					}
					k = tLink(i, k, a);
				}
				if (pick_sum > pick_max)//���ڵ�·����������ֵʱ�Ÿ���
				{
					picks.clear();
					picks.resize(N);
					for (int k = 0; k <= i; k++)
					{
						picks[k] = is_choice[k];//��¼����ֵ����
					}
					pick_max = pick_sum;//��¼����ֵ
					c[i] = c[i - 1] + 1;
					break;
				}
				//����
				is_choice[link[i][j]] = 0;
				pick_sum--;
			}
		}
		is_choice.clear();
		is_choice.resize(N);
		pick_sum = 1;
	}
}

//��ӡ���Ľ��
void Print(vector<int> picks)
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
		{0,1,0,1,0,0},
		{1,0,1,1,1,1},
		{0,1,0,1,1,1},
		{1,1,1,0,0,0},
		{0,1,1,0,0,1},
		{0,1,1,0,1,0} };
	pick_sum = 1;//��¼�Ѿ��������еĽڵ���
	pick_max = 1;//��¼����ֵ
	point_sum = 6;//�ڵ����
	c[0] = 1;
	is_choice[0] = 1;
	flink(Graph);
	findCi(Graph);


	cout << "����ŵĽ�����Ϊ��" << pick_max << endl;
	cout << "��������ŵĽ��Ϊ��" << endl;
	Print(picks);
	cout << "c[i]:" << endl;
	for (int i = 0; i < N; i++) {
		cout << c[i] << " ";
	}
	cout << endl;

	return 0;
}