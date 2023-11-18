# Переменные.
env = Environment(CC='clang-15', CXX='clang-15', CXXFLAGS='-O2 -fPIC')
env.Append(CPPDEFINES=['One_Translation_Unit'])

# Пути системных библиотек.
dirsIncLibSys = [
# C
    '/usr/include',                         # /usr/include/math.h (libc GNU)
   #'/usr/include/x86_64-linux-musl',       # /usr/include/x86_64-linux-musl/math.h (libc musl)
# C++
   #'/usr/include/c++/11',                  # /usr/include/c++/11/string (libc++ gnu)
   #'/usr/include/x86_64-linux-gnu/c++/11', # (libc++ gnu)
   #'/usr/include/c++/v1',
    '/usr/lib/llvm-15/include/c++/v1',      # /usr/lib/llvm-14/include/c++/v1/string
# SDL
    '/usr/include/SDL2',
]

dirsLibSys = [
# C
    '/lib/x86_64-linux-gnu',                # /lib/x86_64-linux-gnu/libc.so.6 (libc GNU)
   #'/usr/lib/x86_64-linux-musl',           # /usr/lib/x86_64-linux-musl/libc.a (libc musl)
# C++
   #'/usr/lib/x86_64-linux-gnu',            # /usr/lib/x86_64-linux-gnu/libc++.so.1 (libc++ gnu)
    '/usr/lib/llvm-15/lib',                 # /usr/lib/llvm-15/lib/libc++.so.1 (библиотека LLVM libc++)
]

# Исполняемые библотеки.
libsAll = Split("""
    dl
    GL
    libm
    libc
    libc++
    SDL2
    SDL2_image
""")

# Исходники библиотек проекта.
filesSrcLibProj =	Glob(	'Lib/imgui-1.89.8/*.cpp') + \
                    Glob(	'Lib/imgui-1.89.8/backends/*.cpp')
dirsIncLibProj  = [
    'Lib',
    'Lib/imgui-1.89.8',
    'Lib/imgui-1.89.8/backends'
]

# Файлы кода.
filesSrcProj = Split("""
    Main.cpp
""")

# Запуск.
env.Program(
	'RpGame',

	# Исходники.
	filesSrcLibProj + filesSrcProj,

	# Папки поиска заголовочных файлов. Например #include "glm/glm.hpp" найдет в "Lib/glm/glm.hpp".
	# Также нужно для отслеживания изменений в .h файлах (неявные зависимости).
	CPPPATH = dirsIncLibSys + dirsIncLibProj,

	# Пути поиска исполняемых библиотек.
	LIBPATH = dirsLibSys,

	# Исполнямые библотеки.
	LIBS = libsAll
)
