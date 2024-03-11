export module M;

export {

template<typename>
class X {};

template<typename T>
class X<T*> {};

template<>
class X<void> {};

X<int>	x1;
X<int*> x2;
X<void> x3;

}