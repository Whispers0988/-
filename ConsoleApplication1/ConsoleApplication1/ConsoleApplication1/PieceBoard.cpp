#include "PieceBoard.h"


PieceBoard::PieceBoard() {}

PieceBoard::PieceBoard(int road) :m_Length(road) {
	loadimage(&img, L"�Ծֽ��汳��.jpg", 1200, 800);
	arr = vector<vector<int>>(m_Length, vector<int>(m_Length));
	for (int i = 0; i < m_Length; i++) { //��ʼ��Ϊȫ1, 1��ʾû������
		for (int j = 0; j < m_Length; j++) {
			arr[i][j] = 1;
		}
	}
}

PieceBoard::~PieceBoard() {}

void PieceBoard::setLength(int length) {
	m_Length = length;
}

//�����Ӷ��еĴ���
void PieceBoard::addPiece(PiecePos pos) {
	lastPieces.push_back(pos);
	if (lastPieces.size() > queueMax) {
		lastPieces.pop_front();
	}
}

int PieceBoard::getLength() {
	return m_Length;
}

vector<vector<int>> PieceBoard::getArr() {
	return arr;
}

void PieceBoard::setArr(vector<vector<int>> newarr) {
	setLength(newarr.size());
	arr = newarr;
}


//���������ת��Ϊ���̾�����Ϣ
bool PieceBoard::calcIndex(int point_x, int point_y, PiecePos& pos) {
	if (mBoard == nullptr) {
		return false;
	}
	else {
		for (int i = 0; i < m_Length; i++) {
			for (int j = 0; j < m_Length; j++) {
				int xpos = mBoard->padding + j * mBoard->space;
				int ypos = mBoard->padding + i * mBoard->space;
				if (point_x - xpos < mBoard->space / 2 && point_y - ypos < mBoard->space / 2) {
					if (arr[i][j] != 1) {
						return false;
					}
					else {
						pos.x = i + 1;
						pos.y = j + 1;
						return true;
					}
				}
			}
		}
		return false;
	}

}

void PieceBoard::updatePieceBoard() {
	initBoard(mBoard->x, mBoard->y, mBoard->width, mBoard->height, mBoard->padding);

}

void PieceBoard::initBoard(int startX, int startY, int width, int height, int padding) {
	int space = (width - padding * 2) / (m_Length - 1);
	int realLength = space * (m_Length - 1);

	if (mBoard == nullptr) {
		mBoard = new Rect();
		mBoard->x = startX;
		mBoard->y = startY;
		mBoard->width = width;
		mBoard->height = height;
		mBoard->padding = padding;
	}

	mBoard->space = space;
	mBoard->realLength = realLength;
}


void PieceBoard::draw() {
	if (mBoard == nullptr) {
		return;
	}

	clearPieceBoard();
	setfillcolor(WHITE);         // �����ɫ����
	fillrectangle(mBoard->x, mBoard->y, mBoard->width, mBoard->height);


	//putimage(0, 0, &img);

	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);

	settextcolor(BLUE);
	settextstyle(15, 0, L"����");
	const wchar_t* row[19] = { L"1",L"2",L"3",L"4" ,L"5",L"6" ,L"7",L"8" ,L"9",L"10" ,L"11",L"12" ,L"13",L"14" ,L"15",L"16" ,L"17",L"18" ,L"19" };
	for (int i = 0; i < m_Length; i++) {
		//����
		line(mBoard->x + mBoard->padding + i * mBoard->space, mBoard->padding, mBoard->x + mBoard->padding + i * mBoard->space, mBoard->padding + mBoard->realLength);
		outtextxy(mBoard->x + mBoard->padding + i * mBoard->space - 8, 0, row[i]);
		//����
		line(mBoard->padding, mBoard->y + mBoard->padding + i * mBoard->space, mBoard->padding + mBoard->realLength, mBoard->y + mBoard->padding + i * mBoard->space);
		outtextxy(5, mBoard->y + mBoard->padding + i * mBoard->space - 8, L'a' + i);
	}

	//������������
	int length = arr.size();
	/*arr[5][5] = 3;
	arr[6][6] = 2;*/
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			setlinecolor(BLACK);
			if (arr[i][j] == 2) {
				setfillcolor(WHITE);
				fillcircle(j * mBoard->space + mBoard->x + mBoard->padding, i * mBoard->space + mBoard->y + mBoard->padding, mBoard->space / 2 - 1);
			}
			else if (arr[i][j] == 3) {
				setfillcolor(BLACK);
				fillcircle(j * mBoard->space + mBoard->x + mBoard->padding, i * mBoard->space + mBoard->y + mBoard->padding, mBoard->space / 2 - 1);
			}
		}
	}
}

void PieceBoard::clearPieceBoard() {
	clearrectangle(mBoard->x, mBoard->y, mBoard->x + mBoard->width, mBoard->y + mBoard->height);
}

void PieceBoard::SetPiece(PieceColor color, PiecePos pos) {

}

//�����Ӽ�¼��������
bool PieceBoard::record_in(PieceColor color, PiecePos pos) {
	if (pos.x > 19 || pos.y > 19 || pos.x < 0 || pos.y < 0 || arr[pos.x - 1][pos.y - 1] != 1) {
		return false;
	}
	else {
		pos.x--;
		pos.y--;
		addPiece(pos);
		if (color == BLACK) {
			arr[pos.x][pos.y] = 3;  //�����3
			return true;
		}
		else {
			arr[pos.x][pos.y] = 2;  //�����2
			return true;
		}
	}

}

//�������
void PieceBoard::clearPieces() {
	for (int i = 0; i < m_Length; i++) { //��Ϊȫ1, 1��ʾû������
		for (int j = 0; j < m_Length; j++) {
			arr[i][j] = 1;
		}
	}
}

void PieceBoard::clearDeque() {
	lastPieces.clear();
}

//��ָ������ȡ�ߣ����ڻ�������ӣ�
void PieceBoard::undoPiece(PiecePos pos) {
	arr[pos.x][pos.y] = 1;
}

//������֣�ֻ��Memento���󽻻������漰��caretaker
Memento PieceBoard::Save(bool turn, int times_B, int times_W)
{
	Memento memento(arr, turn, lastPieces, times_B, times_W);
	return memento;
}

//������֣�ֻ��Memento���󽻻������漰��caretaker
void PieceBoard::Load(Memento memento)
{
	arr = memento.m_arr;
}
