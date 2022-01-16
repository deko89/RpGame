# Способы подключения
#1. var cyl = $"/root/main/Lib/Geometry/Cylinder"
#2. const Math = preload("res://Lib/Geometry/Math.gd")
#3. var Character = load("res://path/to/character.gd")
#	var character_node = Character.new()


# Расчитать уравнение простейшей кривой. На основе уравнения y = a / (x + b) + c
# По 3 значениям в начале, середине и в конце. Т.е. по точкам (0, y1), (0.5*x3, y2), (x3, y3).
# @return Vector3 в котором x = a, y = b, z = c.
static func CalcFormulaCurve(var y1: float, var y2: float, var y3: float, var x3: float):
	var abc: Vector3
	abc.y = x3 * (y2 - y3) / (y1 - 2 * y2 + y3)
	abc.x = abc.y * (y1 - y3) * (1 + abc.y / x3)
	abc.z = y1 - abc.x / abc.y;
	return abc;
