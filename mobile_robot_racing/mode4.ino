void mode4(){
  analogWrite(RGB_R ,255);
  analogWrite(RGB_G ,255);
  analogWrite(RGB_B ,255);
  
  if(u2_rcv_flag){
    if(u2_rcv_data==NULL){
      go(0,0);
    }
    else if(u2_rcv_data==0x55){ //U
    go(30,30); //직진
    }
    else if(u2_rcv_data==0x52){ //R
    go(30,-30); //우회전
    }
    else if(u2_rcv_data==0x44){ //D
    go(-30,-30); //후진
    }
    else if(u2_rcv_data==0x4C){ //L
    go(-30,30); //좌회전
    }
    else if(u2_rcv_data==0x53){ //S
    go(0,0); //정지
    }
    else if(u2_rcv_data==0x41){ //A
    go(-0,-30); //뒤로좌회전
    }
    else if(u2_rcv_data==0x42){ //B
    go(-30,-0); //뒤로우회전
    }
  }



  
}
