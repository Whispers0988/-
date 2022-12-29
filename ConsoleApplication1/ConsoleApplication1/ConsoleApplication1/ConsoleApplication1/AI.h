#pragma once
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "DataInfo.h"

using namespace std;



// 抽象产品类  黑白棋AI 
class HeibaiAI {
public:
	virtual PiecePos calPos(vector<vector<int>> arr, PieceColor color) = 0;
	virtual ~HeibaiAI() {}
};

// 抽象产品类  五子棋AI 
class WuziAI
{
public:
	virtual PiecePos calPos(vector<vector<int>> arr, PieceColor color) = 0;
	virtual ~WuziAI() {}
};

// 具体产品类  黑白棋简单AI 
class Heibai_E_AI : public HeibaiAI {
public:
	PiecePos calPos(vector<vector<int>> arr, PieceColor color) {
		int road = arr.size();
		srand((unsigned)time(NULL));
		PiecePos temp;
		bool flag = true;
		do {
			temp.x = (int)(round(1.0 * rand() / RAND_MAX * (road - 1) + 1));
			temp.y = (int)(round(1.0 * rand() / RAND_MAX * (road - 1) + 1));
			if (temp.x > 19 || temp.x < 1 || temp.y > 19 || temp.y < 1 || arr[temp.x - 1][temp.y - 1] != 1) {
				flag = true;
			}
			else {
				flag = false;
			}
		} while (flag); // 将循环条件改成落子不合法。随机落子位置不合法时进入循环，直到位置合法退出循环。 

		return temp;
	}
};

// 具体产品类  黑白棋中等AI 
class Heibai_D_AI : public HeibaiAI {
public:
	PiecePos calPos(vector<vector<int>> arr, PieceColor color) {
		return PiecePos(0, 0);
	}

};

// 具体产品类  黑白棋困难AI 
class Heibai_M_AI : public HeibaiAI {
public:
	PiecePos calPos(vector<vector<int>> arr, PieceColor color) {
		vector<vector<float>> scores;
		for (size_t i = 0; i < arr.size(); i++) {
			scores.push_back(vector<float>(arr.size(), 0));
		}
		for (size_t i = 0; i < arr.size(); i++) {
			for (size_t j = 0; j < arr.size(); j++) {
				PiecePos pos(i + 1, j + 1);
				if (arr[i][j] == 1) {
					scores[i][j] = zuo(pos, color, arr) + you(pos, color, arr) + shang(pos, color, arr)
						+ xia(pos, color, arr) + zuoshang(pos, color, arr) + youshang(pos, color, arr)
						+ zuoxia(pos, color, arr) + youxia(pos, color, arr);
				}
			}
		}
		int indexi = 0, indexj = 0;
		float smax = -1;
		for (size_t i = 0; i < scores.size(); i++) {
			for (size_t j = 0; j < scores.size(); j++) {
				if (scores[i][j] > smax) {
					smax = scores[i][j];
					indexi = i;
					indexj = j;
				}
			}
		}

		return PiecePos(indexi + 1, indexj + 1);

	}

protected:


	// 判断落子位置是否合法
	bool isLegal(PiecePos pos, PieceColor color, vector<vector<int>> arr) {
		vector<vector<int>> temparr = arr;

		int count_y = you(pos, color, temparr);
		int count_z = zuo(pos, color, temparr);
		int count_s = shang(pos, color, temparr);
		int count_x = xia(pos, color, temparr);
		int count_ys = youshang(pos, color, temparr);
		int count_yx = youxia(pos, color, temparr);
		int count_zs = zuoshang(pos, color, temparr);
		int count_zx = zuoxia(pos, color, temparr);
		int count = count_y + count_z + count_s + count_x + count_ys + count_yx + count_zs + count_zx;

		if (count != 0) {
			return true;
		}
		else {
			return false;
		}

	}

	int you(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempy = pos.y + i;

			if (tempy - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int zuo(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempy = pos.y - i;

			if (tempy - 1 < 0) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int shang(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x - i;

			if (tempx - 1 < 0) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int xia(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x + i;

			if (tempx - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int zuoshang(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x - i;
			int tempy = pos.y - i;
			if (tempx - 1 < 0) {
				return 0;
			}
			if (tempy - 1 < 0) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}
	}

	int youshang(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x - i;
			int tempy = pos.y + i;
			if (tempx - 1 < 0) {
				return 0;
			}
			if (tempy - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}
	}

	int youxia(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x + i;
			int tempy = pos.y + i;
			if (tempx - 1 == temparr.size()) {
				return 0;
			}
			if (tempy - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}
	}

	int zuoxia(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x + i;
			int tempy = pos.y - i;
			if (tempx - 1 == temparr.size()) {
				return 0;
			}
			if (tempy - 1 < 0) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}

	};
};

// 具体产品类  五子棋简单AI
class Wuzi_E_AI : public WuziAI {
public:
	PiecePos calPos(vector<vector<int>> arr, PieceColor color) {
		int road = arr.size();
		srand((unsigned)time(NULL));
		PiecePos temp;
		bool flag = true;
		do {
			temp.x = (int)(round(1.0 * rand() / RAND_MAX * (road - 1) + 1));
			temp.y = (int)(round(1.0 * rand() / RAND_MAX * (road - 1) + 1));
			if (temp.x > 19 || temp.x < 1 || temp.y > 19 || temp.y < 1 || arr[temp.x - 1][temp.y - 1] != 1) {
				flag = true;
			}
			else {
				flag = false;
			}
		} while (flag); // 将循环条件改成落子不合法。随机落子位置不合法时进入循环，直到位置合法退出循环。 

		return temp;
	}
};

// 具体产品类  五子棋中等AI
class Wuzi_M_AI : public WuziAI {
public:
	PiecePos calPos(vector<vector<int>> arr, PieceColor color) {
		ARKPhase = 1.0;
		DEFPhase = 1.0;

		auto defScore = calcDEFScore(arr, color);
		auto arkScore = calcARKScore(arr, color);
		vector<vector<float>> res;
		for (size_t i = 0; i < arr.size(); i++) {
			res.push_back(vector<float>(arr.size(), 0));
		}

		for (size_t i = 0; i < arr.size(); i++) {
			for (size_t j = 0; j < arr.size(); j++) {
				res[i][j] = ARKPhase * arkScore[i][j] + DEFPhase * defScore[i][j];
			}
		}

		int indexi = 0, indexj = 0;
		float smax = -1;
		bool flag = false;

		for (size_t i = 0; i < arr.size(); i++) {
			for (size_t j = 0; j < arr.size(); j++) {
				if (res[i][j] > smax) {
					smax = res[i][j];
					indexi = i;
					indexj = j;
				}
				if (res[i][j] > 1.0) {
					flag = true;
				}
			}
		}

		if (flag) {
			return PiecePos(indexi + 1, indexj + 1);
		}
		else {
			return PiecePos(arr.size() / 2 + 1, arr.size() / 2 + 1);
		}
	}

	vector<vector<float>> calcARKScore(vector<vector<int>> arr, PieceColor color) {
		int dir[8][2] = { {1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1} };
		vector<vector<float>> scores;
		for (size_t i = 0; i < arr.size(); i++) {
			scores.push_back(vector<float>(arr.size(), 0));
		}
		for (size_t i = 0; i < arr.size(); i++) {
			for (size_t j = 0; j < arr.size(); j++) {
				
				if (arr[i][j] != 1) {
					scores[i][j] = 0.0;
					continue;
				}
				int count = 0;
				for (size_t k = 0; k < 4; k++) {
					float score = 1.0;
					int index = 1;
					while (i + dir[k * 2][0] * index < arr.size() && i + dir[k * 2][0] * index >= 0 && j + dir[k * 2][1] * index < arr.size() && j + dir[k * 2][1] * index >= 0) {
						if (color == BLACKPIECE && arr[i + dir[k * 2][0]*index][j + dir[k * 2][1]*index] == 3) {
							score++;
							index++;
						}
						else if (color == WHITEPIECE && arr[i + dir[k * 2][0]*index][j + dir[k * 2][1]*index] == 2) {
							score++;
							index++;
						}
						else {
							if (color == BLACKPIECE && arr[i + dir[k * 2][0] * index][j + dir[k * 2][1] * index] == 2) {
								score -= 0.5;
							}
							else if (color == WHITEPIECE && arr[i + dir[k * 2][0] * index][j + dir[k * 2][1] * index] == 3) {
								score -= 0.5;
							}
							break;
						}
					}
					index = 1;
					while (i + dir[k * 2 + 1][0] * index < arr.size() && i + dir[k * 2 + 1][0] * index >= 0 && j + dir[k * 2 + 1][1] * index < arr.size() && j + dir[k * 2 + 1][1] * index >= 0) {
						if (color == BLACKPIECE && arr[i + dir[k * 2 + 1][0]*index][j + dir[k * 2 + 1][1]*index] == 3) {
							score++;
							index++;
						}
						else if (color == WHITEPIECE && arr[i + dir[k * 2 + 1][0]*index][j + dir[k * 2 + 1][1]*index] == 2) {
							score++;
							index++;
						}
						else {
							if (color == BLACKPIECE && arr[i + dir[k * 2 + 1][0] * index][j + dir[k * 2 + 1][1] * index] == 2) {
								score -= 0.5;
							}
							if (color == WHITEPIECE && arr[i + dir[k * 2 + 1][0] * index][j + dir[k * 2 + 1][1] * index] == 3) {
								score -= 0.5;
							}
							break;
						}
					}
					if (score > 4) {
						ARKPhase = 1.0;
						DEFPhase = 0.0;
						scores[i][j] = 9999;
						return scores;
					}
					if (score == 4) {
						if (DEFPhase < 3.5) {
							DEFPhase = 0.0;
							ARKPhase = 1.0;
						}
						scores[i][j] = 9000;
					}
					if (score == 3.5) {
						if (ARKPhase > 0) {
							DEFPhase = 0.0;
							ARKPhase = 1.0;
						}
						scores[i][j] = 8000;
					}
					if (score == 3) {
						if (ARKPhase > 0) {
							DEFPhase = 0.0;
							ARKPhase = 1.0;
						}
						scores[i][j] = 7000;
					}
					

					count += int(score);
					scores[i][j] += score * score;
				}
				if (count == 0) {
					scores[i][j] = 0;
				}
				else {
					scores[i][j] /= count;
				}
				
			}
		}
		return scores;
	}

	vector<vector<float>> calcDEFScore(vector<vector<int>> arr, PieceColor color) {
		int dir[8][2] = { {1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1} };
		vector<vector<float>> scores;
		for (size_t i = 0; i < arr.size(); i++) {
			scores.push_back(vector<float>(arr.size(), 0));
		}
		for (size_t i = 0; i < arr.size(); i++) {
			for (size_t j = 0; j < arr.size(); j++) {

				if (arr[i][j] != 1) {
					scores[i][j] = 0.0;
					continue;
				}
				int count = 0;
				for (size_t k = 0; k < 4; k++) {
					float score = 0.0;
					bool flag1 = false;
					bool flag2 = false;
					int index = 1;
					while (i + dir[k * 2][0] * index < arr.size() && i + dir[k * 2][0] * index >= 0 && j + dir[k * 2][1] * index < arr.size() && j + dir[k * 2][1] * index >= 0) {
						if (color == BLACKPIECE && arr[i + dir[k * 2][0]*index][j + dir[k * 2][1]*index] == 2) {
							score++;
							index++;
							flag1 = true;
						}
						else if (color == WHITEPIECE && arr[i + dir[k * 2][0]*index][j + dir[k * 2][1]*index] == 3) {
							score++;
							index++;
							flag1 = true;
						}
						else {
							if (color == BLACKPIECE && arr[i + dir[k * 2][0] * index][j + dir[k * 2][1] * index] == 3) {
								score -= 0.5;
							}
							if (color == WHITEPIECE && arr[i + dir[k * 2][0] * index][j + dir[k * 2][1] * index] == 2) {
								score -= 0.5;
							}
							break;
						}
					}
					index = 1;
					while (i + dir[k * 2 + 1][0] * index < arr.size() && i + dir[k * 2 + 1][0] * index >= 0 && j + dir[k * 2 + 1][1] * index < arr.size() && j + dir[k * 2 + 1][1] * index >= 0) {
						if (color == BLACKPIECE && arr[i + dir[k * 2 + 1][0]*index][j + dir[k * 2 + 1][1]*index] == 2) {
							score++;
							index++;
							flag2 = true;
						}
						else if (color == WHITEPIECE && arr[i + dir[k * 2 + 1][0]*index][j + dir[k * 2 + 1][1]*index] == 3) {
							score++;
							index++;
							flag2 = true;
						}
						else {
							if (color == BLACKPIECE && arr[i + dir[k * 2 + 1][0] * index][j + dir[k * 2 + 1][1] * index] == 3) {
								score -= 0.5;
							}
							if (color == WHITEPIECE && arr[i + dir[k * 2 + 1][0] * index][j + dir[k * 2 + 1][1] * index] == 2) {
								score -= 0.5;
							}
							break;
						}
					}
					if (flag1 && flag2) {
						score += 0.9;
					}
					if (score > 3.5) {
						ARKPhase = 0.0;
						DEFPhase = 4.0;
						scores[i][j] = 9999;
						return scores;
					}
					if (score == 3.5) {
						ARKPhase = 0.0;
						DEFPhase = 3.5;
						scores[i][j] = 9999;
						return scores;
					}
					if (score == 3) {
						ARKPhase = 0.0;
						DEFPhase = 3;
						scores[i][j] = 9999;
						return scores;
					}
					count += int(score);
					scores[i][j] += score * score;
				}
				if (count == 0) {
					scores[i][j] = 0;
				}
				else {
					scores[i][j] /= count;
				}

			}
		}
		return scores;
	}

private:
	float ARKPhase = 1.0;
	float DEFPhase = 1.0;
};

// 具体产品类  五子棋困难AI
class Wuzi_D_AI : public WuziAI {
public:
	PiecePos calPos(vector<vector<int>> arr, PieceColor color) {
		return PiecePos(0, 0);
	}

};

// 抽象工厂（基类） 
class AIfactory {
public:
	virtual HeibaiAI* creatHeibaiAI() = 0;
	virtual WuziAI* creatWuziAI() = 0;
	virtual ~AIfactory() {}

};

// 简单AI工厂 
class E_AIfactory : public AIfactory {
public:
	HeibaiAI* creatHeibaiAI() {
		return new Heibai_E_AI();
	}
	WuziAI* creatWuziAI() {
		return new Wuzi_E_AI();
	}

};

// 中等AI工厂
class M_AIfactory : public AIfactory {

public:
	HeibaiAI* creatHeibaiAI() {
		return new Heibai_M_AI();
	}
	WuziAI* creatWuziAI() {
		return new Wuzi_M_AI();
	}
};

// 困难AI工厂 
class D_AIfactory : public AIfactory {
public:
	HeibaiAI* creatHeibaiAI() {
		return new Heibai_D_AI();
	}
	WuziAI* creatWuziAI() {
		return new Wuzi_D_AI();
	}
};

