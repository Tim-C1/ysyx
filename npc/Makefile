MODULE=top
VSRC_DIR = ./vsrc
VINC_PATH += $(VSRC_DIR)
SRCS=$(shell find ./csrc/ -name "*.cpp")
CINC_PATH += $(shell pwd)/include/
CINCLUDES = $(addprefix -CFLAGS -I, $(dir $(abspath $(shell find $(CINC_PATH) -name "*.h"))))
VINCLUDES = $(addprefix -I, $(VINC_PATH))

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
	@./obj_dir/V$(MODULE) $(IMG)

./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE)

.stamp.verilate: ./vsrc/$(MODULE).v ./csrc/main.cpp
	@echo
	@echo "### VERILATING ###"
	verilator -Wall --trace -cc $(VSRC_DIR)/$(MODULE).v -top $(MODULE) --exe $(SRCS) /usr/lib/x86_64-linux-gnu/libreadline.so $(VINCLUDES) $(CINCLUDES)
	@touch .stamp.verilate

.PHONY:lint
lint: ./vsrc/$(MODULE).v
	verilator --lint-only ./vsrc/$(MODULE).v -Ivsrc

.PHONY: clean
clean:
	rm -rf .stamp.*;
	rm -rf ./obj_dir
	rm -rf waveform.vcd
