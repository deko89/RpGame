extends Spatial



# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Spatial_input_event(camera, event, click_position, click_normal, shape_idx):
	if event is InputEventMouseButton and event.pressed:
		#print("Mouse Click/Unclick at: ", event.position)
		if not Input.is_key_pressed(KEY_SHIFT):
			ClearSel()
		add_to_group("selected")
		#get_node("/root/main/Ground").posSel = click_position

func ClearSel():
	var aSel = get_tree().get_nodes_in_group("selected")
	for sel in aSel:
		sel.remove_from_group("selected")
