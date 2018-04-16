#ifndef _LDK_INI_H_
#define _LDK_INI_H_

namespace ldk
{
	enum VariantType
	{
		BOOL,
		INT,
		FLOAT,
		STRING,
		VEC3,
		VEC4
	};

	struct StringLiteral
	{
		char8* start;
		uint32 lenght;
	};

	struct Variant
	{
		VariantType type;
		union 
		{
			uint8 boolvalue;
			uint32 intValue;
			float floatValue;
			Vec3 vec3Value;
			Vec4 vec4Value;
			StringLiteral stringValue;
		};
	};
}
#endif// _LDK_INI_H_
