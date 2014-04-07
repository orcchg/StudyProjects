{$APPTYPE CONSOLE}

uses
  SysUtils;

type
  int = longint;

var
  i, j, t, m, d1, d2: int;
  a, p, val: array[1..50000] of int;

begin
  randseed := strtoint(paramstr(1));
  m := strtoint(paramstr(2));
  d1 := strtoint(paramstr(3));
  d2 := strtoint(paramstr(4));
  for i := 1 to m do
  begin
    val[i] := i div d1 + d2;
  end;
  for i := 1 to m do
  begin
    a[i] := i;
  end;
  for i := m downto 2 do
  begin
    j := random(i) + 1;
    t := a[i];
    a[i] := a[j];
    a[j] := t;
  end;
  t := 0;
  for i := 1 to m do
  begin
    p[a[i]] := i;
    inc(t, val[i]);
  end;
  writeln(t, ' ', 2 * m);
  for i := 1 to m do
  begin
    writeln(val[a[i]]);
  end;
  for i := 1 to m div 2 do
  begin
    writeln(-p[i]);
  end;
  for i := 1 to m div 2 do
    writeln(val[i]);
end.
