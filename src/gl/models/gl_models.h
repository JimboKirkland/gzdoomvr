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
#include "gl/data/gl_vertexbuffer.h"
#include "p_pspr.h"
#include "r_data/voxels.h"
#include "r_data/models/models.h"

class GLSprite;
struct FDrawInfo;

class FGLModelRenderer : public FModelRenderer
{
	int modellightindex = -1;
	FDrawInfo *di;
public:
	FGLModelRenderer(FDrawInfo *d, int mli) : modellightindex(mli), di(d)
	{}
	void PrepareRenderHUDModel(AActor* playermo, FSpriteModelFrame* smf, float ofsX, float ofsY, VSMatrix &objectToWorldMatrix);
	ModelRendererType GetType() const override { return GLModelRendererType; }
	void BeginDrawModel(AActor *actor, FSpriteModelFrame *smf, const VSMatrix &objectToWorldMatrix, bool mirrored) override;
	void EndDrawModel(AActor *actor, FSpriteModelFrame *smf) override;
	IModelVertexBuffer *CreateVertexBuffer(bool needindex, bool singleframe) override;
	void SetVertexBuffer(IModelVertexBuffer *buffer) override;
	void ResetVertexBuffer() override;
	VSMatrix GetViewToWorldMatrix() override;
	void BeginDrawHUDModel(AActor *actor, const VSMatrix &objectToWorldMatrix, bool mirrored) override;
	void EndDrawHUDModel(AActor *actor) override;
	void SetInterpolation(double interpolation) override;
	void SetMaterial(FTexture *skin, bool clampNoFilter, int translation) override;
	void DrawArrays(int start, int count) override;
	void DrawElements(int numIndices, size_t offset) override;
};

