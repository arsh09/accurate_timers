{
  "targets": [
    {
      "target_name": "example",
      "sources": ["example_wrap.cpp" ],
      "include_dirs": [ "." ],
      "cflags": [ "-std=c++11" ],
      "cflags_cc": [ "-std=c++11" ],
      "msvs_settings": {
        "VCCLCompilerTool": {
          "DebugInformationFormat": 3
        }
      }
    }
  ],

}