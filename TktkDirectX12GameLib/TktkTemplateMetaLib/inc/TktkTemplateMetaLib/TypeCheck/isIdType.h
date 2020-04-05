#ifndef IS_ID_TYPE_H_
#define IS_ID_TYPE_H_

#include <type_traits>

// �e���v���[�g�����̌^��id��\����œK�؂��𔻒肷��萔
template <class T>
constexpr bool is_idType_v = (std::is_enum_v<T> || std::is_integral_v<T>);

#endif // !IS_ID_TYPE_H_