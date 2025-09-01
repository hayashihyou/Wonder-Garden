#pragma once
#include "CharacterBase.h"

class Enemy : public CharacterBase
{
public:
	Enemy() {};
private:
	~Enemy() {};
	bool Start()override;
	void Update()override;
	void Draw(RenderContext& rc)override;

};

