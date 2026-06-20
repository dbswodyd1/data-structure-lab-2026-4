A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

def bfs(A):
    """
    큐(queue) 구조를 이용하여 인접 리스트 형식의 그래프를 너비 우선 탐색(BFS)한다.
    
    시작점(0번 노드)으로부터 거리가 가장 가까운 노드들을 수평적으로 우선 방문하며 확장한다.
    갈림길이 여러 개일 경우를 대비하여 오름차순(sorted)으로 번호가 작은 노드부터 순서대로 큐에 삽입한다.
    """
    answer = []                 # 방문한 노드를 순서대로 저장하는 리스트
    visited = [False] * len(A)  # 각 노드의 방문 여부를 확인하기 위한 배열
    queue = [0]                 # 0번 노드를 시작점으로 설정
    visited[0] = True           # 시작점은 방문(True)처리

    while queue:                # queue가 빌 때까지 반복
        curr = queue.pop(0)     # queue의 맨 앞(가장 먼저 넣은 값)에서 꺼낸 노드를 curr에 대입
        answer.append(curr)     # 방문 노드를 answer리스트에 추가

        # 현재 노드와 연결된 노드들을 오름차순(sorted)으로 하나씩 확인
        for neighbor in sorted(A[curr]): 
            if not visited[neighbor]:    # 아직 방문하지 않은 노드인 경우(False) 실행
                visited[neighbor] = True # 노드를 방문(True)처리
                queue.append(neighbor)   # 노드를 queue의 맨 뒤에 추가
    return answer


def dfs(A): 
    """
    스택(stack) 구조를 이용하여 인접 리스트 형식의 그래프를 깊이 우선 탐색(DFS)한다.
    
    시작점(0번 노드)에서 출발하여 한 방향으로 갈 수 있는 가장 깊은 곳까지 탐색한다.
    스택의 후입선출(LIFO) 특성을 활용하여 번호가 가장 작은 노드를 먼저 방문하기 위해,
    인접 노드들을 역순(reversed)으로 스택에 삽입하고 중복 삽입을 방지하도록 처리한다.
    """
    answer = []                  # 방문한 노드를 순서대로 저장하는 리스트
    visited = [False] * len(A)   # 각 노드의 방문 여부를 확인하기 위한 배열
    stack = [0]                  # 0번 노드를 시작점으로 설정

    while stack:                 # stack이 빌 때까지 반복
        curr = stack.pop()       # 스택의 맨 뒤(최근 넣은 값)에서 노드를 curr에 대입
        
        if not visited[curr]:     #visited[curr]이 False인 경우(아직 방문하지 않은 경우) 실행
            visited[curr] = True  #방문한 곳은 True로 바꿈
            answer.append(curr)   #방문한 노드를 answer리스트에 추가
            
            #현재 노드와 연결된 노드들을 역순(reversed)으로 하나씩 확인
            for neighbor in reversed(A[curr]):
                if not visited[neighbor] and (neighbor not in stack):
                    #1. 아직 방문한 적이 없고(False), #2. 스택에 중복된 값이 없는 경우에만 삽입
                    stack.append(neighbor) #스택에 노드 값을 넣는다
                    
    return answer

# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

print("실행된 BFS 결과:", bfs_result)
print("실행된 DFS 결과:", dfs_result)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]
print('PASSED!')

