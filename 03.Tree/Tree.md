### Tree
: Tree는 Root 노드를 중심으로 하여 parent-child 관계를 갖는 노드들의 집합을 의미하는 자료구조이다. Tree가 갖는 속성은 다음과 같다.
*  하나의 Tree에서 특정 child Node를 Root로 하는 Tree를 subtree라 한다.
*  같은 parent의 childs를 Sibling라 한다.
*  한 노드의 Child 개수를 Degree(차수)라 하며, Degree가 0, 즉 child가 없는 노드를 leaf Node라 한다. 
*  Root에서 한 Node까지의 거리는 depth of node라 하는데, 이 중 가장 긴 값을 height of tree라 한다. 

![Tree](https://user-images.githubusercontent.com/86412960/147441927-d508a91e-cdd6-4b63-8870-28b1e8b428a1.png)<br>


parent와 child를 link하는 Tree 구조 특성상 Linked List로 구현하는 것이 일반적인 방법이다. 다만 단순히 parent-child 정보만 갖고 있다면 하나의 node의 child를 탐색하기 위해서는 `node -> child1 -> node(다음 child 찾기 위해) -> child2 -> ...`와 같이 매우 비효율적인 탐색을 수행해야 한다. 따라서 Tree에서는 메타 데이터 Leftmost child와 Next Sibling을 이용하여 child 순회를 보조하기도 한다(leftmost child 탐색 후 Next Sibling을 통해 다음 child 탐색).

### Binary Tree
이진 트리는 모든 노드의 child가 최대 2개까지만 갖도록 제한한 Tree를 의미한다. 따라서 각 child는 left, right child라 표현된다. 그 때문에 다른 Tree와 달리 child 순회가 번거로울 이유가 없고, 따라서 leftmost child와 Next Sibling이 불필요하다.

![Binary Tree](https://user-images.githubusercontent.com/86412960/147441931-97ec5394-59db-4e36-a1f2-b6e9be72396c.png)<br>
#### Full Binary Tree
Binary Tree의 일종으로, 모든 노드가 child가 없거나, 2개의 child를 갖는 Binary Tree. 
#### Complete Binary Tree
최하위 level을 제외하고 모두 꽉 차 있는(= 2개의 child를 갖는) Binary Tree이다. 또한 최하위 level에서는 가장 왼쪽부터 순서대로 차 있는 형태를 갖는다. <br>
Complete Binary Tree의 특징으로는 각 child의 index가 규칙성을 가져 링크에 관한 메타데이터 없이 배열로 구현 가능하다는 점이다. Root의 index를 1로 잡으면 모든 parent는 child index / 2 값의 index를 가지며, 모든 left child는 parent_index * 2, right child는 parent_index * 2 + 1 index를 갖는다.

#### Tree Traversal(Binary Tree)
Binary Tree의 각 노드를 순회하는 방식이다. 
*  Inorder : 왼쪽 subtree -> Parent -> 오른쪽 subtree 순서대로 출력하는 방식이다.
*  Preorder : Parent -> 왼쪽 subtree -> 오른쪽 subtree 순서대로 출력하는 방식이다(현 노드 우선).
*  Postorder : 왼쪽 subtree -> 오른쪽 subtree -> Parent 순서대로 출력하는 방식이다(현 노드 나중에).
*  Level-order : Root부터 아래로 내려가면서 Level 순서대로 출력하는 방식이다. 

In/Pre/Postorder의 경우 재귀함수를 통해 구현 가능하며, Level-order의 경우 상위 level 노드부터 queue에 담고, 먼저 저장된 노드를 dequeue하는 방식으로 구현된다.
#### Threaded Binary Tree
Binary Tree에서 미사용 중인 null link에 Tree Traversal에 필요한 정보를 저장하여 Tree 순회를 더 빠르게 구현하는 것을 의미한다. 저장되는 노드는 순회 정책에 따라 다르며, left null link가 있다면 현재 노드 이전에 방문한 노드를 저장하고, right null link가 있다면 현재 노드 다음에 방문할 노드를 저장한다. 

### Binary Search Tree
탐색에 특화된 Binary Tree로, 기존 Binary Tree에서 left subtree에는 현 노드보다 작은 값만, right subtree에는 현 노드보다 큰 값만 오도록 정렬한 Binary Tree를 의미한다. 
#### 장점
일반적인 Tree 구조는 삽입에 O(1), 탐색에 O(n)의 비용이 걸린다. 삽입은 아무 노드의 child로 붙이면 되고, 탐색은 Tree 내의 모든 노드를 순회해야 하기 때문이다.<br>
반면 Binary Search Tree의 경우 삽입/삭제 시엔 바뀐 노드에 대해 Tree 높이만큼의 링크에서 재조정을 해야 하므로 O(logn), 탐색 시엔 Root에서부터 시작하여 데이터 크기에 따라 Tree의 높이만큼만 탐색하면 되기 때문에 평균적으로 O(logn)의 비용이 든다. 
#### 단점
Tree의 균형 상태에 영향을 많이 받는다. 데이터의 삽입, 삭제에 따라 Tree가 어떤 형태일지 보장할 수 없고, 따라서 사실상 Linked List와 다름 없는 Tree 형태(데이터 n개, 높이 n)일 가능성을 배재할 수 없다. 따라서 극히 드문 확률이지만, 탐색에 O(n)의 비용이 드는 경우도 생긴다(일반 Tree보다 삽입은 복잡하나 탐색은 동일한 최악의 경우). 
*  이를 해결하기 위해서는 작업을 정지하고 추가적인 비용을 들여 Tree를 재조정해야 한다.

### Adelson-Velskii and Landis Tree(AVL Tree)
AVL Tree는 Binary Search Tree의 단점을 보완하기 위해 나온 Tree이다. AVL에서는 매 삽입마다 left subtree와 right subtree의 높이 차이를 점검하여 차이가 2 이상 난다면 Node Rotation을 통해 균형을 맞춰주는 작업을 한다. 따라서 항상 최소의 높이를 유지할 수 있게 하여 삽입/삭제/탐색을 모두 O(logn)으로 고정시킬 수 있다.<br>
AVL Tree는 각 노드에 노드를 root로 하는 subtree의 height 값을 저장하고, 매 삽입/삭제마다 root의 양 subtree의 height 차이를 비교하여 불균형 상태를 탐지한다. 삽입 시에 불균형이 발생하는 경우는 총 4가지가 있다.
*  Node의 Left child의 Left subtree에 삽입해 Node의 Left, Right height 차가 2가 되는 경우: 오른쪽, 시계방향으로 Single Right Rotation을 수행하여 Left subtree, Left child, Node를 left_child(= left subtree), Node(= Left child), right_child(= Node)로 바꿔준다. 만약 left child가 right subtree를 갖고 있었다면, 이는 Node의 left subtree로 옮겨준다(Node는 기존에 갖고 있던 left child가 새 parent가 되면서 비게 됨. 이 자리에 left child의 right subtree를 넣음). 
*  Node의 Right Child에 right subtree를 삽입하면서 불균형이 발생하는 경우: 위의 문제와 방향만 다르다. 즉, Single Left Rotation을 수행한다.
*  Left child의 right subtree가 길어져 불균형이 발생하는 경우: 이 경우 데이터 크기가 Left child - right subtree - parent 순이기 때문에 한 번의 Rotation으로 해결이 불가능하다. 따라서 이를 해결하기 위해선 두 번의 Rotation이 필요하다. 우선 Left Child와 Right Subtree를 축으로 Left Rotation을 수행하여 Left child <- Right Subtree <- parent와 같이 조정한다. 이렇게 되면 불균형은 그대로지만, Left child & Left subtree 상황이 되어 Right Rotation 한번으로 해결이 가능해진다. 즉, Left child & right subtree 상황에선 Left Rotation 후, Right Rotation을 하여 해결한다.
*  Right child의 left subtree가 길어지는 경우: 위 경우와 방향만 다르게, Right Rotation + Left Rotation으로 해결 가능하다.

삭제의 경우에도, 삭제로 생긴 불균형이 위의 4 경우 중 어느 경우인지 파악한 후, 그에 맞춰 Rotation을 하여 균형을 맞춘다.
#### AVL Tree 시간 복잡도
AVL은 항상 1 이하의 height 차를 유지하고, 2 이상의 높이 차가 발생시 한번 조정하여 높이 차 1을 줄인다. 즉, 불균형 발생 시 2번 이상의 조정을 할 일은 없으므로, 균형 조정은 O(1)의 비용을 요구한다(= 데이터가 무수히 많아도 성능에 큰 영향 없음). 또한 균형이 유지되어 Linked List와 유사한 수준의 극단적인 Tree가 발생하지 않기 때문에, 삽입 삭제는 최악의 경우에도 O(logn)의 비용이 소모된다(Binary search tree의 단점 해결).

### Priority Queue(= Heap)
Priority Queue, Heap은 항상 우선순위가 가장 높은 데이터를 Dequeue하는 Queue이다. Heap의 구현은 여러 방법이 존재하지만, 가장 단순한 방법으로는 Complete Binary Tree + Partially Ordered 구조를 응용한 binary heap이 있다.<br>
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
