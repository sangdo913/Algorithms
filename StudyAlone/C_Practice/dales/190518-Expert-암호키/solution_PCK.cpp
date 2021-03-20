extern int check(unsigned char key[200]);

unsigned char testbed[200];

// Number of correct combination 
int correct()
{
  return check(testbed) / 257;
}

void reset_testbed()
{
  for (int i = 0; i < 200; ++i)
    testbed[i] = 0;
}

// both start & end are inclusive
bool is_in(int whereis, int start, int end)
{
  reset_testbed();
  for (int i=start; i<=end; ++i)
    testbed[i] = whereis;

  return correct();
}

void test(unsigned char key[200])
{
  int count = 0;
  for(int whereis = 1; whereis < 256 && count < 200; ++whereis)
  {
    int start=0, end=199;
    if(!is_in(whereis, start, end)) continue;

    // binary search
    while(start < end)
    {
      int end_org = end;

      // test front half
      end = (start + end) / 2;
      if(is_in(whereis, start, end)) continue;

      // else, it is in back half
      start = end + 1;
      end = end_org;
    }

//    assert(start == end);
    key[start] = whereis;
    ++count;
  }
}
