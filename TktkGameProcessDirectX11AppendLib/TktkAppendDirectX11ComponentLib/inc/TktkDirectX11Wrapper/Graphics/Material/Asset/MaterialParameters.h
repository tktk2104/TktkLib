#ifndef MATERIAL_PARAMETERS_H_
#define MATERIAL_PARAMETERS_H_

#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	class MaterialParameters
	{
	public:

		MaterialParameters(
			const std::vector<int>& useTextureIdArray,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shininess
		);

		// コピー禁止
		MaterialParameters(const MaterialParameters& other) = delete;
		MaterialParameters& operator = (const MaterialParameters& other) = delete;

	public:

		// 定数バッファに設定する値を保持する連想配列を取得する
		const std::unordered_map<int, SafetyVoidPtr>& getConstantBufferSetData() const;

		// 定数バッファに設定する値を設定する
		template<class BufferType, class BufferId, std::enable_if_t<is_idType_v<BufferId>>* = nullptr>
		void setConstantBufferSetData(BufferId id, BufferType&& bufferData)
		{
			if (m_constantBufferSetData.count(static_cast<int>(id)) == 0)
			{
				m_constantBufferSetData.emplace(static_cast<int>(id), new BufferType(std::move(bufferData)));
				return;
			}

			if (m_constantBufferSetData.at(static_cast<int>(id)).canCast<BufferType>())
			{
				*(m_constantBufferSetData.at(static_cast<int>(id)).castPtr<BufferType>()) = std::move(bufferData);
			}
			throw std::runtime_error("BufferType Fraud Type");
		}
		template<class BufferType, class BufferId, std::enable_if_t<!is_idType_v<BufferId>>* = nullptr>
		void setConstantBufferSetData(BufferId id) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// シェーダーで使用するテクスチャIdの配列を取得する
		const std::vector<int>& getUseTextureIdArray() const;

		// シェーダーで使用するテクスチャIdを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class... IdTypes, std::enable_if_t<is_idType_all_v<IdTypes...>>* = nullptr>
		void setUseTextureId(IdTypes... textureIds)
		{
			setUseTextureIdImpl({ static_cast<int>(textureIds)... });
		}
		template<class... IdTypes, std::enable_if_t<!is_idType_all_v<IdTypes...>>* = nullptr>
		void setUseTextureId(IdTypes... textureIds) { static_assert(false, "TextureId Fraud Type"); }

		// シェーダーで使用するテクスチャIdを追加する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void addUseTextureId(IdType textureId)
		{
			addUseTextureIdImpl(static_cast<int>(textureId));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void addUseTextureId(IdType textureId) { static_assert(false, "TextureId Fraud Type"); }

		// マテリアルの環境光色を取得する
		const Color& getAmbientColor() const;

		// マテリアルの環境光色を設定する
		void setAmbientColor(Color&& value);

		// マテリアルの拡散反射光色を取得する
		const Color& getDiffuseColor() const;

		// マテリアルの拡散反射光色を設定する
		void setDiffuseColor(Color&& value);

		// マテリアルの鏡面反射光色を取得する
		const Color& getSpecularColor() const;

		// マテリアルの鏡面反射光色を設定する
		void setSpecularColor(Color&& value);

		// マテリアルの自己発光色を取得する
		const Color& getEmissionColor() const;

		// マテリアルの自己発光色を設定する
		void setEmissionColor(Color&& value);

		// マテリアルの光沢を取得する
		float getShininess() const;

		// マテリアルの光沢を設定する
		void setShininess(float value);

	private:

		// 各種id指定系の関数の実装
		void setUseTextureIdImpl(std::vector<int>&& textureIdArray);
		void addUseTextureIdImpl(int textureId);

	private:

		// 定数バッファに設定する値を保持する連想配列
		std::unordered_map<int, SafetyVoidPtr> m_constantBufferSetData;
		// シェーダーで使用するテクスチャIdの配列
		std::vector<int> m_useTextureIdArray;
		// マテリアルの環境光
		Color m_ambientColor;
		// マテリアルの拡散反射光
		Color m_diffuseColor;
		// マテリアルの鏡面反射光
		Color m_specularColor;
		// マテリアルの自己発光
		Color m_emissionColor;
		// マテリアルの光沢
		float m_shininess;
	};
}
#endif // !MATERIAL_PARAMETERS_H_