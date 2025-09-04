#include "stdafx.h"
#include "Stage.h"


bool Stage::Start()
{
    m_stage.Init("Assets/stage/stage.tkm");
    m_stage.Update();
    physicsStaticObject.CreateFromModel(m_stage.GetModel(), m_stage.GetModel().GetWorldMatrix());
   

    return true;
}

void Stage::Update()
{
  
}

void Stage::Render(RenderContext& rc)
{
    m_stage.Draw(rc);
}
