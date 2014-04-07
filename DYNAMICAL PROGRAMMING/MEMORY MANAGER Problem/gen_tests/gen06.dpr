Uses 
  SysUtils;
const
  n=32000;
  m=100000;
var
  i : LongInt;
Begin
  writeln(n,' ',m);
  for i:=1 to 32000 do writeln(1);
  for i:=1 to 16000 do writeln(-2*i);
  for i:=48001 to 99999 do writeln(2);
  writeln(1);
End.
