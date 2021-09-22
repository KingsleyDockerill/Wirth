# Wirth

Wirth - named after Niklaus Wirth, creator of Pascal - is a language inspired by Pascal and C. For example, in regular Pascal a Hello, world! program would be
```pascal
program hello;

begin
  writeln("Hello, world!")
end.
```
Compared to the equivelent in Wirth
```
program hello; { Not required }

begin
  println("Hello, world!") { Writeln exists, but println works with all basic types }
end.
```
Wirth adds much more than a few new builtin functions though.
```
function echo(var a: array(str) = ...) begin
  loop foreach b: a begin
    var c: str = readln(b);
    println(b);
  end;
  throw "Error!"
end;

begin
  try begin
    echo("Hi!", "Hello!", 5.5, "Hola!");
  except: e
    println(e);
  end;
end.
```