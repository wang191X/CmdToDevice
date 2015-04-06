#pragma once

class CSocketService
{
public:
	CSocketService(void);
	virtual ~CSocketService(void);

protected:
	void session();
	void server();
};
