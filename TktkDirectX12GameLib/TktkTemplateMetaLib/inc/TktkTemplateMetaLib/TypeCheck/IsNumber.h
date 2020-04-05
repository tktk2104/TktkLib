#ifndef IS_NUMBER_H_
#define IS_NUMBER_H_

#include <type_traits>

// �e���v���[�g�����̌^��������\�����𔻒肷��N���X
template <class JudgeTypes>
class is_number
{
public:

	static constexpr bool value = (std::is_integral_v<JudgeTypes> || std::is_floating_point_v<JudgeTypes>);
};

// �e���v���[�g�����̌^��������\�����𔻒肷��萔
template <class JudgeTypes>
constexpr bool is_number_v = is_number<JudgeTypes>::value;

#endif // !IS_NUMBER_H_