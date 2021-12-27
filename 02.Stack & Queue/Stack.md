### Stack
#### 개요

![Stack](https://user-images.githubusercontent.com/86412960/147438965-8d379c6f-2ffb-4da8-b0bf-d108c54eda2c.png) <br><br>
Stack은 FILO(First In Last Out) 기반의 자료구조이다. 즉, Stack은 먼저 들어온 데이터는 마지막에 추출되며, 최신 데이터를 우선적으로 추출하는 구조이다. 따라서 Stack의 ADT로는 새로운 값을 입력하는 `void Push(Data)`와 가장 최근에 들어온 값을 추출하는 `dataType Pop(void)`이 존재한다.<br>
스택의 구현은 일반적으로 배열 기반 또는 Linked-List 기반으로 구현된다.
#### Array-based Stack
Stack을 배열 기반으로 구현할 때에는 메타데이터의 보조가 필수적이다. Stack 배열의 용량인 **Capacity**와, Stack의 꼭대기의 index 값인 **TopOfStack**이다. 
> TopOfStack을 고정된 위치(= 0번 index)로 하면 **TopOfStack** 메타데이터가 필요 없지만, 매 Pop마다 전체 데이터를 재정렬해야 하기 때문에 매우 비효율적이다.<br> 따라서 일반적으로는 매 Push, Pop마다 TopOfStack만 재조정하는 방식으로 구현한다. 

Stack 배열을 고정된 크기로 할당한 이후, Push할 때마다 TopOfStack이 한 칸씩 증가하고, Pop할 때마다 TopOfStack이 한 칸씩 감소하게 된다. 
> Pop을 할 때 굳이 해당 데이터를 정리하진 않지만, TopOfStack 이상의 값에 접근하지 못하도록 설계하여 사실상 존재하지 않는 데이터 취급을 한다.

* 장점: 데이터 하나당 요구하는 공간이 적다(메타 데이터를 요구하지만 각 데이터가 1/n로 부담하기 때문에 크게 문제되진 않는다). 
* 단점: 배열 기반이기 때문에, 초기에 큰 공간을 할당 후 많은 데이터를 담지 않는다면 공간 낭비가 발생한다. <br> 구현에 있어 신경 쓸 부분이 많다(Capacity 초과 여부, 그에 따른 공간 재할당, Push/Pop마다 TopofStack 값 조정 등).
#### Linked_List-based Stack
Linked-List 기반으로 구현하게 되면 TopOfStack(LL 특성상 고정 위치를 TopOfStack으로 설정 가능해짐 -> 불필요), Capacity(Linked-List이므로 불필요)가 불필요해진다.
* 장점: 구현이 많이 편해진다(메타데이터 신경 쓸 필요 없음, 공간 재할당 필요 없음). 사용하는 데이터만 공간을 할당 받기 때문에 낭비되는 공간이 없다. 
* 단점: 각 data가 next 값(+ prev 값까지)을 가져야 하기 때문에 데이터 하나가 차지하는 공간이 커진다. 이는 data 크기가 클 경우 미미한 차이기 때문에 문제되진 않는다.
