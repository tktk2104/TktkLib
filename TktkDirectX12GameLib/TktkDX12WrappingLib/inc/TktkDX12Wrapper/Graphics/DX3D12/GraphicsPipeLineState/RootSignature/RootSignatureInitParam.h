#ifndef ROOT_SIGNATURE_INIT_PARAM_H_
#define ROOT_SIGNATURE_INIT_PARAM_H_

#include <vector>
#include <d3d12.h>

namespace tktk
{
	struct RootSignatureInitParam
	{
		enum class ShaderVisiBility
		{
			all = D3D12_SHADER_VISIBILITY_ALL,
			vertex = D3D12_SHADER_VISIBILITY_VERTEX,
			hull = D3D12_SHADER_VISIBILITY_HULL,
			domain = D3D12_SHADER_VISIBILITY_DOMAIN,
			geometry = D3D12_SHADER_VISIBILITY_GEOMETRY,
			pixel = D3D12_SHADER_VISIBILITY_PIXEL
		};

		struct DescriptorRange
		{
			enum class Type
			{
				shaderResourceView		= D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
				unorderedAccessViews	= D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
				constantBufferViews		= D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
				samplers				= D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER
			};

			unsigned int numDescriptors;
			Type type;
		};

		struct RootParam
		{
			ShaderVisiBility				shaderVisibility;
			std::vector<DescriptorRange>	descriptorTableArray;
		};

		struct SamplerDesc
		{
			enum class TexAddressMode
			{
				wrap		= D3D12_TEXTURE_ADDRESS_MODE_WRAP,
				mirror		= D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
				clamp		= D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
				border		= D3D12_TEXTURE_ADDRESS_MODE_BORDER,
				mirrorOnce	= D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE
			};

			enum class BorderColor
			{
				transparentBlack	= D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK,
				opaqueBlack			= D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK,
				opaqueWhite			= D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE
			};

			enum class Filter
			{
				minMagMipPoint						 = D3D12_FILTER_MIN_MAG_MIP_POINT,
				minMagPointMipLinear				 = D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR,
				minPointMagLinearMipPoint			 = D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
				minPointMagMipLinear				 = D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR,
				minLinearMagMipPoint				 = D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT,
				minLinearMagPointMipLinear			 = D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				minMagLinearMipPoint				 = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT,
				minMagMipLinear						 = D3D12_FILTER_MIN_MAG_MIP_LINEAR,
				anisotropic							 = D3D12_FILTER_ANISOTROPIC,
				comparisonMinMagMipPoint			 = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
				comparisonMinMagPointMipLinear		 = D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
				comparisonMinPointMagLinearMipPoint	 = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
				comparisonMinPointMagMipLinear		 = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
				comparisonMinLinearMagMipPoint		 = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
				comparisonMinLinearMagPointMipLinear = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				comparisonMinMagLinearMipPoint		 = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
				comparisonMinMagMipLinear			 = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
				comparisonAnisotropic				 = D3D12_FILTER_COMPARISON_ANISOTROPIC,
				minimumMinMagMipPoint				 = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT,
				minimumMinMagPointMipLinear			 = D3D12_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
				minimumMinPointMagLinearMipPoint	 = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
				minimumMinPointMagMipLinear			 = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
				minimumMinLinearMagMipPoint			 = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
				minimumMinLinearMagPointMipLinear	 = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				minimumMinMagLinearMipPoint			 = D3D12_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
				minimumMinMagMipLinear				 = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR,
				minimumAnisotropic					 = D3D12_FILTER_MINIMUM_ANISOTROPIC,
				maimumMinMagMipPoint				 = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_POINT,
				maimumMinMagPointMipLinear			 = D3D12_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
				maimumMinPointMagLinearMipPoint		 = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
				maimumMinPointMagMipLinear			 = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
				maimumMinLinearMagMipPoint			 = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
				maimumMinLinearMagPointMipLinear	 = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				maimumMinMagLinearMipPoint			 = D3D12_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
				maimumMinMagMipLinear				 = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR,
				maimumAnisotropic					 = D3D12_FILTER_MAXIMUM_ANISOTROPIC,
			};

			enum class ComparisonFunc
			{
				never			 = D3D12_COMPARISON_FUNC_NEVER,
				less			 = D3D12_COMPARISON_FUNC_LESS,
				equal			 = D3D12_COMPARISON_FUNC_EQUAL,
				lessEqual		 = D3D12_COMPARISON_FUNC_LESS_EQUAL,
				greater			 = D3D12_COMPARISON_FUNC_GREATER,
				notEqual		 = D3D12_COMPARISON_FUNC_NOT_EQUAL,
				greaterEqual	 = D3D12_COMPARISON_FUNC_GREATER_EQUAL,
				always			 = D3D12_COMPARISON_FUNC_ALWAYS
			};

			TexAddressMode addressU;
			TexAddressMode addressV;
			TexAddressMode addressW;
			BorderColor bordercolor;
			Filter filter;
			float minLod;
			float maxLod;
			ShaderVisiBility shaderVisibility;
			ComparisonFunc comparisonFunc;
		};

		enum Flag
		{
			None							= 0,
			AllowInputAssemblerInputLayout	= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT,
			DenyVertexShaderRootAccess		= D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS,
			DenyHullShaderRootAccess		= D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS,
			DenyDomainShaderRootAccess		= D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS,
			DenyGeometryShaderRootAccess	= D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS,
			DenyPixelShaderRootAccess		= D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS,
			AllowStreamOutput				= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT,
			LocalRootSignature				= D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE
		};

		unsigned int flag;
		std::vector<RootParam> rootParamArray;
		std::vector<SamplerDesc> samplerDescArray;
	};
}
#endif // !ROOT_SIGNATURE_INIT_PARAM_H_