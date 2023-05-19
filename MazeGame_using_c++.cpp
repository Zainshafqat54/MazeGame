// MazeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<list>
using namespace std;

struct node
{
	char ch;
	int rowNmbr;
	int colNmbr;
	node* next;
	node* prvs;
	node* up;
	node* down;
};
struct StackNode
{
	int xCor;
	int YCor;
	int Dir = 0;
	StackNode* nxt;
};
class Maze
{
private:
	node* Start;
	node* mainhead;
	int NoOfRows;
	int NoOfColumns;
	int RowEnd;
	int ColEnd;
	int SizeOfHurdlesArray;
	int *HurdleRow;
	int *HurdleColumn;
	int RowIndx;
	int ColIndx;
	StackNode* Top;
	bool **visited;
public:
	Maze() {
	Start = NULL;
	mainhead = NULL;
	NoOfRows=0;
	NoOfColumns = 0;
	RowEnd = 0;
	ColEnd = 0;
	SizeOfHurdlesArray = 0;
	RowIndx = 0;
	ColIndx = 0;
	HurdleRow = NULL;
	HurdleColumn = NULL;
	Top = NULL;
	visited = NULL;
	}
	void setVisited();
	void setNoOfRows(int x);
	int getNoOfRows();
	void setNoOfColumns(int x);
	int getNoOfColumns();
	void setEndRow(int x);
	int getEndRow();
	void setColEnd(int x);
	int getColEnd();
	void setSizeOfHurdlesArray(int x);
	int getSizeOfHurdlesArray();
	void setHurdleRow(int x);
	int* getHurdleRow();
	void setHurdleColumn(int x);
	int* getHurdleColumn();
	node* newNode(char dt, int i, int j);
	void ConstructMaze(char** matrix);
	void DisplayMaze();
	bool IsEmpty();
	StackNode* TopValue();
	void Push(int i, int j,int drct);
	void Pop();
	void DisplayStack();
	void FindPath(char** MazeMatrix);
};
bool Maze::IsEmpty()
{
	if (Top == NULL)
		return true;
	else
		return false;
}
StackNode* Maze::TopValue()
{
	return Top;
}
void Maze::Push(int i,int j,int drct)
{
	StackNode* temp;
	temp = new StackNode;
	temp->xCor =i;
	temp->YCor=j;
	temp->Dir = 0;
	temp->nxt = Top;
	Top = temp;
}
void Maze::Pop()
{
	StackNode* temp;
	temp = new StackNode;
	if (!IsEmpty())
	{
		temp = Top;
		Top = temp->nxt;
		free(temp);
	}
}
void Maze::setVisited()
{
	visited = new bool* [NoOfRows];
	for (int i = 0; i < NoOfRows; i++)
	{
		visited[i] = new bool[NoOfColumns];
	}
	for (int i = 0; i < NoOfRows; i++)
	{
		for (int j = 0; j < NoOfColumns; j++)
		{
			visited[i][j] = true;
		}
	}
}
void Maze::DisplayStack()
{
	StackNode* temp;
	temp = new StackNode;
	temp = Top;
	if (temp == NULL)
		cout << "stack is null\n";
	while (temp != NULL)
	{
		cout << "\n";		
		cout<<"(" << temp->xCor << ","<<temp->YCor<<")";		
		temp = temp->nxt;
	}
}
void Maze::setNoOfRows(int x)
{
	NoOfRows = x;
}
int Maze::getNoOfRows()
{
	return NoOfRows;
}
void Maze::setNoOfColumns(int x)
{
	NoOfColumns = x;
}
int Maze::getNoOfColumns()
{
	return NoOfColumns;
}
void Maze::setEndRow(int x)
{
	RowEnd = x;
}
int Maze::getEndRow()
{
	return RowEnd;
}
void Maze::setColEnd(int x)
{
	ColEnd = x;
}
int Maze::getColEnd()
{
	return ColEnd;
}
void Maze::setSizeOfHurdlesArray(int x)
{
	SizeOfHurdlesArray = x;
	HurdleRow = new int[x];
	HurdleColumn = new int[x];
}
int Maze::getSizeOfHurdlesArray()
{
	return SizeOfHurdlesArray;
}
void Maze::setHurdleRow(int x)
{
	HurdleRow[RowIndx] = x;
	RowIndx++;
}
int* Maze::getHurdleRow()
{
	return HurdleRow;
}
void Maze::setHurdleColumn(int x)
{
	HurdleColumn[ColIndx] = x;
	ColIndx++;
}
int* Maze::getHurdleColumn()
{
	return HurdleColumn;
}
node* Maze::newNode(char dt, int i, int j)
{
	node* temp;
	temp = new node;
	temp->ch = dt;
	temp->rowNmbr = i;
	temp->colNmbr = j;
	temp->down = NULL;
	temp->prvs = NULL;
	temp->next = NULL;
	temp->up = NULL;
	return temp;
}
void Maze::ConstructMaze(char** matrix)
{
	
	node* head[100];
	node* righttemp, * newptr;
	righttemp = new node;
	for (int i = 0; i <NoOfRows; i++)
	{
		head[i] = NULL;
		for (int j = 0; j < NoOfColumns; j++)
		{
			newptr = newNode(matrix[i][j],i,j);
			if (!mainhead)
				mainhead = newptr;

			if (!head[i])
				head[i] = newptr;
			else
			{				
				righttemp->next = newptr;
				newptr->prvs = righttemp;
			}	
			righttemp = newptr;
		}

	}
	for (int i = 0; i < NoOfRows - 1; i++) 
	{

		node* firstNode = head[i];;
		node *secondNode = head[i + 1];

		while (firstNode!=NULL  && secondNode!=NULL)
		{

			firstNode->down = secondNode;
			secondNode->up = firstNode;
			firstNode = firstNode->next;
			secondNode = secondNode->next;
		}
	}
}
void Maze::DisplayMaze()
{
	node* rghtNode;
	node *dwnNode = mainhead;
	while (dwnNode) 
	{
		rghtNode = dwnNode;
		while (rghtNode!=NULL)
		{
			cout << rghtNode->ch << " ";
			rghtNode = rghtNode->next;
		}
		cout << endl;
		dwnNode = dwnNode->down;
	}
}
void Maze::FindPath(char**MazeMatrix)
{
	StackNode* temp;
	temp = new StackNode;
	int rw = 0;
	int clmn = 0;
	int drct=0;
	Push(rw, clmn,drct);
	for (;!IsEmpty();)
	{
		temp = TopValue();
		drct = temp->Dir;
		rw = temp->xCor;
		clmn = temp->YCor;
		temp->Dir++;
		Pop();
		Push(rw, clmn, temp->Dir++);
		if (rw == RowEnd && clmn == ColEnd)
		{
			DisplayStack();
			return ;
		}
						
			switch (drct)
			{
			case 0:
				if (rw - 1 >= 0 && MazeMatrix[rw - 1][clmn] && visited[rw - 1][clmn])
				{
					Push(rw - 1, clmn, 0);
					visited[rw - 1][clmn] = false;
					break;
				}
			case 1:
				if (clmn - 1 >= 0 && MazeMatrix[rw][clmn - 1] && visited[rw][clmn - 1])
				{
					Push(rw, clmn - 1, 0);
					visited[rw][clmn - 1] = false;
					break;
				}
			case 2:
				if (rw + 1 < NoOfRows && MazeMatrix[rw + 1][clmn] && visited[rw + 1][clmn])
				{
					Push(rw + 1, clmn, 0);
					visited[rw + 1][clmn] = false;
					break;
				}
			case 3:
				if (clmn + 1 < NoOfColumns && MazeMatrix[rw][clmn + 1] && visited[rw][clmn + 1])
				{
					Push(rw, clmn + 1, 0);
					visited[rw][clmn + 1] = false;
					break;
				}
			default:
				visited[temp->xCor][temp->YCor] = true;
				Pop();
			}
	}
	cout << "path not found\n";
}
int main()
{
	Maze obj;
	int skip = 0;
	ifstream inFile;
	char ch;
	int value;
	inFile.open("input.txt");
	while (!(inFile.eof()))
	{
		inFile>>ch;
		if (skip < 3)
		{			
			skip++;
			continue;
		}
		if (skip == 3)
		{
			value = ch - '0';
			obj.setNoOfRows(value);
			skip++;
			continue;
		}
		if (skip == 4)
		{
			value = ch - '0';
			obj.setNoOfColumns(value);
			skip++;
			continue;
		}
		if (skip == 5)
		{
			value = ch - '0';
			obj.setEndRow(value);
			skip++;
			continue;
		}
		if (skip == 6)
		{
			value = ch - '0';
			obj.setColEnd(value);
			skip++;
			continue;
		}
		if (skip == 7)
		{
			value = ch - '0';
			obj.setSizeOfHurdlesArray(value);
			skip++;
			continue;
		}
		if (skip > 7 && skip%2==0)
		{
			value = ch - '0';
			obj.setHurdleRow(value);
			skip++;
			continue;
		}
		if (skip > 7 && skip % 2 == 1)
		{
			value = ch - '0';
			obj.setHurdleColumn(value);
			skip++;
			continue;
		}
	}
	inFile.close();
	bool flag;
	int* rowHurdleArr = obj.getHurdleRow();
	int* columnHurdleArr = obj.getHurdleColumn();
	char** MazeMatrix;
	MazeMatrix = new char*[obj.getNoOfRows()];
	for (int i = 0; i < obj.getNoOfRows(); i++)
	{
		MazeMatrix[i] = new char[obj.getNoOfColumns()];
	}
	for (int i = 0; i < obj.getNoOfRows(); i++)
	{
		for (int j = 0; j < obj.getNoOfColumns(); j++)
		{
			flag = true;
			if (i == 0 && j == 0)
			{
				MazeMatrix[i][j] = 'S';
				continue;
			}
			if (i == obj.getNoOfRows() - 1 && j == obj.getNoOfColumns() - 1)
			{
				MazeMatrix[i][j] = 'E';
				continue;
			}
			for (int k = 0; k < obj.getSizeOfHurdlesArray(); k++)
			{
				if (i == rowHurdleArr[k] && j == columnHurdleArr[k])
				{
					MazeMatrix[i][j] = '1';
					flag = false;
					break;
				}					
			}
			if (flag)
			{
				MazeMatrix[i][j] = '0';
			}
				
		}
	}
	obj.ConstructMaze(MazeMatrix);
	obj.DisplayMaze();
	obj.setVisited();
	obj.FindPath(MazeMatrix);
	return 0;
}
