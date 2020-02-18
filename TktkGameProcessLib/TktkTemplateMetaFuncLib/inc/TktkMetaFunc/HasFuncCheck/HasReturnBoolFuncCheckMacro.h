#ifndef HAS_RETURN_BOOL_FUNC_CHECK_MACRO_H_
#define HAS_RETURN_BOOL_FUNC_CHECK_MACRO_H_

#include <type_traits>

#define HAS_RETURN_BOOL_FUNC_CHECK(funcName)																		\
																													\
struct has_ ## funcName ## _member_impl																				\
{																													\
	template <class T, class... Args>																				\
	static auto check(T*) -> decltype(																				\
		std::declval<T&>()->funcName(std::declval<Args>()...), std::true_type()										\
		);																											\
																													\
	template <class T, class... Args>																				\
	static auto check(...)->std::false_type;																		\
};																													\
																													\
template <class T, class... Args>																					\
struct has_ ## funcName ## _member : decltype(has_ ## funcName ## _member_impl::check<T, Args...>(nullptr))			\
{																													\
};																													\
																												   	\
template<class... Args>																								\
struct has_ ## funcName ## _checker																				   	\
{																												   	\
	template <class T, typename std::enable_if<has_ ## funcName ## _member<T, Args...>::value>::type* = nullptr>	\
	static bool check(T runClass)																					\
	{																											   	\
		return true;																							   	\
	}																											   	\
	template <class T, typename std::enable_if<!has_ ## funcName ## _member<T, Args...>::value>::type* = nullptr>	\
	static bool check(T runClass)																					\
	{																											   	\
		return false;																							   	\
	}																											   	\
};																												   	\
																													\
template<class... Args>																								\
struct funcName ## _runner																							\
{																													\
	template <class T, typename std::enable_if<has_ ## funcName ## _member<T, Args...>::value>::type* = nullptr>	\
	static bool checkAndRun(T runClass, Args... params)																\
	{																												\
		return runClass-> ## funcName ## (params...);																\
	}																												\
	template <class T, typename std::enable_if<!has_ ## funcName ## _member<T, Args...>::value>::type* = nullptr>	\
	static bool checkAndRun(T runClass, Args... params)																\
	{																												\
		return false;																								\
	}																												\
};

#endif // !HAS_RETURN_BOOL_FUNC_CHECK_MACRO_H_