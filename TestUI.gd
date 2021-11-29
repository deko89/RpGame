extends Panel

# Called when the node enters the scene tree for the first time.
func _ready():
	get_node("Button").connect("pressed", self, "_on_Button_pressed24")
	$Timer.connect("timeout", self, "_on_Timer_timeout")

func _on_Button_pressed():
	get_node("Label").text = "HELLO!"

func _on_Button_pressed24():
	$Label24.text = "HELLO111!"


func _on_Timer_timeout():
	$Sprite.visible = !$Sprite.visible
	$Label24.visible = !$Label24.visible
