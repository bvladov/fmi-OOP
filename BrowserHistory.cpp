#include "BrowserHistory.h"

BrowserHistory::BrowserHistory()
{
	openBlank();
}

BrowserHistory::~BrowserHistory()
{
	clear();
	openBlank();
}

BrowserHistory::BrowserHistory(const BrowserHistory &other)
{
	copy(other);
}

BrowserHistory &BrowserHistory::operator=(const BrowserHistory &other)
{
	if (this != &other)
		copy(other);
	return *this;
}

void BrowserHistory::copy(const BrowserHistory &other)
{
	clear();
	Tab *p = other.pFirst;
	Tab *temp;
	if (p)
		temp = new Tab;
	else
		return;

	while (p)
	{
		temp->url = p->url;
		temp->timestamp = p->timestamp;
		temp->next = new Tab;
		p = p->next;
	}
}

void BrowserHistory::clear()
{
	while (pFirst)
	{
		Tab *temp = this->pFirst;
		this->pFirst = this->pFirst->next;
		delete temp;
	}
	this->pCurr = this->pFirst = nullptr;
}

void BrowserHistory::openBlank()
{
	Tab *tab = new Tab;
	copyUrl(tab->url, "about:blank");
	tab->timestamp = time(&tab->timestamp);
	tab->prev = tab->next = nullptr;
	this->pCurr = this->pFirst = tab;
}

void BrowserHistory::loadPage(const char *url)
{
	copyUrl(this->pCurr->url, url);
}

void BrowserHistory::copyUrl(char *&dest, const char *source)
{
	int size = strlen(source) + 1;
	char *buffer = new char[size];
	strcpy(buffer, source);

	dest = buffer;
}

void BrowserHistory::insertTab(const char *url)
{
	Tab *newTab = new Tab;
	Tab *pLast = this->pCurr;
	while (pLast->next != NULL)
	{
		//find the last element in the list
		pLast = pLast->next;
	}

	copyUrl(newTab->url, url);
	newTab->timestamp = time(&newTab->timestamp);

	//insert after the last tab
	pLast->next = newTab;
	newTab->prev = pLast;
	newTab->next = nullptr;
	this->pCurr = newTab;
}

void BrowserHistory::back()
{
	this->pCurr = (this->pCurr->prev) ? this->pCurr->prev : this->pCurr;
}

void BrowserHistory::forward()
{
	this->pCurr = (this->pCurr->next) ? this->pCurr->next : this->pCurr;
}

void BrowserHistory::remove()
{
	//temp is either current tab or previous tab
	Tab *temp = (this->pCurr->prev) ? this->pCurr->prev : this->pCurr;
	delete[] this->pCurr->url;
	this->pCurr->url = nullptr;

	if (!this->pCurr->next)
	{
		if (!this->pCurr->prev)
		{
			delete this->pCurr;
			this->pCurr = nullptr;
			openBlank();
			return;
		}
		else
		{
			delete temp->next;
			temp->next = nullptr;
			this->pCurr = temp;
			return;
		}
	}
	else
	{
		if (!this->pCurr->prev)
		{
			this->pCurr = this->pCurr->next;
			this->pCurr->prev = nullptr;
			this->pFirst = this->pCurr;
			delete temp;
			return;
		}
	}

	//make a link between previous tab and next tab and remove current tab
	temp->next = this->pCurr->next;
	this->pCurr->next->prev = temp;
	delete this->pCurr;
	this->pCurr = temp->next;
}

void BrowserHistory::print() const
{
	Tab *temp = this->pFirst;
	while (temp)
	{
		if (temp == pCurr)
		{
			cout << '>';
		}

		cout << temp->url << ' ' << temp->timestamp << endl;
		temp = temp->next;
	}
}

void BrowserHistory::mergeSort_Url()
{
	mergeSort(this->pFirst, 1);
}

void BrowserHistory::mergeSort_Timestamp()
{
	mergeSort(this->pFirst, 0);
}

Tab *BrowserHistory::mergeSort(Tab *left, bool byUrl)
{
	if (left == nullptr || left->next == nullptr)
		return left;

	Tab *right = SplitList(left, byUrl);

	//recursively split and sort each half
	left = mergeSort(left, byUrl);
	right = mergeSort(right, byUrl);

	return SortHalves(left, right, byUrl);
}

Tab *BrowserHistory::SplitList(Tab *source, bool byUrl)
{
	Tab *fast;
	Tab *slow;
	Tab *right;

	if (source == nullptr || source->next == nullptr)
	{
		slow = source;
		right = fast = nullptr;
	}
	else
	{
		//slow pointer reaches the middle of the list when fast pointer becomes nullptr
		fast = source->next;
		slow = source;

		while (fast != nullptr)
		{
			fast = fast->next;
			if (fast != nullptr)
			{
				fast = fast->next;
				slow = slow->next;
			}
		}
		right = slow->next;	//now pointing to the right half
		right->prev = nullptr; //break the link
		slow->next = nullptr;  //between the two halves
	}

	return right;
}

Tab *BrowserHistory::SortHalves(Tab *left, Tab *right, bool byUrl)
{
	Tab *result = nullptr;

	//a single element is always sorted, return it
	if (left == nullptr)
		return (right);
	else if (right == nullptr)
		return (left);

	if (byUrl)
	{
		sortUrl(left, right, byUrl, result);
	}
	else
	{
		if (left->timestamp <= right->timestamp)
		{
			if (left->timestamp == right->timestamp)
			{
				sortUrl(left, right, byUrl, result);
			}

			else
			{
				left->next = SortHalves(left->next, right, byUrl); //recursively compare the elements until one of them is nullptr
				left->next->prev = left;
				result = left;
			}
		}
		else
		{
			right->next = SortHalves(left, right->next, byUrl);
			right->next->prev = right;
			result = right;
		}
	}

	//assign the element with lowest value to pFirst and pCurr
	this->pFirst = this->pCurr = result;
	return result;
}

void BrowserHistory::sortUrl(Tab *&left, Tab *&right, bool byUrl, Tab *&result)
{
	if (strcmp(right->url, left->url) >= 0)
	{
		left->next = SortHalves(left->next, right, byUrl);
		left->next->prev = left;
		result = left;
	}
	else
	{
		right->next = SortHalves(left, right->next, byUrl);
		right->next->prev = right;
		result = right;
	}
}