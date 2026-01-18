#pragma once
struct keys // struct for the keys
{
	const bool* myKeys;

	keys();
	~keys();
	void initKeys(const bool* _keys);
};

