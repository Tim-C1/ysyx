import "DPI-C" function void pmem_read(
  input longint raddr, output longint rdata);
import "DPI-C" function void pmem_write(
  input longint waddr, input longint wdata, input byte wmask);

module inst_mem(
    input [63:0] pc,
    output reg [31:0] inst
);
    reg [63:0] inst_bus;
    always @(*) begin
        if (pc >= 64'h80000000) begin
            pmem_read(pc, inst_bus);
            if (pc[2] == 1'b0) begin
                inst = inst_bus[31:0];
            end
            else begin
                inst = inst_bus[63:32];
            end
        end
        else begin
            inst_bus = 64'b0;
            inst = 32'b0;
        end
    end
endmodule

module data_mem(
    input wen,
    input ren,
    input [63:0] addr,
    input [2:0] mem_type,
    input [63:0] wdata,
    output reg [63:0] rdata
);
    reg [63:0] data_bus;
    wire [63:0] addr_offset = addr - (addr & ~64'h7);

    reg [7:0] wmask;
    always @(*) begin
        case (mem_type)
            3'b000: begin
                case (addr_offset)
                    64'h0: begin wmask = 8'b00000001; end
                    64'h1: begin wmask = 8'b00000010; end
                    64'h2: begin wmask = 8'b00000100; end
                    64'h3: begin wmask = 8'b00001000; end
                    64'h4: begin wmask = 8'b00010000; end
                    64'h5: begin wmask = 8'b00100000; end
                    64'h6: begin wmask = 8'b01000000; end
                    64'h7: begin wmask = 8'b10000000; end
                    default: begin wmask = 8'b00000000; end
                endcase
            end

            3'b001: begin
                case (addr_offset)
                    64'h0: begin wmask = 8'b00000011; end
                    64'h1: begin wmask = 8'b00000110; end
                    64'h2: begin wmask = 8'b00001100; end
                    64'h3: begin wmask = 8'b00011000; end
                    64'h4: begin wmask = 8'b00110000; end
                    64'h5: begin wmask = 8'b01100000; end
                    64'h6: begin wmask = 8'b11000000; end
                    default: begin wmask = 8'b00000000; end
                endcase
            end

            3'b010: begin
                case (addr_offset)
                    64'h0: begin wmask = 8'b00001111; end
                    64'h1: begin wmask = 8'b00011110; end
                    64'h2: begin wmask = 8'b00111100; end
                    64'h3: begin wmask = 8'b01111000; end
                    64'h4: begin wmask = 8'b11110000; end
                    default: begin wmask = 8'b00000000; end
                endcase
            end

            3'b011: begin
                case (addr_offset)
                    64'h0: begin wmask = 8'b11111111; end
                    default: begin wmask = 8'b00000000; end
                endcase
            end

            default: begin wmask = 8'b00000000; end
        endcase
    end

    always @(*) begin
        if (wen) begin
            pmem_write(addr, wdata, wmask);
            data_bus = 64'b0;
            rdata = 64'b0;
        end
        else begin
            if (ren) begin
                pmem_read(addr, data_bus);
                case (mem_type)
                    3'b000: begin
                        case (addr_offset)
                            64'h0: begin rdata = {{56{data_bus[7]}}, data_bus[7:0]}; end
                            64'h1: begin rdata = {{56{data_bus[15]}}, data_bus[15:8]}; end
                            64'h2: begin rdata = {{56{data_bus[23]}}, data_bus[23:16]}; end
                            64'h3: begin rdata = {{56{data_bus[31]}}, data_bus[31:24]}; end
                            64'h4: begin rdata = {{56{data_bus[39]}}, data_bus[39:32]}; end
                            64'h5: begin rdata = {{56{data_bus[47]}}, data_bus[47:40]}; end
                            64'h6: begin rdata = {{56{data_bus[55]}}, data_bus[55:48]}; end
                            64'h7: begin rdata = {{56{data_bus[63]}}, data_bus[63:56]}; end
                            default: begin rdata = 64'hffffffffffffffff; end
                        endcase
                    end

                    3'b001: begin
                        case(addr_offset)
                            64'h0: begin rdata = {{48{data_bus[15]}}, data_bus[15:0]}; end
                            64'h1: begin rdata = {{48{data_bus[23]}}, data_bus[23:8]}; end
                            64'h2: begin rdata = {{48{data_bus[31]}}, data_bus[31:16]}; end
                            64'h3: begin rdata = {{48{data_bus[39]}}, data_bus[39:24]}; end
                            64'h4: begin rdata = {{48{data_bus[47]}}, data_bus[47:32]}; end
                            64'h5: begin rdata = {{48{data_bus[55]}}, data_bus[55:40]}; end
                            64'h6: begin rdata = {{48{data_bus[63]}}, data_bus[63:48]}; end
                            default: begin rdata = 64'hffffffffffffffff; end
                        endcase
                    end

                    3'b010: begin
                        case(addr_offset)
                            64'h0: begin rdata = {{32{data_bus[31]}}, data_bus[31:0]}; end
                            64'h1: begin rdata = {{32{data_bus[39]}}, data_bus[39:8]}; end
                            64'h2: begin rdata = {{32{data_bus[47]}}, data_bus[47:16]}; end
                            64'h3: begin rdata = {{32{data_bus[55]}}, data_bus[55:24]}; end
                            64'h4: begin rdata = {{32{data_bus[63]}}, data_bus[63:32]}; end
                            default: begin rdata = 64'hffffffffffffffff; end
                        endcase
                    end

                    3'b011: begin
                        case(addr_offset)
                            64'h0: begin rdata = data_bus; end
                            default: begin rdata = 64'hffffffffffffffff; end
                        endcase
                    end

                    3'b100: begin
                        case (addr_offset)
                            64'h0: begin rdata = {56'b0, data_bus[7:0]}; end
                            64'h1: begin rdata = {56'b0, data_bus[15:8]}; end
                            64'h2: begin rdata = {56'b0, data_bus[23:16]}; end
                            64'h3: begin rdata = {56'b0, data_bus[31:24]}; end
                            64'h4: begin rdata = {56'b0, data_bus[39:32]}; end
                            64'h5: begin rdata = {56'b0, data_bus[47:40]}; end
                            64'h6: begin rdata = {56'b0, data_bus[55:48]}; end
                            64'h7: begin rdata = {56'b0, data_bus[63:56]}; end
                            default: begin rdata = 64'hffffffffffffffff; end
                        endcase
                    end

                    3'b101: begin
                        case(addr_offset)
                            64'h0: begin rdata = {48'b0, data_bus[15:0]}; end
                            64'h1: begin rdata = {48'b0, data_bus[23:8]}; end
                            64'h2: begin rdata = {48'b0, data_bus[31:16]}; end
                            64'h3: begin rdata = {48'b0, data_bus[39:24]}; end
                            64'h4: begin rdata = {48'b0, data_bus[47:32]}; end
                            64'h5: begin rdata = {48'b0, data_bus[55:40]}; end
                            64'h6: begin rdata = {48'b0, data_bus[63:48]}; end
                            default: begin rdata = 64'hffffffffffffffff; end
                        endcase
                    end

                    3'b110: begin
                        case(addr_offset)
                            64'h0: begin rdata = {32'b0, data_bus[31:0]}; end
                            64'h1: begin rdata = {32'b0, data_bus[39:8]}; end
                            64'h2: begin rdata = {32'b0, data_bus[47:16]}; end
                            64'h3: begin rdata = {32'b0, data_bus[55:24]}; end
                            64'h4: begin rdata = {32'b0, data_bus[63:32]}; end
                            default: begin rdata = 64'hffffffffffffffff; end
                        endcase
                    end
                    default: begin rdata = 64'hffffffffffffffff; end
                endcase
            end
            else begin
                rdata = 64'hffffffffffffffff;
                data_bus = 64'hffffffffffffffff;
            end
        end
    end
endmodule

