#include<iostream>

using namespace std;

const int N = 6;//设置矩阵的大小

bool is_choice[N];//记录是否将第i个点加入团中
bool picks[N];//记录已经放入团中的顶点
int pick_sum;//记录已经放入团中的节点数
int pick_max;//记录最优值
int point_sum;//点数


//判断第t个结点是否能够放入团中
bool is_place(int t, int a[][N])
{
	for (int i = 0; i < t; i++)//判断前面的t-1个结点是否与t结点相连
	{
		if (is_choice[i] && !a[t][i])
		{
			return false;
		}
	}
	return true;
}

//求解最大团问题
void max_corp(int t, int a[][N])
{
	if (t >= point_sum)
	{
		if (pick_sum > pick_max)//现在的路径大于最优值时才更新
		{
			for (int i = 0; i < point_sum; i++)
			{
				picks[i] = is_choice[i];//记录最优值结点号
			}
			pick_max = pick_sum;//记录最优值
		}
		return;
	}
	if (is_place(t, a))
	{
		is_choice[t] = 1;
		pick_sum++;
		max_corp(t + 1, a);
		pick_sum--;//回溯
	}
	if (pick_sum + point_sum - t <= pick_max)
		return;
	else//只有已经选择的结点和剩下的节点值大于最优解，才继续往下递归
	{
		is_choice[t] = 0;
		max_corp(t + 1, a);//进入我不选这个顶点的情况
	}
}

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
	pick_sum = 0;//记录已经放入团中的节点数
	pick_max = 0;//记录最优值
	point_sum = 6;//节点个数
	max_corp(0, Graph);


	cout << "最大团的结点个数为：" << pick_max << endl;
	cout << "构成最大团的结点为：" << endl;
	Print(picks);

	return 0;
}