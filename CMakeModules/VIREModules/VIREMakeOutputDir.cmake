include(macro_make_project_out_put_dir)

MACRO(VIRE_MAKE_OUTPUT_DIR path)
  #_VIRE_MAKE_OUTPUT_ROOT_DIR(${path})
  MAKE_PROJECT_OUT_PUT_DIR(${path} ${ARGN})
ENDMACRO()