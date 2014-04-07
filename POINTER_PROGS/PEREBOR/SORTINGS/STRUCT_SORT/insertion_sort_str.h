void Insertion_Sort(member* pA, int n)
{

	int key = 0;
	int i = 0;
	type_el elem;

	for(int j = 1; j < n; ++j)
	{
		key = pA[j].key;
		elem = pA[j].info;
		i = j - 1;
		
		while(i >= 0 && pA[i].key > key)
		{
			pA[i+1].key = pA[i].key;
			pA[i+1].info = pA[i].info;
			--i;
			pA[i+1].key = key;
			pA[i+1].info = elem;
		}
	}
}