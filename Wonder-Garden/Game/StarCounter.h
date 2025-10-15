#pragma once
class StarCounter : public IGameObject
{
public:
	StarCounter() {};
	void AddStarCount();
	int GetStarCount()
	{
		return starCount;
	}

private:
	~StarCounter() {};
	bool Start();


private:
	int starCount = 0;
};

