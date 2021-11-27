#pragma once

#include "SGF/api.h"

#include <string>
#include <memory>
#include <stdexcept>
#include <functional>
#include <unordered_map>

namespace SGF::UI 
{	
	struct Value
	{
	public:
		typedef std::unique_ptr<Value> Ptr;
	};

	struct FunctionValue : Value
	{
	public:
		typedef std::function<void()> Action;

		FunctionValue (Action value)
		{
			m_Value = value;
		}

		Action GetValue() const
		{
			return m_Value;
		}

		void SetValue(Action value)
		{
			m_Value = value;
		}

	private:
		std::function<void()> m_Value;
	};

	struct StringValue : Value
	{
	public:
		StringValue(std::string value)
		{
			m_Value = value;
		}

		std::string GetValue() const
		{
			return m_Value;
		}

		void SetValue(std::string value)
		{
			m_Value = value;
		}
	private:
		std::string m_Value;
	};
	
	class SGF_API Properties
	{
	public:
		Value& operator[](std::string& propertyName) const
		{
			auto propertyIt = std::find(m_PropertyMap.begin(), m_PropertyMap.end(), propertyName);

			if (propertyIt == m_PropertyMap.end())
				throw std::runtime_error("The property with name \"" + propertyName + "\" not found!");

			return *m_PropertyMap.at(propertyName);
		}

		Value& operator[](std::string& propertyName)
		{

			return *m_PropertyMap.at(propertyName);
		}

		const Value& Get(std::string& propertyName) const
		{
			auto propertyIt = std::find(m_PropertyMap.begin(), m_PropertyMap.end(), propertyName);

			if (propertyIt == m_PropertyMap.end())
				throw std::runtime_error("The property with name \"" + propertyName + "\" not found!");

			return *m_PropertyMap.at(propertyName);
		}

		void Add(std::string& propertyName, std::string& value)
		{
			Value::Ptr stringValue = std::make_unique<StringValue>(value);
			m_PropertyMap.insert(std::make_pair(propertyName, std::move(stringValue)));
		}

		void Add(std::string& propertyName, FunctionValue::Action value)
		{
			Value::Ptr functionValue = std::make_unique<FunctionValue>(value);
			m_PropertyMap.insert(std::make_pair(propertyName, std::move(functionValue)));
		}

		void Remove(std::string& propertyName)
		{
			auto propertyIt = std::find(m_PropertyMap.begin(), m_PropertyMap.end(), propertyName);

			if (propertyIt == m_PropertyMap.end())
				throw std::runtime_error("The property with name \"" + propertyName + "\" not found!");

			m_PropertyMap.erase(propertyName);
		}

		void Clear()
		{
			m_PropertyMap.clear();
		}

	private:
		std::unordered_map<std::string, Value::Ptr> m_PropertyMap; 
	};
}