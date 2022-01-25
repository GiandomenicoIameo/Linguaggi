program swap; (* Passaggio di parametri : in out per riferimento *)
  var a, b : integer;
  procedure swap( var a, b : integer );
    var tmp : integer;
  begin
    tmp := a;
    a   := b;
    b   := tmp;
  end;
begin
  write( 'a : ' );
  readln( a );

  write( 'b : ' );
  readln( b );

  swap( a, b );

  writeln( '' );
  writeln( 'a : ', a );
  writeln( 'b : ', b );
end.
