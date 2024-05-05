{
  "targets": [
    {
      "target_name": "example",
      "sources": [ "example.cpp", "example_wrap.cxx" ],
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