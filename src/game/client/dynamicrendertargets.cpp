/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "cbase.h"
#include "dynamicrendertargets.h"	
#include "materialsystem/imaterialsystemhardwareconfig.h"
#include "materialsystem/itexture.h"
#include "tier0/icommandline.h"

void DynamicRenderTargets::InitClientRenderTargets(IMaterialSystem* MaterialSystem, IMaterialSystemHardwareConfig* MaterialSystemHardwareConfig)
{
	BaseClass::InitClientRenderTargets(MaterialSystem, MaterialSystemHardwareConfig);

	CurrentMaterialSystem = MaterialSystem;
	OldViewport = GetViewport();

	InitDynamicRenderTargets();
}

void DynamicRenderTargets::InitDynamicRenderTargets()
{
#if defined(GAMEUI2)
	MaskGameUITexture.Init(CreateMaskGameUITexture());
#endif // GAMEUI2
	DepthBufferTexture.Init(CreateDepthBufferTexture());
	PhysgunBeamTexture.Init(CreatePhysgunBeamTexture());
	MaskViewmodelTexture.Init(CreateMaskViewmodelTexture());
}

void DynamicRenderTargets::ShutdownClientRenderTargets()
{
	BaseClass::ShutdownClientRenderTargets();

	ShutdownDynamicRenderTargets();

	CurrentMaterialSystem = nullptr;
}

void DynamicRenderTargets::ShutdownDynamicRenderTargets()
{
#if defined(GAMEUI2)
	MaskGameUITexture.Shutdown();
#endif // GAMEUI2
	DepthBufferTexture.Shutdown();
	PhysgunBeamTexture.Shutdown();
	MaskViewmodelTexture.Shutdown();
}

void DynamicRenderTargets::PreRender()
{
	UpdateDynamicRenderTargets();
}

void DynamicRenderTargets::UpdateDynamicRenderTargets()
{
	if (CurrentMaterialSystem == nullptr)
		return;

	if (OldViewport != GetViewport())
	{
		ShutdownDynamicRenderTargets();
		InitDynamicRenderTargets();

		OldViewport = GetViewport();
	}
}

Vector2D DynamicRenderTargets::GetViewport()
{
	if (CurrentMaterialSystem == nullptr)
		return Vector2D(0, 0);

	int32 ViewportX, ViewportY;
	CurrentMaterialSystem->GetBackBufferDimensions(ViewportX, ViewportY);
	return Vector2D(ViewportX, ViewportY);
}

#if defined(GAMEUI2)
ITexture* DynamicRenderTargets::CreateMaskGameUITexture()
{
	return CurrentMaterialSystem->CreateNamedRenderTargetTextureEx2(
		"_rt_MaskGameUI",
		GetViewport().x, GetViewport().y, RT_SIZE_FULL_FRAME_BUFFER,
		IMAGE_FORMAT_I8,
		MATERIAL_RT_DEPTH_SHARED,
		TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_NOMIP,
		NULL);
}
#endif // GAMEUI2

ITexture* DynamicRenderTargets::CreateDepthBufferTexture()
{
	return CurrentMaterialSystem->CreateNamedRenderTargetTextureEx2(
		"_rt_DepthBuffer",
		GetViewport().x, GetViewport().y, RT_SIZE_FULL_FRAME_BUFFER,
		IMAGE_FORMAT_R32F,
		MATERIAL_RT_DEPTH_SEPARATE,
		TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_POINTSAMPLE,
		CREATERENDERTARGETFLAGS_NOEDRAM);
}

ITexture* DynamicRenderTargets::CreatePhysgunBeamTexture()
{
	return CurrentMaterialSystem->CreateNamedRenderTargetTextureEx2(
		"_rt_PhysgunBeam",
		GetViewport().x, GetViewport().y, RT_SIZE_FULL_FRAME_BUFFER,
		IMAGE_FORMAT_I8,
		MATERIAL_RT_DEPTH_SHARED,
		TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_NOMIP,
		NULL);
}

ITexture* DynamicRenderTargets::CreateMaskViewmodelTexture()
{
	return CurrentMaterialSystem->CreateNamedRenderTargetTextureEx2(
		"_rt_MaskViewmodel",
		GetViewport().x, GetViewport().y, RT_SIZE_FULL_FRAME_BUFFER,
		IMAGE_FORMAT_I8,
		MATERIAL_RT_DEPTH_SHARED,
		TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_NOMIP,
		NULL);
}

ITexture* DynamicRenderTargets::DrawHudTexture()
{
	return CurrentMaterialSystem->CreateNamedRenderTargetTextureEx2(
		"_rt_hud",
		GetViewport().x, GetViewport().y, RT_SIZE_FULL_FRAME_BUFFER,
		IMAGE_FORMAT_I8,
		MATERIAL_RT_DEPTH_SHARED,
		TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_NOMIP,
		NULL);
}

static DynamicRenderTargets StaticDynamicRenderTargets;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(DynamicRenderTargets, IClientRenderTargets, CLIENTRENDERTARGETS_INTERFACE_VERSION, StaticDynamicRenderTargets);