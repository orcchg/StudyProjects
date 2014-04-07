void Insertion_Sort_D(member* pA, int n)
{

	int key = 0;
	int i = 0;
	type_el elem;

	for(int j = n - 2; j >= 0; --j)
	{
		key = pA[j].key;
		elem = pA[j].info;
		i = j + 1;
		
		while(i < n && pA[i].key > key)
		{
			pA[i-1].key = pA[i].key;
			pA[i-1].info = pA[i].info;
			++i;
			pA[i-1].key = key;
			pA[i-1].info = elem;
		}
	}
}