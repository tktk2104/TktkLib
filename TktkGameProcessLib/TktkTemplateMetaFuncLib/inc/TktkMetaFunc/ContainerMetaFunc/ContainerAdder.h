#ifndef CONTAINER_ADDER_H_
#define CONTAINER_ADDER_H_

#include <type_traits>

struct HasPushFrontMemberImpl
{
	template <class T, class U>
	static auto check(T*, U*) -> decltype(
		std::declval<T>().push_front(std::declval<U>()),
		std::true_type()
		);

	template <class T, class U>
	static auto check(...)->std::false_type;
};

// テンプレートパラメータのクラスが「push_front(T)」を持っているかの判定
template <class T, class U>
struct HasPushFrontMember : decltype (HasPushFrontMemberImpl::check<T, U>(nullptr, nullptr)) {};

// 指定したコンテナに要素を追加する
struct ContainerAdder
{
	template <class Container, class AddObject, typename std::enable_if<HasPushFrontMember<Container, AddObject>::value>::type* = nullptr>
	static void checkToAdd(Container& container, const AddObject& addObject)
	{
		container.push_front(addObject);
	}

	template <class Container, class AddObject, typename std::enable_if<!HasPushFrontMember<Container, AddObject>::value>::type* = nullptr>
	static void checkToAdd(Container& container, const AddObject& addObject)
	{
		container.push_back(addObject);
	}
};
#endif // !CONTAINER_ADDER_H_