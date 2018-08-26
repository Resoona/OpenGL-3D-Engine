#pragma once
#include "../../typedeclaration.h"
#include <vector>

class ShaderResourceDeclaration
{

public:
	virtual const String& GetName() const = 0;
	virtual uint GetRegister() const = 0;
	virtual uint GetCount() const = 0;
};

typedef std::vector<ShaderResourceDeclaration*> ShaderResourceList;