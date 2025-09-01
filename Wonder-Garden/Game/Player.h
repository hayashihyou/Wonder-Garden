#pragma once
#include "CharacterBase.h"

class Player :public CharacterBase
{
public:
	Player() {};
private:
	~Player() {};
	bool Start()override;
	void Update()override;
	void Draw(RenderContext& rc)override;

private:
	ModelRender m_playerModel;

};

