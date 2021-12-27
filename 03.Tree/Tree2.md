
### M-way Search Tree
AVL Tree의 단점(데이터가 많아지면 O(log n)의 비용조차도 부담스러움)을 해결하기 위한 구조로, Binary Tree의 **child 순회가 편리하지만 하나의 노드가 2개의 child만 가질 수 있다는 점** 을 포기하고, 한 노드가 더 많은 자식을 갖는 tree 구조로 눈을 돌렸다.<br>
 **M-way Search Tree**는 노드의 체급을 불려 하나의 노드가 M-1개의 데이터와 M개의 child를 갖는 구조이다. **Binary Search Tree**와 마찬가지로 한 노드 안의 데이터 `di`의 경우 해당 노드의 i-1번째 child(= subtree) `C(i-1)` 안의 모든 데이터보다 값이 커야 하며, `Ci`의 모든 데이터보다 값이 작아야 한다. 
#### 장점 
높이가 h인 M-way Search Tree의 경우 최대 1(level 0) + m(level 1) + m^2(level 2) + ... = (m^(h+1) - 1) / (m-1) 개의 노드를 가질 수 있으며, 따라서 최대 **m^(h+1) - 1**개의 데이터를 저장할 수 있다. 따라서 m의 크기에 따라 기존 AVL tree(**= 2^(h+1) - 1개**)와는 비교도 못할 양의 데이터를 담을 수 있다. 때문에 Search time 또한 O(logm n)로 줄어들 게 된다. 
#### 단점 
기본 Binary Search Tree와 동일한 문제점을 갖는데, **균형이 유지된다는 가정 하에 효율적**이라는 점이다. 하지만 큰 차이가 존재하는데, 단순한 구조의 Binary Search Tree와 달리, M-way Search Tree의 경우 **균형을 유지하는 것이 더 복잡하고, 고비용이란 점**이다.

### B-Tree

![B-Tree](https://user-images.githubusercontent.com/86412960/147461988-1dc8b79a-6801-4084-abb5-6532ea1ac19d.png)<br>
B-Tree는 비유하자면 Partially Balanced M-way Search tree이다. Binary Search Tree의 경우 균형이 어긋나는 경우가 4가지 밖에 되지 않기 떄문에 각 경우에 따라 대응할 수 있었지만, M-way의 경우는 일일히 구분하는 것은 매우 복잡해진다. 따라서 B-Tree는 준-균형을 유지하는 방식을 채택하였으며, 준-균형이란 다음과 같다.
*  루트의 경우 2개 이상, m개 이하의 subtree를 갖는다.
*  Internal Node(= Non-leaf)의 경우 ceil(m/2) 이상 m 이하의 subtree를 갖는다(Node의 data 수가 변동 가능). 
*  Leaf Node의 경우 모두 같은 level에 존재한다(Complete binary tree와 유사).

B-Tree는 이 준-균형만은 유지시키는 방식으로 구현되며, subtree간의 height 격차가 없어 최악의 경우와 평균적인 경우의 차이가 벌어지지 않는다. <br>
이러한 준-균형은 삽입/삭제 시에 무너질 수 있기 때문에 각 경우에 균형이 무너지는 것을 방지하는 추가 작업이 요구된다. 
#### B-Tree 삽입
B-Tree에 새 데이터를 삽입할 때엔 데이터 크기에 따라 leaf node 단계까지 내려가 해당 leaf node의 부모의 왼쪽부터 데이터를 채워넣는다. 그러나 해당 부모의 child가 m+1개 이상이 된다면 B-Tree의 조건이 깨지기 때문에 재조정이 필요하다. 일반적인 경우에는 AVL과 같이 Rotation을 수행하는데, rightmost child를 새 parent로 만들고, 기존 parent를 새 parent의 child로 만드는 **key rotation**을 수행하게 된다. 하지만 이는 근처 노드에 공간 여유가 있어야 가능한 작업으로, 그렇지 못한 경우 **Node Split**을 실행하게 된다. <br>
![B-Tree Insert01](https://user-images.githubusercontent.com/86412960/147466201-1867e039-ce3e-4e91-b279-0c6a09672406.png)<br>
**Node Split**은 용량이 초과된 노드를 둘로 나누는 과정을 의미한다. 이를 구체적으로 표현하면 해당 Node의 중간 값인 n번째  데이터를 Parent Node의 새 데이터 new_par로 올린 후, 1 ~ n-1까지의 데이터를 new_par의 left child로, n+1 ~ m까지의 데이터를 new_par의 right child로 만드는 것을 의미한다. 이 결과, 하나의 node가 2개의 node로 분리되며, parent node의 데이터 하나가 추가된다. 따라서, parent node의 데이터가 m개 이상이 되는 경우가 발생할 수도 있는데, 이 경우 조건에 따라 반복적으로 None / Key Rotation / Node Split을 수행하면 된다.<br>
![B-Tree Insert02](https://user-images.githubusercontent.com/86412960/147466206-ee08b2c1-a528-4afc-a483-f242251f9439.png)<br>
> B-Tree의 삽입은 Tree를 위쪽 방향으로 확장하면서 Leaf Node가 같은 level에 존재하게 유지(= 균형 유지)한다. 
#### B-Tree 삭제
B-Tree에서 데이터 삭제 역시 데이터 크기에 따라 leaf node 단계까지 내려가 해당 leaf node를 제거하는 작업이다. 삽입에서는 child가 m+1개 이상이 되는지를 주시한다면, 삭제에서는 child가 ceil(m/2)개 미만이 되는지를 주시한다. 일반적인 경우 역시 **Key Rotation**을 수행하여 sibling node를 parent에 올리고, 기존 parent 값을 child로 가져오는 작업을 수행한다.<br>
![B-Tree Delete01](https://user-images.githubusercontent.com/86412960/147466210-f28a8cf2-9c05-419c-864f-cc51388e5d87.png)<br>
하지만 만약 sibling node가 ceil(m/2)개의 데이터를 갖고 있어 Key Rotation 시 준-균형을 유지하지 못한다면 **Node Merging**을 수행한다. **Node Merging**은 타겟 node와 sibling node를 병합하는 작업으로, 그 결과 parent node의 데이터가 하나 줄게 된다. 그 때문에 parent의 데이터가 ceil(m/2) 미만이 될 경우 조건에 따라 반복적으로 None / Key Rotation / Node Merging을 수행한다.<br>
![B-Tree Delete02](https://user-images.githubusercontent.com/86412960/147466354-dca2fd5c-43f0-47ca-a178-95c33465385a.png)<br>
> B-Tree 삭제 역시 Tree의 Root부터 수축시키면서 Leaf Node가 같은 level에 존재하게끔 유지시킨다.
#### 장점
*  보다 효율적으로 M-ways Tree의 균형을 유지할 수 있다. 따라서 탐색 속도가 안정적으로 보장된다.  
*  AVL과 비교해보면 같은 양의 데이터 풀에서 더 낮은 높이로 Tree 구현이 가능하다.
#### 단점
*  삽입, 삭제 시 발생하는 Node Split과 Node Merging의 비용이 가변지는 않다. 
*  모든 데이터를 순회하는 작업이 필요할 땐 효율적이지 못하다(child01 -> parent -> child02 -> parent ...).

### B+ Tree
B+ Tree는 B-Tree에서 데이터 순회 비효율을 해결하기 위해 고안된 자료구조이다. 기존 B-Tree는 Internal Node에도 데이터가 담겨 있어 데이터 순회마다 Internal Node도 조회해야 했지만, B+ Tree는 **Internal Node에 데이터를 담지 않고, Key만 담아** Internal Node 조회 필요성을 제거하면서 Leaf Node를 next_sibling pointer로 연결하여 데이터 순회를 효율적으로 구현하였다(이 때 데이터 = 탐색을 위한 key + 실제 value로 구성). 
이 결과 총 Internal Node 수가 B Tree보다 늘어나지만, Internal Node 자체의 용량이 작아 부담이 덜하고, 데이터를 선형 탐색할 수 있게 된다.<br>
![B+ Tree](https://user-images.githubusercontent.com/86412960/147473046-dc183f9b-70f0-454e-9ebc-df1c28b12bb0.png)<br>
#### 장점
*  Internal Node의 용량이 작아져 같은 메모리 크기에서 더 많은 Internal Node를 담을 수 있게 됨.
*  데이터 순회를 O(n)으로 수행 가능.
#### 단점
모든 검색이 logm n번으로 이뤄진다. 따라서 n개의 서로 다른 데이터를 탐색할 때 걸리는 시간은 B-Tree보다 크거나 같다.

---------------------------------------------


### Priority Queue(= Heap)
Priority Queue, Heap은 항상 우선순위가 가장 높은 데이터를 Dequeue하는 Queue이다. Heap의 구현은 여러 방법이 존재하지만, 가장 단순한 방법으로는 **Complete Binary Tree + Partially Ordered 구조**를 응용한 binary heap이 있다.<br>
Binary heap은 Complete binary tree 형태를 취하며, 따라서 leaf level 이전까지는 모두 가득 차있고, leaf level에서는 왼쪽부터 순차적으로 채워진 형태를 갖게 된다. 이러한 구현은 배열 기반 구현에서 child와 parent의 index 관계를 매우 직관적으로 보일 수 있다는 장점을 갖는다. 1번 index부터 level-order에 따라 데이터를 채워넣은 Array-based heap을 분석해보면 n번째 노드의 parent index는 **n / 2**, child index는 **n * 2 또는 n * 2 + 1**임을 알 수 있다.<br>
**Heap Insert** 때에는 Complete binary tree의 마지막 노드 다음 위치에 새 데이터를 집어넣고, 해당 노드의 parent와 우선순위를 비교해가며 위치를 조정한다(따라서 O(log n)의 비용이 요구된다). **Heap Delete**의 경우는 Root에 담긴 값(= 우선 순위가 가장 높은 데이터)을 추출한 후, root에 Complete binary tree의 마지막 노드 데이터를 집어넣고, child와 비교해가며 위치를 조정한다(O(1) - root 추출 - + O(log n)의 비용 요구). 
#### 장점
Heap은 parent - child 간의 정렬만을 고려하고, sibling 간의 정렬은 고려하지 않는다(즉, level n에서의 임의의 노드 x가 level n + 1에서의 임의의 노드 y보다 우선순위가 낮을 수도 있다는 것. 부모 우선순위 > 자식 우선순위만 지켜지면 된다). 이를 Partially Ordered라 하는데, 전체를 정렬하지 않아 정렬에 드는 비용이 더 적다는 장점을 갖는다. 
