import sys

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
# print(concerts)
# [[1, 0, 0, 1, 1, 0], [1, 0, 1, 1, 0, 0], [1, 1, 1, 1, 0, 1], [0, 1, 1, 0, 1, 1], [0, 1, 0, 0, 1, 0]]
###################################

def count_stages(concerts):
    """
    콘서트장 무대 공간을 DFS(깊이 우선 탐색)를 이용하여 분석한뒤,
    펜스(1)로 분리된 독립 무대 공간의 총 개수를 계산하여 반환한다.
    
    concerts 리스트의 행과 열 크기를 파악하여 전체적으로 순회하며 빈 공간(0)을 발견할 때마다 무대 개수를 1씩 추가한다.
    동시에 내부 dfs함수를 호출하여 빈 공간과 인접한 공간을 모두 방문처리(1)로 변경하면서 하나로 묶는다.
    """
    # concerts 리스트가 아예 비어있거나 빈 리스트인 경우 0 반환
    if not concerts or not concerts[0]:
        return 0

    row = len(concerts)    # 세로 크기(행)
    col = len(concerts[0]) # 가로 크기(열)
    answer = 0             # 독립 무대 공간의 개수
    
    if not (1 < row < 10) or not (1 < col < 10):
        print("Error: 크기가 범위를 벗어났습니다.")
        return 0
    
    # 2. DFS(깊이 우선 탐색) 함수 정의
    # 상하좌우로 연결된 모든 빈 공간(0)을 방문하여 하나의 무대 공간으로 묶어주는 역할
    def dfs(r, c):
        # r,c가 범위를 벗어났거나(상하좌우 or 크기 초과) 
        # 현재 위치가 빈 공간(0)이 아닌 경우(펜스(1)이거나 이미 방문한 곳) 탐색 종료
        if r < 0 or r >= row or c < 0 or c >= col or concerts[r][c] != 0:
            return
        
        # 현재 위치의 빈 공간(0)을 1로 변경하여 방문처리(재방문방지)
        concerts[r][c] = 1
        
        # 상, 하, 좌, 우 4방향으로 인접한 공간들을 재귀적으로 탐색
        # 인접한 공간들을 모두 방문처리(1로 변경)하여 하나의 무대 공간으로 묶음
        dfs(r - 1, c)  # 상
        dfs(r + 1, c)  # 하
        dfs(r, c - 1)  # 좌
        dfs(r, c + 1)  # 우

    # 콘서트장 공간 전체를 순회하며 독립된 무대 공간(0) 탐색 시작
    for i in range(row):
        for j in range(col):
            # 만약 새로운 빈 공간(0)을 발견하면 (새로운 무대 공간)
            if concerts[i][j] == 0:
                answer += 1      # 무대 공간 개수 1 증가
                dfs(i, j)        # 연결된 모든 빈 공간(0)을 방문 처리(1로 변경)

    return answer

print(count_stages(concerts))    # 탐색된 무대 공간 수 출력
