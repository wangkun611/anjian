{
  "targets": [
   {
      "target_name": "anjian",
      "sources": [
        "<(INTERMEDIATE_DIR)/anjian_wrap.cc",
        "anjian.cc", "anjian.h",
        "keyboard.cc", "keyboard.h",
        "mouse.cc", "mouse.h",
        "window.h", "window.cc"
      ],
      "include_dirs": ["./"],
      "defines": [
        "BUILDING_NODE_EXTENSION=1",
        "_UNICODE","UNICODE"
      ],
      "OTHER_CFLAGS":[
        "/EHs"
      ],
      "conditions": [
      ],
      "actions": [
        {
          "action_name": "generate wrap file",
          "inputs": [
            "anjian.i", "anjian.h",
            "keyboard.h", "mouse.h",
            "window.h"
          ],
          "outputs": [
            "<(INTERMEDIATE_DIR)/anjian_wrap.cc"
          ],
          "action": [
            "swig -javascript -c++ -node -o <(INTERMEDIATE_DIR)anjian_wrap.cc", "anjian.i"
          ]
        }
      ]
    }
  ]
}
