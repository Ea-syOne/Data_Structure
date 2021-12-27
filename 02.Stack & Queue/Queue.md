### Queue
Queue은 FIFO(First In First Out) 기반의 자료구조이다. 즉, Queue에서는 먼저 들어온 데이터가 우선 추출되며, 나중에 들어온 데이터는 들어온 순서에 따라 추출하는 구조이다. 이렇게 들어온 순서에 따라 추출하는 특징 때문에 Job Scheduling 분야에서 많이 응용되는 자료구조이다. Queue의 ADT로는 새로운 값을 입력하는 Enqueue와 가장 오래된 값을 추출하는 dequeue가 있다.
#### Linked_List-based Queue
Linked List 기반으로 구현할 경우 Stack과 동일한 장단점을 가진다(구현이 쉽고 공간 낭비가 적지만, 하나의 데이터가 사용하는 공간의 크기가 커짐).<br>
다만 Stack과 다른 점은 Queue는 항상 Linked List 마지막에 저장된 오래된 값을 빼와야 하기 때문에, 1) n번 탐색하여 tail 이전 노드까지 찾아가거나, 2) double-linked list로 구현하여 O(1)의 비용으로 접근해야 한다. 공간 여유, 시간 여유에 따라 둘 중 하나를 선택해야 한다(대부분의 상황에선 후자가 유리).
#### Array-based Queue
배열 기반의 Queue의 경우 들어오는 데이터를 배열의 앞부분부터 채우는 방식으로 구현된다. 이 때 dequeue를 수행한 이후 한칸씩 당겨 추출한 값을 지우고 0번째 index에 다음 dequeue 대상이 오게끔하는 것은 매우 비효율적이다(O(n)의 비용). 따라서 Queue는 메타데이터 front(초기값 0)를 이용하여 추출할 데이터에 접근하며, dequeue 이후에는 단순히 front 값을 1 증가시킨다. 즉 Stack에서와 마찬가지로 값을 정리하진 않고, 접근만 막는 방식으로 구현한다.<br>
그러나 이러한 구현에는 Stack과 큰 차이가 있는데, Pop한 index에 새 값을 덮어쓰는 Stack과 달리 Queue는 해당 위치에 다시 접근하는 경우가 없기 때문에, 이 공간은 영구적으로 사용하지 못한다는 점이다. 이를 보완하는 Queue가 Circular Queue로, 메타데이터 front(추출할 위치)와 rear(삽입할 위치)가 배열의 용량을 벗어날 때 0으로 만들어 줌으로써 앞부분을 재활용하게끔 구현한다.
* 장점: 데이터 하나당 요구하는 공간이 적다(배열 기반 Stack과 동일한 이유). 
* 단점: 배열 기반이기 때문에, 초기에 큰 공간을 할당 후 많은 데이터를 담지 않는다면 공간 낭비가 발생한다. <br> 구현에 있어 신경 쓸 부분이 많다(Capacity 초과 여부, front, rear 값 조정 등). <br> front가 지나간 자리 재활용이 불가능하다(일반 Array-based Queue). <br> Enqueue, Dequeue, 접근에 있어 다양한 경우(순회 가능/불가 여부, 용량 초과 등)를 고려해야 한다(Circular Queue).
