
var
a : array[1..500001] of integer;
function BinarySearch(l, r, q : integer): boolean;
begin
if (r - l = 1) then
if ((a[l] = q) or (a[r] = q)) then
result := true
else
result := false
else
if a[(l+r) div 2] > q then
result := BinarySearch(l, (l+r) div 2, q)
else
result := BinarySearch((l+r) div 2, r, q);
end;
var
n, i, k, x : integer;
begin
readln(n);
for i := 1 to n do
read(a[i]);
readln(k);
for i := 1 to k do
begin
read(x);
if BinarySearch(1, n, 10000-x) then
begin
writeln('YES');
exit;
end
end;
writeln('NO');
end.
