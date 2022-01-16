extends MeshInstance

func _init():
	VisualServer.set_debug_generate_wireframes(true)

func _ready():
	var arr = []
	arr.resize(Mesh.ARRAY_MAX)

	# PoolVectorXXArrays for mesh construction.
	#var aTex:  PoolVector2Array
#	var uvs = PoolVector2Array()
#	var normals = PoolVector3Array()

	#######################################
	# Set up the PoolVectorXArrays.
	
	# Создаём цилиндр
	var cyl = $"/root/main/Lib/Geometry/Cylinder"
	cyl.height = 100.0
	cyl.sgmC = 16
	cyl.sgmH = 100
	cyl.MakeCylinder()
	cyl.SetWidth(1, 0.5, 0.2)
	# Изгибаем по ключевым точкам
	var aKey: PoolVector3Array
	aKey.resize(5)
	aKey[0] = Vector3(0, 1, 0)
	aKey[1] = Vector3(10, 10, 5)
	aKey[2] = Vector3(40, 5, 0)
	aKey[3] = Vector3(90, 2, 0)
	aKey[4] = Vector3(100, 5, 0)
	cyl.Spline(aKey)
	
	#######################################

	# Assign arrays to mesh array.
	arr[Mesh.ARRAY_VERTEX] = cyl.aVert
	#arr[Mesh.ARRAY_TEX_UV] = uvs
	#arr[Mesh.ARRAY_NORMAL] = normals
	arr[Mesh.ARRAY_INDEX] = cyl.aInd

	# Create mesh surface from mesh array.
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, arr) # No blendshapes or compression used.

func _input(event):
			
	if event is InputEventKey and Input.is_key_pressed(KEY_P):
		var vp = get_viewport()
		vp.debug_draw = (vp.debug_draw + 1 ) % 4
