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
test_1111_41_OO:
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_2_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_41_Test_TC_OO_2_2.yaml
test_1111_41: test_1111_41_OO
test_1111_42_OO:
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_2_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_OO_2_2.yaml
test_1111_42_LVL:
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_5_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_6_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_7_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_3_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_4_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_42_Test_TC_LVL_2_2.yaml
test_1111_42: test_1111_42_OO test_1111_42_LVL
test_1111_43_OO:
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_OO_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_OO_2_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_OO_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_OO_2_2.yaml
test_1111_43_LVL:
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_5_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_6_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_7_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_3_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_4_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_LVL_2_2.yaml
test_1111_43_CC:
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_4_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_9_2.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_2_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_6_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_6_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_3_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_7_5_Simulated.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_5_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_3_2.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_7_2.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_7_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_5_4_Simulated.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_9_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_9_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_7_4.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_5_2.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_4_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_1_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_4_5_Simulated.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_8_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_5_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_4_4.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_6_5.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_3_1.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_9_4_Simulated.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_3_4_Simulated.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_7_3.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_4_2.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_6_2.yaml
	./scripts/tests/yaml/chiptool.py tests test_1111_43_Test_TC_CC_6_4_Simulated.yaml
test_1111_43: test_1111_43_OO test_1111_43_LVL test_1111_43_CC
testall: test_1111_41_OO test_1111_42_OO test_1111_42_LVL test_1111_43_OO test_1111_43_LVL test_1111_43_CC 
