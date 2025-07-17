# Сборка дочерних проектов.
SConscript([
	'Lib/GEng/SConscript',
])

Import('envGEng', 'dirsIncLibGEng', 'libsGEng')

# Пути поиска исполняемых библиотек.
dirsLibProj = [
	'Lib/GEng',
]

# Исполняемые библиотеки.
libsProj = [
    'libGEng.a',
]

# Пути поиска заголовочных файлов.
dirsIncProj = [
	'Lib',
	'Lib/GEng',
	'Lib/GEng/Lib',
]

# Файлы кода.
filesSrcProj = Split("""
    Main.cpp
""")

# Запуск.
envGEng.Program(
	'RpGame',

	# Исходники.
	filesSrcProj,

	# Папки поиска заголовочных файлов. Например #include "glm/glm.hpp" найдет в "Lib/glm/glm.hpp".
	# Также нужно для отслеживания изменений в .h файлах (неявные зависимости).
	CPPPATH = dirsIncLibGEng + dirsIncProj,

	# Пути поиска исполняемых библиотек.
	LIBPATH = dirsLibProj,

	# Исполнямые библотеки.
	LIBS = libsGEng + libsProj
)
