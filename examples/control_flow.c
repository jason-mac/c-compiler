int classify(int n)
{
  if (n < 0)
  {
    return -1;
  }
  else if (n == 0)
  {
    return 0;
  }

  int result = 0;
  for (int i = 0; i < n; i++)
  {
    if (i % 2 == 0)
    {
      continue;
    }
    result += i;
  }

  int j = n;
  while (j > 0)
  {
    j--;
  }

  do
  {
    result++;
  } while (result < 10 && result != 0);

  return result;
}
