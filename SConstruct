# Переменные.
env = Environment()
env = Environment(CC='clang', CXXFLAGS='-O2 -fPIC')

# Пути исполняемых библиотек.
dirsIncLibExe	= ['/usr/include/SDL2']
dirsLibExe		= ["/usr/lib/x86_64-linux-gnu"]

# Исполнямые библотеки ()системы).
libsExe = ['dl', 'GL', 'SDL2']

# Исходники бБиблиотек проекта.
filesLib	=	Glob(	'Lib/imgui-1.89.8/*.cpp') + \
				Glob(	'Lib/imgui-1.89.8/backends/*.cpp')
dirsLib		=	[		'Lib',
						'Lib/imgui-1.89.8',
						'Lib/imgui-1.89.8/backends'
				]

# Файлы кода.
filesSrc = Split("""
				 Main.cpp
                 """)

# Запуск.
env.Program(
	'RpGame',

	# Исходники.
	filesLib + filesSrc,

	# Папки поиска заголовочных файлов (неявные зависимости).
	CPPPATH = dirsLib + dirsIncLibExe,

	# Пути поиска исполняемых библиотек.
	LIBPATH = dirsLibExe,

	# Исполнямые библотеки.
	LIBS = libsExe
)
