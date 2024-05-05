{
  "targets": [
    {
      "target_name": "timer",
      "sources": ["Timer.h", "timer_wrap.cxx" ],
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