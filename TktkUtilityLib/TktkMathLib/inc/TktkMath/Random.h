#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

// ���������N���X
class Random
{
public:

	// �����̏�����
	static void randomize();

	// �����̃V�[�h�l�����O�Ŏw�肵�ė�����������
	static void randomize(unsigned int seed);

	static int getRandI(int min, int max);

	static float getRandF(float min, float max);

	static unsigned int getSeed();

private:

	static std::mt19937 m_mt;

	static unsigned int m_seed;
};

#endif // !RANDOM_H_