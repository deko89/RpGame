extends Node

const Math = preload("res://Lib/Geometry/Math.gd")

var rad = 0.1
var height = 1.0
var sgmC = 16
var sgmH = 1
var bCloseBeg = true
var bCloseEnd = true

var aVert: PoolVector3Array
var aInd:  PoolIntArray

func MakeCylinder():
	MakeCylinderVert()
	MakeCylinderInd()

func MakeCylinderVert():
	#Вычисление размера и выделение памяти
	var nVertC = sgmC * (sgmH + 1)
	var nVert = nVertC + (bCloseBeg as int) + (bCloseEnd as int)
	aVert.resize(nVert)
	if (bCloseBeg):
		aVert[0] = Vector3(0, 0, 0)
	#Цикл создания, по сегментам окружности.
	var angleStep = 2 * PI / sgmC #Текущий угол и шаг угла
	var hStep = height / sgmH #Текущая высота и шаг.
	var angle = 0.0
	for a in range (bCloseBeg as int, sgmC + bCloseBeg as int):
		#Позиция внизу (на остальных уровнях будет аналогично).
		aVert[a].z = cos(angle) * rad
		aVert[a].y = sin(angle) * rad
		aVert[a].x = 0
		#Устанавливаем данные по вертикали (на уровнях выше).
		var h = hStep
		var t = a + sgmC
		for i in sgmH:
			aVert[t].z = aVert[a].z
			aVert[t].y = aVert[a].y
			aVert[t].x = h
			h += hStep
			t += sgmC
		angle += angleStep
	#Создание крышки.
	if (bCloseEnd):
		aVert[nVert - 1] = Vector3(height, 0, 0)

func MakeCylinderInd():
	#Вычисление размера и выделение памяти для индексов
	var nInd = sgmC * sgmH * 6 + ((bCloseBeg as int) + (bCloseEnd as int)) * sgmC * 3
	aInd.resize(nInd)
	var i = 0
	var lvlStart = bCloseBeg as int #Текущая высота
	#Создание дна.
	if (bCloseBeg):
		for x in sgmC:
			aInd[i]   = 0
			aInd[i+1] = lvlStart if (x + 1 == sgmC) else lvlStart + x + 1 #Следующий по x.
			aInd[i+2] = lvlStart + x
			i += 3
	for y in sgmH:
		var lvlNext = lvlStart + sgmC #Следующая высота
		for s in sgmC:
			var n = 0 if (s + 1 == sgmC) else s + 1 #Следующий сегмент
			aInd[i]   = lvlStart + s
			aInd[i+1] = lvlStart + n
			aInd[i+2] = lvlNext + s
			aInd[i+3] = lvlNext + s
			aInd[i+4] = lvlStart + n
			aInd[i+5] = lvlNext + n
			i += 6
		lvlStart += sgmC
	#Создание крышки.
	if (bCloseEnd):
		var e = aVert.size() - 1
		var s = e - sgmC
		for x in range(s, e):
			aInd[i]   = e
			aInd[i+1] = x
			aInd[i+2] = s if (x + 1 == e) else x + 1 #Следующий по x.
			i += 3

# Установка диаметров в начале, в середине и в конце. Между ними будет интерполяция.
func SetWidth(var y1: float, var y2: float, var y3: float):
	var abc = Math.CalcFormulaCurve(y1, y2, y3, height)
	for i in aVert.size():
		var y = abc.x / (aVert[i].x + abc.y) + abc.z # y = a / (x + b) + c
		var r = y / rad
		aVert[i].y *= r
		aVert[i].z *= r

# Сделать из цилиндра плавную кривую проходящую через заданные точки.
# aKey - ключевые точки, в плоскости XY, через которые будет проходить кривая.
# Предполагается что везде Xi+1 >= Xi, и этот цилиндр лежит вдоль оси X.
func SplineXY(var aKey: PoolVector2Array):
	var nK = aKey.size()
	if nK < 3: return
	# Вычисляем у отрезков ломанной (до ключевой точки): производную и длину.
	var aDerL = PoolRealArray()
	aDerL.resize(nK)
	var aLenL = PoolRealArray()
	aLenL.resize(nK)
	for i in range(1, nK):
		aDerL[i] = (aKey[i].y - aKey[i-1].y) / (aKey[i].x - aKey[i-1].x)
		aLenL[i] = ( aKey[i] - aKey[i-1] ).length()
	# Вычисляем производные.
	var aDer = PoolRealArray()
	aDer.resize(nK)
	for i in range(1, nK - 1):
		# Вес (вклад) производных
		var l1 = aLenL[i]   
		var l2 = aLenL[i+1]
		var m1 = l1 / (l1 + l2)
		var m2 = l2 / (l1 + l2)
		# Средне взвешенная производная
		aDer[i] = aDerL[i] * m1 + aDerL[i+1] * m2
	aDer[0] = aDerL[1] # Производная в первой точке - это прозводная первого отрезка.
	aDer[nK - 1] = aDerL[nK - 1] # В последней - последнего отрезка.
	# Вычисляем положение точек (по оси Y).
	var ke = 0
	for i in aVert.size():
		var p = aVert[i]
		# Поиск участка в котором находится точка (kb <= x <= ke).
		while ke < nK:
			if p.x < aKey[ke].x: break
			if p.x == aKey[ke].x && ke + 1 == nK: break
			ke += 1
		if ke == nK: break
#		if p.x == aKey[ke].x:
#			aVert[i].y += aKey[ke].y
#			continue
		if ke == 0:
			continue # Вершины до первой ключевой пропускаем.
		var kb = ke - 1
		# Вычисление положения.
		var length = aKey[ke].x - aKey[kb].x
		var w = (p.x - aKey[kb].x) / length
		var w2 = w*w
		var w3 = w*w*w
		var y = aKey[kb].y * (1 - 3*w2 + 2*w3) + \
				aKey[ke].y * (3*w2 - 2*w3) + \
				aDer[kb] * (w - 2*w2 + w3) * length + \
				aDer[ke] * (w3 - w2) * length
		# Поворот окружностей цилинда согласно линии изгиба.
		var offset = aVert[i].y # Смещение положения от центра линии.
		var k = ( aKey[kb].y * (-6*w + 6*w2) + \
				  aKey[ke].y * (6*w - 6*w2) + \
				  aDer[kb] * (1 - 4*w + 3*w2) * length + \
				  aDer[ke] * (3*w2 - 2*w) * length ) / length
		var angle = atan(k) + PI / 2
		aVert[i].x += offset * cos(angle)
		aVert[i].y = y + offset * sin(angle)

# Сделать из цилиндра плавную кривую проходящую через заданные точки.
# aKey - ключевые точки, в плоскости, через которые будет проходить кривая.
# Предполагается что везде Xi+1 >= Xi, и этот цилиндр лежит вдоль оси X.
# Построение идёт исходя из того, что сплайн в 3d это 2 независимых сплайна:
# сплайн в плоскости XY + сплайн в поскости XZ
func Spline(var aKey: PoolVector3Array):
	var nK = aKey.size()
	if nK < 3: return
	# Вычисляем у отрезков ломанной (до ключевой точки): изменение и длину.
	var aDltLXY = PoolRealArray()
	aDltLXY.resize(nK)
	var aLenLXY = PoolRealArray()
	aLenLXY.resize(nK)
	var aDltLXZ = PoolRealArray()
	aDltLXZ.resize(nK)
	var aLenLXZ = PoolRealArray()
	aLenLXZ.resize(nK)
	for i in range(1, nK):
		aDltLXY[i] = aKey[i].y - aKey[i-1].y
		aLenLXY[i] = ( Vector2(aKey[i].x, aKey[i].y) - Vector2(aKey[i-1].x, aKey[i-1].y) ).length()
		aDltLXZ[i] = aKey[i].z - aKey[i-1].z
		aLenLXZ[i] = ( Vector2(aKey[i].x, aKey[i].z) - Vector2(aKey[i-1].x, aKey[i-1].z) ).length()
	# Вычисляем изменение за период.
	var aDltXY = PoolRealArray()
	aDltXY.resize(nK)
	var aDltXZ = PoolRealArray()
	aDltXZ.resize(nK)
	for i in range(1, nK - 1):
		#XY
		# Вес (вклад) производных
		var l1 = aLenLXY[i]   
		var l2 = aLenLXY[i+1]
		var m1 = l1 / (l1 + l2)
		var m2 = l2 / (l1 + l2)
		# Средне взвешенная производная
		aDltXY[i] = aDltLXY[i] * m1 + aDltLXY[i+1] * m2
		#YZ
		# Вес (вклад) производных
		l1 = aLenLXZ[i]   
		l2 = aLenLXZ[i+1]
		m1 = l1 / (l1 + l2)
		m2 = l2 / (l1 + l2)
		aDltXZ[i] = aDltLXZ[i] * m1 + aDltLXZ[i+1] * m2
	aDltXY[0] = aDltLXY[1] # Производная в первой точке - это прозводная первого отрезка.
	aDltXY[nK - 1] = aDltLXY[nK - 1] # В последней - последнего отрезка.
	aDltXZ[0] = aDltLXZ[1]
	aDltXZ[nK - 1] = aDltLXZ[nK - 1]
	# Вычисляем положение точек (по оси Y).
	var ke = 0
	var i = 0 # Индекс вершины
	for s in sgmH + 1:
		var p = aVert[i]
		# Поиск участка в котором находится точка (kb <= x <= ke).
		while ke < nK:
			if p.x < aKey[ke].x: break
			if p.x == aKey[ke].x && ke + 1 == nK: break
			ke += 1
		if ke == nK: break
#		if p.x == aKey[ke].x:
#			aVert[i].y += aKey[ke].y
#			continue
		if ke == 0:
			continue # Вершины до первой ключевой пропускаем.
		var kb = ke - 1
		# Вычисление положения.
		var length = aKey[ke].x - aKey[kb].x
		var w = (p.x - aKey[kb].x) / length
		var w2 = w*w
		var w3 = w*w*w
		var y = aKey[kb].y * (1 - 3*w2 + 2*w3) + \
				aKey[ke].y * (3*w2 - 2*w3) + \
				aDltXY[kb] * (w - 2*w2 + w3) + \
				aDltXY[ke] * (w3 - w2)
		var z = aKey[kb].z * (1 - 3*w2 + 2*w3) + \
				aKey[ke].z * (3*w2 - 2*w3) + \
				aDltXZ[kb] * (w - 2*w2 + w3) + \
				aDltXZ[ke] * (w3 - w2)
		# Начало и конец.
		if bCloseBeg && i == 0:
			aVert[0].y = y
			aVert[0].z = z
			i = 1
		if bCloseEnd && s == sgmH:
			aVert[i + sgmC].y = y
			aVert[i + sgmC].z = z
		# Поворот окружностей цилинда согласно линии изгиба.
		# 1. Расчёт углов - сперва находим производную (на плоскостях), потом её арктангенс.
		var kXY = ( aKey[kb].y * (-6*w + 6*w2) + \
				   aKey[ke].y * (6*w - 6*w2) + \
				   aDltXY[kb] * (1 - 4*w + 3*w2) + \
				   aDltXY[ke] * (3*w2 - 2*w) ) / length
		var angleXY = atan(kXY) + PI / 2
		var vXY1 = Vector2( cos(angleXY), sin(angleXY) ) # Единичный вектор (проекции окружности).
		var kZ = ( aKey[kb].z * (-6*w + 6*w2) + \
				   aKey[ke].z * (6*w - 6*w2) + \
				   aDltXZ[kb] * (1 - 4*w + 3*w2) + \
				   aDltXZ[ke] * (3*w2 - 2*w) ) / length
		var angleXZ = atan(kZ)
		# 2. Расчёт точек окружности.
		for j in range (i, i + sgmC):
			# Сперва локально поворачиваем в плоскости XY.
			# Для поворота в XY достаточно радиус умножить вектор (т.к. точки лежат на оси Y).
			# Радиус найти легко - это положение по Y.
			var vXY = vXY1 * aVert[j].y
			# Для поворота в XZ используется функция поворота 2d вектора.
			# Т.к. первый поворот смещает вектор по X, т.е. появляется начальный угол.
			# Функция принимает уже повёрнутый по XY вектор (Z им не затрагивалась).
			var vXZ = Vector2(vXY.x, aVert[j].z)
			vXZ = vXZ.rotated(angleXZ)
			aVert[j].x += vXZ.x
			aVert[j].y = y + vXY.y # (Y не затрагивается вторым вращением.)
			aVert[j].z = z + vXZ.y
		i += sgmC

#func MakeCylinderTex(sgmC : int, sgmH : int, u : float, v : float):
#	assert(sgmC % 2 == 0);
#	aTex.resize( sgmC * (sgmH + 1) );
#	#PosTex* pPos = ReSize(sgmC * (sgmH + 1));
#	#const PosTex *pEndC = pPos + sgmC,
#	#			 *pEndH = pPos + sgmC / 2,
#	#			 *pEnd  = pPos + n;
#	#Цикл по сегментам окружности.
#	var uStep = u / sgmC #Шаг u.
#	var	vStep = v / sgmH #Шаг v.
#	u = 0;
#	#for (; pPos < pEndC; ++pPos) {
#	for x in sgmC:
#		#Позиция внизу (на остальных уровнях будет аналогично).
#		aTex[x].x = u;
#		aTex[x].y = 0;
#		#Устанавливаем данные по вертикали (на уровнях выше).
#		h = x + sgmC
#		v = vStep
#		#for (PosTex* pPosH = pPos + sgmC; pPosH < pEnd; pPosH += sgmC, v += vStep) {
#		for y in range(1, sgmH):
#			aTex[h].x = u
#			aTex[h].y = v
#			h += sgmC
#			v += vStep
#			#pPosH->u = u;
#			#pPosH->v = v;
#		#После середины зеркалим текстуру, чтобы к последней вершине u была 0 (первая и последняя это одна и та же вершина).
#		u = pPos < pEndH ? u + uStep : u - uStep;
