(*
  Problem: memory
  Author: Andrew Stankevich
  Checker by: Semyon Dyatlov
*)
{$O-,R+,Q+,I+,S+}
{$APPTYPE CONSOLE}
uses
  SysUtils, testlib;

const
  MAXM = 100000;

type
  PSegment = ^TSegment;
  TSegment = object
    l, r, p : integer;
    prev, next : PSegment;
    free : boolean;
  end;

var
  n, m, k, s, i, u, cc, ts : integer;
  x, inp, outp : array [1..MAXM+1] of integer;
  h, q, z : array [1..MAXM+1] of PSegment;
  cur, c, cl, cr : PSegment;
  xi : boolean;

procedure swap0(a, b : integer);
var
  t : integer;
begin
  t := x[a];
  x[a] := x[b];
  x[b] := t;
end;

procedure heapify0(a : integer);
var
  t : integer;
begin
  while true do
  begin
    t := a;
    if (a+a<=s) and (x[a+a]>x[t]) then
      t := a+a;
    if (a+a+1<=s) and (x[a+a+1]>x[t]) then
      t := a+a+1;
    if t=a then
      exit;
    swap0(t,a);
    a := t;
  end;
end;

function find(a : integer) : integer;
var
  ll, rr, mm : integer;
begin
  ll := 1;
  rr := s;
  if (s<1) or (a<x[ll]) or (a>x[rr]) then
  begin
    find := -1;
    exit;
  end;
  if (a=x[rr]) then
  begin
    find := rr;
    exit;
  end;
  while rr-ll>1 do
  begin
    mm := (ll+rr) shr 1;
    if (x[mm]<=a) then
      ll := mm
    else
      rr := mm;
  end;
  if (x[ll]=a) then
    find := ll
  else
    find := -1;
end;

procedure swap(a, b : integer);
var
  t : PSegment;
begin
  t := h[a];
  h[a] := h[b];
  h[b] := t;
  h[a]^.p := a;
  h[b]^.p := b;
end;

function better(a, b : integer) : boolean;
begin
  better := h[a].r-h[a].l>h[b].r-h[b].l;
end;

procedure heapify(a : integer);
var
  t : integer;
begin
  while true do
  begin
    t := a;
    if (a+a<=k) and better(a+a,t) then
      t := a+a;
    if (a+a+1<=k) and better(a+a+1,t) then
      t := a+a+1;
    if t=a then
      exit;
    swap(t,a);
    a := t;
  end;
end;

procedure heap_lift(a : integer);
begin
  while (a>1) and better(a,a shr 1) do
  begin
    swap(a,a shr 1);
    a := a shr 1;
  end;
end;

procedure heap_insert(a : PSegment);
begin
  inc(k);
  h[k] := a;
  a.p := k;
  heap_lift(k);
end;

procedure heap_remove(a : integer);
begin
  swap(a,k);
  dec(k);
  if (a>k) then
    exit;
  heap_lift(a);
  heapify(a);
end;

procedure changeleft(a : PSegment; b : integer);
begin
  b := find(b);
  if (b<>-1) then
    q[b] := a;
end;

procedure remove(a : PSegment);
begin
  if a.next<>nil then
    a.next.prev := a.prev;
  if a.prev<>nil then
    a.prev.next := a.next;
end;

procedure insert(a, prv, nxt : PSegment);
begin
  a.next := nxt;
  a.prev := prv;
  if nxt<>nil then
    nxt.prev := a;
  if prv<>nil then
    prv.next := a;
end;

begin
  n := inf.readlongint;
  m := inf.readlongint;

  s := 0;
  for i:=1 to m do
  begin
    inp[i] := inf.readlongint;
    if inp[i]>0 then
    begin
      outp[i] := ouf.readlongint;
      if outp[i]=-1 then
        continue;
      if (outp[i]<1) or (outp[i]>n-inp[i]+1) then
        Quit(_PE,Format('Блока памяти в ответ на запрос %d вышел за границы',[i]));
      inc(s);
      dec(outp[i]);
      x[s] := outp[i];
    end;
  end;

  ts := s;
  for i:=s downto 1 do
    heapify0(i);
  while s>1 do
  begin
    swap0(1,s);
    dec(s);
    heapify0(1);
  end;
  s := 0;
  for i:=1 to ts do
    if (i=1) or (x[i-1]<x[i]) then
    begin
      inc(s);
      x[s] := x[i];
    end;

  for i:=1 to s do
    q[i] := nil;
  k := 1;
  New(h[k]);
  h[k].p := k;
  h[k].l := 0;
  changeleft(h[k],0);
  h[k].r := n;
  h[k].free := true;
  insert(h[k],nil,nil);

  for i:=1 to m do
    if (inp[i]>0) then
    begin
      cur := h[1];
      xi := (k<1) or (cur.r-cur.l<inp[i]);
      if xi then
        xi := xi;
      if (outp[i]=-1) then
      begin
        z[i] := nil;
        if xi then
          continue;
        Quit(_WA,Format('Не выделена память в ответ на запрос %d, хотя это возможно',[i]));
      end;
      cc := find(outp[i]);
      if (cc=-1) or (q[cc]=nil) or not q[cc].free then
        Quit(_WA,Format('Некорректное выделение памяти в ответ на запрос %d',[i]));
      c := q[cc];
      if (c.l+inp[i]>c.r) then
        Quit(_WA,Format('Недостаточно памяти для размещения запроса %d',[i]));
      New(cur);
      z[i] := cur;
      cur.l := c.l;
      cur.free := false;
      changeleft(cur,cur.l);
      cur.r := c.l+inp[i];
      inc(c.l,inp[i]);
      insert(cur,c.prev,c);
      if (c.l<c.r) then
      begin
        changeleft(c,c.l);
        heapify(c.p)
      end
      else
      begin
        remove(c);
        heap_remove(c.p);
      end;
      if xi then
        Quit(_Fail,'Checker Error 137!!!');
    end
    else
    begin
      if (z[-inp[i]]=nil) then
        continue;
      cur := z[-inp[i]];
      z[-inp[i]] := nil;
      z[i] := nil;
      cl := cur.prev;
      cr := cur.next;
      if (cl<>nil) and not cl.free then
        cl := nil;
      if (cr<>nil) and not cr.free then
        cr := nil;
      if (cl=nil) and (cr=nil) then
      begin
        cur.free := true;
        heap_insert(cur);
        continue;
      end;
      if (cl=nil) then
      begin
        changeleft(nil,cr.l);
        cr.l := cur.l;
        changeleft(cr,cr.l);
        cur.l := -1;
        remove(cur);
        heap_lift(cr.p);
        continue;
      end;
      if (cr=nil) then
      begin
        cl.r := cur.r;
        changeleft(nil,cur.l);
        remove(cur);
        heap_lift(cl.p);
        continue;
      end;
      cl.r := cr.r;
      remove(cur);
      changeleft(nil,cur.l);
      remove(cr);
      changeleft(nil,cr.l);
      heap_remove(cr.p);
      heap_lift(cl.p);
    end;

  Quit(_OK,Format('N = %d, M = %d',[n,m]));
end.