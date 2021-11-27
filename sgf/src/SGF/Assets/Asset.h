#pragma once

#include "SGF/Structures.h"
#include "SGF/Core/Logger.h"

namespace SGF::Assets
{
	class IAsset
	{
		virtual bool LoadFromFile(const std::string& fileName) = 0;
	};

	class Image : IAsset
	{
	public:
		Image() {};

		inline SDL_Surface* GetPointer() { return m_Surface.get(); }

		virtual bool LoadFromFile(const std::string& fileName)
		{
			SDL_Surface* surface = IMG_Load(fileName.c_str());

			if (!surface)
				return false;

			m_Surface = SDL_SurfacePtr(std::move(surface));

			return true;
		}

	private:
		SDL_SurfacePtr m_Surface;
	};

	class Font : public IAsset
	{
	public:
		Font(Uint32 size = 12) : m_Size(size) {}

		inline TTF_Font* GetPointer() { return m_Font.get(); }

		virtual bool LoadFromFile(const std::string& fileName)
		{
			TTF_Font* font = TTF_OpenFont(fileName.c_str(), m_Size);

			if (!font)
				return false;

			m_Font = TTF_FontPtr(std::move(font));

			return true;
		}

	private:
		Uint32 m_Size;
		TTF_FontPtr m_Font;
	};

	class LayoutNode
	{
	public:
		typedef std::unique_ptr<LayoutNode> Ptr;

		LayoutNode(const rapidxml::xml_node<>* node)
		{
			m_Name = node->name();

			for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute())
			{
				m_Attributes[attr->name()] = attr->value();
			}

			for (rapidxml::xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling())
			{
				std::string childNodeId = childNode->name();
				std::transform(childNodeId.begin(), childNodeId.end(), childNodeId.begin(), ::tolower);

				m_Children[childNodeId] = std::make_unique<LayoutNode>(childNode);
			}
		}
	private:
		std::string m_Name;
		std::unordered_map<std::string, std::string> m_Attributes;
		std::unordered_map<std::string, LayoutNode::Ptr> m_Children;
	};

	class Layout : public IAsset
	{
	public:
		Layout() : IAsset() {}
		
		virtual bool LoadFromFile(const std::string& fileName)
		{
			std::string bufferString;
			std::stringstream buffer;
			std::ifstream file(fileName);
			
			buffer << file.rdbuf();
			bufferString = buffer.str();
			
			file.close();
			
			m_XML = std::make_unique<rapidxml::xml_document<>>();
			m_XML->parse<0>(&bufferString[0]);

			for (rapidxml::xml_node<>* node = m_XML->first_node("Layout")->first_node(); node; node = node->next_sibling())
			{
				CORE_LOG_INFO("Node: {}", node->name());
				std::string nodeId = node->first_attribute("id")->value();
				m_Elements[nodeId] = std::make_unique<LayoutNode>(node);
			}
		}

	private:
		XML_DocumentPtr m_XML;
		std::unordered_map<std::string, LayoutNode::Ptr> m_Elements;
	};
}