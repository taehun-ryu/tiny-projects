void tact_1()
{
  if (!data_tact1)
  {
    if (digitalRead(tact1) != data_tact1)
    {
      tact1_num++;
    }
  }
  data_tact1 = digitalRead(tact1);
  tactswitch1 = tact1_num;
}

void tact_2()
{
  if (!data_tact2)
  {
    if (digitalRead(tact2) != data_tact2)
    {
      tact2_num++;
    }
  }
  data_tact2 = digitalRead(tact2);
  tactswitch2 = tact2_num;
}

void tact_3()
{
  if (!data_tact3)
  {
    if (digitalRead(tact3) != data_tact3)
    {
      tact3_num++;
    }
  }
  data_tact3 = digitalRead(tact3);
  tactswitch3 = tact3_num;
}

void tact_4()
{
  if (!data_tact4)
  {
    if (digitalRead(tact4) != data_tact4)
    {
      tact4_num++;
    }
  }
  data_tact4 = digitalRead(tact4);
  tactswitch4 = tact4_num;
}
