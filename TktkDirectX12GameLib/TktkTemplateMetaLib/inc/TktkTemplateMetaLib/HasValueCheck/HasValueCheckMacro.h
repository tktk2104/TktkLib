#ifndef HAS_VALUE_CHECK_MACRO_H_
#define HAS_VALUE_CHECK_MACRO_H_

#include <type_traits>

#define HAS_VALUE_CHECK(valueName)																										\
																																		\
/* �uhas_## valueName ##_checker�v�̂��߂̍\���� */																						\
struct has_## valueName ##_chcker_impl																									\
{																																		\
	/* �uJudgePtrType->valueName�v����������Ȃ�ustd::true_type�v�^��Ԃ��֐��ƂȂ� */													\
	template <class JudgePtrType, class ValueType>																						\
	static auto check(JudgePtrType*)																									\
		->decltype(std::declval<JudgePtrType&>()->## valueName ##,																		\
			std::bool_constant<std::is_same_v<decltype(std::declval<JudgePtrType&>()->## valueName ##), ValueType>>());					\
																																		\
	/* �uJudgePtrType->valueName�v���������Ȃ��Ȃ�ustd::false_type�v�^��Ԃ��֐��ƂȂ� */												\
	template <class JudgePtrType, class ValueType>																						\
	static auto check(...)																												\
		->std::false_type;																												\
};																																		\
																																		\
/* �uJudgePtrType->valueName�v����������Ȃ�ustd::true_type�v�A���Ȃ��Ȃ�ustd::false_type�v�̌^�ɂȂ� */								\
template<class JudgePtrType, class ValueType>																							\
using has_## valueName ##_chcker = decltype(has_## valueName ##_chcker_impl::check<JudgePtrType, ValueType>(nullptr));					\
																																		\
/* �uhas_## valueName ##_checker�v�̔���Ŏg�p����ϐ��̌^���w�� */																		\
template<class ValueType>																												\
struct valueName ##_setter																												\
{																																		\
	/* �uJudgePtrType->valueName = ValueType�v����������Ȃ炻�̒l�ɑ������̒l�������� */											\
	template <class JudgePtrType, std::enable_if_t<has_## valueName ##_chcker<JudgePtrType, ValueType>::value>* = nullptr>				\
	static void chackAndSet(JudgePtrType runClass, ValueType&& value)																	\
	{																																	\
		runClass->## valueName ## = std::move(value);																					\
	}																																	\
	/* �uJudgePtrType->valueName = ValueType�v���������Ȃ��Ȃ牽�����Ȃ� */																\
	template <class JudgePtrType, std::enable_if_t<!has_## valueName ##_chcker<JudgePtrType, ValueType>::value>* = nullptr>				\
	static void chackAndSet(JudgePtrType runClass, ValueType&& value) {}																\
};																																		\
																																		\
/* �uhas_## valueName ##_checker�v�̔���Ŏg�p����ϐ��̌^�Ƒ������z��̗v�f�����w�� */												\
template<class ValueType, int ArraySize>																								\
struct valueName ##_array_setter																										\
{																																		\
	/* �uJudgePtrType->valueName = ValueType[ArraySize]�v����������Ȃ炻�̒l�ɑ������̒l�����i�z����R�s�[�j���� */				\
	template <class JudgePtrType, std::enable_if_t<has_## valueName ##_chcker<JudgePtrType, ValueType[ArraySize]>::value>* = nullptr>	\
	static void chackAndSet(JudgePtrType runClass, const ValueType* arrayTop)															\
	{																																	\
		memcpy(&(runClass->## valueName ##), arrayTop, sizeof(ValueType) * ArraySize);													\
	}																																	\
	/* �uJudgePtrType->valueName = ValueType[ArraySize]�v���������Ȃ��Ȃ牽�����Ȃ� */													\
	template <class JudgePtrType, std::enable_if_t<!has_## valueName ##_chcker<JudgePtrType, ValueType[ArraySize]>::value>* = nullptr>	\
	static void chackAndSet(JudgePtrType runClass, const ValueType* arrayTop) {}														\
};

#endif // !HAS_VALUE_CHECK_MACRO_H_