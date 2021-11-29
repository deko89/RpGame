extends MeshInstance

func MakeCylinder(rad: float, height: float, sgmC: int, sgmH: int,
bCloseBottom: bool, bCloseUp: bool):
	#Вычисление размера и выделение памяти
	var nVertC = sgmC * (sgmH + 1)
	Pos* pVert = Make(nVertC + bCloseBottom + bCloseUp);
	const Pos *pEndC = pVert + sgmC,
			  *pEnd  = pVert + nVertC;
	#Цикл создания, по сегментам окружности.
	const Value angleStep = 2 * pi / sgmC,	#Текущий угол и шаг угла
				hStep = height / sgmH;			#Текущая высота и шаг.
	Value angle = 0;
	for (; pVert < pEndC; ++pVert, angle += angleStep) {
		#Позиция внизу (на остальных уровнях будет аналогично).
		pVert->x = cos(angle) * rad;
		pVert->y = sin(angle) * rad;
		pVert->z = 0;
		#Устанавливаем данные по вертикали (на уровнях выше).
		Value h = hStep;
		for (Pos* pVertH = pVert + sgmC; pVertH < pEnd; pVertH += sgmC, h += hStep) {
			pVertH->x = pVert->x;
			pVertH->y = pVert->y;
			pVertH->z = h;
		}
	}
	#Создание дна.
	if (bCloseBottom) {
		pVert = p + (n - bCloseUp? 2: 1);
		pVert->x = 0; pVert->y = 0; pVert->z = 0;
	}
	#Создание крышки.
	if (bCloseUp) {
		pVert = p + (n - 1);
		pVert->x = 0; pVert->y = 0; pVert->z = height;
	}

void Mesh::MakeCylinder(Value rad, Value height, int sgmC, int sgmH, bool bCloseBottom, bool bCloseUp) {
	#Создание вершин
	vert.MakeCylinder(rad, height, sgmC, sgmH, bCloseBottom, bCloseUp);
	#Вычисление размера и выделение памяти для индексов
	TypeInd* pInd = ind.Make(sgmC * sgmH * 6 + ((int)bCloseBottom + bCloseUp) * sgmC * 3);
	for (int y = 0; y < sgmH; ++y) {
		const TypeInd height  = sgmC * y,	   #Текущая высота
					  heightN = height + sgmC; #Следующая высота
		for (int s = 0; s < sgmC; ++s) {
			const TypeInd n = (s + 1 == sgmC)? 0: s + 1; #Следующий сегмент
			*(pInd++) = height	+ s;
			*(pInd++) = height	+ n;
			*(pInd++) = heightN	+ s;
			*(pInd++) = heightN	+ s;
			*(pInd++) = height	+ n;
			*(pInd++) = heightN	+ n;
		}
	}
	#Создание дна.
	if (bCloseBottom) {
		const TypeInd iV = vert.n - (bCloseUp? 2: 1);
		for (TypeInd x = 0; x < sgmC; ++x) {
			*(pInd++) = iV;
			*(pInd++) = (x + 1 == sgmC)? 0: x + 1; #Следующий по x.
			*(pInd++) = x;
		}
	}
	#Создание крышки.
	if (bCloseUp) {
		const TypeInd iV = vert.n - 1, s = iV - bCloseBottom - sgmC, e = s + sgmC;
		for (TypeInd x = s; x < e; ++x) {
			*(pInd++) = iV;
			*(pInd++) = x;
			*(pInd++) = (x + 1 == e)? s: x + 1; #Следующий по x.
		}
	}
}

var rings = 50
var radial_segments = 50
var height = 1
var radius = 1

func _ready():
	var arr = []
	arr.resize(Mesh.ARRAY_MAX)

	# PoolVectorXXArrays for mesh construction.
	var verts = PoolVector3Array()
	var uvs = PoolVector2Array()
	var normals = PoolVector3Array()
	var indices = PoolIntArray()

	#######################################
	# Set up the PoolVectorXArrays.

	# Vertex indices.
	var thisrow = 0
	var prevrow = 0
	var point = 0

	# Loop over rings.
	for i in range(rings + 1):
		var v = float(i) / rings
		var w = sin(PI * v)
		var y = cos(PI * v)

		# Loop over segments in ring.
		for j in range(radial_segments):
			var u = float(j) / radial_segments
			var x = sin(u * PI * 2.0)
			var z = cos(u * PI * 2.0)
			var vert = Vector3(x * radius * w, y, z * radius * w)
			verts.append(vert)
			normals.append(vert.normalized())
			uvs.append(Vector2(u, v))
			point += 1

			# Create triangles in ring using indices.
			if i > 0 and j > 0:
				indices.append(prevrow + j - 1)
				indices.append(prevrow + j)
				indices.append(thisrow + j - 1)

				indices.append(prevrow + j)
				indices.append(thisrow + j)
				indices.append(thisrow + j - 1)

		if i > 0:
			indices.append(prevrow + radial_segments - 1)
			indices.append(prevrow)
			indices.append(thisrow + radial_segments - 1)

			indices.append(prevrow)
			indices.append(prevrow + radial_segments)
			indices.append(thisrow + radial_segments - 1)

		prevrow = thisrow
		thisrow = point
	#######################################

	# Assign arrays to mesh array.
	arr[Mesh.ARRAY_VERTEX] = verts
	arr[Mesh.ARRAY_TEX_UV] = uvs
	arr[Mesh.ARRAY_NORMAL] = normals
	arr[Mesh.ARRAY_INDEX] = indices

	# Create mesh surface from mesh array.
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, arr) # No blendshapes or compression used.
