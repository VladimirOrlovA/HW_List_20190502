#include"list_.h"

void main()
{
	list_<int> n;

	n.push_front(5);
	n.push_front(4);
	n.push_front(3);
	n.push_front(2);
	n.push_front(1);
	n.push_front(0);
	n.push_back(6);
	n.insert(1, 0);
	n.pop_back();
	n.pop_front();

	cout << endl << n << endl;
	n.removeAt(3);
	//cout << endl << n << endl;

	list_<int> copy;
	copy = n;
	copy.pop_back();
	copy.pop_back();
	copy.pop_back();

	cout << endl << copy << endl;
	//copy.pop_back();
	//cout << "List size = " << n.size() << endl;
	//cout << "n[pos] = " << n[3] << endl;

	system("pause");
}


