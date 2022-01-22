program dynamic;
  var a, b : integer;

  procedure p;
    var a, c : integer;
  begin
    a := 10; c := 5;
    c := c + a;
    writeln( c );
  end;

begin
  a := 20;
  p;
end.
