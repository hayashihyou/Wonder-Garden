#include "stdafx.h"

#include "Stage.h"

bool Stage::Start()
{
    // 初期化
    Init();

    return true;
}

void Stage::Render(RenderContext& rc)
{
    m_stageModel.Draw(rc);
}

void Stage::Init()
{
    m_stageModel.Init("Assets/stage/stage.tkm");
    m_stageModel.Update();
    m_physicsStaticObject.CreateFromModel(m_stageModel.GetModel(), m_stageModel.GetModel().GetWorldMatrix());
}
