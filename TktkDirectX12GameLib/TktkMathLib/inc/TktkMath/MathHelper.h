#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

namespace tktkMath
{
	class MathHelper
	{
	public:

		// �~����
		static constexpr float pi{ 3.14159265359f };

		// ����Ȃ��O�ɋ߂�����
		static constexpr float kEpsilon{ 1e-5f };

	public:

		// �Q�̒l����̓�����������^��Ԃ�
		static bool equals(float value1, float value2);

		// �����̒l�����̐��Ȃ�1�A���̐��Ȃ�-1��Ԃ��܂�
		static float sign(float value);

		// �l���w�肳�ꂽ�͈͓��ɐ������܂�
		static float clamp(float value, float min, float max);

		// 2�̒l�̍��̐�Βl���v�Z���܂�
		static float distance(float value1, float value2);

		// 2�̒l�̊Ԃ���`��Ԃ��܂�
		// ��amount�̒l��0�`1�̊Ԃ�Clamp�����
		static float lerp(float value1, float value2, float amount);

		// 2�̒l�̊Ԃ���`��Ԃ��܂�
		// ��amount�̒l��Clamp����Ȃ�
		static float lerpUnclamped(float value1, float value2, float amount);

		// current����target�֌����Ĉړ����܂�
		static float moveTowards(float current, float target, float maxDistanceDelta);

		// ���W�A����x�ɕϊ����܂��B
		static float toDegrees(float radian);

		// �x�����W�A���ɕϊ����܂��B
		static float toRadians(float degree);

		// �����F�x���@
		static float sin(float degree);

		// �R�T�C��
		static float cos(float degree);

		// �^���W�F���g
		static float tan(float degree);

		// �t�T�C���i�߂�l�F�x���@�j
		static float asin(float s);

		// �t�R�T�C���i�߂�l�F�x���@�j
		static float acos(float c);

		// �t�^���W�F���g�i�߂�l�F�x���@�j
		static float atan(float y, float x);
	};
}
#endif