float masshtab(float (*f)(float), int b, float n) 
{
	float m;
	float max = f(-1+n);
	for (float i = -1 + n + n; i < 1; i += n) {
		if (max < f(i))
			max = f(i);
	}
	m = b / max;
	return m;
}
