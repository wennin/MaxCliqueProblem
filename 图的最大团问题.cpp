#include<iostream>
#include<vector>

using namespace std;

const int N = 6;//设置矩阵的大小

vector<bool> is_choice(N);//记录是否将第i个点加入团中
bool picks[N];//记录已经放入团中的顶点
int pick_sum;//记录已经放入团中的节点数
int pick_max;//记录最优值
int point_sum;//顶点数
int c[N];//c[i]为前i个顶点构成的最大团数量
vector<int> i_link;//记录和i相邻的顶点的集合

//往前找到与t顶点相邻的最近的顶点
int tLink(int t,int a[][N])//j代表是从第j位往前找
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
		//与i没有相邻的，或者是与其相邻顶点数加1小于最大团数
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
			if (pick_sum > pick_max)//现在的路径大于最优值时才更新
			{
				for (int k = 0; k <= i; k++)
				{
					picks[k] = is_choice[k];//记录最优值结点号
				}
				pick_max = pick_sum;//记录最优值
				c[i] = c[i - 1] + 1;
			}
			is_choice.clear();
			is_choice.resize(N);
			pick_sum = 1;
		}
	}
}
//求解最大团问题
//void max_corp(int t, int a[][N])
//{
//	if (pick_sum > pick_max)//现在的路径大于最优值时才更新
//	{
//		for (int i = 0; i < N; i++)
//		{
//			picks[i] = is_choice[i];//记录最优值结点号
//		}
//		pick_max = pick_sum;//记录最优值
//		return;
//	}
//	if (tLink(t,t,a) == -1) {//t顶点与前面的顶点都不相邻，直接返回
//		c[t] = c[t - 1];
//		return;
//	}
//	else {
//		int j = tLink(t,t, a);//j为与t相邻的最近的顶点
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

//打印最后的结果
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
	int Graph[N][N] = {//传入的图
		{0,1,1,1,0,0},
		{1,0,1,1,0,1},
		{1,1,0,1,1,0},
		{1,1,1,0,1,0},
		{0,0,1,1,0,1},
		{0,1,0,0,1,0} };
	pick_sum = 1;//记录已经放入团中的节点数
	pick_max = 1;//记录最优值
	point_sum = 6;//节点个数
	c[0] = 1;
	is_choice[0] = 1;
	i_link = { 0,1,1,1,0,0 };
	findCi(Graph);


	cout << "最大团的结点个数为：" << pick_max << endl;
	cout << "构成最大团的结点为：" << endl;
	Print(picks);

	return 0;
}