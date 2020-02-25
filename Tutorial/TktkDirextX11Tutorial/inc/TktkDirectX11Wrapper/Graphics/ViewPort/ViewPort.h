#ifndef VIEW_PORT_H_
#define VIEW_PORT_H_

#include "Asset/ViewPortData.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	class ViewPort
	{
	public:

		// �V���ȃr���[�|�[�g�𐶐�����
		// �����̊֐��Ńr���[�|�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, const Vector2& position, const Vector2& size);

		// �w�肵���r���[�|�[�g���폜����
		// �����̊֐��Ńr���[�|�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���r���[�|�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const ViewPortData& getData(int id);
	};
}
#endif // !VIEW_PORT_H_