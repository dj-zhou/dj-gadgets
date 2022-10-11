project('dj-gadgets', ['c', 'cpp'],
  version: '0.1.9',
  meson_version: '>=0.57',
  default_options: [
    'c_std=gnu18',
    'cpp_std=gnu++2a',
    'werror=true',
    'optimization=g',
    'warning_level=2',
    'b_sanitize=address,undefined',
    'prefix=/usr',
  ]
)

possible_codegen_flags = [
    '-ggdb3',
    '-fvar-tracking-assignments',
]

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

c_codegen_flags = cc.get_supported_arguments(possible_codegen_flags)
cxx_codegen_flags = cpp.get_supported_arguments(possible_codegen_flags)

c_flags = [
    '-Wold-style-definition',
    '-Wmissing-prototypes',
    '-Wstrict-prototypes',
    '-Wno-error=missing-field-initializers',
]

cxx_flags = [
    '-Wno-error=missing-field-initializers',
]

common_flags = [
    '-D_GNU_SOURCE=1',
    '-Wundef',
]

link_flags = [
    '-Wl,--gc-sections',
    '-Wl,--build-id',
    '-fwhole-program',
]

add_project_arguments(
    common_flags,
    language: ['c', 'cpp']
)

add_project_arguments(
    c_flags,
    language: 'c',
)

add_project_arguments(
    cxx_flags,
    language: 'cpp',
)

add_global_arguments(
    c_codegen_flags,
    language: 'c',
)

add_global_arguments(
    cxx_codegen_flags,
    language: 'cpp',
)

add_global_link_arguments(
    c_codegen_flags,
    language: 'c'
)

add_global_link_arguments(
    cxx_codegen_flags,
    language: 'cpp'
)

add_global_link_arguments(
    link_flags,
    language: ['c', 'cpp']
)

executable(
    'ascii-code',
    'ascii-code.cpp',
    install: true,
)

executable(
    'date-time-to-epoch',
    'date-time-to-epoch.cpp',
    install: true,
)

executable(
    'deg-to-rad',
    'deg-to-rad.cpp',
    install: true,
)

executable(
    'double-to-time',
    'double-to-time.cpp',
    install: true,
)

executable(
    'double-to-u8',
    'double-to-u8.cpp',
    install: true,
)

executable(
    'epoch-to-date-time',
    'epoch-to-date-time.cpp',
    install: true,
)

executable(
    'euler-to-quat',
    'euler-to-quat.cpp',
    install: true,
)

executable(
    'float-to-u8',
    'float-to-u8.cpp',
    install: true,
)

executable(
    'get-time-us',
    'get-time-us.cpp',
    install: true,
)

executable(
    'quat-to-euler',
    'quat-to-euler.cpp',
    install: true,
)

executable(
    'quat-to-rot',
    'quat-to-rot.cpp',
    install: true,
)

executable(
    'rad-to-deg',
    'rad-to-deg.cpp',
    install: true,
)

executable(
    'rot-to-quat',
    'rot-to-quat.cpp',
    install: true,
)

executable(
    'u8-to-double',
    'u8-to-double.cpp',
    install: true,
)
executable(
    'u8-to-float',
    'u8-to-float.cpp',
    install: true,
)
