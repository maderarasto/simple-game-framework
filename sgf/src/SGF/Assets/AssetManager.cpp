#include "sgfpch.h"
#include "AssetManager.h"
#include "Asset.h"

using namespace SGF::Assets;


template<class Resource>
Resource& AssetManager<Resource>::Get(const std::string& key)
{
	auto found = m_AssetMap.find(key);

	if (found == m_AssetMap.end())
		CORE_LOG_ERROR("An asset with key \"{}\" not found in asset manager!", key);
	
	return *(found->second);
}


template<class Resource>
const Resource& AssetManager<Resource>::Get(const std::string& key) const
{
	auto found = m_AssetMap.find(key);

	if (found == m_AssetMap.end())
		CORE_LOG_ERROR("An asset with key \"{}\" not found in asset manager!", key);

	return *(found->second);
}


template<class Resource>
void AssetManager<Resource>::Load(const std::string& fileName, const std::string& key)
{
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();
	CORE_LOG_INFO("Filename: {}", fileName);

	if (!resource->LoadFromFile(fileName))
		CORE_LOG_ERROR("Could not load an asset from the file with name \"{}\"!", fileName);
	else
		m_AssetMap.insert(std::make_pair(key, std::move(resource)));
}


template<class Resource>
template<typename Parameter>
void AssetManager<Resource>::Load(const std::string& fileName, const std::string& key, const Parameter& parameter)
{
	std::unique_ptr<Resource> resource = std::make_unique<Resource>(parameter);
	CORE_LOG_INFO("Filename: {}", fileName);

	if (!resource->LoadFromFile(fileName))
		CORE_LOG_ERROR("Could not load an asset from the file with name \"{}\"!", fileName);
	else
		m_AssetMap.insert(std::make_pair(key, std::move(resource)));
}


template<class Resource>
void AssetManager<Resource>::Clear()
{
	m_AssetMap.clear();
}

template SGF_API const Font& AssetManager<Font>::Get(const std::string&) const;
template SGF_API Font& AssetManager<Font>::Get(const std::string&);
template SGF_API void AssetManager<Font>::Load(const std::string&, const std::string&);
template SGF_API void AssetManager<Font>::Load(const std::string&, const std::string&, const int&);
template SGF_API void AssetManager<Font>::Clear();

template SGF_API const Image& AssetManager<Image>::Get(const std::string&) const;
template SGF_API Image& AssetManager<Image>::Get(const std::string&);
template SGF_API void AssetManager<Image>::Load(const std::string&, const std::string&);
template SGF_API void AssetManager<Image>::Clear();