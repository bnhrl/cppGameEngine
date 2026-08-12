#pragma once
#include <rapidjson/document.h>
#include <string>

#include "Color.h"
#include "Vector2.h" 
#include "Vector3.h"

#define JSON_READ(value, data) bnhe::json::Read(value, #data, data)
#define JSON_READ_NAME(value, name, data) bnhe::json::Read(value, name, data)

namespace bnhe::json
{
	using value_t = rapidjson::Value;
	using document_t = rapidjson::Document;
	

	bool Load(const std::string& filename, document_t& document);

	// read json data
	bool Read(const value_t& value, const std::string& name, int& data);
	bool Read(const value_t& value, const std::string& name, float& data); 
	bool Read(const value_t& value, const std::string& name, bool& data); 
	bool Read(const value_t& value, const std::string& name, std::string& data); 
	bool Read(const value_t& value, const std::string& name, Vector2& data); 
	bool Read(const value_t& value, const std::string& name, Vector3& data);
	bool Read(const value_t& value, const std::string& name, Color& data);
}