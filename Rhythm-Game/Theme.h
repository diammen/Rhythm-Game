#pragma once

class theme
{
	theme();
	theme(theme const&);
	void operator=(theme const&) {}
public:
	static theme& GetInstance();
	~theme();
};