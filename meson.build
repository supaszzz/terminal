project('terminal', 'cpp')

cc = meson.get_compiler('cpp')

fltk_dep = cc.find_library('fltk', static: true, required: true)

inc = include_directories('src')
subdir('src')

if host_machine.system() == 'windows'
    link_args = ['-static', '-static-libgcc', '-static-libstdc++', '-lws2_32', '-lcomctl32']
else
    link_args = ['-lpthread', '-lm', '-lX11', '-lfltk']
endif

executable('terminal', sources,
    win_subsystem: 'windows',
    dependencies: [fltk_dep],
    include_directories: inc,
    link_args: link_args
)