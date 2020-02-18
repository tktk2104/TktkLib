#ifndef VIEW_PORT_MANAGER_H_
#define VIEW_PORT_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ViewPortAssets.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	// �uViewPortAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class ViewPortManager
	{
	public:

		// �uViewPortAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃr���[�|�[�g�𐶐�����
		static void create(int id, const Vector2& position, const Vector2& size);

		// �w�肵���r���[�|�[�g���폜����
		static void erase(int id);

		// �S�Ẵr���[�|�[�g���폜����
		static void clear();

		// �w�肵���r���[�|�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const ViewPortData& getData(int id);

	private:

		static CfpPtr<ViewPortAssets> m_assetsPtr;
	};
}
#endif // !VIEW_PORT_MANAGER_H_