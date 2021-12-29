## Disjoint-set
Tree 구조를 기반으로 집합을 표현한 자료구조이다. <br>
![Disjoint Set](https://user-images.githubusercontent.com/86412960/147632055-5dfcf244-3486-4493-8e27-29f82e7bc4b1.png)<br>
### Disjoint-set ADT
#### Makeset(dataType d)
하나의 원소를 갖는 새 집합을 생성.
#### Union(Set s1, Set s2)
두 집합을 병합하는 함수. s1과 s2 중 더 작은 tree의 root의 parent를 더 큰 tree의 root로 지정하여 두 집합을 합치게 된다.<br>
![Disjoint Set Union](https://user-images.githubusercontent.com/86412960/147632058-1f320c72-fba9-4c53-8406-18c42fabcbf8.png)<br>
O(1)의 복잡도를 갖는다.
#### Find(Set s, dataType d)
Find의 경우 d가 존재하는 set의 root 값을 찾아오는 함수. 따라서 작업 시간은 Tree 높이에 영향 받는다.<br>
따라서 Disjoint set은 Tree가 높게 형성되는 것을 피하는 것이 좋는데, 이를 위한 작업을 **Tree Compression**이라 한다. 
##### Tree Compression
**Tree Compression**은 Find 함수에 일부 기능을 추가하는 것으로 구현되는데, Find 과정에서 Root가 아닌 중간 노드들의 parent를 Find 함수에서 구해낸 Root 값으로 바꿔주는 것이다. 따라서 Find 비용을 줄이는 데 도움을 준다.
![Tree Compression](https://user-images.githubusercontent.com/86412960/147632062-ee0e5b8b-173d-42fa-91ea-1856d35698a3.png)
