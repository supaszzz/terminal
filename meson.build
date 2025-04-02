project('terminal', 'cpp', default_options: ['default_library=static'])

cc = meson.get_compiler('cpp')
fltk_dep = cc.find_library('fltk', static: true, required: true)
inc = include_directories('src')
subdir('src')

if host_machine.system() == 'windows'
    link_args = ['-static', '-lws2_32', '-lcomctl32']
else
    link_args = ['-static', '-lpthread', '-lm', '-lX11']
endif

executable('terminal', sources,
    win_subsystem: 'windows',
    dependencies: [fltk_dep],
    include_directories: inc,
    cpp_args: ['-static', '-static-libgcc', '-static-libstdc++'],
    link_args: link_args
)