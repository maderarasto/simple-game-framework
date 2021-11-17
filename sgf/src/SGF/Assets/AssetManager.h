#pragma once

#include "SGF.h"

namespace SGF::Assets
{
	template<class Resource>
	class SGF_API AssetManager
	{
	public:
		AssetManager() {};

		Resource& Get(const std::string& key);
		const Resource& Get(const std::string& key) const;

		template<typename Parameter>
		void Load(const std::string& fileName, const std::string& key, const Parameter& parameter);
		void Load(const std::string& fileName, const std::string& key);

		void Clear();

		AssetManager(const AssetManager<Resource>&) = delete;
		const AssetManager<Resource>& operator=(const AssetManager<Resource>&) = delete;

	private:
		std::unordered_map<std::string, std::unique_ptr<Resource>> m_AssetMap;
	};
}