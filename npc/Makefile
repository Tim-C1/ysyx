MODULE=top
CONFIG_ITRACE = 1

VSRC_DIR = ./vsrc
VINC_PATH += $(VSRC_DIR)

SRCS = $(shell find ./csrc/ -name "*.cpp")

CINC_PATH += $(shell pwd)/include/

CXXFLAGS += $(addprefix -CFLAGS -I, $(dir $(abspath $(shell find $(CINC_PATH) -name "*.h"))))
CXXFLAGS += -CFLAGS -lreadline
CXXFLAGS += -CFLAGS -lSDL2
VFLAGS += $(addprefix -I, $(VINC_PATH))

# link llvm libs
ifdef CONFIG_ITRACE
CXXFLAGS += $(addprefix -CFLAGS , $(shell llvm-config-11 --cxxflags) -fPIE)
CXXFLAGS += $(addprefix -CFLAGS , $(shell llvm-config-11 --libs))
LDFLAGS = $(addprefix -LDFLAGS , -lreadline -ldl -pie -lLLVM-11)
endif

# gdb option
# CXXFLAGS += $(addprefix -CFLAGS , -ggdb3 -fsanitize=address)
CXXFLAGS += $(addprefix -CFLAGS , -ggdb3)
# LDFLAGS += $(addprefix -LDFLAGS , -fsanitize=address)

DIFFSO = /home/ctr/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so

CXXFLAGS += $(addprefix -CFLAGS , -fpermissive)
LDFLAGS += $(addprefix -LDFLAGS , -fpermissive)
LDFLAGS += -LDFLAGS -lSDL2
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
	@./obj_dir/V$(MODULE) $(IMG).bin $(IMG).elf $(DIFFSO)

./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE)

.stamp.verilate:
	@echo
	@echo "### VERILATING ###"
	verilator -Wall --trace -cc $(VSRC_DIR)/$(MODULE).v -top $(MODULE) $(VFLAGS)\
   	--exe $(SRCS)\
   	$(CXXFLAGS) $(LDFLAGS)
	@touch .stamp.verilate

.PHONY:lint
lint: ./vsrc/$(MODULE).v
	verilator --lint-only ./vsrc/$(MODULE).v -Ivsrc

.PHONY: clean .stamp.verilate gdb
clean:
	rm -rf .stamp.*;
	rm -rf ./obj_dir
	rm -rf waveform.vcd
	rm -rf *log*.txt

gdb: ./obj_dir/V$(MODULE)
	@gdb --args  ./obj_dir/V$(MODULE) $(IMG).bin $(IMG).elf $(DIFFSO) batch

run: ./obj_dir/V$(MODULE)
	 ./obj_dir/V$(MODULE) $(IMG).bin $(IMG).elf $(DIFFSO) batch
