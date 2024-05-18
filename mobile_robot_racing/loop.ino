
void loop() {

  

  if(mode==0){
    mode0();
  }

  if(mode == 1){
    mode1();
  }
  else if(mode == 2)
  {
    mode2();
    mode=3;
  }

  else if(mode==3){
    mode3();
  }
  
  else if(mode==4){
    mode4();
  }



} 
