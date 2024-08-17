// funcdemo.js - вычисление расстояния между двумя точками на плоскости
function hypotenuse(x, y)
{
	return Math.sqrt(x*x+y*y);
}
var x1=2;
var y1=3;
var x2=5;
var y2=6;
WScript.Echo("Расстояние между ("+x1+","+y1+") и ("+x2+","+y2+") равно "+hypotenuse(x2-x1,y2-y1));
