#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <string>
#include <ostream>

struct Matrix3;

struct Vector2
{
	Vector2() = default;
	Vector2(float x, float y);
	explicit Vector2(float value);

	float operator[](int index) const;
	float& operator[](int index);

	// Vector2( 0,  0)
	static const Vector2 zero;
	// Vector2( 1,  1)
	static const Vector2 one;
	// Vector2( 0,  1)
	static const Vector2 up;
	// Vector2( 0, -1)
	static const Vector2 down;
	// Vector2(-1,  0)
	static const Vector2 left;
	// Vector2( 1,  0)
	static const Vector2 right;
	// Vector2(-INFINITY, -INFINITY)
	static const Vector2 negativeInfinity;
	// Vector2( INFINITY,  INFINITY)
	static const Vector2 positiveInfinity;

	// �w��x�N�g������P�ʃx�N�g�����쐬���܂�
	static Vector2 normalize(const Vector2& value);
	// 2�̃x�N�g���̂Ȃ��p��Ԃ�
	static float angle(const Vector2& vector1, const Vector2& vector2);
	// �Q�̃x�N�g���̊Ԃ̊p�x���擾
	static float signedAngle(const Vector2& vector1, const Vector2& vector2);
	// 2�̃x�N�g���̓��ς��v�Z���܂�
	static float dot(const Vector2& vector1, const Vector2& vector2);
	// 2�̃x�N�g���̊O�ς��v�Z���܂�
	static float cross(const Vector2& vector1, const Vector2& vector2);
	// 2�̃x�N�g���Ԃ̋������v�Z���܂�
	static float distance(const Vector2& vector1, const Vector2& vector2);
	// 2 �̒����x�N�g���Ԃ̋������v�Z���܂��B
	static float distanceSquared(const Vector2 & vector1, const Vector2 & vector2);
	// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
	static Vector2 lerp(const Vector2& value1, const Vector2& value2, float amount);
	// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
	static Vector2 lerpUnclamped(const Vector2& value1, const Vector2& value2, float amount);
	// current����target�֌����Ĉړ����܂�
	static Vector2 moveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
	// current����target�֌����Ď��Ԃ̌o�߂ŏ��X�Ƀx�N�g����ω������܂�
	static Vector2 smoothDamp(const Vector2& current, const Vector2& target, Vector2* currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
	// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރx�N�g����Ԃ��܂�
	static Vector2 calculateMin(const Vector2& vector1, const Vector2& vector2);
	// ��v����e�����y�A�̍ł������l���܂ރx�N�g����Ԃ��܂�
	static Vector2 calculateMax(const Vector2& vector1, const Vector2& vector2);
	//	�l���w�肳�ꂽ�͈͓��ɐ������܂�
	static Vector2 clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
	// �傫����maxLength�܂Ő��������l���擾���܂�
	static Vector2 clampLength(const Vector2& vector1, float maxLength);
	// �����̃x�N�g���̐��������̃x�N�g�����擾
	static Vector2 perpendicular(const Vector2& inDirection);
	// �@������ɂ��ăx�N�g���ɔ��˂����x�N�g�����擾���܂�
	static Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);
	// 2�̃x�N�g���̊e��������Z����
	static Vector2 scale(const Vector2& vector1, const Vector2& vector2);
	// �����̍s����g���Ĉړ�������
	static Vector2 transform(const Vector2& position, const Matrix3& matrix);

	// �x�N�g���̒���
	float length() const;
	// �x�N�g���̒����̕���
	float lengthSquared() const;
	// �P�ʃx�N�g�����擾����
	Vector2 normalized() const;
	// ���g�ƈ����̒l����̓�����������^��Ԃ�
	bool equals(const Vector2 & other);
	// �l���Đݒ肷��
	void setValue(float x, float y);

	// �x�N�g���̒l�𕶎���ɋN�����������擾
	std::string toString() const;

public:

	float x { 0.0f };
	float y { 0.0f };
};

Vector2 operator - (const Vector2& v);

Vector2& operator += (Vector2& v1, const Vector2& v2);
Vector2& operator -= (Vector2& v1, const Vector2& v2);
Vector2& operator *= (Vector2& v, float s);
Vector2& operator *= (Vector2& v, const Matrix3& m);
Vector2& operator /= (Vector2& v, float s);

Vector2 operator + (Vector2 v1, const Vector2& v2);
Vector2 operator - (Vector2 v1, const Vector2& v2);
Vector2 operator * (Vector2 v, float s);
Vector2 operator * (float s, Vector2 v);
Vector2	operator * (const Vector2& v, const Matrix3& m);
Vector2 operator / (Vector2 v, float s);

bool operator == (const Vector2& lhs, const Vector2& rhs);
bool operator != (const Vector2& lhs, const Vector2& rhs);

std::ostream& operator<<(std::ostream& os, const Vector2& vector2);
#endif
