#ifndef HAS_VALUE_CHECK_MACRO_H_
#define HAS_VALUE_CHECK_MACRO_H_

#include <type_traits>

#define HAS_VALUE_CHECK(valueName)																										\
																																		\
struct has_## valueName ##_chcker_impl																									\
{																																		\
	template <class JudgePtrType, class ValueType>																						\
	static auto check(JudgePtrType*)																									\
		->decltype(std::declval<JudgePtrType&>()->## valueName ##,																		\
			std::bool_constant<std::is_same_v<decltype(std::declval<JudgePtrType&>()->## valueName ##), ValueType>>());					\
																																		\
	template <class JudgePtrType, class ValueType>																						\
	static auto check(...)																												\
		->std::false_type;																												\
};																																		\
																																		\
template<class JudgePtrType, class ValueType>																							\
using has_## valueName ##_chcker = decltype(has_## valueName ##_chcker_impl::check<JudgePtrType, ValueType>(nullptr));					\
																																		\
template<class ValueType>																												\
struct valueName ##_setter																												\
{																																		\
	template <class JudgePtrType, std::enable_if_t<has_## valueName ##_chcker<JudgePtrType, ValueType>::value>* = nullptr>				\
	static void chackAndSet(JudgePtrType runClass, ValueType&& value)																	\
	{																																	\
		runClass->## valueName ## = std::move(value);																					\
	}																																	\
	template <class JudgePtrType, std::enable_if_t<!has_## valueName ##_chcker<JudgePtrType, ValueType>::value>* = nullptr>				\
	static void chackAndSet(JudgePtrType runClass, ValueType&& value) {}																\
};																																		\
template<class ValueType, int ArraySize>																								\
struct valueName ##_array_setter																										\
{																																		\
	template <class JudgePtrType, std::enable_if_t<has_## valueName ##_chcker<JudgePtrType, ValueType[ArraySize]>::value>* = nullptr>	\
	static void chackAndSet(JudgePtrType runClass, const ValueType* arrayTop)															\
	{																																	\
		memcpy(&(runClass->## valueName ##), arrayTop, sizeof(ValueType) * ArraySize);													\
	}																																	\
	template <class JudgePtrType, std::enable_if_t<!has_## valueName ##_chcker<JudgePtrType, ValueType[ArraySize]>::value>* = nullptr>	\
	static void chackAndSet(JudgePtrType runClass, const ValueType* arrayTop) {}														\
};

#endif // !HAS_VALUE_CHECK_MACRO_H_
