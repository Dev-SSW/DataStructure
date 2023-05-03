목표
------------------------------------------

- 덧셈 (+) 연산자를 추가할 수 있다. ("1번 문제: Vector<Object> + Vector<Object>") -> Vector<Object> operator+(const Vector& rhs)

- 덧셈 (+) 연산자를 추가할 수 있다. ("2번 문제: Vector<Object> + Object") -> Vector<Object> operator+(const Object& rhs)

- Vector<Object> 클래스에 insert 메쏘드를 추가할 수 있다.  ("3번 문제: Vector<Object>.insert(itr, Object)") -> iterator insert(iterator itr, const Object& x)

- Vector<Object> 클래스에 erase 메쏘드를 추가할 수 있다. ("4번 문제: Vector<Object>.erase(itr)") -> iterator erase(iterator itr)

실행 결과 확인 방법
------------------------------------------

1번 문제: Vector<Object> + Vector<Object>

Vector[ 3 ] = { 1 , 2 , 3 }
Vector[ 5 ] = { 1 , 2 , 3 , 4 , 5 }
Vector[ 0 ] = {  }

Vector[ 3 ] = { cat , dog , tiger }
Vector[ 5 ] = { one , two , three , four , five }
Vector[ 0 ] = {  }


2번 문제: Vector<Object> + Object

Vector[ 3 ] = { 1 , 2 , 3 }
Vector[ 0 ] = {  }
Vector[ 0 ] = {  }

Vector[ 3 ] = { cat , dog , tiger }
Vector[ 0 ] = {  }
Vector[ 0 ] = {  }


3번 문제: Vector<Object>.insert(itr, Object)

Vector[ 3 ] = { 1 , 2 , 3 }
Vector[ 3 ] = { 1 , 2 , 3 }
itr_val after the insert  : 1

Vector[ 3 ] = { cat , dog , tiger }
Vector[ 3 ] = { cat , dog , tiger }
itr_val after the insert  : cat


4번 문제: Vector<Object>.erase(itr)

Vector[ 3 ] = { 1 , 2 , 3 }
Vector[ 3 ] = { 1 , 2 , 3 }
itr_val after the erase  : 1

Vector[ 3 ] = { cat , dog , tiger }
Vector[ 3 ] = { cat , dog , tiger }
itr_val after the erase  : cat
