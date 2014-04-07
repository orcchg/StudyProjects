{$APPTYPE CONSOLE}

uses
  SysUtils;

type
  int = longint;

var
  i, j, t, m: int;
  a, p: array[1..50000] of int;

begin
  randseed := strtoint(paramstr(1));
  m := strtoint(paramstr(2));
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
  for i := 1 to m do
  begin
    p[a[i]] := i;
  end;
  writeln((m + 1) * (m div 2), ' ', 2 * m);
  for i := 1 to m do
  begin
    writeln(a[i]);
  end;
  for i := m div 2 + 1 to m do
  begin
    writeln(-p[i]);
  end;
  for i := m div 2 + 1 to m do
    writeln(i);
end.
