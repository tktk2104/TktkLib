#ifndef MATERIAL_DATA_H_
#define MATERIAL_DATA_H_

#include <unordered_map>
#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h>
#include "../../ConstantBuffer/Asset/ConstantBufferData.h"

namespace tktk
{
	// マテリアル情報を管理するクラス
	class MaterialData
	{
	public:

		MaterialData(
			int indexBufferStartPos,
			int indexBufferUseCount,
			int useVertexShaderId,
			int usePixelShaderId,
			const std::unordered_map<unsigned int, int>& useTextureIdMap,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shininess
		);
		~MaterialData();

		MaterialData(const MaterialData& other) = delete;
		MaterialData& operator = (const MaterialData& other) = delete;

	public:

		// 使用するインデックスバッファの開始位置を取得する
		int getIndexBufferStartPos() const;

		// 使用するインデックスバッファの幅を取得する
		int getIndexBufferUseCount() const;

		// 使用する頂点シェーダーのIdを取得する
		int getUseVertexShaderId() const;
		// 使用する頂点シェーダーのIdを設定する
		void setUseVertexShaderId(int id);

		// 使用するピクセルシェーダーのIdを取得する
		int getUsePixelShaderId() const;
		// 使用するピクセルシェーダーのIdを設定する
		void setUsePixelShaderId(int id);

		// シェーダーで使用するテクスチャIdの連想配列を取得する
		const std::unordered_map<unsigned int, int>& getUseTextureIdMap() const;
		// シェーダーで使用するテクスチャIdを追加する
		void addUseTextureId(unsigned int stage, int id);
		// シェーダーで使用するテクスチャIdを全て削除する
		void clearUseTextureId();

		// マテリアルの環境光のポインタを取得する
		Color* getAmbientColorPtr();

		// マテリアルの拡散反射光のポインタを取得する
		Color* getDiffuseColorPtr();

		// マテリアルの鏡面反射光のポインタを取得する
		Color* getSpecularColorPtr();

		// マテリアルの自己発光のポインタを取得する
		Color* getEmissionColorPtr();

		// マテリアルの光沢のポインタを取得する
		float* getShininessPtr();

		// 頂点シェーダーが使用する定数バッファに設定する数値の連想配列を取得する
		const std::unordered_map<int, SafetyVoidPtr>& getSetVSConstantBufferParamMap() const;
		// 頂点シェーダーが使用する定数バッファの数値を設定する予約をする
		// ※「T」の型はコピーコンストラクタが無いとビルドエラーになります
		template<class T>
		void settingReservationVSConstantBufferParam(int locationType, const T& param);

		// ピクセルシェーダーが使用する定数バッファに設定する数値の連想配列を取得する
		const std::unordered_map<int, SafetyVoidPtr>& getSetPSConstantBufferParamMap() const;
		// ピクセルシェーダーが使用する定数バッファの数値を設定する予約をする
		// ※「T」の型はコピーコンストラクタが無いとビルドエラーになります
		template<class T>
		void settingReservationPSConstantBufferParam(int locationType, const T& param);

	private:

		// 使用するインデックスバッファの開始位置
		int m_indexBufferStartPos;
		// 使用するインデックスバッファの幅
		int m_indexBufferUseCount;

		// 使用する頂点シェーダーのId
		int m_useVertexShaderId;
		// 使用するピクセルシェーダーのId
		int m_usePixelShaderId;

		// シェーダーで使用するテクスチャIdの連想配列
		std::unordered_map<unsigned int, int> m_useTextureIdMap;

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

		// 頂点シェーダーが使用する定数バッファに設定する数値の連想配列
		std::unordered_map<int, SafetyVoidPtr> m_setVSConstantBufferParamMap;
		// ピクセルシェーダーが使用する定数バッファに設定する数値の連想配列
		std::unordered_map<int, SafetyVoidPtr> m_setPSConstantBufferParamMap;
	};

	// 頂点シェーダーが使用する定数バッファの数値を設定する予約をする
	// ※「T」の型はコピーコンストラクタが無いとビルドエラーになります
	template<class T>
	inline void MaterialData::settingReservationVSConstantBufferParam(int locationType, const T & param)
	{
		if (m_setVSConstantBufferParamMap.count(locationType) != 0)
		{
			if (m_setVSConstantBufferParamMap.at(locationType).canCast<T>())
			{
				*(m_setVSConstantBufferParamMap.at(locationType).castPtr<T>()) = param;
				return;
			}
			m_setVSConstantBufferParamMap.erase(locationType);
		}
		m_setVSConstantBufferParamMap.emplace(locationType, new T(param));
	}

	// ピクセルシェーダーが使用する定数バッファの数値を設定する予約をする
	// ※「T」の型はコピーコンストラクタが無いとビルドエラーになります
	template<class T>
	inline void MaterialData::settingReservationPSConstantBufferParam(int locationType, const T & param)
	{
		if (m_setPSConstantBufferParamMap.count(locationType) != 0)
		{
			if (m_setPSConstantBufferParamMap.at(locationType).canCast<T>())
			{
				*(m_setPSConstantBufferParamMap.at(locationType).castPtr<T>()) = param;
				return;
			}
			m_setPSConstantBufferParamMap.erase(locationType);
		}
		m_setPSConstantBufferParamMap.emplace(locationType, new T(param));
	}
}
#endif // !MATERIAL_DATA_H_