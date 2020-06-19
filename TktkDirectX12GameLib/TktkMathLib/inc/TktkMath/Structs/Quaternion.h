#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <ostream>
#include "TktkMath/Structs/Vector3.h"

namespace tktkMath
{
	struct Matrix4;

	// �R������]��\���N�I�[�^�j�I���̍\����
	struct Quaternion
	{
	public:

		// �R���X�g���N�^
		constexpr Quaternion() = default;
		constexpr Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	public:

		// �C���f�b�N�X�Ŋe�v�f�ɃA�N�Z�X���邽�߂̃I�[�o�[���[�h
		float operator[](int index) const;
		float& operator[](int index);

	public:

		// �I�C���[�p����N�I�[�^�j�I���𐶐�����
		static Quaternion createFromEulerAngle(const Vector3& euler);
		// axis�̎���� degree �x������]����N�I�[�^�j�I���𐶐�����
		static Quaternion createFromAxisAngle(const Vector3& axis, float degree);
		// ��]�s�񂩂�N�I�[�^�j�I�����쐬
		static Quaternion createFromRotationMatrix(const Matrix4& matrix);
		// from����to�ւ̉�]�����߂�
		static Quaternion createFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
		// �w�肵����������������]�����߂�
		static Quaternion createLookRotation(const Vector3& view, const Vector3& up = vec3Up);
		// from����to�ւ̉�]�����߂�
		static Quaternion createRotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);
		// �t�N�I�[�^�j�I�����v�Z����
		static Quaternion calculateInvert(const Quaternion& rotation);
		// �Q�̉�] a �� b �Ԃ̊p�x���v�Z����
		static float calculateAngle(const Quaternion& q1, const Quaternion& q2);
		// ���ς��v�Z����
		static float calculateDot(const Quaternion& q1, const Quaternion& q2);
		// ���K������
		static Quaternion normalize(const Quaternion& q);
		// a��b�̊Ԃ�t�Ő��`��Ԃ���it��0��1�̊ԂŃN�����v����j
		static Quaternion lerp(const Quaternion& value1, const Quaternion& value2, float t);
		// a��b�̊Ԃ�t�Ő��`��Ԃ���
		static Quaternion lerpUnclamped(const Quaternion& value1, const Quaternion& value2, float t);
		// ���ʐ��`���
		static Quaternion slerp(const Quaternion& value1, const Quaternion& value2, float amount);
		// ���ʐ��`���
		static Quaternion slerpUnclamped(const Quaternion& value1, const Quaternion& value2, float amount);

	public:

		// �N�I�[�^�j�I���̃m�������v�Z����
		float calculateLength() const;
		// �I�C���[�p���v�Z����
		Vector3 calculateEulerAngle() const;
		// �e�v�f���Đݒ肷��
		void setValue(float x, float y, float z, float w);
		// from����to�ւ̉�]�����g�ɐݒ肷��
		void setFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
		// �w�肵����������������]�����g�ɐݒ肷��
		void setLookRotation(const Vector3& view, const Vector3& up = vec3Up);
		// �Q�̉�]����̓�����������^��Ԃ�
		bool equals(const Quaternion& other) const;
		// �t�H�[�}�b�g���ꂽ������ɕϊ�
		std::string toString() const;

	public:

		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };
		float w{ 0.0f };
	};

	// �萔�B
	constexpr Quaternion quaternionIdentity = { 0.0f, 0.0f, 0.0f, 1.0f };

	// ���Z�q�I�[�o�[���[�h�B
	Quaternion		operator -  (const Quaternion& q);
	Quaternion&		operator += (Quaternion& q1, const Quaternion& q2);
	Quaternion&		operator -= (Quaternion& q1, const Quaternion& q2);
	Quaternion&		operator *= (Quaternion& q, float s);
	Quaternion&		operator /= (Quaternion& q, float s);
	Quaternion&		operator *= (Quaternion& q1, const Quaternion& q2);
	Quaternion		operator +  (Quaternion q1, const Quaternion& q2);
	Quaternion		operator -  (Quaternion q1, const Quaternion& q2);
	Quaternion		operator *  (Quaternion q1, const Quaternion& q2);
	Quaternion		operator *  (Quaternion q, float s);
	Quaternion		operator *  (float s, Quaternion q);
	Quaternion		operator /  (Quaternion q, float s);
	Vector3			operator *  (const Quaternion& rotation, const Vector3& point);
	std::ostream&	operator << (std::ostream& os, const Quaternion& quaternion);
}
#endif // !QUATERNION_H_