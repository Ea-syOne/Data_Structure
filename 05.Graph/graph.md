## Graph
Graph는 Vertex와 edge로 이루어진 자료구조로, 각 vertex 간의 관계를 edge로 표현하는 자료구조이다. <br>

### Graph 분류
#### 방향에 따른 분류
*  Directed Graph: **방향이 유의미**한 graph. 이 Graph에서는 노드 W에서 V로 가는 edge와 V에서 W로 가는 edge를 다르게 구분한다. 이때 **W -> V** edge가 존재한다면 **W는 V의 in-degree**라 하며, **V는 W의 out-degree**라 한다.
*  Undirected Graph: **방향이 없는** graph. W와 V 사이 edge가 있다면 W에서 V로, V에서 W로 갈 수 있다. 
#### Edge에 따른 분류
*  Weighted Graph: 각 **Edge가 동일하지 않은 비용을 요구하는 Graph**. 경로 문제에서는 일반 Graph보다 좀 더 **현실과 유사**한 Graph이다(지점과 지점 사이의 거리가 다 다르므로).
#### 표현 방식에 따른 분류
*  Adjacency Matrix: Edge를 **행렬**로 표현하는 방식. W -> V의 경우 **A[u][v]** 에 해당 edge의 weight를 저장하는 식으로 표현된다. 
*  Adjacency List: Edge를 **Linked-List**로 표현하는 방식. W가 Vertex X, Y, Z에 접근 가능할 경우 W -> X -> Y -> Z와 같이 표현한다. 
*  AM과 AL의 비교: **행렬**로 표현할 경우 **각 edge를 O(1)로 접근**할 수 있지만, **활성화되지 않은 edge도 공간을 차지**하고 있기 때문에 공간의 낭비가 심할 수 있다.<br> 반면 **List**의 경우 **활성화된 Edge만 표현**하기에 공간 낭비는 없지만 **edge에 접근할 땐 O(k)의 비용**이 요구된다(k = 해당 vertex의 edge 수).<br> 따라서 Edge의 수에 따라 적합한 방식으로 표현하는 것이 중요하다.
### Graph 탐색
#### Breadth-First Search
시작 노드로부터 **가까운 노드 순서로 탐색**을 수행하는 방법이다. BFS는 FIFO인 **Queue 기반**으로 구현되는데, 현 노드의 인접 노드를 모두 Queue에 넣은 후, Dequeue한 노드(= 가장 가까운 노드)로 넘어가 탐색을 이어나가는 방식이다.<br>
#### Depth-First Search
시작 노드로부터 **끝 노드에 도달할 때까지 탐색한 후, 뒤로 돌아가 탐색하지 않은 다른 경로를 탐색**하는 방법이다. DFS의 경우는 FILO인 **Stack을 기반**으로, 하나의 인접 노드로 이동하면서 해당 노드를 Stack에 담았다가, 끝 노드에 도달하면 Stack을 Pop해 이전 노드로 돌아가 아직 탐색하지 않은 인접 노드를 끝 노드까지 탐색하는 동작을 반복한다. 
### Path 탐색 - Dikstra's Algorithm
Diksta's Algorithm은 **Weighted Graph에서 최단 경로를 탐색**하기 위해 제안된 경로 탐색 방법이다. 이 알고리즘이 성립하기 위해서는 **모든 Edge가 non-negative weight**를 가져야 한다.<br>
#### 알고리즘
1.  모든 노드의 거리 d를 Min-Heap 구조로 설계한 후, 이 값들을 INT_MAX 값으로 초기화한다(단 d[start] = 0).
2.  Heap에서 최소값 v를 추출한다. 
3.  추출한 v의 모든 out-degree u에 대해, d[u] > d[v] + w(v,u)라면 d[u]를 d[v] + w(v,u)로 바꾸고, u의 prev 값을 v로 바꾼다.<br>
    >  d[v] + w(v,u)는 v에서 u로 이동할 경우의 거리를 의미한다. 즉 현재 u의 최단거리가 start->v->u보다 길다면 u의 최단거리를 갱신한다는 의미이다. u의 prev 값은 d[u]에 도달하기 직전에 지난 vertex를 의미한다.
4.  변경된 값에 따라 Min-Heap을 재조정한 후, d[dest]가 고정될 때까지 2~3을 반복한다.
### Topological Sort
Acyclic Directed Graph에서 각 vertex의 Direction을 위배하지 않으면서 vertex를 정렬하는 것이다. 일반적으로 정렬할 때에는 모든 vertex가 자신이 이동 가능한 vertices(= out-degrees)가 왼쪽에 오지 않게 정렬한다. 즉 임의의 vertex의 어느 edge를 선택하더라도, edge 방향이 왼쪽 -> 오른쪽으로 나오게끔 정렬한다는 것을 의미한다. 예를 들어 vertex 1, 2, 3 | edge 1->3, 3->2, 1->2와 같이 있을 경우, vertex를 1 3 2로 재조정하는 것이라 할 수 있다. 이렇게 정렬하게 되면 vertex 간의 관계를 더 명확히 알 수 있고, edge 탐색을 더 효율적으로 수행할 수 있다.<br>
#### Sorting Algorithm
Topological Sort는 in-degree 속성을 이용한다. in-degree가 0
1.  in-degree가 0인 vertex를 queue에 넣는다.
2.  queue에서 vertex 하나(= v)를 dequeue한 후, v와 인접한 모든 vertex w에 대해 in-degree 값을 1 감소시킨다. 이때 만약 w의 in-degree가 0이 된다면 queue에 저장한다.
    > v의 in-degree가 0이므로, w는 반드시 v의 out-degree이다. 즉 v는 w의 in-degree.
3.  queue가 빌 때까지 1~2를 반복한다.
