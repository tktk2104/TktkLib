#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <string>
#include <ostream>

namespace tktkMath
{
	struct Matrix4;

	struct Vector3
	{
	public:

		// �R���X�g���N�^
		constexpr Vector3() = default;
		constexpr Vector3(float value) : x(value), y(value), z(value) {}
		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	public:

		// �C���f�b�N�X�Ŋe�v�f�ɃA�N�Z�X���邽�߂̃I�[�o�[���[�h
		float operator[](int index) const;
		float& operator[](int index);

	public:

		// �w��x�N�g������P�ʃx�N�g�����쐬���܂�
		static Vector3 normalize(const Vector3& value);
		// �x�N�g�������K�����ꑼ�̃x�N�g���ƒ�������悤�ɂ��܂�
		static void orthoNormalize(Vector3* normal, Vector3* tangent, Vector3* binormal);
		// �x�N�g����ʂ̃x�N�g���ɓ��e���܂��B
		static Vector3 project(const Vector3& value, const Vector3& onNormal);
		// ���ʂɐ����Ȗ@���x�N�g���ɂ���Ē�`����镽�ʏ�Ƀx�N�g�����ˉe���܂��B
		static Vector3 projectOnPlane(const Vector3& value, const Vector3& planeNormal);
		// 2�̃x�N�g���̓��ς��v�Z���܂�
		static float dot(const Vector3& vector1, const Vector3& vector2);
		// 2�̃x�N�g���̊O�ς��v�Z���܂�
		static Vector3 cross(const Vector3& vector1, const Vector3& vector2);
		// 2�̃x�N�g���Ԃ̋������v�Z���܂�
		static float distance(const Vector3& vector1, const Vector3& vector2);
		// 2 �̒����x�N�g���Ԃ̋������v�Z���܂��B 
		static float distanceSquared(const Vector3& vector1, const Vector3& vector2);
		// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
		static Vector3 lerp(const Vector3& value1, const Vector3& value2, float amount);
		// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
		static Vector3 lerpUnclamped(const Vector3& value1, const Vector3& value2, float amount);
		// current����target�֌����Ĉړ����܂�
		static Vector3 moveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);
		// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރx�N�g����Ԃ��܂�
		static Vector3 calculateMin(const Vector3& vector1, const Vector3& vector2);
		// ��v����e�����y�A�̍ł������l���܂ރx�N�g����Ԃ��܂�
		static Vector3 calculateMax(const Vector3& vector1, const Vector3& vector2);
		//	�l���w�肳�ꂽ�͈͓��ɐ������܂�
		static Vector3 clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
		// �傫����maxLength�܂Ő��������l���擾���܂�
		static Vector3 clampLength(const Vector3& value, float maxLength);
		// �@������ɂ��ăx�N�g���ɔ��˂����x�N�g�����擾���܂�
		static Vector3 reflect(const Vector3& inDirection, const Vector3& inNormal);
		// 2�̃x�N�g���̊e��������Z����
		static Vector3 scale(const Vector3& vector1, const Vector3& vector2);
		// Returns the signed angle in degrees between from and to
		static float signedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);
		// ���݂̈ʒu current ���� target �Ɍ����ăx�N�g������]���܂��B
		static Vector3 rotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);
		// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		static Vector3 slerp(const Vector3& value1, const Vector3& value2, float amount);
		// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		static Vector3 slerpUnclamped(const Vector3& value1, const Vector3& value2, float amount);
		// �ړI�n�Ɍ������Ď��Ԃ̌o�߂ƂƂ��ɏ��X�Ƀx�N�g����ω������܂�
		static Vector3 smoothDamp(const Vector3& cur, const Vector3& target, Vector3* curVelocity, float smoothTime, float deltaTime, float maxSpeed = INFINITY);
		// �w�肳�ꂽ Matrix �ɂ���āAVector3���g�����X�t�H�[�����܂�
		static Vector3 transform(const Vector3& position, const Matrix4& matrix);
		// �w�肳�ꂽ Matrix �ɂ���āA�@���x�N�g�����g�����X�t�H�[�����܂�
		static Vector3 transformNormal(const Vector3& position, const Matrix4& matrix);
		// ���[�E�s�b�`����x�N�g�����쐬
		static Vector3 createFromYawPitch(float yaw, float pitch);
		//  2 �̃x�N�g���Ԃ̉s�p��Ԃ��܂�
		static float angle(const Vector3& from, const Vector3& to);

	public:

		// �x�N�g���̒������v�Z���܂�
		float length() const;
		// �x�N�g���̒����̕������v�Z���܂�
		float lengthSquared() const;
		// �P�ʃx�N�g�����쐬���܂�
		Vector3 normalized() const;
		// ���g�ƈ����̒l����̓�����������^��Ԃ�
		bool equals(const Vector3& other);
		// �l���Đݒ肷��
		void setValue(float x, float y, float z);
		// �s�b�`���擾
		float pitch() const;
		// ���[���擾
		float yaw() const;

		// �x�N�g���̒l�𕶎���ɋN�����������擾
		std::string toString() const;

	public:

		// �e�v�f
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };
	};

	// Vector3�\���̂̒萔�B
	struct Vector3_v
	{
		static constexpr Vector3 zero				{  0.0f };
		static constexpr Vector3 one				{  1.0f };
		static constexpr Vector3 up					{  0.0f,  1.0f,  0.0f };
		static constexpr Vector3 down				{  0.0f, -1.0f,  0.0f };
		static constexpr Vector3 left				{ -1.0f,  0.0f,  0.0f };
		static constexpr Vector3 right				{  1.0f,  0.0f,  0.0f };
		static constexpr Vector3 forwardLH			{  0.0f,  0.0f,  1.0f };	//�iDirectX���j
		static constexpr Vector3 backwardLH			{  0.0f,  0.0f, -1.0f };	//�iDirectX���j
		static constexpr Vector3 forwardRH			{  0.0f,  0.0f, -1.0f };	//�iOpenGL���j
		static constexpr Vector3 backwardRH			{  0.0f,  0.0f,  1.0f };	//�iOpenGL���j
		static constexpr Vector3 negativeInfinity	{ -std::numeric_limits<float>::infinity() };
		static constexpr Vector3 positiveInfinity	{  std::numeric_limits<float>::infinity() };
	};

	// �萔�B�i�񐄏��F�uVector3_v::�v���g���Ă��������j
	constexpr Vector3 vec3Zero = { 0.0f };
	constexpr Vector3 vec3One = { 1.0f };
	constexpr Vector3 vec3Up = { 0.0f,  1.0f,  0.0f };
	constexpr Vector3 vec3Down = { 0.0f, -1.0f,  0.0f };
	constexpr Vector3 vec3Left = { -1.0f,  0.0f,  0.0f };
	constexpr Vector3 vec3Right = { 1.0f,  0.0f,  0.0f };
	constexpr Vector3 vec3ForwardLH = { 0.0f,  0.0f,  1.0f };	//�iDirectX���j
	constexpr Vector3 vec3BackwardLH = { 0.0f,  0.0f, -1.0f };	//�iDirectX���j
	constexpr Vector3 vec3ForwardRH = { 0.0f,  0.0f, -1.0f };	//�iOpenGL���j
	constexpr Vector3 vec3BackwardRH = { 0.0f,  0.0f,  1.0f };	//�iOpenGL���j
	constexpr Vector3 vec3NegativeInfinity = { -std::numeric_limits<float>::infinity() };
	constexpr Vector3 vec3PositiveInfinity = { std::numeric_limits<float>::infinity() };

	// ���Z�q�I�[�o�[���[�h�B
	Vector3			operator -  (const Vector3& v);
	Vector3&		operator += (Vector3& v1, const Vector3& v2);
	Vector3&		operator -= (Vector3& v1, const Vector3& v2);
	Vector3&		operator *= (Vector3& v, float s);
	Vector3&		operator /= (Vector3& v, float s);
	Vector3			operator +  (Vector3 v1, const Vector3& v2);
	Vector3			operator -  (Vector3 v1, const Vector3& v2);
	Vector3			operator *  (Vector3 v, float s);
	Vector3			operator *  (float s, Vector3 v);
	Vector3			operator /  (Vector3 v, float s);
	bool			operator == (const Vector3& lhs, const Vector3& rhs);
	bool			operator != (const Vector3& lhs, const Vector3& rhs);
	std::ostream&	operator << (std::ostream& os, const Vector3& vector3);
}
#endif