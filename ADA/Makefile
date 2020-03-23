all:
	##Para usar este compilador escriba: make 1=nombre_archivo
	##Cabe mencionar que se recomienda que sus programas terminen con la extension .adb

	gnatmake codigo/${1}
	gnatbind -x hello.ali
	gnatlink hello.ali
	./${1}