#ifndef SYSTEM_CONSTANT_BUFFER_PARAM_LOCATION_TYPE_H_
#define SYSTEM_CONSTANT_BUFFER_PARAM_LOCATION_TYPE_H_

namespace tktk
{
	enum class SystemConstantBufferParamLocationType
	{
		texturePosition = -100,
		textureSize,
		size,
		position,
		scaleRate,
		angleDeg,
		color,
		center,
		screenSize,

		worldMatrix = -200,
		viewMatrix,
		projectionMatrix,
		boneMatrices,
		lightAmbientColor,
		lightDiffuseColor,
		lightSpecularColor,
		lightPosition,
		materialAmbientColor,
		materialDiffuseColor,
		materialSpecularColor,
		materialEmissionColor,
		materialShininess,

		albedoColor,
		metallic,
		smoothness,
	};
}
#endif // !SYSTEM_CONSTANT_BUFFER_PARAM_LOCATION_TYPE_H_
