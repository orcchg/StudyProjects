{$APPTYPE CONSOLE}

uses
  SysUtils;

type
  int = longint;

var
  m1, cluster, error: int;
  a1, a2: int;
  len: int = 0;
  n: int = 0;
  x: array[1..100000] of int;

  white: int;
  aa, gap: array[1..100000] of int;
  index: array[1..100000, 1..160] of int;
  
procedure BackNForth;
begin
  while (random(m1) < 11) do
  begin
    inc(len);
    x[len] := cluster + random(error);
    inc(len);
    x[len] := -(len - 1);
  end;
end;

procedure BlackStripe;
var
  i: int;
begin
  i := random(random(random(4))) + 1;
  while (i > 0) do
  begin
    inc(len);
    x[len] := cluster + random(error);
    inc(n, x[len]);
    BackNForth;
    dec(i);
  end;
end;

procedure WhiteStripe;
var
  i, a: int;
begin
  a := a1 + random(a2 + 1 - a1);
  inc(white);
  aa[white] := a;
  for i := 1 to a do
  begin
    inc(len);
    x[len] := cluster + random(error);
    inc(gap[white], x[len]);
    index[white, i] := len;
    BackNForth;
  end;
  inc(n, gap[white]);
end;

procedure DoWhite;
var
  i, j, t, le: int;
  list: array[1..100000] of int;
begin
  le := 0;
  for i := 1 to white do
  begin
    for j := 1 to aa[i] do
    begin
      inc(le);
      list[le] := index[i, j];
    end;
  end;
  for i := le downto 2 do
  begin
    j := random(i) + 1;
    t := list[i];
    list[i] := list[j];
    list[j] := t;
  end;
  for i := 1 to le do
  begin
    inc(len);
    x[len] := -list[i];
  end;
end;

procedure qgap(l, r: int);
var
  i, j: int;
  x, t: int;
begin
  i := l;
  j := r;
  x := gap[(l + r) div 2];
  repeat
    while (gap[i] > x) do inc(i);
    while (gap[j] < x) do dec(j);
    if (i <= j) then
    begin
      t:= gap[i];
      gap[i] := gap[j];
      gap[j] := t;
      inc(i);
      dec(j);
    end;
  until (i > j);
  if (l < j) then qgap(l, j);
  if (i < r) then qgap(i, r);  
end;

procedure DoFill;
var
  i: int;
begin
  qgap(1, white);
  for i := 1 to white do
  begin
    inc(len);
    x[len] := gap[i];
    if (random(16) = 0) then
    begin
      inc(len);
      x[len] := gap[i] + 1 + random(5);
    end;
    if (i < white) and (gap[i] <> gap[i + 1]) and (random(2) = 0) then
    begin
      inc(len);
      x[len] := gap[i];
    end;
  end;
end;

procedure DoQuery;
var
  i: int;
begin
  writeln(n, ' ', len); 
  for i := 1 to len do
  begin
    writeln(x[i]);
  end;
end;

begin
  randseed := strtoint(paramstr(1));
  m1 := strtoint(paramstr(2));
  cluster := random(20000) + 1000;
  a1 := strtoint(paramstr(3));
  a2 := strtoint(paramstr(4));
  error := strtoint(paramstr(5));
  repeat
    BlackStripe;
    WhiteStripe;
  until (len > m1);
  inc(n, random(500));
  inc(len);
  x[len] := 566;
  DoWhite;
  DoFill;
  DoQuery;
end.
