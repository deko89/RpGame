extends KinematicBody


var speed = 4  # movement speed
const speedFast = 18
var spin = 0.01  # rotation speed

var velocity = Vector3.ZERO

# Called when the node enters the scene tree for the first time.
func _ready():
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)


func _unhandled_input(event):
	if event is InputEventMouseMotion and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		rotate_y(-event.relative.x * spin)
		rotate(transform.basis.x, event.relative.y * spin)
   # Mouse in viewport coordinates.
#	if event is InputEventMouseButton:
#		print("Mouse Click/Unclick at: ", event.position)
#	elif event is InputEventMouseMotion:
#		print("Mouse Motion at: ", event.position)
#	# Print the size of the viewport.
#	print("Viewport Resolution is: ", get_viewport().size)
	
func get_input():
	velocity = Vector3.ZERO
	var speedMove
	if Input.is_action_pressed("MoveFast"):
		speedMove = speedFast
	else:
		speedMove = speed
	if Input.is_action_pressed("MoveF"):
		velocity += transform.basis.z * speedMove
	if Input.is_action_pressed("MoveB"):
		velocity -= transform.basis.z * speedMove
	if Input.is_action_pressed("MoveR"):
		velocity -= transform.basis.x * speedMove
	if Input.is_action_pressed("MoveL"):
		velocity += transform.basis.x * speedMove
	if Input.is_action_pressed("MoveU"):
		velocity += transform.basis.y * speedMove
	if Input.is_action_pressed("MoveD"):
		velocity -= transform.basis.y * speedMove

	# Capturing/Freeing the cursor
	if Input.is_action_just_pressed("ui_cancel"):
		if Input.get_mouse_mode() == Input.MOUSE_MODE_VISIBLE:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
		else:
			Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _physics_process(_delta):
	get_input()
# warning-ignore:return_value_discarded
	move_and_slide(velocity, Vector3.UP, false, 4, 0.785398, false)
