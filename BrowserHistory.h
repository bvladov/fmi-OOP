#ifndef _BROWSER_HISTORY_INCLUDED_
#define _BROWSER_HISTORY_INCLUDED_

#include <time.h>
#include <iostream>
#include <string.h>

using namespace std;

struct Tab
{
	char *url;
	time_t timestamp;
	Tab *prev;
	Tab *next;
};

class BrowserHistory
{
private:
	Tab *pCurr;
	Tab *pFirst;

public:
	BrowserHistory();
	~BrowserHistory();

	void openBlank();
	void loadPage(const char *url);
	void insertTab(const char *url);
	void back();
	void forward();
	void remove();
	void print() const;

	void mergeSort_Url();
	void mergeSort_Timestamp();

	Tab *mergeSort(Tab *head, bool byUrl);
	Tab *SplitList(Tab *source, bool byUrl);
	Tab *SortHalves(Tab *left, Tab *right, bool byUrl);
	void sortUrl(Tab *&left, Tab *&right, bool byUrl, Tab *&result);

	void copy(const BrowserHistory &other);
	void clear();
	void copyUrl(char *&dest, const char *source);

private:
	BrowserHistory(const BrowserHistory &other);
	BrowserHistory &operator=(const BrowserHistory &other);
};

#endif _BROWSER_HISTORY_INCLUDED_
