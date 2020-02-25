#ifndef HAS_FUNC_CHECK_MACRO_H_
#define HAS_FUNC_CHECK_MACRO_H_

#include <type_traits>

#define HAS_FUNC_CHECK(funcName)																														\
																																						\
/* �uhas_## funcName ##_checker�v�̂��߂̍\���� */																										\
struct has_## funcName ##_checker_impl																													\
{																																						\
	/* �uReturnType = JudgePtrType->## funcName ##(ArgsType...)�v����������Ȃ�ustd::true_type�v�^��Ԃ��֐��ƂȂ� */									\
	template <class JudgePtrType, class ReturnType, class... ArgsType>																					\
	static auto check(JudgePtrType*)																													\
		->decltype(std::declval<JudgePtrType&>()->## funcName ##(std::declval<ArgsType>()...),															\
			std::bool_constant<std::is_same_v<decltype(std::declval<JudgePtrType&>()->## funcName ##(std::declval<ArgsType>()...)), ReturnType>>());	\
																																						\
	/* �uReturnType = JudgePtrType->## funcName ##(ArgsType...)�v���������Ȃ��Ȃ�ustd::false_type�v�^��Ԃ��֐��ƂȂ�	*/								\
	template <class JudgePtrType, class ReturnType, class... ArgsType>																					\
	static auto check(...)																																\
		->std::false_type;																																\
};																																						\
																																						\
/* �uReturnType = JudgePtrType->## funcName ##(ArgsType...)�v����������Ȃ�ustd::true_type�v�A���Ȃ��Ȃ�ustd::false_type�v�̌^�ɂȂ� */				\
template <class JudgePtrType, class ReturnType, class... ArgsType>																						\
using has_## funcName ##_checker = decltype(has_## funcName ##_checker_impl::check<JudgePtrType, ReturnType, ArgsType...>(nullptr));					\
																																						\
																																						\
/* �uhas_## funcName ##_member�v�̔���Ŏg�p����֐��̈����A�߂�l���w�� */																				\
template<class ReturnType, class... ArgsType>																											\
struct funcName ##_runner																																\
{																																						\
	/* �uReturnType = JudgePtrType->## funcName ##(ArgsType...)�v����������Ȃ�֐������s���Ă��̖߂�l��Ԃ� */										\
	template <class JudgePtrType, std::enable_if_t<has_## funcName ##_checker<JudgePtrType, ReturnType, ArgsType...>::value>* = nullptr>				\
	static ReturnType checkAndRun(JudgePtrType runClass, ReturnType&& defaultReturnValue, ArgsType... params)											\
	{																																					\
		return std::forward<ReturnType>(runClass->## funcName ##(params...));																			\
	}																																					\
																																						\
	/* �uReturnType = JudgePtrType->## funcName ##(ArgsType...)�v���������Ȃ��Ȃ�֐������s�����ɁudefaultReturnValue�v��Ԃ� */						\
	template <class JudgePtrType, std::enable_if_t<!has_## funcName ##_checker<JudgePtrType, ReturnType, ArgsType...>::value>* = nullptr>				\
	static ReturnType checkAndRun(JudgePtrType runClass, ReturnType&& defaultReturnValue, ArgsType... params)											\
	{																																					\
		return std::forward<ReturnType>(defaultReturnValue);																							\
	}																																					\
																																						\
};																																						\
/* �uhas_## funcName ##_member�v�̔���Ŏg�p����֐��̖߂�l�������ivoid�j�̏ꍇ */																		\
template <class... ArgsType>																															\
struct funcName ##_runner<void, ArgsType...>																											\
{																																						\
	/* �uJudgePtrType->## funcName ##(ArgsType...)�v����������Ȃ�֐������s���� */																		\
	template <class JudgePtrType, std::enable_if_t<has_## funcName ##_checker<JudgePtrType, void, ArgsType...>::value>* = nullptr>						\
	static void checkAndRun(JudgePtrType runClass, ArgsType... params)																					\
	{																																					\
		runClass->## funcName ##(params...);																											\
	}																																					\
																																						\
	/* �uJudgePtrType->## funcName ##(ArgsType...)�v���������Ȃ��Ȃ牽�����Ȃ� */																		\
	template <class JudgePtrType, std::enable_if_t<!has_## funcName ##_checker<JudgePtrType, void, ArgsType...>::value>* = nullptr>						\
	static void checkAndRun(JudgePtrType runClass, ArgsType... params) {}																				\
};

#endif // !HAS_FUNC_CHECK_MACRO_H_