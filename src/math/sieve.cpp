const int MAX = 1e6+10;
vector<bool> prime(MAX, true);	
 
void Sieve() // O(nlog(logn))
{ 
	prime[0] = prime[1] = 0;
	for (int i = 2; i*i <= MAX; i++)
		if (prime[i])
			for (int j = i * 2; j <= MAX; j += i)
				prime[j] = 0;
}v