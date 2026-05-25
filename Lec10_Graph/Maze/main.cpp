#include "Location2D.h"
#include <stack>
#include <deque>
#include <iostream> // printf 등을 위해 포함

using namespace std;
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
{'1', '1', '1', '1', '1', '1'},
{'e', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '1'},
{'1', '0', '1', '0', '1', '1'},
{'1', '0', '1', '0', '0', 'x'},
{'1', '1', '1', '1', '1', '1'},
};

bool isValidLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
	else return map[r][c] == '0' || map[r][c] == 'x';
}

int main() {
	int ds_num;
	printf("미로 탐색 알고리즘 선택: 1)Stack, 2)Deque \n");
	scanf_s("%d", &ds_num);
	switch (ds_num) {
	case 1:
	{   // 괄호 시작: case 1 내에서만 변수가 유효하게 만듭니다.
		stack<Location2D> locStack;
		Location2D entry(1, 0);
		locStack.push(entry);

		while (locStack.empty() == false) {
			Location2D here = locStack.top();
			locStack.pop();

			int r = here.row, c = here.col;
			printf("(%d,%d) ", r, c);
			if (map[r][c] == 'x') {
				printf("\n미로 탐색 성공\n");
				break;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
			}
		}
		break;
	}   // 괄호 끝

	case 2:
	{   // 중괄호 시작
		deque<Location2D> locDeque; // 위치 덱 객체 생성 (스택처럼 활용)
		Location2D entry(1, 0);     // 입구 위치
		locDeque.push_front(entry); // 덱의 앞(front)에 입구 삽입

		while (locDeque.empty() == false) {
			// 1. 가장 최근에 들어온 맨 앞(front)의 데이터를 꺼냅니다.
			Location2D here = locDeque.front();
			locDeque.pop_front();

			int r = here.row, c = here.col;
			printf("(%d,%d) ", r, c);

			// 출구('x')에 도달했는지 확인
			if (map[r][c] == 'x') {
				printf("\n미로 탐색 성공!\n");
				break;
			}
			else {
				map[r][c] = '.'; // 현재 위치를 방문 완료('.') 처리

				// 2. 💡 핵심: 새로 발견한 갈림길들을 모두 맨 앞(front)에 push합니다.
				// 먼저 들어간 것보다 나중에 들어간 것이 먼저 나오는 DFS(스택) 구조가 됩니다.
				if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c)); // 상
				if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c)); // 하
				if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1)); // 좌
				if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1)); // 우
			}
		}
		break;
	}   // case2중괄호 끝
	} //switch 중괄호

	// DFS를 거치면서 '.'으로 변해버린 길들을 다시 '0'과 'e'로 되돌려줍니다.
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			if (map[r][c] == '.') {
				// (1,0) 자리는 원래 입구('e')였으므로 'e'로, 나머지는 길('0')로 복구
				if (r == 1 && c == 0) map[r][c] = 'e';
				else map[r][c] = '0';
			}
		}
	}

	printf("BFS 결과");
	deque<Location2D> locDeque; // 위치 덱 객체 생성 (큐처럼 활용)
	Location2D entry(1, 0);     // 입구 위치
	locDeque.push_back(entry); // 덱의 뒤(back)에 입구 삽입	

	while (locDeque.empty() == false) {
		Location2D here = locDeque.front();
		locDeque.pop_front();

		int r = here.row, c = here.col;
		printf("(%d,%d) ", r, c);

		// 출구('x')에 도달했는지 확인
		if (map[r][c] == 'x') {
			printf("\n미로 탐색 성공!\n");
			return 0;
		}
		else {
			map[r][c] = '.';

			if (isValidLoc(r - 1, c)) locDeque.push_back(Location2D(r - 1, c)); // 상
			if (isValidLoc(r + 1, c)) locDeque.push_back(Location2D(r + 1, c)); // 하
			if (isValidLoc(r, c - 1)) locDeque.push_back(Location2D(r, c - 1)); // 좌
			if (isValidLoc(r, c + 1)) locDeque.push_back(Location2D(r, c + 1)); // 우
		}
	}
	printf("\n미로 탐색 실패\n");

	return 0;
}//main  중괄호