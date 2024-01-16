main:
	./scripts/run_in_build_env.sh "./scripts/build/build_examples.py --target=linux-x64-all-clusters-no-ble-asan-clang build"
zapgen:
	./scripts/tools/zap/generate.py ./examples/all-clusters-app/all-clusters-common/all-clusters-app.zap
gen: zapgen main	
zap:
	./scripts/tools/zap/run_zaptool.sh ./examples/all-clusters-app/all-clusters-common/all-clusters-app.zap