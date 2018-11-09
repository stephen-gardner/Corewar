d='gui_only_temp'; cd src/vm/; mkdir -p $d; cp corewar_gui_*.c $d/; cd $d/; listfunctions; cd ..; rm -rf $d; cd ../..;
