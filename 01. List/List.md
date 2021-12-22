## List

### List ADT
List는 데이터를 연속적으로 연결하여 저장하는 자료구조로, 동일한 속성을 갖는 데이터 묶음을 관리하는 데에 사용하는 가장 일반적인 자료구조이다.<br> 
List를 관리하는 핵심적인 기능은 3가지가 있는데, **데이터 삽입(Insert)**, **데이터 제거(Delete)**, **데이터 탐색(Find)** 이다. List를 구현하고자 할 때 이 3가지 기능의 성능을 고려하여 구현해야 하는데, 
모든 기능을 가장 효율적으로 수행하는 자료구조는 없기에 각 기능의 우선순위에 따라 알맞은 자료구조를 사용해야 한다.<br>

### Array List
가장 기본적인 List인 array List는 배열을 이용하여 구현한다. 메모리 상의 한 지점에서 연속적으로 값을 저장하며, 이를 index를 통해 접근할 수 있는 구조이다. 
#### 장점
*  배열은 C, python, java 등에서 기본으로 제공해주기 때문에, **구현이 매우 쉽다**.
*  별도의 메타데이터 없이 각 데이터를 저장할 공간만 있어도 된다.
#### 단점
*  한 번 공간을 할당한 이후 **공간을 축소/확장을 하기 위해서는 큰 비용**을 들여야 한다. 이 때문에 배열 기반 List는 
1) _사용하는 데이터의 최대 사이즈를 미리 알고 그에 맞춰 공간 할당을 하거나_, 
2) _충분히 큰 크기로 할당하거나(공간의 낭비 발생)_, 
3) _C++ vector와 같이 공간 재할당 비용을 최소화한 채로 사용하게 된다_.
*  삽입/삭제 시 해당 위치 이후 값들을 한 칸씩 밀거나 당겨줘야 하기 때문에 삽입/삭제의 복잡도가 크다(_O(N)의 시간복잡도_).
*  탐색도 pattern matching 방식으로 하기 때문에 sorting과 그에 기반한 별도의 탐색 알고리즘 없이는 O(N)의 시간복잡도를 갖는다. 
#### 총평
Array List는 어느 Language에서도 **보편적으로 지원**하고, List의 **구현이 매우 편리**하지만,<br>
**삽입/삭제/탐색의 비용이 크기 때문에** 관리하는 데이터의 양이 커질 경우 **상당한 비효율**이 발생한다.

### Linked List
Linked List는 Array List에서의 **삽입/삭제 성능을 개선**하기 위해 제안된 자료구조이다. 하나의 **Node**에 **Data**와 다음 Node를 가리키는 Pointer인 **Next**를 저장하며, Next를 통해 각 데이터를 연결하는 구조이다.
#### 장점
*  자료가 저장된 위치에 기반한 indexing을 하지 않기 때문에 각 Node가 디스크(또는 메모리) 상에 연속적으로 저장될 필요가 없다. 따라서 공간의 활용 측면에서 array List보다 더 유연하다.
*  위의 이유 때문에 List의 크기가 변동되더라도 재할당할 필요가 없다. 따라서 크기를 확정할 수 없는 List에서는 더 유리하다.
*  삽입의 경우 삽입할 위치를 입력받는다면 new -> Next를 pos -> Next로 만들고, pos -> Next를 new로 만들기만 하면 되기 때문에 O(1)의 시간복잡도를 갖는다. 
#### 단점
*  Next라는 메타데이터가 매 노드마다 필요하기 때문에 Array List보다 더 큰 비용이 요구된다. data의 크기가 작을 경우, 예를 들어 pointer 변수와 같은 크기의 데이터라면 Array List 사용 시보다 2배의 공간이 요구된다. 
*  탐색의 경우 Array List와 동일하게 O(N)의 비용이 든다. 
*  삭제는 pos 값을 입력 받으면 pos_prev -> next를 pos->next로 만들어 줘야하기 때문에 pos 이전 Node인 pos_prev를 탐색해야 하고, 따라서 O(N) + O(1) = O(N)의 비용이 들게 된다. 
> 이 문제를 해결하기 위해서 제안된 자료구조가 Double-Linked List로, 각 Node가 next 뿐만 아니라 prev Node pointer도 갖는 구조이다. 그만큼 공간 사용 측면에서 손해를 보지만, 위치가 주어질 때의 삭제 비용을 O(1)로 줄여준다는 장점이 있다.

### Skip List
Linked List, Double-Linked List에 거쳐 삽입, 삭제의 성능을 O(1)까지 끌어 올렸지만, 여전히 탐색은 O(N)으로 보완되지 못한 형태이다. Linked-List에서 Find를 더 효율적으로 하기 위해 보완한 구조가 Skip List로, Skip List는 2가지 특징을 갖는다. 
*  각 Node가 하나 이상의 next 값을 갖는다(= next 배열을 갖는다). 이때 모든 Node가 MAX_LEVEL개의 next를 갖진 않는다(공간을 절약하기 위함). 
*  List의 data들이 크기 순으로 정렬되어 있다.

Skip List는 MAX_LEVEL개의 next를 갖는 head, tail Node에 의해 관리되며(각각 -∞, +∞ 값을 가짐), 모든 Node는 같은 Level 상에서 next로 Link되어 있다. 이를 보이면 다음 그림과 같다. <br>
![skip](https://user-images.githubusercontent.com/86412960/125391694-dffc5400-e3df-11eb-92a0-cf17d289bc19.png)
<br>
따라서 Find(x)를 하게 되면 head의 MAX_LEVEL부터 시작해서 data level에 내려올 때까지 다음 로직을 반복한다.
*  만약 현재 level의 next Node가 갖는 data가 x보다 크다면 현재 Node의 하위 level로 내려가고, x보다 작거나 같다면 next Node의 하위 level로 내려간다.

이를 반복하다 data level까지 내려가면 원하는 값을 찾을 수 있게 된다. <br>
#### 시간 복잡도
따라서 하나의 data를 찾는데엔 MAX_LEVEL번의 작업이 필요하고, 즉 Level의 높이에 따라 탐색의 동작 시간이 결정되고 이는 구현 방식에 따라 다르다. <br>
Skip List에서 많이 채택한 방식으로는 Random 방식이 있다. 반대 개념으로는 고정된 index Node에 정해진 next level을 부여하는 perfect skip list가 있지만, 이는 삽입/삭제 시마다 바뀐 index에 따라 재조정해야 하기 떄문에 비효율적으로 여겨진다. Random Skip List의 경우 확률에 기반한 방식으로, 삽입/삭제 시 마다 Coin toss를 통해 다음 Level을 가질지를 결정하는 방식이다. 예를 들어 y를 삽입하게 되면 우선 next 0에 다음 Node pointer를 넣고, coin toss를 한다. 만약 앞면이라면 next 1을 갖고, 다음 level 1 Node Pointer를 가리키게 한다. 이후 다시 coin toss를 하여 level 2를 가질지 결정하고, 앞면이면 이를 반복한다. 
#### 장점
*  탐색이 빠르다. Random Skip List의 경우 보통 Log n의 level을 갖기 떄문에, 평균 O(log n)의 탐색 시간을 갖는다(확률성 자료구조이기 떄문에 최악의 경우는 O(N)이 나올 수 있다).
#### 단점
*  데이터 정렬, next 배열 조정 때문에 삽입, 삭제가 좀 더 오래 걸린다.  
