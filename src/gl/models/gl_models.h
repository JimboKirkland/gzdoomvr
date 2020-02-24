// 
//---------------------------------------------------------------------------
//
// Copyright(C) 2005-2016 Christoph Oelckers
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/
//
//--------------------------------------------------------------------------
//

#pragma once

#include "tarray.h"
#include "p_pspr.h"
#include "r_data/voxels.h"
#include "r_data/models/models.h"

class GLSprite;
struct FDrawInfo;
class FRenderState;

class FModelVertexBuffer : public IModelVertexBuffer
{
	int mIndexFrame[2];
	IVertexBuffer *mVertexBuffer;
	IIndexBuffer *mIndexBuffer;

public:

	FModelVertexBuffer(bool needindex, bool singleframe);
	~FModelVertexBuffer();

	FModelVertex *LockVertexBuffer(unsigned int size) override;
	void UnlockVertexBuffer() override;

	unsigned int *LockIndexBuffer(unsigned int size) override;
	void UnlockIndexBuffer() override;

	void SetupFrame(FModelRenderer *renderer, unsigned int frame1, unsigned int frame2, unsigned int size) override;
	void Bind(FRenderState &state);
};

class FGLModelRenderer : public FModelRenderer
{
	int modellightindex = -1;
	HWDrawInfo* di;
public:
	FGLModelRenderer(HWDrawInfo* d, int mli) : modellightindex(mli), di(d)
	{}
	void PrepareRenderHUDModel(AActor* playermo, FSpriteModelFrame* smf, float ofsX, float ofsY, VSMatrix& objectToWorldMatrix);
	ModelRendererType GetType() const override { return GLModelRendererType; }
	void BeginDrawModel(AActor* actor, FSpriteModelFrame* smf, const VSMatrix& objectToWorldMatrix, bool mirrored) override;
	void EndDrawModel(AActor* actor, FSpriteModelFrame* smf) override;
	IModelVertexBuffer* CreateVertexBuffer(bool needindex, bool singleframe) override;
	void SetVertexBuffer(IModelVertexBuffer* buffer) override;
	void ResetVertexBuffer() override;
	VSMatrix GetViewToWorldMatrix() override;
	void BeginDrawHUDModel(AActor* actor, const VSMatrix& objectToWorldMatrix, bool mirrored) override;
	void EndDrawHUDModel(AActor* actor) override;
	void SetInterpolation(double interpolation) override;
	void SetMaterial(FTexture* skin, bool clampNoFilter, int translation) override;
	void DrawArrays(int start, int count) override;
	void DrawElements(int numIndices, size_t offset) override;
	HWDrawInfo* GetDrawInfo() { return di; }
};

