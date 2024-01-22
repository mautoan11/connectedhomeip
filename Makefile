main:
	./scripts/run_in_build_env.sh "./scripts/build/build_examples.py --target=linux-x64-all-clusters-no-ble-asan-clang build"
	./out/linux-x64-all-clusters-no-ble-asan-clang/chip-all-clusters-app
zapgen:
	./scripts/tools/zap/generate.py ./examples/all-clusters-app/all-clusters-common/all-clusters-app.zap
gen: zapgen main	
zap:
	./scripts/tools/zap/run_zaptool.sh ./examples/all-clusters-app/all-clusters-common/all-clusters-app.zap
all: zap gen
test: 
	./scripts/tests/yaml/chiptool.py tests Test_Device_41
	./scripts/tests/yaml/chiptool.py tests Test_Device_42
	./scripts/tests/yaml/chiptool.py tests Test_Device_42_2
test42: 
	./scripts/tests/yaml/chiptool.py tests Test_Device_42_2_1
	./scripts/tests/yaml/chiptool.py tests Test_Device_42_2_2
	./scripts/tests/yaml/chiptool.py tests Test_Device_42_2_3
	./scripts/tests/yaml/chiptool.py tests Test_Device_42
test2: 
	./scripts/tests/yaml/chiptool.py tests BBB
	./scripts/tests/yaml/chiptool.py tests Test_Device_42_2
	./scripts/tests/yaml/chiptool.py tests Test_Device_43
	./scripts/tests/yaml/chiptool.py tests Test_Device_44
testgen:
	python ./examples/all-clusters-app/mytests/MyGenereTest.py
test_1111_41:
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_2_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_2_4.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_2_2.yaml
test_1111_42:
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_2_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_2_4.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_2_2.yaml
