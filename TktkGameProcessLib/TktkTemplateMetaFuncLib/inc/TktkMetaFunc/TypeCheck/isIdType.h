#ifndef IS_ID_TYPE_H_
#define IS_ID_TYPE_H_

#include <type_traits>

// テンプレート引数の型がidを表す上で適切かを判定する定数
template <class T>
constexpr bool is_idType_v = (std::is_enum_v<T> || std::is_integral_v<T>);

// 
template <class... Ts>
class is_idType_all
{
public:

	template <class Head, class... Body>
	struct is_idType_all_check
	{
		static constexpr unsigned int value = is_idType_v<Head> + is_idType_all_check<Body...>::value;
	};

	template <class Head>
	struct is_idType_all_check<Head>
	{
		static constexpr unsigned int value = is_idType_v<Head>;
	};

public:

	static constexpr bool value = (is_idType_all_check<Ts...>::value == sizeof...(Ts));
};

template <class... Ts>
constexpr bool is_idType_all_v = is_idType_all<Ts...>::value;

#endif // !IS_ID_TYPE_H_