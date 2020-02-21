#ifndef MOVIE_PLAYER_MAKER_H_
#define MOVIE_PLAYER_MAKER_H_

#include "MoviePlayer.h"

namespace tktk
{
	class MoviePlayerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static MoviePlayerMaker& makeStart();

	public:

		// �쐬����
		MoviePlayer* create();

		// �`��D��x��ݒ肷��
		MoviePlayerMaker& drawPriority(float value);

		// �\�����铮���Id��ݒ肷��
		MoviePlayerMaker& movieId(int value);

		// ����̒��S�ʒu��ݒ肷��i���� 0.0�`1.0�j
		MoviePlayerMaker& movieCenterPosRate(const Vector2& value = Vector2(0.5f, 0.5f));

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		MoviePlayerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		MoviePlayerMaker& blendParam(float value = 1.0f);

		// �\�����铮��̔��]�t���O��ݒ肷��
		MoviePlayerMaker& reverseFlag(ReverseFlag value);

		// �\�����铮��̐ؔ����`��͈͂�ݒ肷��
		MoviePlayerMaker& useClipping(
			const Vector2& clippingLeftTopPos,		// �؂蔲��������W
			const Vector2& clippingRightBottomPos	// �؂蔲���E�����W
		);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		MoviePlayerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^
		static MoviePlayerMaker m_self;

	private:

		float m_drawPriority{ 0 };
		int m_movieId{ -1 };
		Vector2 m_movieCenterPosRate{ Vector2(0.5f, 0.5f) };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		ReverseFlag m_reverseFlag{ ReverseFlag::NOT_REVERSE };
		bool m_useClipping{ false };
		Vector2 m_clippingLeftTopPos{ Vector2::zero };
		Vector2 m_clippingRightBottomPos{ Vector2::one };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !MOVIE_PLAYER_MAKER_H_