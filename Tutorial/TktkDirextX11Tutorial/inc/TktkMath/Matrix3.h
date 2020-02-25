#ifndef MATRIX3_H_
#define MATRIX3_H_

#include <ostream>

struct Vector2;

struct Matrix3
{
public:

	Matrix3() = default;

	Matrix3(
		float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33);

	// �[���s��
	static const Matrix3 zero;
	// �P�ʍs��
	static const Matrix3 identity;

	// �ړ��s��𐶐�
	static Matrix3 createTranslation(const Vector2& translation);
	// ��]�s��𐶐�
	static Matrix3 createRotation(float degree);
	// �X�P�[���s��𐶐�
	static Matrix3 createScale(const Vector2& scale);
	// �ړ��A��]�A�X�P�[���̒l����s��𐶐�
	static Matrix3 createTRS(const Vector2& translation, float rotate, const Vector2& scale);

	// �t�s��𐶐�
	static Matrix3 calculateInvert(const Matrix3& matrix);
	//// �t�s��𐶐��i��]�ƕ��s�ړ��̂݁j
	//static Matrix3 calculateInvertFast(const Matrix3& matrix);
	// �s��̍s�Ɨ�����ւ��܂��B
	static Matrix3 calculateTranspose(const Matrix3& matrix);

	// 2�̍s��̑Ή�����l�̊Ԃ���`��Ԃ��܂�
	//static Matrix3 lerp(const Matrix3& value1, const Matrix3& value2, float amount);

	// ���s�ړ��x�N�g����ݒ�
	void setTranslation(const Vector2& translation);
	// �ړ��A��]�A�X�P�[���̒l���Đݒ�
	void setTRS(const Vector2& translation, float rotate, const Vector2& scale);

	// ���s�ړ��x�N�g�����v�Z
	Vector2 calculateTranslation() const;
	// ��]���v�Z
	float calculateRotation() const;
	// �X�P�[���l���v�Z
	Vector2 calculateScale() const;

	// ����x�N�g�����v�Z
	Vector2 calculateUp() const;
	// �E�x�N�g�����v�Z
	Vector2 calculateRight() const;

	// �t�H�[�}�b�g���ꂽ������ɕϊ�
	std::string toString() const;

public:

	float m[3][3]{};
};

Matrix3 operator - (const Matrix3& m);

Matrix3& operator += (Matrix3& m1, const Matrix3& m2);
Matrix3& operator -= (Matrix3& m1, const Matrix3& m2);
Matrix3& operator *= (Matrix3& m1, const Matrix3& m2);
Matrix3& operator *= (Matrix3& m, float s);
Matrix3& operator /= (Matrix3& m, float s);

Matrix3 operator + (Matrix3 m1, const Matrix3& m2);
Matrix3 operator - (Matrix3 m1, const Matrix3& m2);
Matrix3 operator * (Matrix3 m1, const Matrix3& m2);
Matrix3 operator * (Matrix3 m, float s);
Matrix3 operator * (float s, Matrix3 m);
Matrix3 operator / (Matrix3 m, float s);

std::ostream& operator<<(std::ostream& os, const Matrix3& matrix);
#endif