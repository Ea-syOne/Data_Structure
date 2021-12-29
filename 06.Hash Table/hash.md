## Hash Table
Hash Table의 경우 삽입, 삭제, 탐색에 특화된 자료구조이다. 그러기 위해 최소, 최대 값 탐색, 정렬 등의 기능은 깔끔하게 포기한다.<br>
각 데이터는 Key 값을 가지며, Key 값을 이용해 데이터가 저장될 위치를 지정하게 된다. 따라서 특정 Key를 가진 데이터를 탐색하고자 할 때 특정 위치만을 탐색하여 탐색량을 현저히 줄일 수 있는 구조이다.
### Hash Table 구조
*  **Bucket**: Hash Table에서 데이터를 담는 공간 단위. Hash Table은 하나 이상의 Bucket로 구성된다. 
*  **Hash Function**: 데이터를 넣을 Bucket을 지정해주는 함수. 데이터 삽입의 경우 f(data.key)가 가리키게 되는 Bucket에 삽입을 하게 된다.<br> Hash Function의 경우 계산이 복잡하지 않아야 하며(비용이 적어야 하며), 후술할 Collision을 최소화해야 한다.
*  **Collision**: 하나의 Bucket에 Key가 다른 데이터들이 담기게 되는 것을 의미한다. Collision이 발생하게 되면 데이터의 탐색 시간이 Hash Table이 의도하는 시간보다 더 길어질 수 밖에 없다(Bucket의 데이터 양이 많아지므로). 

### Hash Insert - Collision 최소화 방안
Hash Insert에서 주의할 점은 Collision 관리라 할 수 있다. 여기에는 크게 2가지 방안이 존재한다.
#### Seperate Chaining(= Open Hashing)
Collision이 발생하면 해당 Bucket이 아닌 새 공간을 할당하여 해당 공간에 Key가 다른 데이터를 담고, 두 공간을 next pointer로 Linking하는 방식이다. Hash Table이 아닌 공간을 할당하여 사용하기 때문에 Open Hashing이라고도 불린다. <br>
이 구현 방식에서 탐색을 하게 되면 Key에 따라 Bucket을 찾은 후, Bucket 내에서 Key와 일치하는 공간이 나올 때까지 Linked List를 탐색 후(추가 작업), 해당 공간 내에서 데이터를 찾게 된다. 따라서 탐색에 다소 Overhead가 발생하지만 데이터를 놓치지 않고 구현도 쉬운 장점이 있다.
>  Linked List 역시 길어질수록 매우 비효율적이기 때문에, 하나의 Bucket에 매달린 Linked List가 일정 이상 길어지면 이를 Tree로 변환하기도 한다. 대표적으로 Java 8 이상에서 이러한 방식으로 구현한다.
#### Open Addressing(= Closed Hashing)
Collision이 발생할 경우, 정해진 규칙에 따라 빈 Bucket을 찾아 해당 Bucket에 저장하는 방법이다. 처음 만들어진 Hash Table 공간에서만 데이터를 저장하기 때문에 Closed Hashing이라고도 불린다. <br>
빈 Bucket을 찾는 규칙은 일반적으로 다음 3가지가 있다.
*  **Linear** - 해당 Bucket 바로 다음 Bucket을 본다. Linear 방식의 경우 특정 Bucket 범위에 Collision이 집중될 경우 그 근처 Bucket에 계속 배치하면서 데이터가 배치된 Bucket 클러스터가 커지게 된다. 이 결과 평균 탐색 시간이 증가하게 된다.
>  f(key) = A => Bucket A 탐색 => 없으니 바로 옆 탐색 => 다른 Collision으로 인해 이미 차있음 => 옆 탐색 => 또 아님 => ... <br> 이를 1차 군집(Primary Clustering) 현상이라 한다. 
*  **Quadratic** - 이차 함수 결과 값을 이용해 빈 Bucket을 찾아가는 방식이다. 특정 Bucket 범위에 Collision이 집중되더라도 그 근처에 배치될 경우가 적기 때문에 1차 군집은 잘 일어나지 않는다. 하지만 한 Bucket에 Collision이 n번 발생될 때 Quadratic 계산을 최소 1 + 2 + ... + n 번 수행해야 되기 때문에 비효율적으로 동작할 수 있다(= 2차 군집). >  이를 해결하기 위해 2개의 함수를 사용하는 Double Hashing을 사용한다. 
*  **Random** - 무작위로 빈 Bucket을 탐색하는 방식. 오히려 좋을 수도 있다.

Open Addressing은 Hash Table 내 빈 공간을 사용하여 **효율적인 공간 관리**를 할 수 있도록 하지만 Hash Table이 **가득 차게 되면 더 이상 데이터를 넣을 수 없다**는 단점과 **빈 Bucket을 찾는 데에서 발생하는 Overhead가 데이터 적재율이 높아질수록 가파르게 상승**한다는 단점이 존재한다.
>  따라서 Open Addressing 방식에서는 **적재율이 임계점 이상을 넘어가면 Hash Table을 두배로 키우고 모든 원소를 다시 Hashing**하는 작업을 수행하게 된다(= **Rehashing**).
### Hash Delete(Open Addressing)
Open Addressing에서는 삭제에 따라 추가적인 문제가 발생할 수 있다. Bucket A에 key=x가 담겨있어 Bucket A+1에 key=y를 저장한 상태에서, key=x 데이터를 모두 delete해 **Bucket A가 비게 된 상황**을 가정해보자. 이때 key=y인 데이터를 탐색할 경우 Bucket **A를 빈 Bucket으로 판단하여 탐색을 중단**하고 key=y인 Bucket이 존재하지 않는다고 판단하게 된다. 즉 **Find(data with key=y)를 할 경우 Hash Table에 그 값이 있음에도 못찾는 경우가 발생**한다.<br>
이를 방지하기 위해 Open Addressing에서는 Bucket이 지워질 때 **DELETED라는 상수값**을 넣어준다. 그리고 **Find**를 하게 될 경우 탐색한 Bucket이 DELETED라면 탐색 Function에 따라 다음 Bucket을 찾아가게 한다. **Insert**를 하게 되는 경우엔 DELETED Bucket은 빈 Bucket으로 보고 해당 Bucket에 삽입을 수행한다.
> Insert를 하게 될 때엔 우선 해당 key를 가진 Bucket이 존재하는지 탐색 -> 없다면 삽입할 Bucket 탐색 순으로 작업하기 때문에, 서로 다른 Bucket에 같은 key 값을 가진 data가 담기는 경우는 존재하지 않는다.

#### 장점
*  삽입, 삭제, 탐색이 모두 빠르다. 삽입, 삭제의 경우 해당 위치에서 지우면 되니 Find + O(1)이고, 탐색의 경우에도 Key에 따라 Indexing된 공간만 탐색하기 때문에 상당히 빠르다.
#### 단점 
*  Hash Function, 또는 빈 Bucket 탐색 Function을 어떤 것을 쓰느냐에 따라 효율이 좌우된다.
*  크기 등에 따라 정렬해야 하는 데이터 관리에는 적합하지 않다.
*  공간을 상당히 많이 소비한다. 
