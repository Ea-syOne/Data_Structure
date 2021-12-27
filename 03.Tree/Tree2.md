### Priority Queue(= Heap)
Priority Queue, Heap은 항상 우선순위가 가장 높은 데이터를 Dequeue하는 Queue이다. Heap의 구현은 여러 방법이 존재하지만, 가장 단순한 방법으로는 **Complete Binary Tree + Partially Ordered 구조**를 응용한 binary heap이 있다.<br>
Binary heap은 Complete binary tree 형태를 취하며, 따라서 leaf level 이전까지는 모두 가득 차있고, leaf level에서는 왼쪽부터 순차적으로 채워진 형태를 갖게 된다. 이러한 구현은 배열 기반 구현에서 child와 parent의 index 관계를 매우 직관적으로 보일 수 있다는 장점을 갖는다. 1번 index부터 level-order에 따라 데이터를 채워넣은 Array-based heap을 분석해보면 n번째 노드의 parent index는 **n / 2**, child index는 **n * 2 또는 n * 2 + 1**임을 알 수 있다.<br>
**Heap Insert** 때에는 Complete binary tree의 마지막 노드 다음 위치에 새 데이터를 집어넣고, 해당 노드의 parent와 우선순위를 비교해가며 위치를 조정한다(따라서 O(log n)의 비용이 요구된다). **Heap Delete**의 경우는 Root에 담긴 값(= 우선 순위가 가장 높은 데이터)을 추출한 후, root에 Complete binary tree의 마지막 노드 데이터를 집어넣고, child와 비교해가며 위치를 조정한다(O(1) - root 추출 - + O(log n)의 비용 요구). 
#### 장점
Heap은 parent - child 간의 정렬만을 고려하고, sibling 간의 정렬은 고려하지 않는다(즉, level n에서의 임의의 노드 x가 level n + 1에서의 임의의 노드 y보다 우선순위가 낮을 수도 있다는 것. 부모 우선순위 > 자식 우선순위만 지켜지면 된다). 이를 Partially Ordered라 하는데, 전체를 정렬하지 않아 정렬에 드는 비용이 더 적다는 장점을 갖는다. 

### M-way Search Tree
AVL Tree의 경우 데이터가 적당히 많을 경우까지는 우수한 성능을 제공하지만, 데이터가 너무 많아지면 Tree의 높이가 너무 높아지고, 따라서 O(log n)의 비용조차도 부담스럽게 된다. 연구자들은 이러한 문제의 근본적인 원인을 **하나의 노드가 2개의 child만 가질 수 있다는 점**으로 판단했고, 따라서 한 노드가 더 많은 자식을 갖는 tree 구조로 눈을 돌렸다.<br>
 M-way Search Tree는 노드의 체급을 불려 하나의 노드가 M-1개의 데이터와 M개의 child를 갖는 구조이다. 이때 한 노드 안의 데이터 di의 경우 해당 노드의 i-1번째 child(= subtree) c(i-1) 안의 모든 데이터보다 값이 커야 하며, i번째 child ci의 모든 데이터보다 값이 작아야 한다. 
#### 장점 
높이가 h인 M-way Search Tree의 경우 최대 1(level 0) + m(level 1) + m^2(level 2) + ... = (m^(h+1) - 1) / (m-1) 개의 노드를 가질 수 있으며, 따라서 최대 m^(h+1) - 1개의 데이터를 저장할 수 있다. 따라서 m의 크기에 따라 기존 AVL tree와는 비교도 못할 양의 데이터를 담을 수 있다. 이때 Search time은 O(logm(N+1))이 요구된다. 
#### 단점 
기본 Binary Search Tree와 동일한 문제점을 갖는데, 균형이 유지된다는 가정 하에 효율적이라는 점이다. 하지만 큰 차이가 존재하는데, 단순한 구조의 Binary Search Tree와 달리, M-way Search Tree의 경우 균형을 유지하는 것이 더 복잡하고, 고비용이란 점이다.

### B-Tree
B-Tree는 비유하자면 Partially Balanced M-way Search tree이다. Binary Search Tree의 경우 균형이 어긋나는 경우가 4가지 밖에 되지 않기 떄문에 각 경우에 따라 대응할 수 있었지만, M-way의 경우는 일일히 구분하는 것은 매우 복잡해진다. 따라서 B-Tree는 준-균형을 유지하는 방식을 채택하였으며, 준-균형이란 다음과 같다.
*  루트의 경우 2개 이상, m개 이하의 subtree를 갖는다.
*  Internal Node(= Non-leaf)의 경우 ceil(m/2) 이상 m 이하의 subtree를 갖는다(Node의 data 수가 변동 가능). 
*  Leaf Node의 경우 모두 같은 level에 존재한다(Complete binary tree와 유사).

B-Tree는 이 준-균형만은 유지시키는 방식으로 구현되며, subtree간의 height 격차가 없어 최악의 경우와 평균적인 경우의 차이가 벌어지지 않는다. <br>
이러한 준-균형은 삽입/삭제 시에 무너질 수 있기 때문에 각 경우에 균형이 무너지는 것을 방지하는 추가 작업이 요구된다. 
#### B-Tree 삽입
B-Tree에 새 데이터를 삽입할 때엔 leaf node 단계까지 내려가 해당 leaf node의 부모의 왼쪽부터 데이터를 채워넣는다. 그러나 해당 부모의 child가 m개 이상이 된다면 B-Tree의 조건이 깨지기 때문에 재조정이 필요하다. 일반적인 경우에는 AVL과 같이 Rotation을 수행하는데, rightmost child를 새 parent로 만들고, 기존 parent를 새 parent의 child로 만드는 key rotation을 수행하게 된다. 하지만 이는 근처 노드에 공간 여유가 있어야 가능한 작업으로, 그렇지 못한 경우 **Node Split**을 실행하게 된다. <br>
**Node Split**은 용량이 초과된 노드를 둘로 나누는 과정을 의미한다. 이를 구체적으로 표현하면 해당 Node의 중간 값인 n번째  데이터를 Parent Node의 새 데이터 new_par로 올린 후, 1 ~ n-1까지의 데이터를 new_par의 left child로, n+1 ~ m까지의 데이터를 new_par의 right child로 만드는 것을 의미한다. 이 결과, 하나의 node가 2개의 node로 분리되며, parent node의 데이터 하나가 추가된다. 따라서, parent node의 데이터가 m개 이상이 되는 경우가 발생할 수도 있는데, 이 경우 조건에 따라 반복적으로 None / Key Rotation / Node Split을 수행하면 된다.
#### B-Tree 삭제
