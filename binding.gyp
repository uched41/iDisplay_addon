 {
    "targets": [
      {
        "target_name": "idisplay",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [ "idisplay.cpp" ],
        "include_dirs" : [
          "<!@(node -p \"require('node-addon-api').include\")",
          "sdk/lib/include",
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")",
        ],
        "libraries":[
            "/home/ched/node_js/idisplay_addon/lib/libiD_BD_x64.so",
            ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
        "ldflags":[
            "-L/usr/lib"
          ]
      }
    ]
  }