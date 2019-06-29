#ifndef _COMMANDS_INCLUDED_
#define _COMMANDS_INCLUDED_

#include "BrowserHistory.h"

class Commands{
private:
	BrowserHistory browserHistory;
	char command[7];

public:
	Commands();
	~Commands();

	void go(const char* url);
	void insert(const char* url);
	void back();
	void forward();
	void remove();
	void print();

	void mergeSortUrl();
	void mergeSortTime();
};

#endif