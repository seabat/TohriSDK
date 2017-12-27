
"====================
"syntastic
"====================
"let g:syntastic_c_config_file = '.config'
let g:syntastic_c_check_header = 1 
let g:syntastic_c_include_dirs = [ '$TOHRI_SDK_PATH/sources/apps/sbt-web-server/server/inc', '$TOHRI_SDK_PATH/out/$TOHRI_SDK_TARGET/obj/include' ]

"====================================
" Add include file paths to open 'gf'
"====================================
set path+=$TOHRI_SDK_PATH/sources/apps/sbt-web-server/server/inc
set path+=$TOHRI_SDK_PATH/out/$TOHRI_SDK_TARGET/obj/include

