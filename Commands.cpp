#include "Commands.h"
#include <string.h>

Commands::Commands()
{
	//receive commands from standard input
	while (true)
	{
		cin >> command;

		if (!strcmp(command, "GO"))
		{
			char *url = new char[1000];
			cin >> url;
			go(url);
		}

		if (!strcmp(command, "INSERT"))
		{
			char *url = new char[1000];
			cin >> url;
			insert(url);
		}

		if (!strcmp(command, "BACK"))
			back();

		if (!strcmp(command, "FORWARD"))
			forward();

		if (!strcmp(command, "REMOVE"))
			remove();

		if (!strcmp(command, "PRINT"))
			print();

		if (!strcmp(command, "SORT"))
		{
			char by[4];
			cin >> by;
			if (!strcmp(by, "URL"))
				mergeSortUrl();
			if (!strcmp(by, "TIME"))
				mergeSortTime();
		}
	}
}

void Commands::go(const char *url)
{
	browserHistory.loadPage(url);
}

void Commands::insert(const char *url)
{
	browserHistory.insertTab(url);
}

void Commands::back()
{
	browserHistory.back();
}

void Commands::forward()
{
	browserHistory.forward();
}

void Commands::remove()
{
	browserHistory.remove();
}

void Commands::print()
{
	browserHistory.print();
}

void Commands::mergeSortUrl()
{
	browserHistory.mergeSort_Url();
}

void Commands::mergeSortTime()
{
	browserHistory.mergeSort_Timestamp();
}

Commands::~Commands()
{
}