#pragma once

template<typename T>
class ResourceHolder
{
private:
	std::unordered_map<std::string, T*> _resourcesMap;
	std::unordered_map<std::string, std::string> _resourcesPathesMap;

public:
	ResourceHolder(const std::string& configFile);
	~ResourceHolder();

public:
	void loadAll();
	void releaseAll();

public:
	T* get(const std::string& resName);
	void remove(const std::string& resName);

private:
	void parseConfigLine(const std::string& line, std::string& key, std::string& value);
	void loadConfigFile(const std::string & configFile);
};
