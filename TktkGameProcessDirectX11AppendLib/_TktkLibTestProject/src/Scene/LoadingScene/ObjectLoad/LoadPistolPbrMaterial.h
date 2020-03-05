#pragma once

#include "CommonIncludePaths.h"

#include <TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/Material/Material.h>
#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/SystemConstantBufferId.h>
#include <TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/PbrConstantBufferData.h>

static void LoadPistolPbrMaterial()
{
	tktk::Material::duplicate(MATERIAL_PBR_PISTOL, MATERIAL_PISTOL);

	tktk::MaterialData* pistolPbrMaterial = tktk::Material::getDataPtr(MATERIAL_PBR_PISTOL);

	pistolPbrMaterial->getParametersRef().setUseTextureId(-(MATERIAL_PISTOL * 100 + 2));

	pistolPbrMaterial->setUseVertexShaderId(tktk::SystemVertexShaderId::PbrMesh);
	pistolPbrMaterial->setUsePixelShaderId(tktk::SystemPixelShaderId::PbrMesh);

	tktk::PbrConstantBufferData pbrBuffer;
	pbrBuffer.albedoColor = Color::white;
	pbrBuffer.metallic = 1.0f;
	pbrBuffer.smoothness = 1.0f;

	pistolPbrMaterial->getParametersRef().setConstantBufferSetData(tktk::SystemConstantBufferId::Pbr, std::move(pbrBuffer));
}