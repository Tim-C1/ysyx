MODULE=top

.PHONY:sim
sim: waveform.vcd $(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!

.PHONY:verilate
verilate: .stamp.verilate

.PHONY:build
build: obj_dir/Vtop

.PHONY:waves
waves: waveform.vcd
	@echo
	@echo "### WAVES ###"
	gtkwave waveform.vcd

waveform.vcd: ./obj_dir/V$(MODULE)
	@echo
	@echo "### SIMULATING ###"
	@./obj_dir/V$(MODULE)

./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE)

.stamp.verilate: ./vsrc/$(MODULE).v ./csrc/main.cpp
	@echo
	@echo "### VERILATING ###"
	verilator -Wall --trace -cc ./vsrc/$(MODULE).v -top $(MODULE) --exe ./csrc/main.cpp -Ivsrc
	@touch .stamp.verilate

.PHONY:lint
lint: ./vsrc/$(MODULE).v
	verilator --lint-only./vsrc/$(MODULE).v -Ivsrc

.PHONY: clean
clean:
	rm -rf .stamp.*;
	rm -rf ./obj_dir
	rm -rf waveform.vcd
