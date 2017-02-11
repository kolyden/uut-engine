#pragma once
#include "VertexElement.h"
#include "RenderState.h"
#include "Topology.h"

namespace uut
{
	namespace DX12
	{
		class ShaderByteCode
		{
		public:
			void* _date;
			size_t _size;
		};
	
		struct StreamOutputDesc
		{
			List<VertexElement> _entries;
			uint _numEntries;
		};
	
		enum class BlendLogicOp
		{
			Clear,
			Set,
			Copy,
			CopyInv,
			NoOp,
			Invert,
			And,
			Nand,
			Or,
			Nor,
			Xor,
			Equiv,
			AndRev,
			AndInv,
			OrRev,
			OrInv,
		};
	
		struct RenderTargetBlendDesc
		{
			bool blendEnable = false;
			bool logicOpEnable = false;
			BlendingState color;
			BlendingState alpha;
			BlendLogicOp logicOp;
			uint8_t writeMask;
		};
	
		// from https://msdn.microsoft.com/en-us/library/windows/desktop/dn770339(v=vs.85).aspx
		struct BlendDesc
		{
			bool _alphaToCoverageEnable = false;
			bool _independentBlendEnable = false;
			RenderTargetBlendDesc renderTarget[8];
		};
	
		// from https://msdn.microsoft.com/en-us/library/windows/desktop/dn770387(v=vs.85).aspx
		struct RasterizerDesc
		{
			FillMode fillMode = FillMode::Solid;
			CullMode cullMode = CullMode::Clockwise;
			bool frontCounterCW = false;
			int depthBias = 0;
			float depthBiasClamp = 0;
			float slopeScaledDepthBias = 0;
			bool depthClipEnable = true;
			bool multisampleEnable = false;
			bool antialiasedLineEnable = false;
			uint forceSampleCount = 0;
			bool conservativeRaster = false;
		};
	
		enum class StencilOp
		{
			Keep,
			Zero,
			Replace,
			IncrSat,
			DecrSat,
			Invert,
			Incr,
			Decr,
		};
	
		// from https://msdn.microsoft.com/en-us/library/windows/desktop/dn770355(v=vs.85).aspx
		struct DepthStencilOpDesc
		{
			StencilOp FailOp = StencilOp::Keep;
			StencilOp DepthFailOp = StencilOp::Keep;
			StencilOp PassOp = StencilOp::Keep;
			CompareFunc stencilFunc = CompareFunc::Always;
		};
	
		// from https://msdn.microsoft.com/en-us/library/windows/desktop/dn770356(v=vs.85).aspx
		struct DepthStencilDesc
		{
			bool depthEnable = true;
			bool depthWriteMask = true;
			CompareFunc depthFunc = CompareFunc::Less;
			bool stencilEnable = false;
			uint8_t stencilReadMask = 0;
			uint8_t stencilWriteMask = 0;
			DepthStencilOpDesc frontFace;
			DepthStencilOpDesc backFace;
		};
	
		// from https://msdn.microsoft.com/en-us/library/windows/desktop/bb173059(v=vs.85).aspx
		enum class InputFormat
		{};
	
		struct InputElement
		{
			String semanticName;
			uint semanticIndex;
			InputFormat format;
			uint inputSlot;
			uint alignedByteOffset;
			bool inputSlotClass;
			uint instanceDateStepRate;
		};
	
		struct GISampleDesc
		{
			uint count;
			uint quality;
		};
	
		class PipelineStateDesc
		{
		public:
			ShaderByteCode _vs;
			ShaderByteCode _ps;
			ShaderByteCode _ds;
			ShaderByteCode _hs;
			ShaderByteCode _gs;
			BlendDesc blendState;
			uint sampleMask;
			RasterizerDesc rasterizerState;
			DepthStencilDesc depthStencilState;
			List<InputElement> inputLayout;
			Topology topologyType;
			uint numRenderTargets;
			InputFormat RTVFormats[8];
			InputFormat DSVFormat;
			GISampleDesc sampleDesc;
			uint nodeMask;
			bool degugFlag;
		};
	}
}