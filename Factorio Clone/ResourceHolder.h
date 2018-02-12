#pragma once

template<typename T>
class ResourceHolder
{
private:
	std::unordered_map<std::string, T*> _resourcesMap;

public:
	ResourceHolder();
	~ResourceHolder();

public:
	T* get(const std::string& resName, const std::string& resPath);
	void remove(const std::string& resName);
};
