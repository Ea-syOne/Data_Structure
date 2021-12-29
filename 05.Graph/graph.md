## Graph
Graph는 Vertex와 edge로 이루어진 자료구조로, 각 vertex 간의 관계를 표현하는 자료구조이다. 

### Graph 분류
#### 방향에 따른 분류
*  Directed Graph: 방향이 유의미한 graph. 이 Graph에서는 노드 W에서 V로 가는 edge와 V에서 W로 가는 edge를 다르게 구분한다.
*  Undirected Graph: 방향이 없는 graph. W와 V 사이 edge가 있다면 W에서 V로, V에서 W로 갈 수 있다. 
#### 표현 방식에 따른 분류
*  Adjacency Matrix: Edge를 행렬로 표현하는 방식. W -> V의 경우 A[u][v]에 해당 edge의 weight를 저장하는 식으로 표현된다. 
*  Adjacency List: Edge를 Linked-List로 표현하는 방식. W가 Vertex X, Y, Z에 접근 가능할 경우 W -> X -> Y -> Z와 같이 표현한다. 
*  AM과 AL의 비교: 행렬로 표현할 경우 각 edge를 O(1)로 접근할 수 있지만, 활성화되지 않은 edge도 공간을 차지하고 있기 때문에 공간의 낭비가 심할 수 있다.<br> 반면 List의 경우 활성화된 Edge만 표현하기에 공간 낭비는 없지만 edge에 접근할 땐 O(k)의 비용이 요구된다(k = 해당 vertex의 edge 수).<br> 따라서 Edge의 수에 따라 적합한 방식으로 표현하는 것이 중요하다.
### Graph 탐색
#### Breadth-First Search
#### Depth-First Search
### Path 탐색 - Dikstra's Algorithm

### 
