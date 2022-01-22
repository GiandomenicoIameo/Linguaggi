program static;
  var a : integer;

  procedure s;
    var b : integer;
  begin
    b := 5;
    a := a + b;
  end;

begin

  a := 10;
  s;
  a := a + 1;
  writeln( a );
  
end.
