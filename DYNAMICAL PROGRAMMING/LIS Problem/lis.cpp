/*  ���������� ������������ ��������������������� (���) 
 * (����. Longest increasing subsequence - LIS) 
 *  ������ x ����� n - ��� ������������������ x[i1] < x[i2] < ... < x[ik]
 *  �������� ������ x �����, ��� i1 < i2 < ... < ik, 1 <= ij <= n,
 *  ������ k - ���������� �� ���������.
 */
 
 /* O(n^2) */
 
 #include <iostream>
 #include <conio.h>
 #include <vector>
 #include <stack>
 using std::cin;
 using std::cout;
 using std::endl;
 using std::vector;
 using std::stack;
 
 int main()
 {
	int lis = 0;
	int c;

	vector<int> x;
	x.clear();
	
	while (cin>>c) {
		x.push_back(c);
	}
	
	int N = x.size();

	int* a = new int[N];
	int* prev = new int[N];
	
	for (int i = 0; i < N; ++i) {
		a[i] = 0;
		prev[i] = -1;
	}
	
	a[0] = 1;
	int pos = 0;
	
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < i; ++j) {
			if ( (x[i] > x[j]) )//&& (a[j] + 1 > a[i]) ) 
			{
				a[i] = a[j] + 1;
				prev[i] = j;
			}
//			lis = (lis > a[i]) ? lis : a[i];
			if (lis <= a[i]) {
				lis = a[i];
				pos = i;
			}
		}
	}
	
	cout << "LIS length: " << lis << " pos: " << pos << endl;
	
	for (int i = 0; i < N; ++i) {
		cout << prev[i] << " ";
	}
	
	cout << endl;
	for (int i = 0; i < N; ++i) {
		cout << a[i] << " ";
	}
	
	delete [] a;
	
	stack<int> s;
	
	cout << endl;
	while (pos != -1) {
//		cout << x[pos] << " ";
		s.push(x[pos]);
		pos = prev[pos];
	}
	
	delete [] prev;
	
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	
	cin.ignore();
	_getch();
	return 0;
}
	