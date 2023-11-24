main:
	gn gen out/debug
	ninja -C out/debug
	./out/debug/chip-tool interactive start
run:
	./out/debug/chip-tool interactive start
pull:
	git reset HEAD^ --hard
	git pull
	gn gen out/debug
	ninja -C out/debug
	./out/debug/chip-tool
gdb:
	gn gen out/debug
	ninja -C out/debug
	gdb ./out/debug/chip-tool

gdb_old:
	gn gen out/debug
	ninja -C out/debug
	gdb -ex run ./out/debug/chip-tool interactive start

gdbfast:
	gn gen out/debug
	ninja -C out/debug
	gdb run --args ./out/debug/chip-tool -asyncread -asyncwrite
