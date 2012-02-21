/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef CVT_XMLATTRIBUTE_H
#define CVT_XMLATTRIBUTE_H

#include <cvt/io/xml/XMLLeaf.h>

namespace cvt {
	/**
	  \ingroup XML
	*/
	class XMLAttribute : public XMLLeaf {
		public:
			XMLAttribute( const String& name, const String& value );
			XMLAttribute( const XMLAttribute& other );
			XMLAttribute& operator=( const XMLAttribute& other );
			~XMLAttribute();

			void xmlString( String& str ) const;
	};

	inline XMLAttribute::XMLAttribute( const String& name, const String& value ) : XMLLeaf( XML_NODE_ATTRIBUTE, name, value )
	{
	}

	inline XMLAttribute::XMLAttribute( const XMLAttribute& other ) : XMLLeaf( XML_NODE_ATTRIBUTE, other._name, other._value )
	{
	}

	inline XMLAttribute::~XMLAttribute()
	{
	}

	inline XMLAttribute& XMLAttribute::operator=( const XMLAttribute& other )
	{
		_name = other._name;
		_value = other._value;
		return *this;
	}

	inline void XMLAttribute::xmlString( String& str ) const
	{
		str = " ";
		str += _name;
		str += "=\"";
		str += _value;
		str += "\"";
	}
}

#endif
