#pragma once

template<typename T>
class ResourceHolder
{
private:
	std::unordered_map<std::string, T*> _resourcesMap;
	std::unordered_map<std::string, std::string> _resourcesPathesMap;
	std::function<void(const std::string&, size_t, size_t)> _callbackFunction;
	size_t _oldSize;
	size_t _maxValue;
	std::string _progressText;

public:
	ResourceHolder(const std::string& resourcePath);
	~ResourceHolder();

public:
	void loadAll();
	void releaseAll();
	size_t getResourcesCount();
	void setProgressCallback(std::function<void(const std::string&, size_t, size_t)> callback, const std::string& progressText, size_t oldSize, size_t maxValue);

public:
	T* get(const std::string& resName);
	void remove(const std::string& resName);

private:
	void parseConfigLine(const std::string& line, std::string& key, std::string& value);
	void loadConfigFile(const std::string & resourcePath);
};
