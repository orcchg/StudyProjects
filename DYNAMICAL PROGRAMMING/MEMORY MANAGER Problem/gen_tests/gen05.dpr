program gen01;
{$APPTYPE CONSOLE}
uses
  SysUtils;
const
  M=100;
  N=100;

var
  i,j,sum,ibq,num:longint;
  bq:array[1..M] of longint;
begin
  randseed:=StrToInt(ParamStr(1));

  writeln(N,' ',M);
  sum:=0;
  ibq:=0;
  for i:=1 to M do
  begin
    if (random(5)=3) and (sum>0) then
    begin
      writeln(N-sum+1);
      inc(ibq);
      bq[ibq]:=i;
    end else
    begin
      if (ibq>0) then
        if (random(7)=3) then
        begin
          num:=random(ibq)+1;
          writeln(-bq[num]);
          bq[num]:=bq[ibq];
          dec(ibq);
        end else
        begin
          num:=random(10)+1;
          if (sum+num<=N) then inc(sum,num);
          writeln(num)
        end
      else
      begin
        num:=random(10)+1;
        if (sum+num<=N) then inc(sum,num);
        writeln(num)
      end;
    end;
  end;


end.
