void mode0() {
  TS_a();
  TS_b();

  go(0,0);
  
  if(a % 7== 1 && num_a >0 && num_b >0){//A스위치 1번 누르고 B버튼 1번이상 누를경우
    i_degree = 0;
    i_radian = (i_degree * 3.1415926535897932384626433832795)/180;
    mode=1;
  }
  if(a % 7 == 2 && num_a >0 && num_b >0){//A2번 누르고 B버튼 누를경우
    i_degree = 15;
    i_radian = (i_degree * 3.1415926535897932384626433832795)/180;
    mode=1;
  }
  if(a % 7 == 3 && num_a >0 && num_b >0 ){//3번 누를경우
    i_degree = 30;
    i_radian = (i_degree * 3.1415926535897932384626433832795)/180;
    mode=1;
  }
  if(a % 7 == 4 && num_a >0 && num_b >0){//4번 누를경우
    i_degree = 45;
    i_radian = (i_degree * 3.1415926535897932384626433832795)/180;
    mode=1;
  }
  if(a % 7 == 5 && num_a >0 && num_b >0){//5번
    i_degree = 60;
    i_radian = (i_degree * 3.1415926535897932384626433832795)/180;
    mode=1;
  }
  if(a % 7 == 6 && num_a >0 && num_b >0){//6번
    i_degree = 75;
    i_radian = (i_degree * 3.1415926535897932384626433832795)/180;
    mode=1;
  }
  if(a % 7 == 0 && num_a >0 && num_b >0){//7번
    i_degree = 90;
    i_radian = (i_degree * 3.1415926535897932384626433832795)/180;
    mode=1;
  }
}
