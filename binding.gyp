{
  "targets": [
   {
      "target_name": "anjian",
      "sources": [
        "<(INTERMEDIATE_DIR)/anjian_wrap.cc",
        "anjian.cc", "anjian.h",
        "keyboard.cc", "keyboard.h",
        "mouse.cc", "mouse.h"
      ],
      "include_dirs": ["./"],
      "defines": [
        "BUILDING_NODE_EXTENSION=1",
      ],
      "conditions": [
      ],
      "actions": [
        {
          "action_name": "generate wrap file",
          "inputs": [
            "anjian.i", "anjian.h",
            "keyboard.h", "mouse.h"
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
