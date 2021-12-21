#include<iostream>
#include<vector>

using namespace std;

const int N = 6;//设置矩阵的大小

vector<bool> is_choice(N);//记录是否将第i个点加入团中
vector<int> picks(N);//记录已经放入团中的顶点
int pick_sum;//记录已经放入团中的节点数
int pick_max;//记录最优值
int point_sum;//顶点数
int c[N];//c[i]为前i个顶点构成的最大团数量
vector<vector<int>> link(N);//link[i]表示编号小于i且与i相邻的顶点

//找到编号小于i且与i相邻的顶点,正序排列
void flink(int a[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i][j])link[i].push_back(j);
		}
	}
}

//以j为起始点，寻找link[i]中与j相邻的顶点
int tLink(int t, int j,int a[][N])
{
	for (int i = link[t].size()-pick_sum; i >= 0; i--) {
		for (int k = t - 1; k >= 0; k--) {
			//选中的点必须要和其他选中的点相连
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
		//与i没有相邻的，或者是与其相邻顶点数加1小于最大团数
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
				if (pick_sum > pick_max)//现在的路径大于最优值时才更新
				{
					picks.clear();
					picks.resize(N);
					for (int k = 0; k <= i; k++)
					{
						picks[k] = is_choice[k];//记录最优值结点号
					}
					pick_max = pick_sum;//记录最优值
					c[i] = c[i - 1] + 1;
					break;
				}
				//回溯
				is_choice[link[i][j]] = 0;
				pick_sum--;
			}
		}
		is_choice.clear();
		is_choice.resize(N);
		pick_sum = 1;
	}
}

//打印最后的结果
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
	int Graph[N][N] = {//传入的图
		{0,1,0,1,0,0},
		{1,0,1,1,1,1},
		{0,1,0,1,1,1},
		{1,1,1,0,0,0},
		{0,1,1,0,0,1},
		{0,1,1,0,1,0} };
	pick_sum = 1;//记录已经放入团中的节点数
	pick_max = 1;//记录最优值
	point_sum = 6;//节点个数
	c[0] = 1;
	is_choice[0] = 1;
	flink(Graph);
	findCi(Graph);


	cout << "最大团的结点个数为：" << pick_max << endl;
	cout << "构成最大团的结点为：" << endl;
	Print(picks);
	cout << "c[i]:" << endl;
	for (int i = 0; i < N; i++) {
		cout << c[i] << " ";
	}
	cout << endl;

	return 0;
}