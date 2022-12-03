#ifndef PIECEBOARD_H
#define PIECEBOARD_H

#include "Memento.h"
#include <graphics.h>


class Memento;

//����
class PieceBoard
{
public:
	//��ȥ������λ�ü�¼
	deque<PiecePos> lastPieces;
private:
	
	int queueMax = 12;

	vector<PiecePos> m_vecPos; //������ӵ�λ��  
	int m_Length = 9;

	Rect *mBoard = nullptr;
	// ���ڼ�¼���
	vector<vector<int>> arr = vector<vector<int>>(m_Length, vector<int>(m_Length));
	IMAGE img;
	
public:
	PieceBoard() ;
	PieceBoard(int road);
	~PieceBoard();

	void setLength(int length);

	//�����Ӷ��еĴ���
	void addPiece(PiecePos pos);

	int getLength();

	vector<vector<int>> getArr();

	void setArr(vector<vector<int>> newarr);

	//���������ת��Ϊ���̾�����Ϣ
	bool calcIndex(int point_x, int point_y, PiecePos& pos);

	void updatePieceBoard();

	void initBoard(int startX, int startY, int width, int height, int padding);

	void draw();

	void clearPieceBoard();

	void SetPiece(PieceColor color, PiecePos pos);

	//�����Ӽ�¼��������
	bool record_in(PieceColor color, PiecePos pos);

	//�������
	void clearPieces();

	void clearDeque();

	//��ָ������ȡ�ߣ����ڻ�������ӣ�
	void undoPiece(PiecePos pos);

	//������֣�ֻ��Memento���󽻻������漰��caretaker
	Memento Save(bool turn, int times_B, int times_W);
	
	//������֣�ֻ��Memento���󽻻������漰��caretaker
	void Load(Memento memento);
	
};


#endif