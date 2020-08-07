#pragma once

#include <vector>
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2D.h>
#include "../VertexColor2DPolygonVertexData.h"

class VertexColor2DPolygonDrawer
	: public tktk::ComponentBase
{
public:

	VertexColor2DPolygonDrawer(
		float drawPriority,
		int blendStateId,
		int depthStencilStateId,
		int rasterizerStateId,
		const std::vector<VertexColor2DPolygonVertexData>& vertexArray,
		const tktkMath::Color& blendRate
	);

public:

	void start();
	void draw() const;

public:

	// �u�����h�X�e�[�gID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
	void setBlendStateId(IdType id)
	{
		setBlendStateIdImpl(static_cast<int>(id));
	}
	template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
	void setBlendStateId(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

	// �[�x�X�e���V���X�e�[�gID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
	void setDepthStencilStateId(IdType id)
	{
		setDepthStencilStateIdImpl(static_cast<int>(id));
	}
	template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
	void setDepthStencilStateId(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

	// ���X�^���C�U�X�e�[�gID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
	void setRasterizerStateId(IdType id)
	{
		setRasterizerStateIdImpl(static_cast<int>(id));
	}
	template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
	void setRasterizerStateId(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

	// ���_�����Đݒ肷��i���v���ɒ��_���w�肵�Ă��������j
	void setVertexArray(const std::vector<VertexColor2DPolygonVertexData>& vertexArray);

	// �u�����h���[�g���Đݒ肷��
	void setBlendRate(const tktkMath::Color& blendRate);

private:

	// �e��id�w��n�̊֐��̎���
	void setBlendStateIdImpl(int id);
	void setDepthStencilStateIdImpl(int id);
	void setRasterizerStateIdImpl(int id);

private:

	int m_blendStateId{ -1 };
	int m_depthStencilStateId{ -1 };
	int m_rasterizerStateId{ -1 };
	std::vector<VertexColor2DPolygonVertexData> m_vertexArray{};
	tktkMath::Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform{  };
};